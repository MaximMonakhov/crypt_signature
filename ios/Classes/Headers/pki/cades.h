/*
 * Copyright(C) 2004-2006 ������ ���
 *
 * ���� ���� �������� ����������, ����������
 * �������������� �������� ������ ���.
 *
 * ����� ����� ����� ����� �� ����� ���� �����������,
 * ����������, ���������� �� ������ �����,
 * ������������ ��� �������������� ����� ��������,
 * ���������������, �������� �� ���� � ��� ��
 * ����� ������������ ������� ��� ����������������
 * ���������� ���������� � ��������� ������ ���.
 */

/*!
 * \file $RCSfile$
 * \version $Revision: 189530 $
 * \date $Date:: 2019-02-25 18:02:41 +0400#$
 * \author $Author: sdenis $
 *
 * \brief API ��� ������ � CAdES (CMS Advanced Electronic Signatures)
 */

#ifndef _CADES_H_INCLUDED
#define _CADES_H_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1400) && !defined(CADES_NOFORCE_MANIFEST)

#define CADES_ASSEMBLY_NAME "CryptoPro.PKI.CAdES"
#define CADES_ASSEMBLY_VERSION "2.0.0.0"

#ifndef CP_ASSEMBLY_PUBLICKEYTOKEN
#define CP_ASSEMBLY_PUBLICKEYTOKEN "a6d31b994cfcddc4"
#endif // CP_ASSEMBLY_PUBLICKEYTOKEN

#ifdef _M_IX86
#define CADES_ASSEMBLY_PROCARCH "x86"
#endif // _M_IX86

#ifdef _M_AMD64
#define CADES_ASSEMBLY_PROCARCH "amd64"
#endif // _M_AMD64

#ifdef _M_IA64
#define CADES_ASSEMBLY_PROCARCH "ia64"
#endif // _M_IA64

#pragma comment(linker,"/manifestdependency:\"type='win32' " \
        "name='" CADES_ASSEMBLY_NAME "' " \
        "version='" CADES_ASSEMBLY_VERSION "' " \
        "processorArchitecture='" CADES_ASSEMBLY_PROCARCH "' " \
        "language='*' " \
        "publicKeyToken='" CP_ASSEMBLY_PUBLICKEYTOKEN "'\"")

#endif // defined(_MSC_VER) && (_MSC_VER >= 1400) && !defined(CADES_NOFORCE_MANIFEST)

#if !defined CADES_DLL_DEFINES
#   define CADES_DLL_DEFINES
#   if defined _WIN32 && !defined CADES_STATIC
#	ifdef CADES_DLL
#	    define CADES_CLASS __declspec(dllexport)
#	    define CADES_API __declspec(dllexport)
#	    define CADES_DATA __declspec(dllexport)
#	    define CADES_EXTERN_TEMPLATE
#	else // defined CADES_DLL
#	    define CADES_CLASS __declspec(dllimport)
#	    define CADES_API __declspec(dllimport)
#	    define CADES_DATA __declspec(dllimport)
#	    define CADES_EXTERN_TEMPLATE extern
#	endif // !defined CADES_DLL
#   else // defined _WIN32 && !defined CADES_STATIC
#	define CADES_CLASS
#	define CADES_API
#	define CADES_DATA
#	define CADES_EXTERN_TEMPLATE
#       define NO_EXPIMP_CDLLLIST_ITERATORS
#   endif // !defined _WIN32 ||  defined CADES_STATIC
#endif // !defined CADES_DLL_DEFINES

#if defined _WIN32
#   include <windows.h>
#   include <wincrypt.h>
#   include <prsht.h>
#else
#include<CSP_WinCrypt.h>
#include<CSP_WinDef.h>
#include<CSP_WinError.h>
#ifndef __in  
#   define __in 
#endif
#ifndef __in_opt
#   define __in_opt
#endif
#ifndef __out
#   define __out
#endif
#ifndef __out_opt
#   define __out_opt
#endif
#ifndef __reserved
#   define __reserved
#endif
#endif	/* _WIN32 */

