#ifndef _CPENROLL_H
#define _CPENROLL_H

#include<support.h>
#include <string>
#include <memory>
#include <list>
#include <vector>
#include<SecureBuffer.h>
#include<BSTR.h>

#define XECR_PKCS10_V2_0     0x1
#define XECR_PKCS7           0x2
#define XECR_CMC             0x3
#define XECR_PKCS10_V1_5     0x4
#define XECR_PKCS7_TWICE     0x5

/*! \ingroup EnrollAPI
     *  \brief �������� �������� �� ���������� � ��������� 
     *	   ���������� ������������
     *
     *  \xmlonly <locfile><header>UnixEnroll.h</header><ulib>libenroll.so</ulib></locfile>\endxmlonly
*/
class CPEnroll
{
public:
    /*! \ingroup EnrollAPI
     *  \brief ��������� �������� ������������
     *
     *  \xmlonly <locfile><header>UnixEnroll.h</header><ulib>libenroll.so</ulib></locfile>\endxmlonly
     */
    class UserCallbacks
    {
    public:
	/*! 
	 *  \brief ������ �� ���������� ��������� ����������� � 
	 *         ��������� ���������� ������������
	 *
	 *  \param pbCert   [in] ��������������� ����������
	 *  \param cbCert   [in] ����� �����������
	 *
	 *  \return true - � ������ �������� �� ��������� �����������
	 *
	 *  \note ������������� �� �����������, ���� ������������ 
	 *        put_SupressAddRootUI()
	 */
	virtual bool askPermissionToAddToRootStore( 
		const BYTE* pbCert, DWORD cbCert, bool = false) const=0;

	/*! 
	 *  \brief ������������
	 */
	virtual UserCallbacks* clone() const=0;

	/*! 
	 *  \brief ����������
	 */
	virtual ~UserCallbacks() {}
    };
public:
    

    /*! 
     *  \fn UnixEnroll::~UnixEnroll
     *  \brief ����������
     */
    virtual ~CPEnroll() {};
    /*! 
     *  \fn UnixEnroll::CPEFactory
     *  \brief ����� ��� �������� �������� ������ CPEnroll
     *  \param callbacks    [in] �������� ��� ������� ���������� �� ��������� ��������� �����������. ������������ 
     *  �� Unix-��������. ��� ������ ������ �� Unix �������� callbacks ������ ���� �����. �� Windows �������� ������������.
     *  \param handlePKCS7  [in] TRUE - ������ ����� �������� � PKCS7, FALSE - ������ ����� �������� � PKCS10.
     */
    static CPEnroll *CPEFactory(const UserCallbacks* callbacks = 0, bool handlePKCS7 = false);

    /*!
     *  \brief ���������� �������� S/MIME � ������ PKCS#10 (�� �����������)
     *
     *  \param value	[in] TRUE - ����������.
     *
     *	\return S_OK - � ������ ������ 
     */
    virtual HRESULT put_EnableSMIMECapabilities( bool value){
	UNUSED(value);
	return E_NOTIMPL;
    }
    
    /*! 
     *  \brief ������������ ������������ ���� � ���������� (�� �����������)
     *
     *  \param value	[in] TRUE - ������������, FALSE - ������� �����.
     *
     *	\return S_OK - � ������ ������ 
     */
    virtual HRESULT put_UseExistingKeySet(bool value){
	UNUSED(value);
	return E_NOTIMPL;
    }
    
    /*! 
     *  \brief ������ �������� ���-������� ��� PKCS#10
     *
     *  \param hashOid	[in] OID ���-�������.
     *
     *	\return S_OK - � ������ ������ 
     */
    virtual HRESULT put_HashAlgorithm( BSTR hashOid){
	UNUSED(hashOid);
	return E_NOTIMPL;
    }
    
    /*! 
     *  \brief ������ ��� ����������
     *
     *  ���� ��� ���������� �� ������, �� ��� ������������ ��� 
     *  ��������� GUID. 
     *
     *  \param cName	[in] ��� ����������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��� ������������� UseExistingKeySet, ���������
     *  �������� ��� ����������.
     */
    virtual HRESULT put_ContainerName( BSTR cName){
	UNUSED(cName);
	return E_NOTIMPL;
    }

