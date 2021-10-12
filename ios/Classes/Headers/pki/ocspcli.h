#ifndef _OCSPCLI_H_INCLUDED
#define _OCSPCLI_H_INCLUDED

#if defined _WIN32
#   include <prsht.h>
#endif	/* _WIN32 */

#include<ocsp.h>
#include<cplib/Blob.h>

#if defined _WIN32 && !defined CRYPTCP && !defined OCSPCLI_STATIC
    #ifdef _CPOCSPCLIDLL
        #define OCSPCLI_CLASS __declspec(dllexport)
    #else
	#define OCSPCLI_CLASS __declspec(dllimport)
        #ifndef CP_IGNORE_PRAGMA_MANIFEST
#include<pki_ocsp_client_assembly.h>
            #ifdef _WIN64
                #pragma comment(linker,"/manifestdependency:\"type='win32' " \
                "name='" PKI_OCSP_CLIENT_ASSEMBLY_NAME_X64 "' " \
                "version='" PKI_OCSP_CLIENT_ASSEMBLY_VERSION_X64 "' " \
                "processorArchitecture='amd64' " \
                "language='*' " \
                "publicKeyToken='" PKI_OCSP_CLIENT_ASSEMBLY_PUBLICKEYTOKEN_X64 "'\"")
            #else
                #pragma comment(linker,"/manifestdependency:\"type='win32' " \
                "name='" PKI_OCSP_CLIENT_ASSEMBLY_NAME_X86 "' " \
                "version='" PKI_OCSP_CLIENT_ASSEMBLY_VERSION_X86 "' " \
                "processorArchitecture='x86' " \
                "language='*' " \
                "publicKeyToken='" PKI_OCSP_CLIENT_ASSEMBLY_PUBLICKEYTOKEN_X86 "'\"")
            #endif
        #endif
    #endif // _CPTSPCLIDLL
#else /*CRYPTCP*/
    #define OCSPCLI_CLASS 
#endif /*CRYPTCP*/

typedef enum {
    OCSPCLI_SKIP_IE_PROXY_CONFIGURATION = 0x1
} OCSPCLI_FLAGS;

namespace CryptoPro {
namespace PKI {
namespace OCSP {
namespace Client {

    class CRequest;

    class OCSPCLI_CLASS CResponse
    {
    public:
	// ����� ������:
	CResponse(void);
	~CResponse(void);

	// �����������
	CResponse(const CResponse& Response);
	CResponse& operator= (const CResponse& Response);

	void Export(unsigned char *pbContent, unsigned long *pdwLen) const;
	void Import(const unsigned char *pbContent, unsigned long dwLen,
	    const CRequest *Request = NULL);
	int Verify(PCCERT_CONTEXT pCert = NULL,
	    char *AllowedCriticalExtensions = NULL) const;
	int VerifyCertificate(PCCERT_CONTEXT pCert = NULL,
	    bool VerifyAllSR = true, HCERTSTORE *Stores = NULL,
	    unsigned long StoresNumber = 0) const;
	int VerifySR(unsigned long Index = 0,
	    char *AllowedSRCriticalExtensions = NULL,
	    bool *KnownAuthStatus = NULL) const;


	// �������� OCSP-������:
	ResponseStatus get_Status() const;
	ALG_ID get_SignatureAlgorithm() const;
	const char * get_SignatureAlgorithmOID() const;
	const CBlob& get_SignatureAlgorithmParameters() const;
	HCERTSTORE get_Certificates() const;
	const CDateTime get_ProducedAt() const;
	
	CResponderID::Type get_responderIDType() const;
	const CBlob& get_responderID() const;
	
	unsigned long get_SRNumber() const;
	unsigned long get_SRIndexByCert(
	    PCCERT_CONTEXT pCert, PCCERT_CONTEXT pIssuerCert = NULL) const;
	unsigned long get_SRIndexByCertID(const CCertID certID) const;
	PCCERT_CONTEXT get_OCSPCertificate(HCERTSTORE *Stores = NULL,
	    unsigned long StoresNumber = 0) const;