#define szOID_aa_signingCertificate "1.2.840.113549.1.9.16.2.12"
#define szOID_aa_ets_otherSigCert "1.2.840.113549.1.9.16.2.19"
#define szOID_aa_signingCertificateV2 "1.2.840.113549.1.9.16.2.47"

#define CADES_DEFAULT		0x00000000
#define CADES_BES		0x00000001
#define CADES_T                 0x00000005
#define CADES_X_LONG_TYPE_1	0x0000005D
#define PKCS7_TYPE              0x0000ffff

#define CADES_DISABLE_REDUNDANCY          0x00010000
#define CADES_USE_OCSP_AUTHORIZED_POLICY  0x00020000

#define CADES_AUTH_ANONYMOUS	0x00
#define CADES_AUTH_BASIC	0x01
#define CADES_AUTH_NTLM		0x02
#define CADES_AUTH_DIGEST	0x08
#define CADES_AUTH_NEGOTIATE	0x10

#define CADES_VERIFY_SUCCESS			    0x00
#define CADES_VERIFY_INVALID_REFS_AND_VALUES	    0x01
#define CADES_VERIFY_SIGNER_NOT_FOUND		    0x02
#define CADES_VERIFY_NO_VALID_SIGNATURE_TIMESTAMP   0x03
#define CADES_VERIFY_REFS_AND_VALUES_NO_MATCH	    0x04
#define CADES_VERIFY_NO_CHAIN			    0x05
#define CADES_VERIFY_END_CERT_REVOCATION	    0x06
#define CADES_VERIFY_CHAIN_CERT_REVOCATION	    0x07
#define CADES_VERIFY_BAD_SIGNATURE		    0x08
#define CADES_VERIFY_NO_VALID_CADES_C_TIMESTAMP	    0x09
#define CADES_VERIFY_BAD_POLICY			    0x0A
#define CADES_VERIFY_UNSUPPORTED_ATTRIBUTE	    0x0B
#define CADES_VERIFY_FAILED_POLICY 		    0x0C
#define CADES_VERIFY_ECONTENTTYPE_NO_MATCH	    0x0D

#define CADES_TIMESTAMP_NO_CERT_REQ 0x00000001
#define CADES_CHECK_CERT_REQ 0x00000002
#define CADES_SKIP_IE_PROXY_CONFIGURATION 0x00000004

#ifndef DEFINE_CADES_STRUCT_MEMBERS
#define DEFINE_CADES_STRUCT_MEMBERS(className)
#endif // DEFINE_CADES_STRUCT_MEMBERS

typedef struct _CADES_AUTH_PARA
{
    DWORD dwSize;
    DWORD dwAuthType;
    LPCWSTR wszUsername;
    LPCWSTR wszPassword;
    PCCERT_CONTEXT pClientCertificate;
    DEFINE_CADES_STRUCT_MEMBERS(_CADES_AUTH_PARA)
} CADES_AUTH_PARA, *PCADES_AUTH_PARA;

typedef struct _CADES_SERVICE_CONNECTION_PARA
{
    DWORD dwSize;
    LPCWSTR wszUri;
    PCADES_AUTH_PARA pAuthPara;
    DEFINE_CADES_STRUCT_MEMBERS(_CADES_SERVICE_CONNECTION_PARA)
} CADES_SERVICE_CONNECTION_PARA, *PCADES_SERVICE_CONNECTION_PARA;

typedef struct _CADES_PROXY_PARA
{
    DWORD dwSize;
    LPCWSTR wszProxyUri;
    PCADES_AUTH_PARA pProxyAuthPara;
    DEFINE_CADES_STRUCT_MEMBERS(_CADES_PROXY_PARA)
} CADES_PROXY_PARA, *PCADES_PROXY_PARA;

typedef struct _CADES_SIGN_PARA
{
    DWORD dwSize;
    DWORD dwCadesType;
    PCCERT_CONTEXT pSignerCert;
    LPCSTR szHashAlgorithm;
    HCERTSTORE hAdditionalStore;
    PCADES_SERVICE_CONNECTION_PARA pTspConnectionPara;
    PCADES_PROXY_PARA pProxyPara;
    LPVOID pCadesExtraPara;
#ifdef CADES_PARA_HAS_EXTRA_FIELDS
    DWORD cAdditionalOCSPServices;
    LPCWSTR *rgAdditionalOCSPServices;
#endif //CADES_PARA_HAS_EXTRA_FIELDS
    DEFINE_CADES_STRUCT_MEMBERS(_CADES_SIGN_PARA)
} CADES_SIGN_PARA, *PCADES_SIGN_PARA;