    /*! 
     *  \brief ������ ��� CSP ��� �������� �����
     *
     *  ��� CSP ���������� �������� ��������� �����.
     *
     *  \param pType	[in] ��� CSP.
     *
     *	\return S_OK - � ������ ������ 
     */
    virtual HRESULT put_ProviderType( DWORD pType){
	UNUSED(pType);
	return E_NOTIMPL;
    }
    
    /*! 
     *  \brief ������ ��� CSP ��� �������� �����
     *
     *  ���������� CSP � ������� �������� �������� ����.
     *
     *  \param pName	[in] ��� CSP.
     *
     *	\return S_OK - � ������ ������ 
     */
    virtual HRESULT put_ProviderName( BSTR pName){
	UNUSED(pName);
	return E_NOTIMPL;
    }
    
    /*! 
     *  \brief ������ �������� ��������� �����
     *
     *  �� ��������� ������� ��������� ����� ��������, ��� ���
     *  ���������� ����� ������ CRYPT_EXPORTABLE. 
     *
     *  \param keyFlags	[in] ����� �������� ��������� �����.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ������ ������ ������ ������ � �������� CPGenKey() � CryptGenKey().
     */
    virtual HRESULT put_GenKeyFlags( DWORD keyFlags){
	UNUSED(keyFlags);
	return E_NOTIMPL;
    }
    
    /*! 
     *  \brief ������ ��������� ������� � ����� ��� �������� 
     *
     *  �������� �� ��������� CERT_SYSTEM_STORE_CURRENT_USER.
     *
     *  \param storeFlags [in] ����� �������� ���������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��� Unix ������ ���������� �������� ��������:
     *	    - CERT_SYSTEM_STORE_CURRENT_USER
     *	    - CERT_SYSTEM_STORE_LOCAL_MACHINE
     *  
     *  �������� �������������� ������ �������� ��������� 
     *  ������ � �������� CertOpenStore().
     */
    virtual HRESULT put_RequestStoreFlags( DWORD storeFlags){
	UNUSED(storeFlags);
	return E_NOTIMPL;
    }
    
    /*! 
     *  \brief ������ ����� �������� CSP
     *
     *  �������� �� ��������� 0.
     *
     *  \param provFlags [in] ����� �������� CSP.
     *
     *	\return S_OK - � ������ ������ 
     *  
     *  \note
     *  �������� �������������� ������ �������� CSP
     *  ������ � �������� CPAcquireContext() � CryptAcquireContext().
     */
    virtual HRESULT put_ProviderFlags( DWORD provFlags){
	UNUSED(provFlags);
	return E_NOTIMPL;
    }
    
    /*! 
     *  \brief ������ ��� ��������� �����
     *
     *  \param _dwKeySpec [in] ��� ��������� �����.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ������ ������������ ����:
     *	    - AT_KEYEXCHANGE - � ������������ ���������� ������ 
     *		����������, � ���;
     *	    - AT_SIGNATURE - ������ ���;
     *  
     *  \note
     *  ������ ��� �� �������� CPGenKey() � CryptGenKey().
     *
     *  \todo
     *  TODO:XXX � ������� �� ICertEnroll ��� �������� �� ��������� ???
     */
    virtual HRESULT put_KeySpec( DWORD _dwKeySpec){
	UNUSED(_dwKeySpec);
	return E_NOTIMPL;
    }
    
    /*! 
     *  \brief ������ ����������� ����� AT_KEYEXCHANGE
     *
     *  \param value [in] ����������� ����� AT_KEYEXCHANGE.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��� �������� ��������� ������ � ������ ���� AT_KEYEXCHANGE. ���
     *  ������ ���� AT_SIGNATURE ��� �������� ����� ���� ������������.
     *
     *  \note
     *  ���� �������� �������� FALSE (0), �� ������ �������� ��������� 
     *  �������� KeyUsage:
     *	    - CERT_DATA_ENCIPHERMENT_KEY_USAGE
     *	    - CERT_KEY_ENCIPHERMENT_KEY_USAGE
     *	    - CERT_DIGITAL_SIGNATURE_KEY_USAGE
     *	    - CERT_NON_REPUDIATION_KEY_USAGE
     *
     *  \note
     *  ���� �������� �������� TRUE (!=0), �� ������ �������� ��������� 
     *  �������� KeyUsage:
     *	    - CERT_DATA_ENCIPHERMENT_KEY_USAGE
     *	    - CERT_KEY_ENCIPHERMENT_KEY_USAGE
     */
    virtual HRESULT put_LimitExchangeKeyToEncipherment( int value){
	UNUSED(value);
	return E_NOTIMPL;
    }
    
