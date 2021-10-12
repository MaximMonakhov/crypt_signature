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
 * \author $Author: dim $
 *
 * \brief ��������� �������� � �� �� ����������
 *
 */

#ifndef _UNIXREQUEST_H
#define _UNIXREQUEST_H

#include<stdarg.h>

#ifdef _WIN32
#include<Certsrv.h>
#endif//_WIN32
#ifdef UNIX
#include<CSP_WinCrypt.h>
#ifndef VARIANT
#   define VARIANT void*
#endif//VARIANT
#endif // UNIX

#include<SecureBuffer.h>
//#include "UnixEnroll.h"
#include<BSTR.h>
#include <vector>
#include <string>
#include<support.h>
#include <map>

#ifndef _WIN32
    typedef unsigned short VARIANT_CSP_BOOL;
#endif//_WIN32

//========= CertSrv.h ===========

// TODO:X ���� ����������� ��������� MonoTouch � ��. �������� ����� 
// ������ �� � namespace ru::CryptoPro

#define PROPTYPE_LONG	     0x00000001	// Signed long
#define PROPTYPE_DATE	     0x00000002	// Date+Time
#define PROPTYPE_BINARY	     0x00000003	// Binary data
#define PROPTYPE_STRING	     0x00000004	// Unicode String
#define PROPTYPE_MASK	     0x000000ff

//========= CertCli.h ===========


#define	CR_IN_BASE64HEADER	( 0 )
#define	CR_IN_BASE64	( 0x1 )
//#define	CR_IN_BINARY	( 0x2 )
//#define	CR_IN_ENCODEANY	( 0xff )
#define	CR_IN_ENCODEMASK	( 0xff )
//#define	CR_IN_FORMATANY	( 0 )
#define	CR_IN_PKCS10	( 0x100 )
//#define	CR_IN_KEYGEN	( 0x200 )
//#define	CR_IN_PKCS7	( 0x300 )
//#define	CR_IN_CMC	( 0x400 )
#define	CR_IN_FORMATMASK	( 0xff00 )
//#define	CR_IN_RPC	( 0x20000 )
//#define	CR_IN_FULLRESPONSE	( 0x40000 )
//#define	CR_IN_CRLS	( 0x80000 )
//#define	CR_IN_MACHINE	( 0x100000 )
//#define	CR_IN_ROBO	( 0x200000 )
//#define	CR_IN_CLIENTIDNONE	( 0x400000 )
//#define	CR_IN_CONNECTONLY	( 0x800000 )
//#define	CR_IN_CLIENTFLAGSMASK	( ( ( ( ( CR_IN_ENCODEMASK | CR_IN_RPC )  | CR_IN_MACHINE )  | CR_IN_CLIENTIDNONE )  | CR_IN_CONNECTONLY )  )

#define	CR_DISP_INCOMPLETE	( 0 )
#define	CR_DISP_ERROR	( 0x1 )
#define	CR_DISP_DENIED	( 0x2 )
#define	CR_DISP_ISSUED	( 0x3 )
#define	CR_DISP_ISSUED_OUT_OF_BAND	( 0x4 )
#define	CR_DISP_UNDER_SUBMISSION	( 0x5 )
#define	CR_DISP_REVOKED	( 0x6 )

#define	CR_OUT_BASE64HEADER	( 0 )
#define	CR_OUT_BASE64	( 0x1 )
#define	CR_OUT_BINARY	( 0x2 )
#define	CR_OUT_BASE64REQUESTHEADER	( 0x3 )
//#define	CR_OUT_HEX	( 0x4 )
//#define	CR_OUT_HEXASCII	( 0x5 )
#define	CR_OUT_BASE64X509CRLHEADER	( 0x9 )
//#define	CR_OUT_HEXADDR	( 0xa )
//#define	CR_OUT_HEXASCIIADDR	( 0xb )
//#define	CR_OUT_HEXRAW	( 0xc )
#define	CR_OUT_ENCODEMASK	( 0xff )
#define	CR_OUT_CHAIN	( 0x100 )
#define	CR_OUT_CRLS	( 0x200 )
//#define	CR_OUT_NOCRLF	( 0x40000000 )
//#define	CR_OUT_NOCR	( 0x80000000 )
#define CR_UNKNOWN_ERR ( -1 )
#define CR_WRONG_PASS ( -2 )
#define CR_OLD_MARKER ( -3 )
#define CR_NOT_EXIST_MARKER ( -4 )
#define CR_WRONG_MARKER_NAME ( -5 )

#define CR_PROP_NONE               0  // Invalid
//#define CR_PROP_FILEVERSION        1  // String
//#define CR_PROP_PRODUCTVERSION     2  // String
//#define CR_PROP_EXITCOUNT          3  // Long
//
//// CR_PROP_EXITCOUNT Elements:
//#define CR_PROP_EXITDESCRIPTION    4  // String, Indexed
//
//#define CR_PROP_POLICYDESCRIPTION  5  // String
//#define CR_PROP_CANAME             6  // String
//#define CR_PROP_SANITIZEDCANAME    7  // String
//#define CR_PROP_SHAREDFOLDER       8  // String
//#define CR_PROP_PARENTCA           9  // String
//#define CR_PROP_CATYPE            10  // Long
#define CR_PROP_CASIGCERTCOUNT    11  // Long

// CR_PROP_CASIGCERTCOUNT Elements:
#define CR_PROP_CASIGCERT         12  // Binary, Indexed

// CR_PROP_CASIGCERTCOUNT Elements:
#define CR_PROP_CASIGCERTCHAIN    13  // Binary, Indexed