typedef struct _CADES_EXTRA_PARA
{
    DWORD dwSize;
    DWORD dwFlags;
    DEFINE_CADES_STRUCT_MEMBERS(_CADES_EXTRA_PARA)
} CADES_EXTRA_PARA, *PCADES_EXTRA_PARA;

typedef struct _CADES_COSIGN_PARA
{
    DWORD dwSize;
    PCMSG_SIGNER_ENCODE_INFO pSigner;
    PCADES_SIGN_PARA pCadesSignPara;
    DEFINE_CADES_STRUCT_MEMBERS(_CADES_COSIGN_PARA)
} CADES_COSIGN_PARA, *PCADES_COSIGN_PARA;

typedef struct _CADES_ENCODE_INFO
{
    DWORD dwSize;
    PCMSG_SIGNED_ENCODE_INFO pSignedEncodeInfo;
    DWORD cSignerCerts;
    PCCERT_CONTEXT *rgSignerCerts;
    DWORD cHashAlgorithms;
    LPCSTR *rgHashAlgorithms;
    DEFINE_CADES_STRUCT_MEMBERS(_CADES_ENCODE_INFO)
} CADES_ENCODE_INFO, *PCADES_ENCODE_INFO;

typedef struct _CADES_SIGN_MESSAGE_PARA
{
    DWORD dwSize;
    PCRYPT_SIGN_MESSAGE_PARA pSignMessagePara;
    PCADES_SIGN_PARA pCadesSignPara;
    DEFINE_CADES_STRUCT_MEMBERS(_CADES_SIGN_MESSAGE_PARA)
} CADES_SIGN_MESSAGE_PARA, *PCADES_SIGN_MESSAGE_PARA;

typedef struct _CADES_VERIFICATION_PARA
{
    DWORD dwSize;
    LPVOID pMessageContentHash;
    PCADES_PROXY_PARA pProxyPara;
    HCERTSTORE hStore;
    CSP_BOOL bReserved2;
    LPVOID pReserved3;
    DWORD dwCadesType;
#ifdef CADES_PARA_HAS_EXTRA_FIELDS
    DWORD dwFlags;
#endif //CADES_PARA_HAS_EXTRA_FIELDS
    DEFINE_CADES_STRUCT_MEMBERS(_CADES_VERIFICATION_PARA)
} CADES_VERIFICATION_PARA, *PCADES_VERIFICATION_PARA;

typedef struct _CADES_VERIFICATION_INFO
{
    DWORD dwSize;
    DWORD dwStatus;
    PCCERT_CONTEXT pSignerCert;
    LPFILETIME pSigningTime;
    LPFILETIME pReserved;
    LPFILETIME pSignatureTimeStampTime;
    DEFINE_CADES_STRUCT_MEMBERS(_CADES_VERIFICATION_INFO)
} CADES_VERIFICATION_INFO, *PCADES_VERIFICATION_INFO;

typedef struct _CADES_VERIFY_MESSAGE_PARA
{
    DWORD dwSize;
    PCRYPT_VERIFY_MESSAGE_PARA pVerifyMessagePara;
    PCADES_VERIFICATION_PARA pCadesVerifyPara;
    DEFINE_CADES_STRUCT_MEMBERS(_CADES_VERIFY_MESSAGE_PARA)
} CADES_VERIFY_MESSAGE_PARA, *PCADES_VERIFY_MESSAGE_PARA;

typedef struct _CADES_ENHANCE_MESSAGE_PARA
{
    DWORD dwSize;
    DWORD dwMsgEncodingType;
    PCADES_SIGN_PARA pCadesSignPara;
    DEFINE_CADES_STRUCT_MEMBERS(_CADES_ENHANCE_MESSAGE_PARA)
} CADES_ENHANCE_MESSAGE_PARA, *PCADES_ENHANCE_MESSAGE_PARA;