    /*! 
     *  \brief ������ ��������� ������������� �� � ����� ��� �������� 
     *
     *  �������� �� ��������� CERT_SYSTEM_STORE_CURRENT_USER.
     *
     *  \param flags [in] ����� �������� ���������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��� Unix ������ ���������� �������� ��������:
     *	    - CERT_SYSTEM_STORE_CURRENT_USER
     *	    - CERT_SYSTEM_STORE_LOCAL_MACHINE
     *  
     *  �������� �������������� ������ �������� ��������� 
     *  ������ � �������� CertOpenStore().
     */
    virtual HRESULT put_CAStoreFlags( DWORD flags){
	UNUSED(flags);
	return E_NOTIMPL;
    }
    /*! 
     *  \brief ������ ��������� ������������ ������������ � ����� 
     *		��� �������� 
     *
     *  �������� �� ��������� CERT_SYSTEM_STORE_CURRENT_USER.
     *
     *  \param flags [in] ����� �������� ���������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��� Unix ������ ���������� �������� ��������:
     *	    - CERT_SYSTEM_STORE_CURRENT_USER
     *	    - CERT_SYSTEM_STORE_LOCAL_MACHINE
     *  
     *  �������� �������������� ������ �������� ��������� 
     *  ������ � �������� CertOpenStore().
     */
    virtual HRESULT put_MyStoreFlags( DWORD flags){
	UNUSED(flags);
	return E_NOTIMPL;
    }
    
    /*! 
     *  \brief ������ ���������� ��������� �������� ������������ � 
     *		����� ��� �������� 
     *
     *  �������� �� ��������� CERT_SYSTEM_STORE_CURRENT_USER.
     *
     *  \param flags [in] ����� �������� ���������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��� Unix ������ ���������� �������� ��������:
     *	    - CERT_SYSTEM_STORE_CURRENT_USER
     *	    - CERT_SYSTEM_STORE_LOCAL_MACHINE
     *  
     *  �������� �������������� ������ �������� ��������� 
     *  ������ � �������� CertOpenStore().
     */
    virtual HRESULT put_RootStoreFlags( DWORD flags){
	UNUSED(flags);
	return E_NOTIMPL;
    }
    
    /*! 
     *  \brief ������ ��� ��������� ������������ ������������
     *
     *  �������� �� ��������� "My".
     *
     *  \param name [in] ��� ���������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  �������� ��������� ��� ��������� 
     *  ������ � �������� CertOpenStore().
     */
    virtual HRESULT put_MyStoreName( BSTR name){
	UNUSED(name);
	return E_NOTIMPL;
    }
    
    /*! 
     *  \brief ��������� �� ������� ���������������� � ��������� 
     *		�������� �� ����������
     *
     *  �������� �� ��������� true.
     *
     *  \param value [in] ��������� �� �������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��� �������� ����� � ������� PKCS#10 �������� ����������������
     *  � ��������� ��������. �� ������ ��� ������ �� �������� ���� � ��.
     *  �� ��� ���, ���� �� �� ���������� ������ � �� ������ PKCS#7
     *  �����. �� ��������� PKCS#7 ������ � �������� ��������� 
     *  ������������ �����������, ���������������� ���������. ������,
     *  ��� ����� ������� ��� ������������ ����� ��������� �������� 
     *  ����� ����������������� ���������� �������� DeleteRequestCert
     *  � �������� false.
     */
    virtual HRESULT put_DeleteRequestCert( bool value){
	UNUSED(value);
	return E_NOTIMPL;
    }
    
