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

/// Инициализация провайдера и получение списка контейнеров
bool initCSP()
{
    DisableIntegrityCheck();
    
    /// Инициализация контекста
    HCRYPTPROV phProv = 0;
    
    if (!CryptAcquireContextA(&phProv, NULL, NULL, PROV_GOST_2012_256, CRYPT_SILENT | CRYPT_VERIFYCONTEXT)) {
        printf("Не удалось инициализировать context\n");
        printf("%d\n", CSP_GetLastError());
        return false;
    }
    
    printf("\nContext = %d\n", (LONG)phProv);
    
    /// Получение списка контейнеров
    DWORD pdwDataLen = 0;
    DWORD flag = 1;
    
    if (!CryptGetProvParam(phProv, PP_ENUMCONTAINERS, NULL, &pdwDataLen, flag)) {
        printf("Не удалось получить список контейнеров закрытого ключа\n");
        return false;
    }
    
    BYTE* data = (BYTE*)malloc(pdwDataLen);
    
    while (CryptGetProvParam(phProv, PP_ENUMCONTAINERS, data, &pdwDataLen, flag)) {
        printf("\n Container = %s\n", data);
        flag = 2;
    };
    
    CryptReleaseContext(phProv, 0);
    
    free(data);
    
    return true;
}

bool addCert() {
    CRYPT_DATA_BLOB certBlob;
    
    NSString* pathToCertFileString = [[NSBundle mainBundle] pathForResource:@"test256" ofType:@"pfx"];
    const char* pathtoCertFile = [pathToCertFileString UTF8String];
    FILE *file = fopen(pathtoCertFile, "rb");
    fseek(file, 0, SEEK_END);
    certBlob.cbData = (DWORD)ftell(file);
    fseek(file, 0, SEEK_SET);
    certBlob.pbData = (BYTE*)malloc(certBlob.cbData);
    fread(certBlob.pbData, 1, certBlob.cbData, file);
    fclose(file);
    
    /// Добавление контейнера
    HCERTSTORE certStore = PFXImportCertStore(&certBlob, L"123", CRYPT_SILENT);
    
    if (!certStore) {
        printf("Не удалось добавить контейнер закрытого ключа");
        return false;
    } else {
        printf("Контейнер успешно добавлен\n");
    }
    
    /// Вывод информации о сертификате
    PCCERT_CONTEXT pPrevCertContext = NULL;
    
    do {
        pPrevCertContext = CertEnumCertificatesInStore(certStore, pPrevCertContext);
        if (pPrevCertContext != NULL) {
            DWORD csz = CertNameToStrA(X509_ASN_ENCODING, &pPrevCertContext->pCertInfo->Subject, CERT_SIMPLE_NAME_STR, NULL, 0);
            LPSTR psz = (LPSTR)malloc(csz);
            
            CertNameToStrA(X509_ASN_ENCODING, &pPrevCertContext->pCertInfo->Subject, CERT_SIMPLE_NAME_STR, psz, csz);
            
            printf("cert - %s\n", psz);
            
            free(psz);
        }
    } while (pPrevCertContext != NULL);
    
    /// Закрытие certStore
    if (certStore) CertCloseStore(certStore, CERT_CLOSE_STORE_FORCE_FLAG);
    
    HCRYPTPROV hProv = 0;

    if(!CryptAcquireContext(
                            &hProv,
                            _TEXT("\\\\.\\HDIMAGE\\test"),
                            NULL,
                            PROV_GOST_2012_256,
                            CRYPT_SILENT))
    {
        printf("CryptAcquireContext error\n");
        return false;
    }

    //--------------------------------------------------------------------
    // Установка параметров в соответствии с паролем.

    CRYPT_PIN_PARAM param;
    param.type = CRYPT_PIN_PASSWD;
    param.dest.passwd = (char*)"123";

    if(!CryptSetProvParam(
                          hProv,
                          PP_CHANGE_PIN,
                          (BYTE*)&param,
                          0))
    {
        printf("Set pin error\n");
        wchar_t buf[256];
        CSP_FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, CSP_GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                       buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
        printf("%ls\n", buf);
        return false;
    }
    
    return true;
}

bool removeCert() {
    return false;
}