typedef struct _CADES_VIEW_SIGNATURE_PARA
{
    DWORD dwSize;
    DWORD dwMsgEncodingType;
    HCRYPTPROV hCryptProv;
    DEFINE_CADES_STRUCT_MEMBERS(_CADES_VIEW_SIGNATURE_PARA)
} CADES_VIEW_SIGNATURE_PARA, *PCADES_VIEW_SIGNATURE_PARA;

typedef void* PCADES_CONVERT_CONTEXT;

typedef CRYPT_SEQUENCE_OF_ANY CADES_BLOB_ARRAY, *PCADES_BLOB_ARRAY;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// Low-level API
CADES_API HCRYPTMSG WINAPI CadesMsgOpenToEncode(  
    __in DWORD dwMsgEncodingType,
    __in DWORD dwFlags,
    __in PCADES_ENCODE_INFO pvMsgEncodeInfo,
    __in_opt LPSTR pszInnerContentObjID,
    __in PCMSG_STREAM_INFO pStreamInfo);

CADES_API CSP_BOOL WINAPI CadesMsgIsType(
    __in HCRYPTMSG hCryptMsg,
    __in DWORD dwSignatureIndex,
    __in DWORD dwCadesType,
    __out CSP_BOOL *pbResult);

CADES_API CSP_BOOL WINAPI CadesMsgIsTypeEncoded(
    __in DWORD dwEncodingType,
    __in PBYTE pbSignerInfo,
    __in DWORD cbSignerInfo,
    __in DWORD dwCadesType,
    __out CSP_BOOL *pbResult);

CADES_API CSP_BOOL WINAPI CadesMsgEnhanceSignature(
    __in HCRYPTMSG hCryptMsg,
    __in DWORD dwSignatureIndex,
    __in_opt PCADES_SIGN_PARA pCadesSignPara);

CADES_API CSP_BOOL WINAPI CadesMsgEnhanceSignatureAll(
    __in HCRYPTMSG hCryptMsg,
    __in_opt PCADES_SIGN_PARA pCadesSignPara);
/* ��� ����� testCadesMsgCreateSignature_CADES_T_FutureCRL �� coverparams.
CADES_API CSP_BOOL WINAPI CadesMsgEnhanceSignatureTimeStamp(HCRYPTMSG,
	PCCERT_CONTEXT, LPCSTR, VOID*, VOID*);
*/
CADES_API CSP_BOOL WINAPI CadesMsgAddEnhancedSignature(
    __in HCRYPTMSG hCryptMsg,
    __in PCADES_COSIGN_PARA pCadesCosignPara);

CADES_API CSP_BOOL WINAPI CadesMsgVerifySignature(
    __in HCRYPTMSG hCryptMsg,
    __in DWORD dwSignatureIndex,
    __in_opt PCADES_VERIFICATION_PARA pVerificationPara,
    __out_opt PCADES_VERIFICATION_INFO *ppVerificationInfo);

CADES_API CSP_BOOL WINAPI CadesMsgCountersignEncoded(
    __in DWORD dwEncodingType,
    __in PBYTE pbSignerInfo,
    __in DWORD cbSignerInfo,
    __in DWORD cCountersigners,
    __in PCADES_COSIGN_PARA rgCountersigners,
    __out PCRYPT_DATA_BLOB *ppCountersignature);

CADES_API CSP_BOOL WINAPI CadesMsgCountersign(
    __in HCRYPTMSG hCryptMsg,
    __in DWORD dwIndex,
    __in DWORD cCountersigners,
    __in PCADES_COSIGN_PARA rgCountersigners);

CADES_API CSP_BOOL WINAPI CadesMsgVerifyCountersignatureEncoded(
    __in HCRYPTPROV hCryptProv,
    __in DWORD dwEncodingType,
    __in PBYTE pbSignerInfo,
    __in DWORD cbSignerInfo,
    __in PBYTE pbSignerInfoCountersignature,
    __in DWORD cbSignerInfoCountersignature,
    __reserved PCERT_INFO pciCountersigner,
    __in_opt PCADES_VERIFICATION_PARA pVerificationPara,
    __out_opt PCADES_VERIFICATION_INFO *ppVerificationInfo);