    /*!
     *  \brief ��������� �� ������������� ���������� � �������� ���������
     *
     *  �������� �� ��������� false.
     *  \todo TODO:XXX � ������� �� ICertEnroll, � �������� ��� true ???
     *
     *  \param value [in] ��������� �� �������������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��������� ����������� � ��������� ������������� � ��� 
     *  ��������� � ��������� "My", � ��������, �������������
     *  ��� ���������� �������� ���������. ��� ������� �������� true,
     *  ���������� ������� ������ ����������� � ���������, �� �������� 
     *  �� ����� ���������� ������ ����, ���� �������� �������� �� 
     *  ������ ��������� ����������. � ���������, ���� ��� ��������
     *  true, �� �������� �������� (�����-�����, USB-�����, 
     *  USB-���� � �.�.) �� ���������, �� ������ ��������� �������� 
     *  ����� ����������������.
     * 
     *  \note
     *  ��� ����, ��� �� �� ���������� ������� ������ ����������� 
     *  ��������� ���������� �������� false.
     *
     *  \note
     *  ������������ ��������:
     *	    - acceptPKCS7()
     *
     *  \note
     *  ������ ����� �������� CPSetKeyParam() � CryptSetKeyParam().
     */
    virtual HRESULT put_WriteCertToCSP( bool value){
	UNUSED(value);
	return E_NOTIMPL;
    }

    /*!
     *  \brief ������ PIN (������) ����������
     *
     *  �������� �� ��������� - �� �����.
     *
     *  \param pin [in] PIN (������) ����������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ����� PIN (������) ��� �������� ������� ��� 
     *  ��������� ����������� ��� ������ � ������ CRYPT_SILENT 
     *  (��� ��� ������������� ���������� ���������� ��� ������������ 
     *  ���������� ������������ (TUI ��� GUI)).
     */
    virtual HRESULT put_PIN( const CSecurePin& pin){
	UNUSED(pin);
	return E_NOTIMPL;
    }

    /*!
     *  \brief �� ����������� ������������� ��� ��������� ���������
     *		����������� � ��������� ���������� ������������
     *
     *  �������� �� ��������� - false.
     *
     *  \param value [in] PIN (������) ����������.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��� ��������� �������� true, ����� 
     *  UnixEnroll::askPermissionToAddToRootStore()
     *  �� ����� ����������.
     */
    virtual HRESULT put_SupressAddRootUI( bool value){
	UNUSED(value);
	return E_NOTIMPL;
    }


    /*!
     *  \brief �������� ���������� � ������ �� ����������
     *
     *  \param flags [in] �������� �� ���������� ��������� (critical)
     *  \param name  [in] OID ����������
     *  \param value [in] ����������, �������������� � BASE64
     *
     *	\return S_OK - �������
     *
     *  \note
     *  ����� createRequest() ��������� ���������� � ������, � �����
     *  createPKCS10() ���.
     */
    virtual HRESULT addExtensionToRequest( LONG flags, BSTR name, BSTR value){
	UNUSED(flags);
	UNUSED(name);
	UNUSED(value);
	return E_NOTIMPL;
    }


    /*! 
     *  \brief ���������� ��� ������ ��� ��������� ����������� � 
     *		���������
     *
     *  \param pdwStatus [out] ��� ������ ��� ��������� ����������� � 
     *				���������
     *
     *	\retval S_OK		������� (� pdwStatus ���������� ��� 
     *				������)
     *	\retval E_INVALIDARG	pdwStatus ��� �� ����� (==NULL)
     */
    virtual HRESULT get_InstallToContainerStatus( DWORD *pdwStatus){
	UNUSED(pdwStatus);
	return E_NOTIMPL;
    }

     /*! 
     *  \brief ���������� ��� ����������
     *
     *	\retval S_OK		�������
     */
    virtual HRESULT get_ContainerName ( BSTR *cName )
    {
	UNUSED ( cName );
	return E_NOTIMPL;
    }


    /*! 
     *  \brief ������� ������ PKCS#10
     *
     *  \param rdn     [in]  �������������� ��� (DN) ��������� �����
     *  \param usage   [in]  ������ OID ������������ ������������� 
     *			     ����� (Extended Key Usage (EKU))
     *  \param request [out] ������, �������������� � BASE64
     *
     *	\return S_OK - �������
     *
     *  \note
     *  ���������� ���������� �������� ������� addExtensionToRequest()
     *
     *	\note
     *	���������� BSTR ������ �������, ������ ���� ����������� 
     *  �������� SysFreeString()
     */
    virtual HRESULT createPKCS10( BSTR rdn, BSTR usage, BSTR *request){
	UNUSED(rdn);
	UNUSED(usage);
	UNUSED(request);
	return E_NOTIMPL;
    }
    
