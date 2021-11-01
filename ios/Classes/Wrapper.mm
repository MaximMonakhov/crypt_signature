//
//  Wrapper.mm
//  KristaCrypt
//
//  Created by Кристофер Кристовский on 27.08.2020.
//  Copyright © 2020 Кристофер Кристовский. All rights reserved.
//

#import "Wrapper.h"
#include "Headers/CPROCSP.h"
#include "Headers/DisableIntegrity.h"

#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)

extern bool USE_CACHE_DIR;
bool USE_CACHE_DIR = false;

void handleError(NSString* message) {
    DWORD error = CSP_GetLastError();
    
    printf("\nОшибка\n");
    printf("%s ", [message UTF8String]);
    printf("%d\n", error);
    
    wchar_t buf[256];
    CSP_FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                       buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
    printf("%ls\n", buf);
}

/// Инициализация провайдера и получение списка контейнеров
int initCSP()
{
    int INIT_CSP_OK = 0;
    //int INIT_CSP_LICENSE_ERROR = 1;
    int INIT_CSP_ERROR = -1;
    
    printf("\nИнициализация провайдера и получение списка контейнеров\n\n");
    
    DisableIntegrityCheck();
    
    /// Инициализация контекста
    HCRYPTPROV phProv = 0;
    
    if (!CryptAcquireContextA(&phProv, NULL, NULL, PROV_GOST_2012_256, CRYPT_SILENT | CRYPT_VERIFYCONTEXT)) {
        printf("Не удалось инициализировать context\n");
        handleError(@"CryptAcquireContextA");
        return INIT_CSP_ERROR;
    }
    
    printf("\nКонтекст инициализирован\n");
    printf("Context HCRYPTPROV = %d\n", (LONG)phProv);
    
    /// Получение списка контейнеров
    DWORD pdwDataLen = 0;
    DWORD flag = 1;
    
    printf("\nПолучение списка контейнеров\n\n");
    if (!CryptGetProvParam(phProv, PP_ENUMCONTAINERS, NULL, &pdwDataLen, flag)) {
        DWORD error = CSP_GetLastError();
        if (error == ERROR_NO_MORE_ITEMS) {
            printf("Список контейнеров пуст\n");
            CryptReleaseContext(phProv, 0);
            return INIT_CSP_OK;
        }
        
        printf("Не удалось получить список контейнеров CryptGetProvParam (PP_ENUMCONTAINERS)\n");
        handleError(@"CryptAcquireContextA");
        CryptReleaseContext(phProv, 0);
        return INIT_CSP_ERROR;
    }
    
    BYTE* data = (BYTE*)malloc(pdwDataLen);
    
    int i = 1;
    
    while (CryptGetProvParam(phProv, PP_ENUMCONTAINERS, data, &pdwDataLen, flag)) {
        printf("\nКонтейнер #%d\n", i);
        printf("%s\n", data);
        flag = 2;
        i++;
    };
    
    free(data);
    CryptReleaseContext(phProv, 0);
    
    return INIT_CSP_OK;
}

wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
    /// TODO: освободить память после new
    wchar_t* wString=new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}

