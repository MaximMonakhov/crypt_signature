/* [Windows 1251]
 * [Use `iconv -f WINDOWS-1251', if needed]
 */
/*
 * Copyright(C) 2005-2011
 *
 * ���� ���� �������� ����������, ����������
 * �������������� �������� ������-���.
 *
 * ����� ����� ����� ����� �� ����� ���� �����������,
 * ����������, ���������� �� ������ �����,
 * ������������ ��� �������������� ����� ��������,
 * ���������������, �������� �� ���� � ��� ��
 * ����� ������������ ������� ��� ����������������
 * ���������� ���������� � ��������� ������-���.
 *
 * This is proprietary information of
 * Crypto-Pro company.
 *
 * Any part of this file can not be copied, 
 * corrected, translated into other languages,
 * localized or modified by any means,
 * compiled, transferred over a network from or to
 * any computer system without preliminary
 * agreement with Crypto-Pro company
 */

/*!
 * \version $Revision: 56941 $
 * \date $Date: 2009-09-11 14:09:02 +0400 (Пт, 11 сен 2009) $
 * \author $Author: dedal $
 *
 * \brief ��������� �������� � �� �� ���������� ���������� ��� Standalone CA
 *
 */

#ifndef __CPCA15_REQUEST_H__
#define __CPCA15_REQUEST_H__
#include<UnixRequestImpl.h>
#include<CPCA15UserInfo.h>

/*! \ingroup EnrollAPI
 *  \class CPCA15Request::UnixRequest 
 *  \brief \n
 *  \brief ���������� ��������� �������������� � "��������� �� 1.4/1.5"
 *
 *  \xmlonly <locfile><header>UnixEnroll.h</header> <ulib>libenroll.so</ulib></locfile>\endxmlonly
 * 
 * ������� �� ������ ���������� �����������:
 * 	- X509AuthAnonymous - �� ��������������
 * 	- X509AuthKerberos - �� ��������������
 * 	- X509AuthUsername - ������ �� ������ ���������� �������, ��� 
 * 				��������������� ��������� �����������
 * 	- X509AuthCertificate - ������ �� ����������� ��� �������� 
 * 				�����
 * 	- strConfig - ������ ���������� � https://
 * 	- GetRequest(...CR_OUT_HTML...) - ���������� PKCS#10 ������ 
 * 				� ������� HTML ��� ����������� ������
 * 	- GetCertificate(...CR_OUT_HTML...) - ���������� ���������� 
 * 				� ������� HTML ��� ����������� ������
 *
 * strConfig ������ ������ ����� ��� "https://cpca.external.example.ru/UI"
 *
 */

class CPCA15Request: public UnixRequestImpl
{
protected:
    std::string RequestId;
    std::string CertHTMLId;
    std::string strCertificate;
    std::string strSerial;
    HCERTSTORE hUserStore;
    PCCERT_CONTEXT pUserCert;
    CSP_BOOL fNeedFreeProv;
    DWORD dwCertKeySpec;
    HCRYPTPROV hUserProv;
    BSTR bstrCertHTML;
    BSTR bstrRequestHTML;

public:
    CPCA15Request():RequestId("-1"),
		     CertHTMLId("-1"),
		     strCertificate(),
		     strSerial(),
		     hUserStore(0),
		     pUserCert(0),
		     fNeedFreeProv(FALSE),
		     dwCertKeySpec(0),
		     hUserProv(0),
		     bstrCertHTML(0),
		     bstrRequestHTML(0)
    {
	
    };
    virtual HRESULT SetCredential( 
	/* [in] */ UserCallbacks *pCallbacks,
	/* [in] */ X509EnrollmentAuthFlags AuthType,
	/* [in] */ X509EnrollmentCheckChainFlags CheckChainType,
	    /* [in] */ const BSTR strCredential,
	/* [in][out] */ CSecurePin *sbPassword,
	/* [in] */ CSP_BOOL UseLocalMachineCert);

    virtual HRESULT SetCredential( 
        /* [in] */ LONG hWnd,
        /* [in] */ X509EnrollmentAuthFlags anAuthType,
        /* [in] */ BSTR strCredential,
	/* [in] */ BSTR strPassword)
    {
	return UnixRequestImpl::SetCredential(hWnd,anAuthType,strCredential,strPassword);
    };	

    virtual HRESULT GetRequestParams(
	/* [in] */ BSTR strConfig,
	/* [in] */ BSTR strTemplate,
	/* [retval][out] */ BSTR *pstrRDN,
	/* [retval][out] */ BSTR *pstrEKUsage,
	/* [retval][out] */ DWORD *pKeySpec,
	/* [retval] */ std::vector<AttrTriple> *pAttrs
	);

    virtual HRESULT Submit( 
	/* [in] */ LONG Flags, /* CR_IN_BASE64HEADER, CR_IN_PKCS10 */
	/* [in] */ const BSTR strRequest,
	/* [in] */ const BSTR strAttributes,
	/* [in] */ const BSTR strConfig,
	/* [retval][out] */ LONG *pDisposition);

