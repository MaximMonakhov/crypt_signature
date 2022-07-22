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

NSString* getError() {
    DWORD error = CSP_GetLastError();
    
    printf("\nОшибка\n");
    printf("%d\n", error);
    
    wchar_t buf[256];
    CSP_FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                       buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
    printf("%ls\n", buf);
    
    return [[NSString alloc] initWithBytes:buf length:wcslen(buf)*sizeof(*buf) encoding:NSUTF32LittleEndianStringEncoding];
}

NSString* getErrorResponse(NSString* message) {
    NSDictionary *map = [[NSDictionary alloc] initWithObjectsAndKeys: @(false), @"success", message, @"message", getError(), @"exception", nil];
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:map
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:NULL];
    
    return [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
}

/// Инициализация провайдера и получение списка контейнеров
bool initCSP()
{
    printf("\nИнициализация провайдера и получение списка контейнеров\n\n");
    
    DisableIntegrityCheck();
    
    /// Инициализация контекста
    HCRYPTPROV phProv = 0;
    
    if (!CryptAcquireContextA(&phProv, NULL, NULL, PROV_GOST_2012_256, CRYPT_SILENT | CRYPT_VERIFYCONTEXT)) {
        printf("Не удалось инициализировать context CryptAcquireContextA\n");
        return false;
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
            return true;
        }
        
        printf("Не удалось получить список контейнеров CryptGetProvParam (PP_ENUMCONTAINERS)\n");
        CryptReleaseContext(phProv, 0);
        return false;
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
    
    return true;
}

wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
    /// освободить память после new
    wchar_t* wString=new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;
}

NSString* addCertificate(NSString* pathToCert, NSString* password) {
    const char *pathToCertFileChar = [pathToCert UTF8String];
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
    
    if (!certStore)
        return getErrorResponse(@"Не удалось добавить контейнер закрытого ключа (PFXImportCertStore).\nПроверьте правильность введенного пароля");
    printf("\nКонтейнер успешно добавлен\n\n");
    
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
                NSDictionary *map = [[NSDictionary alloc] initWithObjectsAndKeys:base64Certificate, @"certificate", containerName, @"alias", @(true), @"success", nil];
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
        return getErrorResponse(@"Не удалось Закрытие certStore и дескриптора сертификата (CryptAcquireContext)");
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
        return getErrorResponse(@"Не удалось установить пароль на ключевой контейнер (CryptSetProvParam (PP_CHANGE_PIN))");
    }
    
    return result;
}

NSString* digest(NSString* alias, NSString* password, NSString* message) {
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    
    BYTE *pbHash = NULL;
    DWORD cbHash;
    
    const char *dataChar = [message UTF8String];
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
        return getErrorResponse(@"Не удалось получить дескриптор провайдера (CryptAcquireContext)");
    }
    
    printf("Установка параметров в соответствии с паролем\n");
    const char *passwordChar = [password UTF8String];
    
    if(!CryptSetProvParam(
                          hProv,
                          PP_KEYEXCHANGE_PIN,
                          (BYTE*)passwordChar,
                          0))
    {
        return getErrorResponse(@"Не удалось установить параметры в соответствии с паролем (CryptSetProvParam(PP_KEYEXCHANGE_PIN))");
    }
    
    printf("Создание объекта функции хэширования\n");
    if(!CryptCreateHash(
                        hProv,
                        CALG_GR3411_2012_256,
                        0,
                        0,
                        &hHash))
    {
        return getErrorResponse(@"Не удалось создать объект функции хэширования (CryptCreateHash)");
    }
    
    //--------------------------------------------------------------------
    // Вычисление криптографического хэша буфера.
    
    if(!CryptHashData(
                      hHash,
                      pbBuffer,
                      cbBuffer,
                      0))
    {
        return getErrorResponse(@"Не удалось вычислить криптографический хэш буфера (CryptHashData)");
    }
    
    if(!CryptGetHashParam(hHash,
                          HP_HASHVAL,
                          NULL,
                          &cbHash,
                          0))
    {
        return getErrorResponse(@"Не удалось получить размер хэша(CryptGetHashParam)");
    }
    
    pbHash = (BYTE*)malloc(cbHash);
    if(!pbHash) {
        return getErrorResponse(@"Out of memmory");
    }
    
    if(!CryptGetHashParam(hHash,
                          HP_HASHVAL,
                          pbHash,
                          &cbHash,
                          0))
    {
        return getErrorResponse(@"Не удалось получить хэш (CryptGetHashParam)");
    }
    
    DWORD hashBase64Len;
    CryptBinaryToStringA(pbHash, cbHash, CRYPT_STRING_BASE64, NULL, &hashBase64Len);
    LPSTR hashBase64String = (char*)malloc(hashBase64Len);
    CryptBinaryToStringA(pbHash, cbHash, CRYPT_STRING_BASE64, hashBase64String, &hashBase64Len);
    
    NSDictionary *map = [[NSDictionary alloc] initWithObjectsAndKeys: @(true), @"success", message, @"message", [NSString stringWithUTF8String:hashBase64String], @"digest",@"CALG_GR3411_2012_256", @"digestAlgorithm", nil];
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:map
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:NULL];
    
    if(pbHash)
        free(pbHash);
    
    // Уничтожение объекта функции хэширования.
    if(hHash)
        CryptDestroyHash(hHash);
    
    // Освобождение дескриптора провайдера.
    if(hProv)
        CryptReleaseContext(hProv, 0);
    
    return [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
}