NSString* addCert(NSString* pathtoCertFile, NSString* password) {
    const char *pathToCertFileChar = [pathtoCertFile UTF8String];
    const char *passwordChar = [password UTF8String];
    
    NSString* result;
    NSString* containerName;
    
    printf("\nУстановка контейнера\n\n");
    
    CRYPT_DATA_BLOB certBlob;
    
    FILE *file = fopen(pathToCertFileChar, "rb");
    fseek(file, 0, SEEK_END);
    certBlob.cbData = (DWORD)ftell(file);
    fseek(file, 0, SEEK_SET);
    certBlob.pbData = (BYTE*)malloc(certBlob.cbData);
    fread(certBlob.pbData, 1, certBlob.cbData, file);
    fclose(file);
    
    LPCWSTR passwordL = convertCharArrayToLPCWSTR(passwordChar);
    
    /// Добавление контейнера
    HCERTSTORE certStore = PFXImportCertStore(&certBlob, passwordL, CRYPT_SILENT | CRYPT_EXPORTABLE);
    
    free((void*)passwordL);
    
    if (!certStore) {
        printf("Не удалось добавить контейнер закрытого ключа");
        handleError(@"PFXImportCertStore");
        return NULL;
    } else {
        printf("\nКонтейнер успешно добавлен\n\n");
    }
    
    /// Вывод информации о сертификате
    PCCERT_CONTEXT pPrevCertContext = NULL;
    printf("Информация о сертификатах в конейнере\n");
    
    do {
        pPrevCertContext = CertEnumCertificatesInStore(certStore, pPrevCertContext);
        if (pPrevCertContext != NULL) {
            DWORD csz = CertNameToStrA(X509_ASN_ENCODING, &pPrevCertContext->pCertInfo->Subject, CERT_SIMPLE_NAME_STR, NULL, 0);
            LPSTR psz = (LPSTR)malloc(csz);
            
            CertNameToStrA(X509_ASN_ENCODING, &pPrevCertContext->pCertInfo->Subject, CERT_SIMPLE_NAME_STR, psz, csz);
            
            printf("Сертификат: %s\n", psz);
            
            HCRYPTPROV hProv = 0;
            if (CryptAcquireCertificatePrivateKey(pPrevCertContext, CRYPT_ACQUIRE_SILENT_FLAG, NULL, &hProv, NULL, NULL)) {
                printf("Сертификат связанный с приватным ключем: %s\n", psz);
                
                NSData *certificateEncodedData = [NSData dataWithBytes:pPrevCertContext->pbCertEncoded length:pPrevCertContext->cbCertEncoded];
                NSString *base64Certificate = [certificateEncodedData base64EncodedStringWithOptions:0];
                
                DWORD pdwDataLen = 0;
                CryptGetProvParam(hProv, PP_CONTAINER, NULL, &pdwDataLen, NULL);
                BYTE* data = (BYTE*)malloc(pdwDataLen);
                CryptGetProvParam(hProv, PP_CONTAINER, data, &pdwDataLen, NULL);
                const char *ch = reinterpret_cast<const char*>(data);
                containerName = [NSString stringWithFormat:@"%s", ch];
                NSDictionary *map = [[NSDictionary alloc] initWithObjectsAndKeys:base64Certificate, @"certificate", containerName, @"alias", nil];
                NSData *jsonData = [NSJSONSerialization dataWithJSONObject:map
                                                                   options:NSJSONWritingPrettyPrinted
                                                                     error:NULL];
                
                result = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
            }
            
            free(psz);
            CryptReleaseContext(hProv, 0);
        }
    } while (pPrevCertContext != NULL);
    
    /// Закрытие certStore и дескриптора сертификата
    if (certStore) CertCloseStore(certStore, CERT_CLOSE_STORE_FORCE_FLAG);
    if (pPrevCertContext) CertFreeCertificateContext(pPrevCertContext);
    
    HCRYPTPROV hProv = 0;
    NSString *pathString = [@"\\\\.\\HDIMAGE\\" stringByAppendingString:containerName];
    const char *path = [pathString UTF8String];
    if(!CryptAcquireContext(
                            &hProv,
                            _TEXT(path),
                            NULL,
                            PROV_GOST_2012_256,
                            CRYPT_SILENT))
    {
        handleError(@"CryptAcquireContext");
        return NULL;
    }
    
    //--------------------------------------------------------------------
    // Установка параметров в соответствии с паролем.
    
    printf("\nУстановка пароля на ключевой контейнер\n\n");
    
    CRYPT_PIN_PARAM param;
    param.type = CRYPT_PIN_PASSWD;
    param.dest.passwd = (char*)passwordChar;
    
    if(!CryptSetProvParam(
                          hProv,
                          PP_CHANGE_PIN,
                          (BYTE*)&param,
                          0))
    {
        printf("Set pin error\n");
        handleError(@"CryptSetProvParam (PP_CHANGE_PIN)");
        return NULL;
    }
    
    return result;
}