    virtual HRESULT ListRequests(   
		    BSTR strConfig,
		    RequestMap & Request
		    );

    virtual HRESULT ListRequestsEx(BSTR strConfig,
		      RequestMapEx & rMap,
		      ReqType type = CA15Request);

    virtual HRESULT GetRequestId(
	      LONG* pRequestId
	      );

    virtual HRESULT GetCertificate(
       LONG Flags,
       BSTR* pstrCertificate
    );

    virtual HRESULT GetRequest(
       LONG Flags,
       BSTR* pstrRequest
    );

    virtual HRESULT GetCACertificate( 
	/* [in] */ LONG fExchangeCertificate, /* �� ������������ */
	/* [in] */ const BSTR strConfig,
	/* [in] */ LONG Flags, /* CR_OUT_BASE64HEADER, CR_OUT_CHAIN */
	/* [retval][out] */ BSTR *pstrCertificate) ;

#if 0    
    virtual HRESULT GetDispositionMessage( 
	/* [retval][out] */ BSTR *pstrDispositionMessage);
#endif	

    virtual HRESULT RetrievePending( 
	/* [in] */ LONG RequestId,
	/* [in] */ const BSTR strConfig,
	/* [retval][out] */ LONG *pDisposition);

    virtual HRESULT GetCAProperty( 
	/* [in] */ const BSTR strConfig,
	/* [in] */ LONG PropId, /* CR_PROP_BASECRL, CR_PROP_DELTACRL, CR_PROP_TEMPLATES */
	/* [in] */ LONG PropIndex, 
	/* [in] */ LONG PropType, /* PROPTYPE_BINARY, PROPTYPE_STRING */
	/* [in] */ LONG Flags, /* CV_OUT_BASE64HEADER, CV_OUT_BASE64REQUESTHEADER, CV_OUT_BASE64X509CRLHEADER */
	/* [retval][out] */ VARIANT *pvarPropertyValue);

    virtual HRESULT AcknowledgeInstallCert( 
	/* [in] */ LONG RequestId,
	/* [in] */ const BSTR strConfig
	);

    virtual HRESULT RegisterUser( 
	/* [in] */ BSTR bstrConfig,
	/* [in] */ void * pUserInfo
	);

    virtual HRESULT GetUserRegisterInfo( 
	/* [in] */ BSTR bstrConfig,
	/* [in] */ void * pUserInfo
	);

    virtual HRESULT GetUserRegisterStatus( 
	/* [in] */ BSTR bstrConfig,
	/* [in] */ LONG * pUserRegisterId,
	/* [in] */ LONG * pUserReqisterStatus
	);
    
    virtual ~CPCA15Request()
    {
	if (fNeedFreeProv && hUserProv)
	    CryptReleaseContext(hUserProv,0);
	if (pUserCert)
	    CertFreeCertificateContext(pUserCert);
	if (hUserStore)
	    CertCloseStore(hUserStore,0);
	if (bstrCertHTML)
	    SysFreeString(bstrCertHTML);
	if (bstrRequestHTML)
	    SysFreeString(bstrRequestHTML);
    };

protected:
    virtual HRESULT CA15GetEnrollParams(const std::string & UIURL,
	std::vector<std::string> &templates, 
	std::vector<std::string> &EKUs, 
	std::vector<std::string> &keySpecs, 
	std::string & strDN);
	
    virtual HRESULT GetTokenStr(std::string & strToken);
    virtual HRESULT CredPreValidate()
    {
	if (AuthType != X509AuthUsername && AuthType != X509AuthCertificate)
	    return NTE_PERM;
	if ((CheckChainType & ~X509CC_NoHostNameCheck) != X509CC_TLS)
	    return NTE_PERM;
	return S_OK;
    };
    
    virtual HRESULT RetrieveIssued( /* [in] */ const BSTR strConfig);
    virtual HRESULT PKCS10ToRequestId(BSTR bstrConfig, const std::string & PKCS10);
    virtual HRESULT MakePKCS7x2(BSTR Source,BSTR * Dest);
    virtual PCCERT_CONTEXT GetCertContext(HCERTSTORE hStore);

    virtual HRESULT encodeRequestToPKCS7(std::vector<BYTE>& Request);
    virtual HRESULT decodeRequestFromPKCS7(std::vector<BYTE>& Request);

    virtual HRESULT GetPubKeyFromPKCS7(const std::string & strPKCS7, 
	PCERT_REQUEST_INFO * pReqInfo, LONG Disp);
    virtual HRESULT GetRequestIdFromPKCS7(BSTR bstrConfig,
	BSTR bstrRequest);

    virtual HRESULT GetHTML(BSTR bstrConfig, bool get_cert, 
	const std::string & PKCS = "");

    virtual HRESULT ListRequestsAllEx(BSTR strConfig,
		      RequestMapEx & rCertMap,
		      RequestMapEx & rRequestMap,
		      RequestMapEx & rRevokedMap
		      );
    virtual void ClearCertificateData(void);
};
#endif