	// ���������� OCSP-������:
	bool get_HasNonce() const;
	bool VerifyNonce(const unsigned char *pbContent, unsigned long dwLen) const;
	const ASN1::CExtensions& get_AdditionalExtensions() const;
	const ASN1::CExtensions *get_SRAdditionalExtensions(
	    unsigned long Index = 0) const;

	// �������� ��������� �������:
	CCertStatus::Type get_SRStatus(unsigned long Index = 0) const;
	const CDateTime *get_SRRevTime(unsigned long Index = 0) const;
	const ASN1::CrlReason *get_SRRevReason(unsigned long Index = 0) const;

	const CCertID get_SRCertID(unsigned long Index = 0) const;
	const CDateTime get_SRThisUpdate(unsigned long Index = 0) const;
	const CDateTime *get_SRNextUpdate(unsigned long Index = 0) const;

	// ���������� ��������� �������:
	const CDateTime *get_SRArchiveCutoff(unsigned long Index = 0) const;
	const CExtHistoricalRequest *get_SRHistoricalRequest(
	    unsigned long Index = 0) const;
	const CExtCrlID *get_SRCRLReference(unsigned long Index = 0) const;

	friend class CRequest;

#if !defined UNIX
	void Display(HWND hWnd = 0, const wchar_t *Title = NULL,
	    HCERTSTORE *Stores = NULL,
	    unsigned long StoresNumber = 0) const;
	HPROPSHEETPAGE get_PropPage(HCERTSTORE *Stores = NULL,
	    unsigned long StoresNumber = 0) const;
#endif	/* !UNIX */

    private:
	void clear();
	class Impl;
	Impl *pImpl;
    };
#ifdef _WIN32
    interface IResponseHandler;
#else
    class IResponseHandler;
#endif //_WIN32

    class OCSPCLI_CLASS CRequest
    {
    public:
	enum enumAuthTypes
	{
	    atAnonymous	= 0x00,
	    atBasic	= 0x01,
	    atNTLM	= 0x02,
	    atDigest	= 0x08,
	    atNegotiate	= 0x10
	};

	enum enumCertToInclude
	{
	    incNone,
	    incCertOnly,
	    incChainExceptRoot,
	    incChainWhole,
	    incDefault = 0xff
	};

	// ����� ������:
	CRequest(void);
	CRequest(PCCERT_CONTEXT pCert, PCCERT_CONTEXT pIssuerCert = NULL);
	~CRequest(void);

	// ��� ������ ������ ���� ������ ��������� ������������, ����� ��������
	// ������������ ������ �����������.
	friend class CResponse;
	friend class CResponse::Impl;

	// �����������
	CRequest(const CRequest& Request);
	CRequest& operator= (const CRequest& Request);

	void Export(unsigned char *pbContent, unsigned long *pdwLen);
	void Import(unsigned char *pbContent, unsigned long dwLen);

	void Sign(PCCERT_CONTEXT pCert,
	    enumCertToInclude CertsToInclude = incDefault,
	    wchar_t *PinCode = NULL);
	int Verify(PCCERT_CONTEXT pCert = NULL,
	    char *AllowedCriticalExtensions = NULL, bool VerifyAllSR = true) const;
	int VerifyCertificate(PCCERT_CONTEXT pCert = NULL,
	    HCERTSTORE *Stores = NULL, unsigned long StoresNumber = 0) const;
	int VerifySR(unsigned long Index = 0,
	    char *AllowedSRCriticalExtensions = NULL) const;
	PCCERT_CONTEXT get_RequestorCertificate(HCERTSTORE *Stores = NULL,
	    unsigned long StoresNumber = 0) const;

	// �������� OCSP-�������
	ALG_ID get_SignatureAlgorithm() const;
	const char * get_SignatureAlgorithmOID() const;
	HCERTSTORE get_Certificates() const;

	void put_UseNonce(bool Value);
	bool get_UseNonce() const;