NSString* sign(NSString* alias, NSString* password, NSString* data) {
    printf("\nПодписание\n");
    HCRYPTPROV hProv = 0;            // Дескриптор CSP
    HCRYPTHASH hHash = 0;
    
    BYTE *pbHash = NULL;
    DWORD cbHash;
    
    BYTE *pbSignature = NULL;
    DWORD cbSignature;
    
    const char *dataChar = [data UTF8String];
    DWORD cbBuffer;
    CryptStringToBinaryA(dataChar, strlen(dataChar), CRYPT_STRING_BASE64, NULL, &cbBuffer, 0, NULL);
    BYTE* pbBuffer = (BYTE*)malloc(cbBuffer);
    CryptStringToBinaryA(dataChar, strlen(dataChar), CRYPT_STRING_BASE64, pbBuffer, &cbBuffer, 0, NULL);
    
    printf("Получение дескриптора провайдера\n");
    NSString *pathString = [@"\\\\.\\HDIMAGE\\" stringByAppendingString:alias];
    const char *path = [pathString UTF8String];
    if(!CryptAcquireContext(
                            &hProv,
                            _TEXT(path),
                            NULL,
                            PROV_GOST_2012_256,
                            CRYPT_SILENT))
    {
        handleError(@"CryptAcquireContext");
        return NULL;
    }
    
    printf("Установка параметров в соответствии с паролем\n");
    const char *passwordChar = [password UTF8String];
    
    if(!CryptSetProvParam(
                          hProv,
                          PP_KEYEXCHANGE_PIN,
                          (BYTE*)passwordChar,
                          0))
    {
        printf("Set pin error\n");
        handleError(@"CryptSetProvParam (PP_KEYEXCHANGE_PIN)");
        return NULL;
    }
    
    printf("Создание объекта функции хэширования\n");
    if(!CryptCreateHash(
                        hProv,
                        CALG_GR3411_2012_256,
                        0,
                        0,
                        &hHash))
    {
        printf("CryptCreateHash error\n");
        return NULL;
    }
    
    //--------------------------------------------------------------------
    // Вычисление криптографического хэша буфера.
    
    if(!CryptHashData(
                      hHash,
                      pbBuffer,
                      cbBuffer,
                      0))
    {
        handleError(@"CryptHashData");
        return NULL;
    }
    
    if(!CryptGetHashParam(hHash,
                          HP_HASHVAL,
                          NULL,
                          &cbHash,
                          0))
    {
        printf("CryptGetHashParam error \n");
        return NULL;
    }
    
    pbHash = (BYTE*)malloc(cbHash);
    if(!pbHash) {
        printf("Out of memmory \n");
        return NULL;
    }
    
    if(!CryptGetHashParam(hHash,
                          HP_HASHVAL,
                          pbHash,
                          &cbHash,
                          0))
    {
        printf("CryptGetHashParam error \n");
        return NULL;
    }
    
    DWORD hashBase64Len;
    CryptBinaryToStringA(pbHash, cbHash, CRYPT_STRING_BASE64, NULL, &hashBase64Len);
    LPSTR hashBase64String = (char*)malloc(hashBase64Len);
    CryptBinaryToStringA(pbHash, cbHash, CRYPT_STRING_BASE64, hashBase64String, &hashBase64Len);
    
    printf("Хэш: ");
    printf("%s", hashBase64String);
    
    //--------------------------------------------------------------------
    // Определение размера подписи и распределение памяти.
    
    if(!CryptSignHash(
                      hHash,
                      AT_KEYEXCHANGE,
                      NULL,
                      0,
                      NULL,
                      &cbSignature))
    {
        printf("CryptSignHash error\n");
        handleError(@"CryptSignHash");
        return NULL;
    }
    
    //--------------------------------------------------------------------
    // Распределение памяти под буфер подписи.
    
    pbSignature = (BYTE *)malloc(cbSignature);
    
    if(!pbSignature)
    {
        printf("Out of memmory \n");
        return NULL;
    }
    
    // Подпись объекта функции хэширования.
    printf("Подпись объекта функции хэширования\n");
    if(!CryptSignHash(
                      hHash,
                      AT_KEYEXCHANGE,
                      NULL,
                      0,
                      pbSignature,
                      &cbSignature))
    {
        handleError(@"CryptSignHash");
        return NULL;
    }
    
    DWORD signatureBase64Len;
    CryptBinaryToStringA(pbSignature, cbSignature, CRYPT_STRING_BASE64, NULL, &signatureBase64Len);
    LPSTR signatureBase64String = (char*)malloc(signatureBase64Len);
    CryptBinaryToStringA(pbSignature, cbSignature, CRYPT_STRING_BASE64, signatureBase64String, &signatureBase64Len);
    
    printf("Сигнатура: ");
    printf("%s", signatureBase64String);
    
    // Освобождение памяти
    
    if(pbHash)
        free(pbHash);
    if(pbSignature)
        free(pbSignature);
    
    // Уничтожение объекта функции хэширования.
    if(hHash)
        CryptDestroyHash(hHash);
    
    // Освобождение дескриптора провайдера.
    if(hProv)
        CryptReleaseContext(hProv, 0);
    
    return [NSString stringWithUTF8String:signatureBase64String];
}