void sign() {
    HCRYPTPROV hProv = 0;            // Дескриптор CSP
    HCRYPTKEY hKey = 0;              // Дескриптор ключа
    HCRYPTHASH hHash = 0;
    
    BYTE *pbHash = NULL;
    BYTE *pbKeyBlob = NULL;
    BYTE *pbSignature = NULL;
    
    BYTE *pbBuffer = (BYTE *)malloc(1024);
    memset(pbBuffer, 0, 1024);
    DWORD dwBufferLen = 1024;//(DWORD)(strlen((char *)pbBuffer)+1);
    DWORD cbHash;
    DWORD dwSigLen;
    
    // Получение дескриптора провайдера.
    if(!CryptAcquireContext(
                            &hProv,
                            _TEXT("\\\\.\\HDIMAGE\\test"),
                            NULL,
                            PROV_GOST_2012_256,
                            CRYPT_SILENT))
    {
        printf("CryptAcquireContext error\n");
        return;
    }
    
    //--------------------------------------------------------------------
    // Установка параметров в соответствии с паролем.
    
    if(!CryptSetProvParam(
                          hProv,
                          PP_KEYEXCHANGE_PIN,
                          (BYTE*)"123",
                          0))
    {
        printf("Set pin error\n");
        wchar_t buf[256];
        CSP_FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, CSP_GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                       buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
        printf("%ls\n", buf);
        return;
    }
    
    if(!CryptGetUserKey(
       hProv,
       AT_KEYEXCHANGE,
       &hKey))
    {
        printf("CryptGetUserKey\n");
        wchar_t buf[256];
        CSP_FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, CSP_GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                       buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
        printf("%ls\n", buf);
        return;
    }
    
    //--------------------------------------------------------------------
    // Создание объекта функции хэширования.
    if(!CryptCreateHash(
                        hProv,
                        CALG_GR3411_2012_256,
                        0,
                        0,
                        &hHash))
    {
        printf("CryptCreateHash error\n");
        return;
    }
    
    //--------------------------------------------------------------------
    // Передача параметра HP_OID объекта функции хэширования.
    //--------------------------------------------------------------------
    
    //--------------------------------------------------------------------
    // Определение размера BLOBа и распределение памяти.
    
    if(!CryptGetHashParam(hHash,
                          HP_OID,
                          NULL,
                          &cbHash,
                          0))
    {
        printf("CryptGetHashParam error \n");
        return;
    }
    
    pbHash = (BYTE*)malloc(cbHash);
    if(!pbHash) {
        printf("Out of memmory \n");
        return;
    }
    
    // Копирование параметра HP_OID в pbHash.
    
    if(!CryptGetHashParam(hHash,
                          HP_OID,
                          pbHash,
                          &cbHash,
                          0))
    {
        printf("CryptGetHashParam error \n");
        return;
    }
    
    //--------------------------------------------------------------------
    // Вычисление криптографического хэша буфера.
    
    if(!CryptHashData(
                      hHash,
                      pbBuffer,
                      dwBufferLen,
                      0))
    {
        printf("CryptHashData error\n");
        return;
    }
    
//    BYTE rgbHash[64];
//    CHAR rgbDigits[] = "0123456789abcdef";
//    if(!CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0))
//    {
//        printf("CryptGetHashParam error \n");
//        wchar_t buf[256];
//        CSP_FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
//                       NULL, CSP_GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//                       buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
//        printf("%ls\n", buf);
//        return;
//    }
//
//    for(int i = 0; i < cbHash; i++)
//    {
//        printf("%c%c", rgbDigits[rgbHash[i] >> 4],
//            rgbDigits[rgbHash[i] & 0xf]);
//    }
//    printf("\n");
    
    //--------------------------------------------------------------------
    // Определение размера подписи и распределение памяти.
    
    if(!CryptSignHash(
                     hHash,
                     AT_KEYEXCHANGE,
                     NULL,
                     0,
                     NULL,
                     &dwSigLen))
    {
        printf("CryptSignHash error\n");
        wchar_t buf[256];
        CSP_FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, CSP_GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                       buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
        printf("%ls\n", buf);
        return;
    }
    
    wchar_t buf[256];
    CSP_FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                   NULL, CSP_GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                   buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
    printf("%ls\n", buf);
    
    //--------------------------------------------------------------------
    // Распределение памяти под буфер подписи.
    
    pbSignature = (BYTE *)malloc(dwSigLen);
    
    if(!pbSignature)
    {
        printf("Out of memmory \n");
        return;
    }
    
    // Подпись объекта функции хэширования.
    if(!CryptSignHash(
                     hHash,
                     AT_KEYEXCHANGE,
                     NULL,
                     0,
                     pbSignature,
                     &dwSigLen))
    {
        printf("CryptSignHash error\n");
        wchar_t buf[256];
        CSP_FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, CSP_GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                       buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
        printf("%ls\n", buf);
        return;
    }
    
    DWORD base64Len;
    CryptBinaryToStringA(pbSignature, dwSigLen, CRYPT_STRING_BASE64, NULL, &base64Len);
    LPSTR base64String = (char*)malloc(base64Len);
    CryptBinaryToStringA(pbSignature, dwSigLen, CRYPT_STRING_BASE64, base64String, &base64Len);
    printf("%s", base64String);
    
    if(pbHash)
        free(pbHash);
    if(pbKeyBlob)
        free(pbKeyBlob);
    if(pbSignature)
        free(pbSignature);
    
    // Уничтожение объекта функции хэширования.
    if(hHash)
        CryptDestroyHash(hHash);
    
    printf("The hash object has been destroyed.\n");
    printf("The signature is created.\n\n");
    
    // Уничтожение дескриптора ключа пользователя.
    
    if(hKey)
        CryptDestroyKey(hKey);
    
    // Освобождение дескриптора провайдера.
    
    if(hProv)
        CryptReleaseContext(hProv, 0);
    
    printf("The program ran to completion without error. \n");
    return;
}
