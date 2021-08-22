#ifndef __CPENROLL_IMPL_H__
#define __CPENROLL_IMPL_H__
#include<CPEnroll.h>

struct cpcrypt_store_handle
{
    cpcrypt_store_handle() : store_(0), trust_(false) {}
    ~cpcrypt_store_handle();

    bool open(
	const std::wstring & store,
	bool issystem,
	unsigned long flags = CERT_STORE_OPEN_EXISTING_FLAG | CERT_STORE_READONLY_FLAG);

    bool open(
	const std::wstring & store,
	unsigned long flags = CERT_STORE_OPEN_EXISTING_FLAG | CERT_STORE_READONLY_FLAG | CERT_SYSTEM_STORE_CURRENT_USER);
    HANDLE store_;
    bool trust_;
private:
    // ����������� ���������
    cpcrypt_store_handle& operator=(const cpcrypt_store_handle& handle);
    cpcrypt_store_handle(const cpcrypt_store_handle& handle);
};

class CPEnrollImpl: public CPEnroll
{
    public:
	CPEnrollImpl();

	~CPEnrollImpl();

	virtual HRESULT SetSignerCertificate(PCCERT_CONTEXT pSignerCert);
	virtual HRESULT put_HashAlgorithm( BSTR hashOid);
	virtual HRESULT AddCProLicenseExt();
    protected:
	HRESULT encodeRequestToPKCS7(std::vector<BYTE>& Request);
	HRESULT createPKCSRequest(BSTR rdn, BSTR usage, BSTR* request, 
			    bool includeAddedExtensions, int EncodeToPKCS7);
	HRESULT prepareKeyUsage(const std::string& usage, std::vector<std::string>& usageArray);
	HRESULT processPKCS7Ex(BSTR bstrData, LONG * plCertInstalled, bool bLeafPresent, std::vector<BYTE>& certificate);
	HRESULT addCertificateToRootStore(const BYTE* pbCert, DWORD cbCert) const;
	HRESULT addCertificateToCAStore(const BYTE* pbCert, DWORD cbCert) const;
	HRESULT addCertificateToStore(const BYTE* pbCert, DWORD cbCert, cpcrypt_store_handle& store) const;
	HRESULT isSelfSigned(const BYTE* pbCert, DWORD cbCert) const;
	HRESULT getVersion() const;
	HRESULT getCertificatesFromPKCS7(
	    const BYTE* pbMsg, const DWORD cbMsg,
	    HCERTSTORE& hStore) const;
	HRESULT getMessageFromBSTR(BSTR msg, std::vector<BYTE>& ret);
	HRESULT findRequestedCertificate(
	    HCERTSTORE hStore,
	    std::vector<BYTE>& certificate,
	    PCCERT_CONTEXT *cert_context = NULL) const;
        HRESULT fetchContInfoFromCertContext(PCCERT_CONTEXT pCertCtx);

	HCRYPTPROV hProv;
	DWORD dwKeySpec;
	BSTR hashAlgorithm_;
	BSTR containerName_;
	DWORD providerType_;
	BSTR providerName_;
	DWORD keyFlags_;
	DWORD requestStoreFlags_;
	DWORD rootStoreFlags_;
	DWORD myStoreFlags_;
	DWORD caStoreFlags_;
	DWORD provFlags_;
	DWORD version_;
	bool limitExchangeKeyToEncipherment_;
	BSTR myStoreName_;
	bool deleteRequest_;
	bool writeToCSP_;
	bool useExisting_;
	CSecurePin pin_;
	DWORD installToContainerStatus_;
	bool supressAddRootUi_;
	PCCERT_CONTEXT pSignerCertificate_;

	struct Extension {
	    std::string oid;
	    CSP_BOOL critical;
	    std::vector<BYTE> value;
	    std::string value_string;

	    Extension() {
	    }

	    Extension( 
		const char* argOid,
		LONG argCritical,
		const std::vector<BYTE>& argValue,
		const std::string &value_string = std::string())
	    : oid(argOid), critical(argCritical), value(argValue), value_string(value_string) {
	    }
	};

	std::list<Extension> extensions_;
	std::auto_ptr<UserCallbacks> userCallbacks_;
};

#endif