//#define CR_PROP_CAXCHGCERTCOUNT   14  // Long
//
//// CR_PROP_CAXCHGCERTCOUNT Elements:
//#define CR_PROP_CAXCHGCERT        15  // Binary, Indexed
//
//// CR_PROP_CAXCHGCERTCOUNT Elements:
//#define CR_PROP_CAXCHGCERTCHAIN   16  // Binary, Indexed

// CR_PROP_CASIGCERTCOUNT Elements:
// Fetch only if CR_PROP_CRLSTATE[i] == CA_DISP_VALID
// May also be available if CR_PROP_CRLSTATE[i] == CA_DISP_INVALID
#define CR_PROP_BASECRL           17  // Binary, Indexed

// CR_PROP_CASIGCERTCOUNT Elements:
// Fetch only if Delta CRLs enabled && CR_PROP_CRLSTATE[i] == CA_DISP_VALID
// May also be available if CR_PROP_CRLSTATE[i] == CA_DISP_INVALID
#define CR_PROP_DELTACRL          18  // Binary, Indexed

//// CR_PROP_CASIGCERTCOUNT Elements:
//#define CR_PROP_CACERTSTATE       19  // Long, Indexed

// CR_PROP_CASIGCERTCOUNT Elements:
#define CR_PROP_CRLSTATE          20  // Long, Indexed

//#define CR_PROP_CAPROPIDMAX       21  // Long
//#define CR_PROP_DNSNAME           22  // String
//#define CR_PROP_ROLESEPARATIONENABLED 23 // Long
//#define CR_PROP_KRACERTUSEDCOUNT  24  // Long
//#define CR_PROP_KRACERTCOUNT      25  // Long

//// CR_PROP_KRACERTCOUNT Elements:
//#define CR_PROP_KRACERT           26  // Binary, Indexed

//// CR_PROP_KRACERTCOUNT Elements:
//#define CR_PROP_KRACERTSTATE      27  // Long, Indexed

//#define CR_PROP_ADVANCEDSERVER    28  // Long
#define CR_PROP_TEMPLATES         29  // String

//// CR_PROP_CASIGCERTCOUNT Elements:
//// Fetch only if CR_PROP_CRLSTATE[i] == CA_DISP_VALID
//#define CR_PROP_BASECRLPUBLISHSTATUS 30  // Long, Indexed
//
//// CR_PROP_CASIGCERTCOUNT Elements:
// Fetch only if Delta CRLs enabled && CR_PROP_CRLSTATE[i] == CA_DISP_VALID
//#define CR_PROP_DELTACRLPUBLISHSTATUS 31  // Long, Indexed

// CR_PROP_CASIGCERTCOUNT Elements:
#define CR_PROP_CASIGCERTCRLCHAIN 32  // Binary, Indexed

//// CR_PROP_CAXCHGCERTCOUNT Elements:
//#define CR_PROP_CAXCHGCERTCRLCHAIN 33 // Binary, Indexed
//
//// CR_PROP_CASIGCERTCOUNT Elements:
//#define CR_PROP_CACERTSTATUSCODE  34  // Long, Indexed
//
//// CR_PROP_CASIGCERTCOUNT Elements:
//#define CR_PROP_CAFORWARDCROSSCERT 35  // Binary, Indexed
//
//// CR_PROP_CASIGCERTCOUNT Elements:
//#define CR_PROP_CABACKWARDCROSSCERT 36  // Binary, Indexed
//
//// CR_PROP_CASIGCERTCOUNT Elements:
//#define CR_PROP_CAFORWARDCROSSCERTSTATE 37  // Long, Indexed
//
//// CR_PROP_CASIGCERTCOUNT Elements:
//#define CR_PROP_CABACKWARDCROSSCERTSTATE 38  // Long, Indexed
//
//// CR_PROP_CASIGCERTCOUNT Elements:
//#define CR_PROP_CACERTVERSION       39  // Long, Indexed
//#define CR_PROP_SANITIZEDCASHORTNAME 40  // String
//
//// CR_PROP_CERTCDPURLS Elements:
//#define CR_PROP_CERTCDPURLS 41  // String, Indexed
//
//// CR_PROP_CERTAIAURLS Elements:
//#define CR_PROP_CERTAIAURLS 42  // String, Indexed
//
//// CR_PROP_CERTAIAOCSPURLS Elements:
//#define CR_PROP_CERTAIAOCSPURLS 43  // String, Indexed
//
//// CR_PROP_LOCALENAME Elements:
//#define CR_PROP_LOCALENAME 44  // String

#define CR_PROP_TEMPLATES_CA20 300 // String

//========= CertView.h ===========


#define CV_OUT_BASE64HEADER     ( 0 )
#define CV_OUT_BASE64   ( 0x1 )
//#define CV_OUT_BINARY   ( 0x2 )
#define CV_OUT_BASE64REQUESTHEADER      ( 0x3 )
//#define CV_OUT_HEX      ( 0x4 )
//#define CV_OUT_HEXASCII ( 0x5 )
#define CV_OUT_BASE64X509CRLHEADER      ( 0x9 )
//#define CV_OUT_HEXADDR  ( 0xa )
//#define CV_OUT_HEXASCIIADDR     ( 0xb )
//#define CV_OUT_HEXRAW   ( 0xc )
//#define CV_OUT_ENCODEMASK       ( 0xff )
//#define CV_OUT_NOCRLF   ( 0x40000000 )
//#define CV_OUT_NOCR     ( 0x80000000 )


//========= UnixRequest.h ===========

#define	CR_OUT_HTML	( 0xc3 )


//========= CertCli.h ===========

/*! \ingroup EnrollAPI
 *  \brief ��� �������������� � ��
 */