NSString* sign(NSString* alias, NSString* password, NSString* digest) {
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    
    BYTE *pbSignature = NULL;
    DWORD cbSignature;
    
    const char *dataChar = [digest UTF8String];
    DWORD cbHash;
    CryptStringToBinaryA(dataChar, strlen(dataChar), CRYPT_STRING_BASE64, NULL, &cbHash, 0, NULL);
    BYTE* pbHash = (BYTE*)malloc(cbHash);
    CryptStringToBinaryA(dataChar, strlen(dataChar), CRYPT_STRING_BASE64, pbHash, &cbHash, 0, NULL);
    
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
        return getErrorResponse(@"Не удалось получить дескриптор провайдера (CryptAcquireContext)");
    }
    
    printf("Установка параметров в соответствии с паролем\n");
    const char *passwordChar = [password UTF8String];
    
    if(!CryptSetProvParam(
                          hProv,
                          PP_KEYEXCHANGE_PIN,
                          (BYTE*)passwordChar,
                          0))
    {
        return getErrorResponse(@"Не удалось установить параметры в соответствии с паролем (CryptSetProvParam(PP_KEYEXCHANGE_PIN))");
    }
    
    printf("Создание объекта функции хэширования\n");
    if(!CryptCreateHash(
                        hProv,
                        CALG_GR3411_2012_256,
                        0,
                        0,
                        &hHash))
    {
        return getErrorResponse(@"Не удалось создать объект функции хэширования (CryptCreateHash)");
    }
    
    
    if(!CryptSetHashParam(hHash,
                          HP_HASHVAL,
                          pbHash,
                          0))
    {
        return getErrorResponse(@"Не удалось установить хэш у дескриптора хэширования (CryptSetHashParam(HP_HASHVAL))");
    }
    
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
        return getErrorResponse(@"Не удалось определить размер подписи (CryptSignHash)");
    }
    
    //--------------------------------------------------------------------
    // Распределение памяти под буфер подписи.
    
    pbSignature = (BYTE *)malloc(cbSignature);
    
    if(!pbSignature)
    {
        return getErrorResponse(@"Out of memmory");
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
        return getErrorResponse(@"Не удалось подписать объект функции хэширования (CryptSignHash)");
    }
    
    DWORD signatureBase64Len;
    CryptBinaryToStringA(pbSignature, cbSignature, CRYPT_STRING_BASE64, NULL, &signatureBase64Len);
    LPSTR signatureBase64String = (char*)malloc(signatureBase64Len);
    CryptBinaryToStringA(pbSignature, cbSignature, CRYPT_STRING_BASE64, signatureBase64String, &signatureBase64Len);
    
    printf("Сигнатура: ");
    printf("%s", signatureBase64String);
    
    NSDictionary *map = [[NSDictionary alloc] initWithObjectsAndKeys: @(true), @"success", digest, @"digest", [NSString stringWithUTF8String:signatureBase64String], @"signature", @"CALG_GR3410_12_256", @"signatureAlgorithm", nil];
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:map
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:NULL];
    
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
    
    return [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
}
