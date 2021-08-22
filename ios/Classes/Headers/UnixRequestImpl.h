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
 * \brief ��������� �������� � �� �� ���������� ����������
 *
 */

#ifndef __URL_REQUEST_IMPL_H__
#define __URL_REQUEST_IMPL_H__

#include<UnixRequest.h>
#include<WinCryptEx.h>

#ifdef _WIN32
#   define snprintf(buf,count,...) _snprintf_s(buf,count,_TRUNCATE,__VA_ARGS__)
#endif


class UnixRequestImpl: public UnixRequest
{
    public:
    UnixRequestImpl();

    virtual HRESULT SetCredential( 
	/* [in] */ UserCallbacks *pCallbacks,
	/* [in] */ X509EnrollmentAuthFlags AuthType,
	/* [in] */ X509EnrollmentCheckChainFlags CheckChainType,
	    /* [in] */ const BSTR strCredential,
	/* [in][out] */ CSecurePin *sbPassword,
	/* [in] */ CSP_BOOL UseLocalMachineCert);

    virtual HRESULT SetCredential( 
        /* [in] */ LONG hWnd,
        /* [in] */ X509EnrollmentAuthFlags AuthType,
        /* [in] */ BSTR strCredential,
	/* [in] */ BSTR strPassword);

    virtual HRESULT GetDispositionMessage( 
	/* [retval][out] */ BSTR *pstrDispositionMessage);

    virtual ~UnixRequestImpl();
   
public:    
    static const char szBeginCert[];
    static const char szEndCert[];
    static const char szBeginCertRequest[];
    static const char szEndCertRequest[];
    static const char szBeginCRL[];
    static const char szEndCRL[];
protected:
    UserCallbacks *pCallbacks;
    LONG Disposition;
    X509EnrollmentAuthFlags AuthType;
    X509EnrollmentCheckChainFlags CheckChainType;
    std::string Credential;
    CSecurePin *sbPassword;
    CSP_BOOL UseLocalMachineCert_;
};

template <class T> class CPAutoArray
{
    private:
	T * ptr;
	CPAutoArray(const CPAutoArray & ) {};
    public:
	
	CPAutoArray(T * aPtr = 0):ptr(aPtr) {};
	T * get() { return ptr;};
	void replace (T * aPtr)
	{
	    if (ptr)
		delete [] ptr;
	    ptr = aPtr;	
	};
	~CPAutoArray() 
	{ 
	    if (ptr) 
		delete [] ptr; 
	};
};
typedef CPAutoArray<char> ACharPtr;

#endif
