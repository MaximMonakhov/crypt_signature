#ifndef __CPCRYPT_H__
#define __CPCRYPT_H__

#if defined( __cplusplus )
extern "C" {
#endif

CSP_BOOL
CPCryptInstallCertificate (HCRYPTPROV hProv, DWORD dwKeySpec,
	const BYTE * pbCertificate, DWORD cbCertificate,
	LPCWSTR pwszStoreName, DWORD dwStoreFlags, 
	CSP_BOOL fInstallToContainer, DWORD *pdwInstallToContainerStatus);
//static CSP_BOOL
//CPCryptCreateTemplate (CERT_REQUEST_INFO * pCertRequest,
//	CRYPT_ALGORITHM_IDENTIFIER * SignatureAlgorithm,
//	CERT_INFO *pCertInfo, DWORD * pcbCertInfo);
CSP_BOOL
CPCryptInstallTemplate (HCRYPTPROV hProv, DWORD dwKeySpec, 
	DWORD dwCertEncodingType,
	CERT_REQUEST_INFO * pCertRequest,
	LPCWSTR pwszStoreName, DWORD dwStoreFlags);


/** Функции CPCryptGetDefaultSignatureOIDInfo() и 
 * CPCryptGetDefaultHashOIDInfo() находят соответственно
 * OID алгоритма подписи по умолчанию и OID алгоритма хэша 
 * по умолчанию для заданного OID-а алгоритма ключа.
 *
 * Если провайдер поддерживает несколько алгоритмов хэша,
 * совместимых с алгоритмом ключа, выбирается алгоритм
 * хэша GR3411. Если GR3411 несовместим с алгоритмом ключа,
 * выбирается SHA1. Если SHA1 несовместим, выбирается первый
 * алгоритм хэша, который совместим с алгоритмом ключа.
 *
 * В случае, если алгоритм ключа получается из контекста
 * провайдера (HCRYPTPROV), рекомендуется получать OID
 * алгоритма ключа с помощью функции CryptExportPublicKeyInfo(),
 * поскольку, если для ГОСТ-ового провайдера получать OID через
 * AlgId, полученный через CryptGetKeyParam(KP_ALGID), в случае,
 * если ключ AT_KEYEXCHANGE, для найденных OIDов (szOID_CP_DH_EX,
 * szOID_CP_DH_EL) не будет найден алгоритм подписи/хэша, в силу
 * особенностей регистрации OIDов CSP (видимо неправильных).
 */
PCCRYPT_OID_INFO
CPCryptGetDefaultHashOIDInfo( LPCSTR szPubKeyOID );

ALG_ID 
CPCryptGetProviderHashAlgId(HCRYPTPROV hCryptProv, LPCSTR pubKeyObjId);

ALG_ID CPGetDefaultGostHashAlgId(LPCSTR szPubKeyOID);

PCCRYPT_OID_INFO
CPCryptGetDefaultSignatureOIDInfo( LPCSTR szPubKeyOID );

PCCRYPT_OID_INFO
CPCryptGetSignatureOIDInfo( LPCSTR szPubKeyOID, LPCSTR szHashOID );

PCCRYPT_OID_INFO
CPCryptGetPublicKeyOIDInfo( LPCSTR szPubKeyOID, DWORD dwKeySpec );

#if defined( __cplusplus )
}       // Balance extern "C" above
#endif

#endif /* __CPCRYPT_H__ */