#ifndef _WIN32
typedef 
enum X509EnrollmentAuthFlags
    {
		X509AuthNone		= 0,	/*!< �������������� �������� */
		X509AuthAnonymous	= 1,	/*!< ������ ��� �������������� */
		X509AuthKerberos	= 2,	/*!< �� �������������� */
		X509AuthUsername	= 4,	/*!< �������������� �� ����� � ������ */
		X509AuthCertificate	= 8		/*!< �������������� �� ����������� ����������� */
    } 	X509EnrollmentAuthFlags;
#endif//_WIN32

//========= UnixRequest.h ===========

/*! \ingroup EnrollAPI
 *  \brief ����� �������� ������������� TLS ���������� ��� 
 *         �������������� �������� � �� (� ��� ����� �� ���� ������� 
 *         ������������ �/��� ���)
 */
typedef 
enum X509EnrollmentCheckChainFlags
    {
		X509CC_None		= 0,		/*!< �������������� �������� */
		X509CC_TLS		= 1,		/*!< ����������� �������� TLS */
		X509CC_NoHostNameCheck= 2,	/*!< ������� ���� - �� ��������� DNS ��� (�����) ��.
										������ ��� ������� GetCACertificate() � GetCAProperty() */
		X509CC_NoCheck = 4	/*!< ������� ���� - �� ��������� ������.
							������ ��� ������� GetCACertificate() � GetCAProperty() */
    } 	X509EnrollmentCheckChainFlags;

/*! \ingroup EnrollAPI
 *  \brief ����� ��������� �������������� � �� (�����, ��������� 
 *         ����������, �������� ��������, �������� � ��������� �������)
 *
 *  \xmlonly <locfile><header>UnixEnroll.h</header> <ulib>libenroll.so</ulib></locfile>\endxmlonly
 * 
 * �������� ��������� �������� ICertRequest �� Microsoft CryptoAPI.
 */
class UnixRequest
{
public:	    ///// UnixRequest
    /*!
     *  \brief ����������� ������� �������������� � ��
     *
     *  \param pszCA_type_name [in] �������� ���� ��:
     *                  - "CPCA15";
     *                  - "MSCAstd";
     *                  - "MSCAent" (TODO: � ������ ������ �� ��������������);
     *
     *	\return ��������� �� ������ � ������ ������ 
     */
    static UnixRequest *URFactory(const char *pszCA_type_name);

    /*!
     *  \brief ��������� �������� ������������
     *
     *  \xmlonly <locfile><header>UnixEnroll.h</header> <ulib>libenroll.so</ulib></locfile>\endxmlonly
     */
    class UserCallbacks
    {
    public:
	/*!
	 *  \brief ������ �����/��.�������/Thumbprint ��� ����� �� ��
	 *
	 *  \param prompt   [in]  ����������� ��� ����� �����
	 *  \param strCredentialCAThumbprint [out] ����� ��� �����
	 *
	 *  \return true � ������ ��������� �����
	 *
	 *  \note ������������� �� ����������� � ������ ����:
	 *	- ������ ��� ������������ � ����������;
	 *	- �� ������������ TLS;
	 *	- ������ ������ ���� �����������.
	 *  \note  ���������� BSTR ������ ������ ���� ����������� 
	 *         �������� SysFreeString()
	 */
	virtual bool askCredentialCAThumbprint( 
		    const BSTR prompt,
		    BSTR *strCredentialCAThumbprint){
	    UNUSED(prompt);
	    UNUSED(strCredentialCAThumbprint);
	    return false;	// �� ��������� - �����
	}

	/*!
	 *  \brief ������ ������������� ������������ Thumbprint ������ 
	 *         �� ������������ ��
	 *
	 *  \param prompt   [in]  ����������� ��� ����� �����
	 *  \param strCAThumbprint [in] ����� ��� �����
	 *
	 *  \return true � ������ �������������� �������������
	 *
	 *  \note ������������� �� ����������� � ������ ����:
	 *	- �� ������������ TLS;
	 *	- ������ ������ ���� �����������.
	 */
	virtual bool showForCheckCAThumbprint( 
		    const BSTR prompt,
		    const BSTR strCAThumbprint){
	    UNUSED(prompt);
	    UNUSED(strCAThumbprint);
	    return false;	// �� ��������� - �����
	}

	/*!
	 *  \brief ������ ������/������� ��� ����� �� ��
	 *
	 *  \param prompt   [in]  ����������� ��� ����� ������
	 *  \param password [out] ����� ��� ������
	 *
	 *  \return true � ������ ��������� �����
	 *
	 *  \note ������������� �� ����������� � ������ ����
	 *	������/������ ����� � ����������.
	 */
	virtual bool askPassword( 
		    const BSTR prompt,
		    CSecurePin &password){
	    UNUSED(prompt);
	    UNUSED(password);
	    return false;	// �� ��������� - �����
	}

	/*!
	 *  \brief ������������
	 */
	virtual UserCallbacks* clone() const=0;

	/*!
	 *  \brief ����������
	 */
	virtual ~UserCallbacks() {}
    };

    virtual ~UnixRequest() {}

    /*!
     *  \brief ������������� ����������� ��������� ������ 
     *         �������������� ��� �������������� � ��
     *
     *  \param pCallbacks [in] ���������� ������� � ������������ (NULL, 
     *			���� �� ���������)
     *  \param AuthType   [in] ��� ��������������:
     *		- X509AuthAnonymous - strCredential � sbPassword 
     *		  	������ ���� NULL;
     *		- X509AuthCertificate - ������������ ���������� 
     *			�������, SHA-1 Thumbprint �������� ������� 
     *			� strCredential;
     *		- X509AuthKerberos - �� ��������������;
     *		- X509AuthUsername - �� �����/��.������� � 
     *			������/������� ���������� �������;
     *  \param CheckChainType [in] ����� �������� ����������� TLS 
     *			������� ��
     *  \param strCredential [in] ��� ������������, ��. ������� (NULL, 
     *		���� �� ��������� ��� ������������ pCallbacks)
     *  \param sbPassword [in/out] ������ ��� ������ ���������� 
     *		������� (NULL, ���� �� ��������� ��� ������������ pCallbacks)
     *  \param UseLocalMachineCert [in] ������������ ��� ��������������
     *		���������� �� ��������� ���������� ���������� ������
     *		��������� �������� ������������ (�� ��������� FALSE)
     *
     *	\return S_OK - � ������ ������ 
     */
    virtual HRESULT SetCredential(
	/* [in] */ UserCallbacks *pCallbacks,
	/* [in] */ X509EnrollmentAuthFlags AuthType,
	/* [in] */ X509EnrollmentCheckChainFlags CheckChainType,
	/* [in] */ const BSTR strCredential,
	/* [in][out] */ CSecurePin *sbPassword,
	/* [in] */ CSP_BOOL UseLocalMachineCert = FALSE) = 0;

