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


/** ������� CPCryptGetDefaultSignatureOIDInfo() � 
 * CPCryptGetDefaultHashOIDInfo() ������� ��������������
 * OID ��������� ������� �� ��������� � OID ��������� ���� 
 * �� ��������� ��� ��������� OID-� ��������� �����.
 *
 * ���� ��������� ������������ ��������� ���������� ����,
 * ����������� � ���������� �����, ���������� ��������
 * ���� GR3411. ���� GR3411 ����������� � ���������� �����,
 * ���������� SHA1. ���� SHA1 �����������, ���������� ������
 * �������� ����, ������� ��������� � ���������� �����.
 *
 * � ������, ���� �������� ����� ���������� �� ���������
 * ���������� (HCRYPTPROV), ������������� �������� OID
 * ��������� ����� � ������� ������� CryptExportPublicKeyInfo(),
 * ���������, ���� ��� ����-����� ���������� �������� OID �����
 * AlgId, ���������� ����� CryptGetKeyParam(KP_ALGID), � ������,
 * ���� ���� AT_KEYEXCHANGE, ��� ��������� OID�� (szOID_CP_DH_EX,
 * szOID_CP_DH_EL) �� ����� ������ �������� �������/����, � ����
 * ������������ ����������� OID�� CSP (������ ������������).
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
