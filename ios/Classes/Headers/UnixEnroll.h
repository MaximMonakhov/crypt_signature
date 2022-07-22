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
 * \version $Revision: 127051 $
 * \date $Date:: 2015-09-09 05:08:20 -0700#$
 * \author $Author: pav $
 *
 * \brief ��������� �������� �� ����������
 *
 */

#ifndef _UNIXENROLL_H
#define _UNIXENROLL_H

#include <string>
#include <memory>
#include <list>
#include <vector>
#include<CSP_WinCrypt.h>
#include<SecureBuffer.h>
#include<BSTR.h>
#include<CPEnrollImpl.h>

#if __GNUC__==2
typedef std::basic_string <wchar_t> std::wstring;
#endif
#ifdef ANDROID
namespace std {
	typedef basic_string<wchar_t> wstring;
}
#endif

// TODO:X ���� ����������� ��������� MonoTouch � ��. �������� ����� 
// ������ �� � namespace ru::CryptoPro

#define XECR_PKCS10_V2_0     0x1
#define XECR_PKCS7           0x2
#define XECR_CMC             0x3
#define XECR_PKCS10_V1_5     0x4

// BSTR SysAllocStringLen( const wchar_t *str, unsigned int cch);

/*! \ingroup EnrollAPI
 *  \brief �������� �������� �� ���������� � ��������� 
 *	   ���������� ������������
 *
 *  \xmlonly <locfile><header>UnixEnroll.h</header> <ulib>libenroll.so</ulib></locfile>\endxmlonly
 * 
 * �������� ��������� �������� ICertEnroll �� Microsoft CryptoAPI.
 */
class UnixEnroll: public CPEnrollImpl
{
protected:
	bool handlePKCS7_;
public:
    /*! 
     *  \brief �����������
     *
     *  \param callbacks    [in] ������� ������� � ������������
     *  \param handlePKCS7  [in] � ������ ������ �� ������������
     */
    UnixEnroll(
	const CPEnroll::UserCallbacks& callbacks,
	bool handlePKCS7 = false);

    /*! 
     *  \fn UnixEnroll::~UnixEnroll
     *  \brief ����������
     */
    ~UnixEnroll();

    /*!
     *  \brief ���������� �������� S/MIME � ������ PKCS#10 (�� �����������)
     *
     *  \param value	[in] true - ����������.
     *
     *	\return S_OK - � ������ ������ 
     */
    virtual HRESULT put_EnableSMIMECapabilities(bool value)
    { 
	UNUSED(value);
	return S_OK;
    }
    
    /*! 
     *  \brief ������������ ������������ ���� � ���������� (�� �����������)
     *
     *  \param value	[in] true - ������������, false - ������� �����.
     *
     *	\return S_OK - � ������ ������ 
     */
    virtual HRESULT put_UseExistingKeySet(bool value);
    