    class AttrTriple 
    {
	public:
	    LONG Flags;
	    BSTR Name;
	    BSTR Value;

	    AttrTriple():Flags(0),Name(0),Value(0) { };
	    ~AttrTriple()
	    {
		if (Name)
		    SysFreeString(Name);
		if (Value)
		    SysFreeString(Value);
	    };
    };

    class RequestInfoEx
    {
	    bool has_items;
	public:
	    LONG Disposition;
	    std::string sent_date;
	    std::string approval_date;
	    std::string comment;
	    std::string PKCS;
	    RequestInfoEx():has_items(false),Disposition(-1),
		sent_date(),approval_date(),comment(),PKCS()
	    {
	    };
	    RequestInfoEx(
		LONG Disposition_,
		const std::string & sent_date_,
		const std::string & approval_date_,
		const std::string & comment_,
		const std::string & PKCS_
	    ): has_items(true),
	       Disposition(Disposition_),
	       sent_date(sent_date_),
	       approval_date(approval_date_),
	       comment(comment_),
	       PKCS(PKCS_)
	    {
	    };
	    bool empty()
	    {
		return !has_items;
	    };
    };

    typedef enum 
    {
	CA15None=0,
	CA15Cert=1,
	CA15Request=2,
	CA15Revoke=3
    } ReqType;

    typedef std::map<std::string,RequestInfoEx> RequestMapEx;

    /*! \ingroup EnrollAPI
     *  \brief �������� ���������� �� ��������� ������� �� ����������
     *
     *  \param strConfig [in]  URL CA 
     *  \param strTemplate [in]  ��� �������
     *  \param pstrRDN     [out] �������������� ���
     *  \param pstrEKUsage [out] ������ ����������� ������������� �����
     *  \param pKeySpec [out] KeySpec 
     *  \param pAttrs [out] ��������� �� ������ �����: ��������� ������ 
     *    UnixEnroll::addExtensionToRequest
     *
     *	\retval S_OK		�����
     *	\retval ERROR_MORE_DATA �������� *plCntAttr ���� ����, 
     *				������������ ����������� ������
     *
     *  \note  ���������� BSTR ������ ������ ���� ����������� 
     *         �������� SysFreeString()
     */

    virtual HRESULT GetRequestParams( 
	/* [in] */ BSTR strConfig,
	/* [in] */ BSTR strTemplate,
	/* [retval][out] */ BSTR *pstrRDN,
	/* [retval][out] */ BSTR *pstrEKUsage,
	/* [retval][out] */ DWORD *pKeySpec,
	/* [retval] */ std::vector<AttrTriple> *pAttrs
	){
	    UNUSED(strConfig);
	    UNUSED(strTemplate);
	    UNUSED(pstrRDN);
	    UNUSED(pstrEKUsage);
	    UNUSED(pKeySpec);
	    UNUSED(pAttrs);
	    return E_NOTIMPL; /* ��������� ������ ��� CPCA15Request */
    }

    /*!
    *	\brief �������� ������ ��������������� ��������
    *   \param strConfig [in]  URL CA 
    *  	\param Requests [out] ����� ��������������� ��������
    *	������ �������� - Disposition     */
    typedef std::map<std::string,LONG> RequestMap;

    virtual HRESULT ListRequests(
	/* [in] */ BSTR strConfig,
	/* [out] */ RequestMap &Requests 
    ) {
	UNUSED(strConfig);
	UNUSED(Requests);
	return E_NOTIMPL;
    }
    /*!
    *	\brief �������� ����������� ������ ��������������� ��������
    *   \param strConfig [in]  URL CA 
    *  	\param Requests [out] ����� ��������������� ��������
	*	\param type [in] ��� �������
    *	������ �������� - Disposition     */

    virtual HRESULT ListRequestsEx(
		BSTR strConfig,
	    RequestMapEx & Requests,
		ReqType type = CA15Request
	) {
	UNUSED(strConfig);
	UNUSED(Requests);
	UNUSED(type);
	return E_NOTIMPL;
    }