CADES_API CSP_BOOL WINAPI CadesMsgVerifyCountersignatureEncodedEx(
    __in HCRYPTPROV hCryptProv,
    __in DWORD dwEncodingType,
    __in PBYTE pbSignerInfo,
    __in DWORD cbSignerInfo,
    __in PBYTE pbSignerInfoCountersignature,
    __in DWORD cbSignerInfoCountersignature,
    __reserved DWORD dwSignerType,
    __reserved void * pvSigner,
    __reserved DWORD dwFlags,
    __reserved void * pvReserved,
    __in_opt PCADES_VERIFICATION_PARA pVerificationPara,
    __out_opt PCADES_VERIFICATION_INFO *ppVerificationInfo);

CADES_API CSP_BOOL WINAPI CadesMsgGetSigningCertId(
    __in HCRYPTMSG hCryptMsg,
    __in DWORD dwSignatureIndex,
    __out PCRYPT_DATA_BLOB *ppCertId);

CADES_API CSP_BOOL WINAPI CadesMsgGetSigningCertIdEx(
    __in PCMSG_SIGNER_INFO pSignerInfo,
    __out PCRYPT_DATA_BLOB *ppCertId);

CADES_API CSP_BOOL WINAPI CadesMsgGetSigningCertIdEncoded(
    __in DWORD dwEncodingType,
    __in PBYTE pbSignerInfo,
    __in DWORD cbSignerInfo,
    __out PCRYPT_DATA_BLOB *ppCertId);

CADES_API ALG_ID WINAPI CadesMsgGetSigningCertIdHashAlg(
    __in HCRYPTMSG hCryptMsg,
    __in DWORD dwSignatureIndex);

CADES_API CSP_BOOL WINAPI CadesMsgGetSignatureTimestamps( 
    __in HCRYPTMSG hCryptMsg,
    __in DWORD dwSignatureIndex,
    __out PCADES_BLOB_ARRAY *ppTimestamps);

CADES_API CSP_BOOL WINAPI CadesMsgGetCadesCTimestamps( 
    __in HCRYPTMSG hCryptMsg,
    __in DWORD dwSignatureIndex,
    __out PCADES_BLOB_ARRAY *ppTimestamps);

CADES_API CSP_BOOL WINAPI CadesMsgGetCertificateValues(
    __in HCRYPTMSG hCryptMsg,
    __in DWORD dwSignatureIndex,
    __out PCADES_BLOB_ARRAY *ppCertificates);

CADES_API CSP_BOOL WINAPI CadesMsgGetRevocationValues(
    __in HCRYPTMSG hCryptMsg,
    __in DWORD dwSignatureIndex,
    __out PCADES_BLOB_ARRAY *ppCRLs,
    __out PCADES_BLOB_ARRAY *ppBasicOCSPResponses);

CADES_API ALG_ID WINAPI CadesMsgGetSigningCertIdHashAlgEx(
    __in PCMSG_SIGNER_INFO pSignerInfo);

CADES_API CSP_BOOL WINAPI CadesMsgGetSignatureTimestampsEx( 
    __in PCMSG_SIGNER_INFO pSignerInfo,
    __out PCADES_BLOB_ARRAY *ppTimestamps);

CADES_API CSP_BOOL WINAPI CadesMsgGetCadesCTimestampsEx( 
    __in PCMSG_SIGNER_INFO pSignerInfo,
    __out PCADES_BLOB_ARRAY *ppTimestamps);

CADES_API CSP_BOOL WINAPI CadesMsgGetCertificateValuesEx(
    __in PCMSG_SIGNER_INFO pSignerInfo,
    __out PCADES_BLOB_ARRAY *ppCertificates);

CADES_API CSP_BOOL WINAPI CadesMsgGetRevocationValuesEx(
    __in PCMSG_SIGNER_INFO pSignerInfo,
    __out PCADES_BLOB_ARRAY *ppCRLs,
    __out PCADES_BLOB_ARRAY *ppBasicOCSPResponses);