	void put_DisableProducedAtCheck(bool Value);
	bool get_DisableProducedAtCheck() const;

	void put_AdditionalExtensions(ASN1::CExtensions *Extensions);
	const ASN1::CExtensions *get_AdditionalExtensions() const;

	void put_UseAcceptableResponses(bool Value);
	bool get_UseAcceptableResponses() const;

	// ���������� 
	void AddSingleRequest();
	unsigned long get_SRNumber() const;

	// �������� ��������� ��������
	void put_SRCertIDFromCert(PCCERT_CONTEXT pCert,
	    PCCERT_CONTEXT pIssuerCert = NULL, unsigned long Index = 0,
	    const char *HashAlgorithmOID = NULL);
	void put_SRCertID(CCertID Value, unsigned long Index = 0);
	const CCertID get_SRCertID(unsigned long Index = 0) const;

	// ���������� ��������� ��������
	void put_SRHistoricalRequest(CExtHistoricalRequest *Value, unsigned long Index = 0);
	const CExtHistoricalRequest *get_SRHistoricalRequest(unsigned long Index = 0) const;

	void put_SRServiceLocatorFromCertAIA(PCCERT_CONTEXT pCert, unsigned long Index = 0);
	void put_SRServiceLocator(CExtServiceLocator *Value, unsigned long Index = 0);
	const CExtServiceLocator *get_SRServiceLocator(unsigned long Index = 0) const;

	void put_SRCRLLocatorFromCertCDP(PCCERT_CONTEXT pCert, unsigned long Index = 0);
	void put_SRCRLLocator(CExtCRLLocator *Value, unsigned long Index = 0);
	const CExtCRLLocator *get_SRCRLLocator(unsigned long Index = 0) const;

	void put_SRAdditionalExtensions(ASN1::CExtensions *Extensions, unsigned long Index = 0);
	const ASN1::CExtensions *get_SRAdditionalExtensions(unsigned long Index = 0) const;

	// ����� ��� �������� OCSP-�������
	void put_OCSPAuthType(enumAuthTypes Value);
	enumAuthTypes get_OCSPAuthType() const;

	void put_OCSPAddress(const wchar_t *Value);
	bool put_OCSPAddressFromCertAIA(
	    PCCERT_CONTEXT pCert, unsigned long Index);
	const wchar_t* get_OCSPAddress() const;

	void put_OCSPUserName(const wchar_t *Value);
	const wchar_t* get_OCSPUserName() const;

	void put_OCSPPassword(const wchar_t *Value);
	const wchar_t* get_OCSPPassword() const;

	void put_ClientCertificate(PCCERT_CONTEXT Value);
	PCCERT_CONTEXT get_ClientCertificate() const;

	void put_ProxyAuthType(enumAuthTypes Value);
	enumAuthTypes get_ProxyAuthType() const;

	void put_ProxyAddress(const wchar_t *Value);
	const wchar_t* get_ProxyAddress() const;

	void put_ProxyUserName(const wchar_t *Value);
	const wchar_t* get_ProxyUserName() const;

	void put_ProxyPassword(const wchar_t *Value);
	const wchar_t* get_ProxyPassword() const;

	void put_ResponseHandler(IResponseHandler *Value);

	void put_Flags(DWORD dwFlags);
	DWORD get_Flags() const;

	CResponse& Send(bool Verify = true);
    CBlob get_Response() const;
	unsigned long get_HTTPStatus() const;

#if !defined UNIX
	void Display(HWND hWnd = 0, const wchar_t *Title = NULL) const;
	HPROPSHEETPAGE get_PropPage() const;
#endif	/* !UNIX */

    private:
	void clear();
	class Impl;
	Impl *pImpl;
    };

    extern "C" CSP_BOOL CALLBACK IsOCSPAuthorized(PCCERT_CONTEXT pOCSPCert);

} // namespace Client
} // namespace OCSP
} // namespace PKI
} // namespace CryptoPro

#endif // _OCSPCLI_H_INCLUDED