    /*! 
     *  \brief �������� ����� ������������ ������
     *
     *  \param Flags       [in]  �������������� ������ CR_OUT_HTML 
     *			(��������� ��� ������)
     *  \param pstrRequest [out] ������
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note  ���������� BSTR ������ ������ ���� ����������� 
     *         �������� SysFreeString()
     */
    virtual HRESULT GetRequest( 
	/* [in] */ LONG Flags, /* CR_OUT_HTML */
	/* [retval][out] */ BSTR *pstrRequest){
	    UNUSED(Flags);
	    UNUSED(pstrRequest);
	    return E_NOTIMPL; /* ��������� ������ ��� CPCA15Request */
    }

public:	    ///// ICertRequest
    /*!
     *  \brief ��������� ������ �� ����������
     *
     *  \param Flags         [in]  CR_IN_BASE64HEADER|CR_IN_PKCS10
     *  \param strRequest    [in]  �������� ������ � �������� �������
     *  \param strAttributes [in]  �������������� ������������� ��������, 
     *				   �������������� � ����������� �������
     *				   (�� ������ � ���������� ������ 
     *				   ������� PKCS#10)
     *  \param strConfig     [in]  ����� ������, �������� 
     *				   "https://cpca.example.ru/UI"
     *  \param pDisposition  [out] ��������� ������ �������
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note  ��������� ���������� ������ �������:
     *		- CR_DISP_DENIED - ������ ��������� ��
     *		- CR_DISP_ERROR - ��������� ������ ������� 
     *				(��������� ���������)
     *		- CR_DISP_INCOMPLETE - ��������� ������� �� ��������� 
     *		- CR_DISP_ISSUED - ���������� ����� (��� ����� ��������)
     *		- CR_DISP_ISSUED_OUT_OF_BAND - ���������� ����� 
     *				(����� �����) ��������������� �� ��, 
     *				� �� �� ����
     *		- CR_DISP_UNDER_SUBMISSION - ���������� ��������� � 
     *				�������� ������, ��������� ����� 
     *				�������� ����� ���������� ���������
     */
    virtual HRESULT Submit( 
	/* [in] */ LONG Flags, /* CR_IN_BASE64HEADER, CR_IN_PKCS10 */
	/* [in] */ const BSTR strRequest,
	/* [in] */ const BSTR strAttributes,
	/* [in] */ const BSTR strConfig,
	/* [retval][out] */ LONG *pDisposition) = 0;

    /*!
     *  \brief �������� ������ �������
     *
     *  \b �� �������������� � ������� ������
     *
     *  ������������ ��� ��������� �������� �������, ���� � �������� 
     *  ��� ��� �������� �������, ���� CR_DISP_INCOMPLETE, ���� 
     *  CR_DISP_UNDER_SUBMISSION.
     *
     *  \param RequestId    [in]  ������������� �������
     *  \param strConfig    [in]  ����� ������, �������� 
     *				   "https://cpca.example.ru/UI"
     *  \param pDisposition [out] ������� ��������� ������ �������
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note  ��������� ���������� ������ �������:
     *		- CR_DISP_DENIED - ������ ��������� ��
     *		- CR_DISP_ERROR - ��������� ������ ������� 
     *				(��������� ���������)
     *		- CR_DISP_INCOMPLETE - ��������� ������� �� ���������, 
     *				��������� ����� �������� ����� 
     *				���������� ���������
     *		- CR_DISP_ISSUED - ���������� ����� (��� ����� ��������)
     *		- CR_DISP_ISSUED_OUT_OF_BAND - ���������� ����� 
     *				(����� �����) ��������������� �� ��, 
     *				� �� �� ����
     *		- CR_DISP_UNDER_SUBMISSION - ���������� ��������� � 
     *				�������� ������, ��������� ����� 
     *				�������� ����� ���������� ���������
     */
    virtual HRESULT RetrievePending( 
	/* [in] */ LONG RequestId,
	/* [in] */ const BSTR strConfig,
	/* [retval][out] */ LONG *pDisposition) = 0;

    /*!
     *  \brief ����������� ��������� �����������
     *
     *  \b �� �������������� � ������� ������
     *
     *  ������������ ��������� ����������� � (��� ������ �����)
     *  TokenId ��������� �����
     *  \param RequestId    [in]  ������������� �������
     *  \param strConfig    [in]  ����� ������, �������� 
     *				   "https://cpca.example.ru/UI"
     *	\return S_OK - � ������ ������ 
     *
     *  \note  ��������� ���������� ������ �������:
     *		- CR_DISP_DENIED - ������ ��������� ��
     *		- CR_DISP_ERROR - ��������� ������ ������� 
     *				(��������� ���������)
     *		- CR_DISP_INCOMPLETE - ��������� ������� �� ���������, 
     *				��������� ����� �������� ����� 
     *				���������� ���������
     *		- CR_DISP_ISSUED - ���������� ����� (��� ����� ��������)
     *		- CR_DISP_ISSUED_OUT_OF_BAND - ���������� ����� 
     *				(����� �����) ��������������� �� ��, 
     *				� �� �� ����
     *		- CR_DISP_UNDER_SUBMISSION - ���������� ��������� � 
     *				�������� ������, ��������� ����� 
     *				�������� ����� ���������� ���������
     */
    virtual HRESULT AcknowledgeInstallCert( 
	/* [in] */ LONG RequestId,
	/* [in] */ const BSTR strConfig
	)
    {
	UNUSED(RequestId);
	UNUSED(strConfig);
	return E_NOTIMPL;
    }



    /*!
     *  \brief �������� ��������� ��� ����������, ���������� ��� 
     *         ��������� �������� �������
     *
     *  \b �� �������������� � ������� ������
     *
     *  GetLastStatus ���������� ��������� ��� ��������, �� �������
     *  ������ ��� � �� �������� �������.
     *
     *  \param pStatus [out] ��������� ��� ��������
     *
     *	\return S_OK - � ������ ������ 
     */
    virtual HRESULT GetLastStatus( 
	/* [retval][out] */ LONG *pStatus) {
	UNUSED(pStatus);
	return E_NOTIMPL; /* ������ �� ����� ������������� */
    }

    /*!
     *  \brief �������� ������������� �������� �������
     *
     *  \param pRequestId [out] ������������� �������
     *
     *	\return S_OK - � ������ ������ 
     */
    virtual HRESULT GetRequestId( 
	/* [retval][out] */ LONG *pRequestId) = 0;

    /*!
     *  \brief �������� ���������������� ��������� ��� �������� 
     *         ������� ��������� �������
     *
     *  \param pstrDispositionMessage [out] ���������
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note  ���������� BSTR ������ ������ ���� ����������� 
     *         �������� SysFreeString()
     */
    virtual HRESULT GetDispositionMessage( 
	/* [retval][out] */ BSTR *pstrDispositionMessage) = 0;

