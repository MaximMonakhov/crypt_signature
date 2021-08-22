/*
 * CryptFindOIDInfo.cpp::CryptLoadOIDInfo и altreg.cpp обмениваются данными
 * в altreg.cpp не хочется использовать _CRYPT_OID_INFO_
 * и не хочется заниматься распределением памяти
 */
#define AREG_MAX_DATALEN 256
struct AREG_CRYPT_OID_INFO {
    // DWORD           cbSize;
    // LPCSTR          pszOID;
    char pszOID[AREG_MAX_DATALEN];
    // LPCWSTR         pwszName;
    TCHAR pszName[AREG_MAX_DATALEN];
    /* union { */
    /* 	DWORD       dwValue; */
    /* 	ALG_ID      Algid; */
    /* 	DWORD       dwLength; */
    /* }; */
    unsigned Algid;
    // DWORD dwGroupId;
    unsigned dwGroupId;
    // CRYPT_DATA_BLOB ExtraInfo;
    unsigned char pb[AREG_MAX_DATALEN];
    unsigned cb;
};