CADES_API CSP_BOOL WINAPI CadesMsgGetSignatureTimestampsEncoded( 
    __in DWORD dwEncodingType,
    __in PBYTE pbSignerInfo,
    __in DWORD cbSignerInfo,
    __out PCADES_BLOB_ARRAY *ppTimestamps);

CADES_API CSP_BOOL WINAPI CadesMsgGetCadesCTimestampsEncoded( 
    __in DWORD dwEncodingType,
    __in PBYTE pbSignerInfo,
    __in DWORD cbSignerInfo,
    __out PCADES_BLOB_ARRAY *ppTimestamps);

CADES_API CSP_BOOL WINAPI CadesMsgGetCertificateValuesEncoded(
    __in DWORD dwEncodingType,
    __in PBYTE pbSignerInfo,
    __in DWORD cbSignerInfo,
    __out PCADES_BLOB_ARRAY *ppCertificates);

CADES_API CSP_BOOL WINAPI CadesMsgGetRevocationValuesEncoded(
    __in DWORD dwEncodingType,
    __in PBYTE pbSignerInfo,
    __in DWORD cbSignerInfo,
    __out PCADES_BLOB_ARRAY *ppCRLs,
    __out PCADES_BLOB_ARRAY *ppBasicOCSPResponses);

CADES_API ALG_ID WINAPI CadesMsgGetSigningCertIdHashAlgEncoded(
    __in DWORD dwEncodingType,
    __in PBYTE pbSignerInfo,
    __in DWORD cbSignerInfo);

// User Interface API
#if defined _WIN32
CADES_API CSP_BOOL WINAPI CadesMsgUIDisplaySignature(
    __in HCRYPTMSG hCryptMsg,
    __in DWORD dwSignatureIndex,
    __in_opt HWND hwndParent,
    __in_opt LPCWSTR title);

CADES_API CSP_BOOL WINAPI CadesMsgUIDisplaySignatureByHash(
    __in HCRYPTMSG hCryptMsg,
    __in DWORD dwSignatureIndex,
    __in_opt HWND hwndParent,
    __in_opt LPCWSTR title,
    __in_opt const BYTE* pbHashBlob,
    __in_opt DWORD cbHashBlob,
    __in_opt PCRYPT_ALGORITHM_IDENTIFIER pHashAlgorithm);

CADES_API CSP_BOOL WINAPI CadesMsgUIDisplaySignatures(
    __in HCRYPTMSG hCryptMsg,
    __in_opt HWND hwndParent,
    __in_opt LPCWSTR title);

CADES_API CSP_BOOL WINAPI CadesMsgUIDisplaySignaturesByHash(
    __in HCRYPTMSG hCryptMsg,
    __in_opt HWND hwndParent,
    __in_opt LPCWSTR title,
    __in_opt const BYTE* pbHashBlob,
    __in_opt DWORD cbHashBlob,
    __in_opt PCRYPT_ALGORITHM_IDENTIFIER pHashAlgorithm);

CADES_API CSP_BOOL WINAPI CadesMsgViewSignature(
    __in HCRYPTMSG hCryptMsg,
    __in DWORD dwSignatureIndex,
    __out LPCPROPSHEETPAGE **prgPropPages,
    __out DWORD *pcPropPages);

CADES_API CSP_BOOL WINAPI CadesMsgViewSignatures(
    __in HCRYPTMSG hCryptMsg,
    __out LPCPROPSHEETPAGE **prgPropPages,
    __out DWORD *pcPropPages);

CADES_API CSP_BOOL WINAPI CadesViewSignature(
    __in PCADES_VIEW_SIGNATURE_PARA pCadesViewSignaturePara,
    __in DWORD dwSignatureIndex,
    __in const BYTE *pbSignedBlob,
    __in DWORD cbSignedBlob,
    __out LPCPROPSHEETPAGE **prgPropPages,
    __out DWORD *pcPropPages);

CADES_API CSP_BOOL WINAPI CadesViewSignatureDetached(
    __in PCADES_VIEW_SIGNATURE_PARA pCadesViewSignaturePara,
    __in DWORD dwSignatureIndex,
    __in const BYTE *pbDetachedSignBlob,
    __in DWORD cbDetachedSignBlob,
    __in DWORD cToBeSigned,
    __in const BYTE *rgpbToBeSigned[],
    __in DWORD rgcbToBeSigned[],
    __out LPCPROPSHEETPAGE **prgPropPages,
    __out DWORD *pcPropPages);