    /*!
     *  \brief �������� ���������� ��
     *
     *  \param fExchangeCertificate [in] FALSE - �������� ���������� 
     *			������� ������������ ��, TRUE - �������� 
     *			���������� ����������, ������������ ��� 
     *			���������� � ����� ��
     *  \param strConfig       [in]  ����� ������, �������� 
     *				   "https://cpca.example.ru/UI"
     *  \param Flags           [in]  CR_OUT_BASE64HEADER|CR_OUT_CHAIN
     *  \param pstrCertificate [out] ����������
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note  ���������� BSTR ������ ������ ���� ����������� 
     *         �������� SysFreeString()
     */
    virtual HRESULT GetCACertificate( 
	/* [in] */ LONG fExchangeCertificate, /* �� ������������ */
	/* [in] */ const BSTR strConfig,
	/* [in] */ LONG Flags, /* CR_OUT_BASE64HEADER, CR_OUT_CHAIN */
	/* [retval][out] */ BSTR *pstrCertificate) = 0;

    /*!
     *  \brief �������� ����������� ���������� ��
     *
     *  \param Flags           [in]  CR_OUT_BASE64HEADER|CR_OUT_CHAIN
     *  \param pstrCertificate [out] ����������
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note  ���������� BSTR ������ ������ ���� ����������� 
     *         �������� SysFreeString()
     */
    virtual HRESULT GetCertificate( 
	/* [in] */ LONG Flags, /* CR_OUT_HTML, CR_OUT_BASE64HEADER, CR_OUT_CHAIN */
	/* [retval][out] */ BSTR *pstrCertificate) = 0;

public:	    ///// ICertRequest2
    /*!
     *  \brief �������� ������ �������
     *
     *  \b �� �������������� � ������� ������
     *
     *  ������������ ��� ��������� �������� ������� �� ������ �������
     *  ��� ��������� ������ �������������� �����������.
     *
     *  ��������� �� �� ������, ��� � UnixRequest::RetrievePending(),
     *  � �������������� ������������ ������ �� ��������� ������ 
     *  �����������.
     *
     *  \param strConfig       [in]  ����� ������, �������� 
     *				   "https://cpca.example.ru/UI"
     *  \param RequestId       [in]  ������������� �������
     *  \param strSerialNumber [in]  �������� ����� �����������, ���� 
     *				   RequestId == -1
     *  \param pDisposition [out] ������� ��������� ������ �������
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note  ��������� ���������� ������ �������:
     *		- CR_DISP_DENIED - ������ ��������� ��
     *		- CR_DISP_ERROR - ��������� ������ ������� 
     *				(��������� ���������)
     *		- CR_DISP_INCOMPLETE - ��������� ������� �� ���������, 
     *				��������� ����� �������� ����� 
     *				���������� ���������
     *		- CR_DISP_ISSUED - ���������� ����� (��� ����� ��������)
     *		- CR_DISP_ISSUED_OUT_OF_BAND - ���������� ����� 
     *				(����� �����) ��������������� �� ��, 
     *				� �� �� ����
     *		- CR_DISP_UNDER_SUBMISSION - ���������� ��������� � 
     *				�������� ������, ��������� ����� 
     *				�������� ����� ���������� ���������
     */
    virtual HRESULT GetIssuedCertificate( 
	/* [in] */ const BSTR strConfig,
	/* [in] */ LONG RequestId,
	/* [in] */ const BSTR strSerialNumber,
	/* [retval][out] */ LONG *pDisposition){
	UNUSED(strConfig);
	UNUSED(RequestId);
	UNUSED(strSerialNumber);
	UNUSED(pDisposition);
	return E_NOTIMPL; /* ������ �� ����� ������������� */
    }

    /*!
     *  \brief �������� ��������� �� ������ ��� ��������� ���� ��������
     *
     *  \b �� �������������� � ������� ������
     *
     *  \param hrMessage [in] ��� ����������
     *  \param Flags     [in] ������ ���������:
     *				���� (0) - ������ ����� ���������;
     *				CR_GEMT_HRESULT_STRING - ������������� 
     *				    �������� ��� ���������� � ���������� 
     *				    � ����������������� ����;
     *  \param pstrErrorMessageText [out] ���������
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note  ���������� BSTR ������ ������ ���� ����������� 
     *         �������� SysFreeString()
     */
    virtual HRESULT GetErrorMessageText( 
	/* [in] */ LONG hrMessage,
	/* [in] */ LONG Flags,
	/* [retval][out] */ BSTR *pstrErrorMessageText){
	UNUSED(hrMessage);
	UNUSED(Flags);
	UNUSED(pstrErrorMessageText);
	return E_NOTIMPL; /* ������ �� ����� ������������� */
    }
    /*!
     *  \brief ���������������� ������������     
     *  \param bstrConfig       [in]  ����� ������, �������� "https://cpca.example.ru/UI"
     *  \param pUserInfo       [in] ������ � ������������ 
     *			    ������� �� ���� ��
    *
     *	\return S_OK - � ������ ������ 
     *
     */
    virtual HRESULT RegisterUser( 
	/* [in] */ BSTR bstrConfig,
	/* [in] */ void * pUserInfo
	)
    {
	UNUSED(bstrConfig);
	UNUSED(pUserInfo);
	return E_NOTIMPL; /* ��������� ��� CPCA1.5 */
    }
    /*!
     *  \brief �������� ������ ����� ����������� ������������     
     *  \param bstrConfig       [in]  ����� ������, �������� 
     *  \param pUserInfo       [in][out] ������ � ������������ 
     *			    ������� �� ���� ��
    *
     *	\return S_OK - � ������ ������ 
     *
     */
    virtual HRESULT GetUserRegisterInfo( 
	/* [in] */ BSTR bstrConfig,
	/* [in] */ void * pUserInfo
	)
    {
	UNUSED(bstrConfig);
	UNUSED(pUserInfo);
	return E_NOTIMPL; /* ��������� ��� CPCA1.5 */
    }