    /*! \ingroup EnrollAPI
     *  \brief ������� ������ ����������
     *
     *  \param flags   [in]  ��� ������� �� ����������
     *  \param rdn     [in]  �������������� ��� (DN) ��������� �����
     *  \param usage   [in]  ������ OID ������������ ������������� 
     *			     ����� (Extended Key Usage (EKU))
     *  \param request [out] ������, �������������� � BASE64
     *
     *	\return S_OK - �������
     *
     *  \note
     *  �������������� ��������� ���� �������� �� ����������:
     *	    - XECR_PKCS10_V1_5
     *	    - XECR_PKCS10_V2_0
     *
     *  \note
     *  ��������� ���������� �������� ������� addExtensionToRequest()
     *
     *	\note
     *	���������� BSTR ������ �������, ������ ���� ����������� 
     *  �������� SysFreeString()
     */
    virtual HRESULT createRequest( LONG flags, BSTR rdn, BSTR usage, BSTR *request){
	UNUSED(flags);
	UNUSED(rdn);
	UNUSED(usage);
	UNUSED(request);
	return E_NOTIMPL;
    }
    
    /*! \ingroup EnrollAPI
     *  \brief ���������� PKCS#7 ����� �� ��
     *
     *  \param msg [in] PKCS#7 ���������, �������������� � BASE64, 
     *		        ������� �������� ���������� ��� ������� 
     *		        ������������ ��������������� �������
     *
     *	\return S_OK - �������
     *
     *  \note
     *  ������� ������������, ��� ����� ��������� �������� ����������, 
     *  ��� � ���, � ����������� �� �������� ����������� ��. ����������,
     *  ����������� �� ��������� �������� ���� �� �������, ����������
     *  � ��������� MY. �������� ���������� ���������� � ���������
     *  ROOT, ��������� ����������� ������������� �� ���������� �
     *  ��������� CA. ���� � ��������� PKCS#7 ����������� �����-����
     *  �������� ����������, �� � ������������ ������������� 
     *  �������������.
     *  ������������ ����� ��������� ��������� ��������������� 
     *  ������������, ������� �� �� �������� �� ��� ��� ���� ��������.
     *  ����� ������������ � ��������� ������������ � ��������� ROOT
     *  �� �������� ������ ��� ���� ��������.
     *
     *  \note
     *  �� ��������� ������������ ���������: MY, CA, ROOT � REQUEST, 
     *  ������ ������������ ����� �������� ����� � ������� ��������� 
     *  �������:
     *	    - put_MyStoreName()
     */
    virtual HRESULT acceptPKCS7( BSTR msg){
	UNUSED(msg);
	return E_NOTIMPL;
    }

     /*! \ingroup EnrollAPI
     *  \brief ���������� ���������� ��� ������� ������������ PKCS#7
     *
     *  ����� installPKCS7Ex � ������� �� acceptPKCS7 �� ������������
     *  ��� ��������� ������������, ���������� �� ������� ������������.
     *  �� ������������ ������ ��� ��������� ����������� ��� �������
     *  � ����������� ��������� ������������.
     *
     *  \param msg [in] PKCS#7 ���������, �������������� � BASE64, 
     *		        ������� �������� ���������� ��� ������� 
     *
     *  \param plCertEncoded [out] ����� ������������, 
     *		        ������������� � ��������� ���������
     *
     *	\retval S_OK            �������
     *	\retval ERROR_CANCELLED �������� �������� ������������� 
     *
     *  \note
     *  ���� � ��������� PKCS#7 ����������� �����-����
     *  �������� ����������, �� � ������������ ������������� 
     *  ������������� �� ��� ���������.
     */
    virtual HRESULT installPKCS7( BSTR msg){
	UNUSED(msg);
	return E_NOTIMPL;
    }

    /*! \ingroup EnrollAPI
     *  \brief ���������� ����������, �� ������� ����� �������� ������ � PKCS#7
     *  
     *
     *  \param pSignerCert  [in]  ���������� � ����������� 
     *	\retval S_OK            �������
     */
 
    virtual HRESULT SetSignerCertificate(
      /* [in] */  PCCERT_CONTEXT pSignerCert
      ){
	UNUSED(pSignerCert);
	return E_NOTIMPL;
    }

    virtual HRESULT AddCProLicenseExt(){
	return E_NOTIMPL;
    }
};

#endif /* _CPENROLL_H */