CADES_API CSP_BOOL WINAPI CadesViewSignatures(
    __in PCADES_VIEW_SIGNATURE_PARA pCadesViewSignaturePara,
    __in const BYTE *pbSignedBlob,
    __in DWORD cbSignedBlob,
    __out LPCPROPSHEETPAGE **prgPropPages,
    __out DWORD *pcPropPages);

CADES_API CSP_BOOL WINAPI CadesViewSignaturesDetached(
    __in PCADES_VIEW_SIGNATURE_PARA pCadesViewSignaturePara,
    __in const BYTE *pbDetachedSignBlob,
    __in DWORD cbDetachedSignBlob,
    __in DWORD cToBeSigned,
    __in const BYTE *rgpbToBeSigned[],
    __in DWORD rgcbToBeSigned[],
    __out LPCPROPSHEETPAGE **prgPropPages,
    __out DWORD *pcPropPages);

CADES_API CSP_BOOL WINAPI CadesUIDisplaySignature(
    __in PCADES_VIEW_SIGNATURE_PARA pCadesViewSignaturePara,
    __in DWORD dwSignatureIndex,
    __in const BYTE *pbSignedBlob,
    __in DWORD cbSignedBlob,
    __in_opt HWND hwndParent,
    __in_opt LPCWSTR title);

CADES_API CSP_BOOL WINAPI CadesUIDisplaySignatures(
    __in PCADES_VIEW_SIGNATURE_PARA pCadesViewSignaturePara,
    __in const BYTE *pbSignedBlob,
    __in DWORD cbSignedBlob,
    __in_opt HWND hwndParent,
    __in_opt LPCWSTR title);

CADES_API CSP_BOOL WINAPI CadesUIDisplaySignatureDetached(
    __in PCADES_VIEW_SIGNATURE_PARA pCadesViewSignaturePara,
    __in DWORD dwSignatureIndex,
    __in const BYTE *pbDetachedSignBlob,
    __in DWORD cbDetachedSignBlob,
    __in DWORD cToBeSigned,
    __in const BYTE *rgpbToBeSigned[],
    __in DWORD rgcbToBeSigned[],
    __in_opt HWND hwndParent,
    __in_opt LPCWSTR title);

CADES_API CSP_BOOL WINAPI CadesUIDisplaySignaturesDetached(
    __in PCADES_VIEW_SIGNATURE_PARA pCadesViewSignaturePara,
    __in const BYTE *pbDetachedSignBlob,
    __in DWORD cbDetachedSignBlob,
    __in DWORD cToBeSigned,
    __in const BYTE *rgpbToBeSigned[],
    __in DWORD rgcbToBeSigned[],
    __in_opt HWND hwndParent,
    __in_opt LPCWSTR title);

CADES_API CSP_BOOL WINAPI CadesFreeSignaturePropPages(
    __in LPCPROPSHEETPAGE *prgPropPages,
    __in DWORD pcPropPages);

#endif // _WIN32

// Simplified API

CADES_API CSP_BOOL WINAPI CadesSignMessage(
    __in PCADES_SIGN_MESSAGE_PARA pSignPara,
    __in CSP_BOOL fDetachedSignature,
    __in DWORD cToBeSigned,
    __in const BYTE* rgpbToBeSigned[],
    __in DWORD rgcbToBeSigned[],
    __out PCRYPT_DATA_BLOB *ppSignedBlob);

CADES_API CSP_BOOL WINAPI CadesSignHash(
    __in PCADES_SIGN_MESSAGE_PARA pSignPara,
    __in const BYTE* pbHash,
    __in DWORD cbHash,
    __in_opt LPCSTR pszInnerContentObjID,
    __out PCRYPT_DATA_BLOB *ppSignedBlob);