    /*!
     *  \brief �������� ������ ����� ����������� ������������     
     *  \param bstrConfig	    [in]  ����� ������, �������� 
     *  \param pUserRegisterId	    [out] ID ������� �� ����������� ������������
     *  \param pUserRegisterStatus  [out] ������ ������� �� ����������� ������������
     *  		� ������ �������� � ������ ����������� ����������� ��� ������
     *  		��������� �������� :
     *  		CR_UNKNOWN_ERR - ����������� ������
     *  		CR_WRONG_PASS - ������ �������� ������
     *  		CR_OLD_MARKER - ������������ ������ �������
     *  		CR_NOT_EXIST_MARKER - ������ �������������� ������ �������
     *  		CR_WRONG_MARKER_NAME - ������ � ����� ������� �������
     *	\return S_OK - � ������ ������ 
     *
     */
    virtual HRESULT GetUserRegisterStatus( 
	/* [in] */ BSTR bstrConfig,
	/* [in] */ LONG * pUserRegisterId,
	/* [in] */ LONG * pUserRegisterStatus
	)
    {
	UNUSED(bstrConfig);
	UNUSED(pUserRegisterId);
	UNUSED(pUserRegisterStatus);
	return E_NOTIMPL; /* ��������� ��� CPCA1.5 */
    }


    /*!
     *  \brief ���������� �������� ��
     *
     *  ���� ����� ������������� ��������� ������ ICertAdmin2::GetCAProperty
     *  Microsoft CryptoAPI, ������ �������� ������� ������ �� 
     *  msdn.microsoft.com.
     *
     *  \param strConfig [in] ����� ������, �������� 
     *				   "https://cpca.example.ru/UI"
     *  \param PropId    [in] ��. ��������. ��������������:
     *		- CR_PROP_CASIGCERTCOUNT - ���-�� ������ �� (LONG);
     *		- CR_PROP_CASIGCERTCHAIN - ������� PropIndex ����� �� (BINARY);
     *		- CR_PROP_BASECRL - ��� PropIndex ����� �� (BINARY);
     *		- CR_PROP_DELTACRL - ���������� ��� PropIndex ����� �� (BINARY);
     *		- CR_PROP_TEMPLATES - ������ �������� �� (STRING);
     *  \param PropIndex [in] ����������� � ���� ����� ��������;
     *  \param PropType  [in] ��� ��������. ��������������:
     *		- PROPTYPE_LONG;
     *		- PROPTYPE_BINARY;
     *		- PROPTYPE_STRING;
     *  \param Flags     [in] ��������� ��������������. ��������������:
     *		- CV_OUT_BASE64HEADER;
     *		- CV_OUT_BASE64REQUESTHEADER;
     *		- CV_OUT_BASE64X509CRLHEADER;
     *  \param pvarPropertyValue [out] ��������
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note  ���������� BSTR ������ ������ ���� ����������� 
     *         �������� SysFreeString()
     */
    virtual HRESULT GetCAProperty( 
	/* [in] */ const BSTR strConfig,
	/* [in] */ LONG PropId, /* CR_PROP_BASECRL, CR_PROP_DELTACRL, CR_PROP_TEMPLATES */
	/* [in] */ LONG PropIndex, 
	/* [in] */ LONG PropType, /* PROPTYPE_BINARY, PROPTYPE_STRING */
	/* [in] */ LONG Flags, /* CV_OUT_BASE64HEADER, CV_OUT_BASE64REQUESTHEADER, CV_OUT_BASE64X509CRLHEADER */
	/* [retval][out] */ VARIANT *pvarPropertyValue) = 0;

    /*!
     *  \brief ���������� ������ �������� ��
     *
     *  \b �� �������������� � ������� ������
     *
     *  \param strConfig  [in] ����� ������, �������� 
     *				   "https://cpca.example.ru/UI"
     *  \param PropId     [in] ��. ��������. �������� ������ 
     *		UnixRequest::GetCAProperty � ICertAdmin2::GetCAProperty
     *  \param pPropFlags [out] ������
     *
     *	\return S_OK - � ������ ������ 
     */
    virtual HRESULT GetCAPropertyFlags( 
	/* [in] */ const BSTR strConfig,
	/* [in] */ LONG PropId,
	/* [retval][out] */ LONG *pPropFlags){
	UNUSED(strConfig);
	UNUSED(PropId);
	UNUSED(pPropFlags);
	return E_NOTIMPL; /* ������ �� ����� ������������� */
    }

    /*!
     *  \brief ���������� ������������ ��� �������� ��
     *
     *  \b �� �������������� � ������� ������
     *
     *  \param strConfig  [in] ����� ������, �������� 
     *				   "https://cpca.example.ru/UI"
     *  \param PropId     [in] ��. ��������. �������� ������ 
     *		UnixRequest::GetCAProperty � ICertAdmin2::GetCAProperty
     *  \param pstrDisplayName [out] ������������ ���
     *
     *	\return S_OK - � ������ ������ 
     */
    virtual HRESULT GetCAPropertyDisplayName( 
	/* [in] */ const BSTR strConfig,
	/* [in] */ LONG PropId,
	/* [retval][out] */ BSTR *pstrDisplayName){
	UNUSED(strConfig);
	UNUSED(PropId);
	UNUSED(pstrDisplayName);
	return E_NOTIMPL; /* ������ �� ����� ������������� */
    }