    /*! 
     *  \brief ������ ��� ����������
     *
     *  ���� ��� ���������� �� ������, �� ��� ������������ ��� 
     *  ��������� GUID. 
     *
     *  \param cName	[in] ��� ����������.
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ��� ������������� UseExistingKeySet, ���������
     *  �������� ��� ����������.
     */
    virtual HRESULT put_ContainerName( BSTR cName)
    {
	containerName_ = SysAllocString(cName);
	return S_OK;
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
    virtual HRESULT put_ProviderType( DWORD pType)
    {
	providerType_ = pType;
	return S_OK;
    }
    
    /*! 
     *  \brief ������ ��� CSP ��� �������� �����
     *
     *  ���������� CSP, � ������� �������� �������� ����.
     *
     *  \param pName	[in] ��� CSP.
     *
     *	\return S_OK - � ������ ������ 
     */
    virtual HRESULT put_ProviderName( BSTR pName)
    {
	providerName_ = SysAllocString(pName);
	return S_OK;
    }
    
    /*! 
     *  \brief ������ �������� ��������� �����
     *
     *  �� ��������� ������� ��������� ����� ��������. ��� ���
     *  ���������� ������� ������������ ���� CRYPT_EXPORTABLE. 
     *
     *  \param keyFlags	[in] ����� �������� ��������� �����.
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note
     *  ������ ������ ������ ������ � �������� CPGenKey() � CryptGenKey().
     */
    virtual HRESULT put_GenKeyFlags( DWORD keyFlags)
    {
	keyFlags_ = keyFlags;
	return S_OK;
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
    virtual HRESULT put_RequestStoreFlags( DWORD storeFlags)
    {
	requestStoreFlags_ = storeFlags;
	return S_OK;
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
    virtual HRESULT put_ProviderFlags( DWORD provFlags)
    {
	provFlags_ |= provFlags; /* TODO:XXX ������ OR ??? */
	return S_OK;
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
     *  ������ ����� �������� CPGenKey() � CryptGenKey().
     */
     /*
     *  TODO:XXX � ������� �� ICertEnroll ��� �������� �� ��������� ???
     */
    virtual HRESULT put_KeySpec( DWORD _dwKeySpec)
    {
	dwKeySpec = _dwKeySpec;
	return S_OK;
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
     *  ���� �������� �������� 0 (false), �� ������ �������� ��������� 
     *  �������� KeyUsage:
     *	    - CERT_DATA_ENCIPHERMENT_KEY_USAGE
     *	    - CERT_KEY_ENCIPHERMENT_KEY_USAGE
     *	    - CERT_DIGITAL_SIGNATURE_KEY_USAGE
     *	    - CERT_NON_REPUDIATION_KEY_USAGE
     *
     *  \note
     *  ���� �������� �������� �� 0 (true), �� ������ �������� ��������� 
     *  �������� KeyUsage:
     *	    - CERT_DATA_ENCIPHERMENT_KEY_USAGE
     *	    - CERT_KEY_ENCIPHERMENT_KEY_USAGE
     */
    virtual HRESULT put_LimitExchangeKeyToEncipherment( int value)
    {
	limitExchangeKeyToEncipherment_ = value ? true : false;
	return S_OK;
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
    virtual HRESULT put_CAStoreFlags( DWORD flags)
    {
	caStoreFlags_ = flags;
	return S_OK;
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
    virtual HRESULT put_MyStoreFlags( DWORD flags)
    {
	myStoreFlags_ = flags;
	return S_OK;
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
    virtual HRESULT put_RootStoreFlags( DWORD flags)
    {
	rootStoreFlags_ = flags;
	return S_OK;
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
    virtual HRESULT put_MyStoreName( BSTR name)
    {
	myStoreName_ = SysAllocString(name);
	return S_OK;
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
     *  ������������ �����������, ���������������� ���������.
     *  ��� ����� ������� ��� ������������ ����� ��������� �������� 
     *  ����� ����������������� ���������� �������� DeleteRequestCert
     *  � �������� false.
     */
    virtual HRESULT put_DeleteRequestCert( bool value)
    {
	deleteRequest_ = value;
	return S_OK;
    }
    
    /*!
     *  \brief ��������� �� ������������� ���������� � �������� ���������
     *
     *  �������� �� ��������� false.                                     
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
     *  �� ����� ���������� ������ ���� � ��� ������, ���� �������� �������� �� 
     *  ������ ��������� ����������. � ���������, ���� ��� ��������
     *  true, �� �������� �������� (�����-�����, USB-�����, 
     *  USB-���� � �.�.) �� ���������, �� ������ ��������� �������� 
     *  ����� ����������������.
     * 
     *  \note
     *  ��� ����, ����� �� ���������� ������� ������ ����������� 
     *  ��������� ���������� �������� false.
     *
     *  \note
     *  ������������ ��������:
     *	    - acceptPKCS7()
     *
     *  \note
     *  ������ ����� �������� CPSetKeyParam() � CryptSetKeyParam().
     */
     /*
     *  �������� �� ��������� false.
     *  TODO:XXX � ������� �� ICertEnroll, � �������� ��� true ???
     */
    virtual HRESULT put_WriteCertToCSP( bool value)
    {
	writeToCSP_ = value;
	return S_OK;
    }
    
    /*!
     *  \brief ������ PIN (������) ����������
     *
     *  �������� �� ��������� �� ������.
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
    virtual HRESULT put_PIN( const CSecurePin& pin)
    {
	//������� ��� ��� ����� �� ����� ����, ����� �� ����� �����
	if (pin.ptr()[pin.len() - 1] != 0)
	    return NTE_BAD_DATA;
	pin_.copy(pin);
	return S_OK;
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
    virtual HRESULT put_SupressAddRootUI( bool value)
    {
	supressAddRootUi_ = value;
	return S_OK;
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
    virtual HRESULT addExtensionToRequest( LONG flags, BSTR name, BSTR value) {
        std::vector<BYTE> binary;
        HRESULT hr = UnixEnroll::getMessageFromBSTR(value,binary);
        if( S_OK != hr ) {
            return hr;
        }
        
        const char *oid = ConvertBSTRToString(name);
        
        extensions_.push_back(Extension(oid, flags, binary) );

        delete[] oid;
        
        return S_OK;
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
    virtual HRESULT get_InstallToContainerStatus( DWORD *pdwStatus) {
        if(!pdwStatus) {
            return E_INVALIDARG;
        }
        *pdwStatus = installToContainerStatus_;
        return S_OK;
    }
    
    /*! 
     *  \brief ������� ������ PKCS#10
     *
     *  \param rdn     [in]  ���������� ��� (DN) ��������� �����
     *  \param usage   [in]  ������ OID ������������ ������������� 
     *			     ����� (Extended Key Usage (EKU))
     *  \param request [out] ������, �������������� � BASE64
     *
     *	\return S_OK - �������
     *
     *  \note
     *  ���������� ����������, �������� ������� addExtensionToRequest()
     *
     *	\note
     *	���������� BSTR ������ ������� ������ ���� ����������� 
     *  �������� SysFreeString()
     */
    virtual HRESULT createPKCS10( BSTR rdn, BSTR usage, BSTR *request) {
        return
	    createPKCSRequest(rdn, usage, request, false,false);
    }
    
    /*!
     *  \brief ������� ������ ����������
     *
     *  \param flags   [in]  ��� ������� �� ����������
     *  \param rdn     [in]  ���������� ��� (DN) ��������� �����
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
     *  ��������� ����������, �������� ������� addExtensionToRequest()
     *
     *	\note
     *	���������� BSTR ������ ������� ������ ���� ����������� 
     *  �������� SysFreeString()
     */
    virtual HRESULT createRequest( LONG flags, BSTR rdn, BSTR usage, BSTR *request) {
        if( XECR_PKCS10_V2_0 == flags || XECR_PKCS10_V1_5 == flags ) {
            return createPKCSRequest(rdn, usage, request, true, false);
        } else if (flags == XECR_PKCS7) {
            return createPKCSRequest(rdn, usage, request, true, true);
	} else if (flags == XECR_PKCS7_TWICE) {
	    return createPKCSRequest(rdn, usage, request, true, 2);
        } else
            return E_NOTIMPL;
    }
    
    /*!
     *  \brief ��������� PKCS#7 ������ �� ��
     *
     *  \param msg [in] PKCS#7 ���������, �������������� � BASE64.
     *		        �������� ���������� ��� ������� 
     *		        ������������, ��������������� �������
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
    virtual HRESULT acceptPKCS7( BSTR msg);

     /*!
     *  \brief ���������� ���������� ��� ������� ������������ PKCS#7
     *
     *  ����� installPKCS7 � ������� �� acceptPKCS7 �� ������������
     *  ��� ��������� ������������, ���������� �� ������� ������������.
     *  �� ������������ ������ ��� ��������� ����������� ��� �������
     *  � ����������� ��������� ������������.
     *
     *  \param msg [in] PKCS#7 ���������, �������������� � BASE64, 
     *		        ������� �������� ���������� ��� ������� 
     *
     *	\retval S_OK            �������
     *	\retval ERROR_CANCELLED �������� �������� ������������� 
     *
     *  \note
     *  ���� � ��������� PKCS#7 ����������� �����-����
     *  �������� ����������, �� � ������������ ������������� 
     *  ������������� �� ��� ���������.
     */
    virtual HRESULT installPKCS7( BSTR msg);
    /*!
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
     *  \param plCertInstalled [out] ����� ������������, 
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
    
    HRESULT installPKCS7Ex( BSTR msg, LONG * plCertInstalled);
     /*!
     *  \brief ���������� ����������, �� ������� ����� �������� ������ � PKCS#7
     *  
     *
     *  \param pSignerCert  [in]  ���������� � ����������� 
     *	\retval S_OK            �������
     */
 
private:
    HRESULT findCertificateInRequestStore(
	const BYTE* pbCert, DWORD cbCert,
	std::vector<BYTE>& foundedCert,
	cpcrypt_store_handle& store) const;
    HRESULT createCerificateContextFromRequestStore(
	const BYTE* pbCert, DWORD cbCert,
	PCCERT_CONTEXT& pCertContext,
	cpcrypt_store_handle& handle) const;
    HRESULT installCertificateToStore(
	PCCERT_CONTEXT pPrivateKeyCertContext,
	const BYTE* pbCert, DWORD cbCert);
    std::string prepareKeyUsageString( const std::string& usage );
    HRESULT encodeRequestToPKCS7(std::vector<BYTE>& Request); 
    HRESULT prepareKeyUsage(
	const std::string& usage,
	std::vector<std::string>& usageArray);
};

#endif /* _UNIXENROLL_H */