CADES_API CSP_BOOL WINAPI CadesVerifyHash(
    __in PCADES_VERIFY_MESSAGE_PARA pVerifyPara,
    __in DWORD dwSignerIndex,
    __in const BYTE* pbDetachedSignBlob,
    __in DWORD cbDetachedSignBlob,
    __in const BYTE* pbHash,
    __in DWORD cbHash,
    __in PCRYPT_ALGORITHM_IDENTIFIER pHashAlgorithm,
    __out_opt PCADES_VERIFICATION_INFO *ppVerificationInfo);

CADES_API CSP_BOOL WINAPI CadesAddHashSignature(
    __in PCADES_SIGN_MESSAGE_PARA pSignPara,
    __in const BYTE* pbDetachedSignBlob,
    __in DWORD cbDetachedSignBlob,
    __in const BYTE* pbHash,
    __in DWORD cbHash,
    __out PCRYPT_DATA_BLOB *ppSignedBlob);

CADES_API CSP_BOOL WINAPI CadesVerifyMessage(
    __in PCADES_VERIFY_MESSAGE_PARA pVerifyPara,
    __in DWORD dwSignerIndex,
    __in const BYTE* pbSignedBlob,
    __in DWORD cbSignedBlob,
    __out_opt PCRYPT_DATA_BLOB* ppDecodedBlob,
    __out_opt PCADES_VERIFICATION_INFO *ppVerificationInfo);

CADES_API CSP_BOOL WINAPI CadesVerifyDetachedMessage(
    __in PCADES_VERIFY_MESSAGE_PARA pVerifyPara,
    __in DWORD dwSignerIndex,
    __in const BYTE* pbDetachedSignBlob,
    __in DWORD cbDetachedSignBlob,
    __in DWORD cToBeSigned,
    __in const BYTE* rgpbToBeSigned[],
    __in DWORD rgcbToBeSigned[],
    __out_opt PCADES_VERIFICATION_INFO *ppVerificationInfo);

CADES_API CSP_BOOL WINAPI CadesEnhanceMessage(
    __in PCADES_ENHANCE_MESSAGE_PARA pEnhancePara,
    __in DWORD dwSignerIndex,
    __in const BYTE* pbSignedBlob,
    __in DWORD cbSignedBlob,
    __out PCRYPT_DATA_BLOB* ppEnhancedBlob);

CADES_API CSP_BOOL WINAPI CadesEnhanceMessageAll(
    __in PCADES_ENHANCE_MESSAGE_PARA pEnhancePara,
    __in const BYTE* pbSignedBlob,
    __in DWORD cbSignedBlob,
    __out PCRYPT_DATA_BLOB* ppEnhancedBlob);

// Utility API

CADES_API CSP_BOOL WINAPI CadesFreeVerificationInfo(
    __in PCADES_VERIFICATION_INFO pVerificationInfo);

CADES_API CSP_BOOL WINAPI CadesFreeBlob(
    __in PCRYPT_DATA_BLOB pBlob);

CADES_API CSP_BOOL WINAPI CadesFreeBlobArray(
    __in PCADES_BLOB_ARRAY pBlobArray);

CADES_API DWORD WINAPI CadesFormatMessage(
    __in DWORD dwFlags,
    __in_opt LPCVOID lpSource,
    __in DWORD dwMessageId,
    __in DWORD dwLanguageId,
    __out LPTSTR lpBuffer,
    __in DWORD nSize,
    __in_opt va_list* Arguments);

// Convert API

CADES_API PCADES_CONVERT_CONTEXT WINAPI CadesMsgConvertCreateContext( 
    __in PCMSG_STREAM_INFO pStreamInfo,
    __in PBYTE pbDetachedMessage,
    __in DWORD cbDetachedMessage);

CADES_API CSP_BOOL WINAPI CadesMsgConvertUpdate(
    __in PCADES_CONVERT_CONTEXT pConvertContext,
    __in const BYTE* pbData,
    __in DWORD cbData,
    __in CSP_BOOL fFinal);

CADES_API CSP_BOOL WINAPI CadesMsgConvertFreeContext( 
    __in PCADES_CONVERT_CONTEXT pConvertContext);

#ifdef __cplusplus 
} /* extern "C" */
#endif // __cplusplus

#endif // _CADES_H_INCLUDED