    /*!
     *  \brief ���������� ������ ����, ������� ���� �������� �� ��
     *
     *  \b �� �������������� � ������� ������
     *
     *  \param PropId    [in] ��. ��������
     *  \param PropIndex [in] ����������� � ���� ����� ��������
     *  \param PropType  [in] ��� ��������
     *  \param Flags     [in] ��������� ������ ��������
     *  \param pvarPropertyValue [out] ��������
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note  ���������� BSTR ������ ������ ���� ����������� 
     *         �������� SysFreeString()
     */
    virtual HRESULT GetFullResponseProperty( 
	/* [in] */ LONG PropId,
	/* [in] */ LONG PropIndex,
	/* [in] */ LONG PropType,
	/* [in] */ LONG Flags,
	/* [retval][out] */ VARIANT *pvarPropertyValue){
	UNUSED(PropId);
	UNUSED(PropIndex);
	UNUSED(PropType);
	UNUSED(Flags);
	UNUSED(pvarPropertyValue);
	return E_NOTIMPL; /* ������ �� ����� ������������� */
    }

public:	    ///// ICertRequest3
    /*!
     *  \brief ������������� ��������� ������ 
     *         �������������� ��� �������������� � ��
     *
     *  \param hWnd [in] ���������� ����, �� Unix �� ������������.
     *  \param AuthType   [in] ��� ��������������:
     *		- X509AuthAnonymous - strCredential � sbPassword 
     *		  	������ ���� NULL;
     *		- X509AuthCertificate - ������������ ���������� 
     *			�������, SHA-1 Thumbprint �������� ������� 
     *			� strCredential;
     *		- X509AuthKerberos - �� ��������������;
     *		- X509AuthUsername - �� �����/��.������� � 
     *			������/������� ���������� �������;
     *  \param strCredential [in] ��� ������������, ��. ������� ��� 
     *		Thumbprint ����������� ����������� (NULL, 
     *		���� �� ���������)
     *  \param strPassword [in] ������ ��� ������ ���������� 
     *		������� (NULL, ���� �� ���������)
     *
     *	\return S_OK - � ������ ������ 
     */
    virtual HRESULT SetCredential( 
        /* [in] */ LONG hWnd,
        /* [in] */ X509EnrollmentAuthFlags AuthType,
        /* [in] */ BSTR strCredential,
	/* [in] */ BSTR strPassword) = 0;
    /*!
     *  \brief �������� ������������� �������� ������� � ���� ������
     *
     *  \b �� �������������� � ������� ������
     *
     *  \param pstrRequestId [out] ������������� �������
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note  ���������� BSTR ������ ������ ���� ����������� 
     *         �������� SysFreeString()
     */
    virtual HRESULT GetRequestIdString( 
	/* [retval][out] */ BSTR *pstrRequestId){
	UNUSED(pstrRequestId);
	return E_NOTIMPL; /* ������ �� ����� ������������� */
    }

    /*!
     *  \brief �������� ������ �������
     *
     *  \b �� �������������� � ������� ������
     *
     *  ������������ ��� ��������� �������� �������, �� ������ �������
     *  ��� ��������� ������ ���������� �������������� �����������.
     *
     *  ��������� ���� ������, ��� � UnixRequest::RetrievePending(),
     *  � �������������� ������������ ������ �� ��������� ������ 
     *  �����������.
     *
     *  \param strConfig       [in]  ����� ������, �������� 
     *				   "https://cpca.example.ru/UI"
     *  \param strRequestId    [in]  ������������� ������� � ���� ������
     *  \param strSerialNumber [in]  �������� ����� �����������, ���� 
     *				   RequestId == -1. ������� �� �������
     *                             ����� ���������������� ����, ��� 
     *				   ������������� ����� ���� ��������� 
     *				   �� ����� ���� ����������� ����
     *  \param pDisposition [out] ������� ��������� ������ �������
     *
     *	\return S_OK - � ������ ������ 
     *
     *  \note  ��������� ���������� ������ �������:
     *		- CR_DISP_DENIED - ������ ��������� ��
     *		- CR_DISP_ERROR - ��������� ������ ������� 
     *				(��������� ���������)
     *		- CR_DISP_INCOMPLETE - ��������� ������� �� ���������, 
     *				��������� ����� �������� ����� 
     *				���������� ���������
     *		- CR_DISP_ISSUED - ���������� ����� (��� ����� ��������)
     *		- CR_DISP_ISSUED_OUT_OF_BAND - ���������� ����� 
     *				(����� �����) ��������������� �� ��, 
     *				� �� �� ����
     *		- CR_DISP_UNDER_SUBMISSION - ���������� ��������� � 
     *				�������� ������, ��������� ����� 
     *				�������� ����� ���������� ���������
     */
    virtual HRESULT GetIssuedCertificate2( 
	/* [in] */ BSTR strConfig,
	/* [in] */ BSTR strRequestId,
	/* [in] */ BSTR strSerialNumber,
	/* [retval][out] */ LONG *pDisposition){
	UNUSED(strConfig);
	UNUSED(strRequestId);
	UNUSED(strSerialNumber);
	UNUSED(pDisposition);
	return E_NOTIMPL; /* ������ �� ����� ������������� */
    }

    /*!
     *  \brief �������� ������� ���������� �������� ������� 
     *         ������������ �������
     *
     *  \b �� �������������� � ������� ������
     *
     *  \param pValue [out] ������� ����������
     *
     *	\return S_OK - � ������ ������ 
     */
    virtual HRESULT GetRefreshPolicy( 
	/* [retval][out] */ VARIANT_CSP_BOOL *pValue){
	UNUSED(pValue);
	return E_NOTIMPL; /* ������ �� ����� ������������� */
    }

};
#endif /* _UNIXEREQUEST_H */
