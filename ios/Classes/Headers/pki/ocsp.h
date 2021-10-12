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
 * \version $Revision: 194763 $
 * \date $Date:: 2019-06-17 17:39:27 +0400#$
 * \author $Author: sdenis $
 *
 * \brief ������ ��� ������ � OCSP (Online Certificate Status Protocol)
 */

#ifndef _OCSP_H_INCLUDED
#define _OCSP_H_INCLUDED

#if !defined UNIX
#   include <windows.h>
#   include <wincrypt.h>
#endif	/* !UNIX */

#include <list>
#include <cplib/Blob.h>
#include <cplib/DateTime.h>
#include <asn1/CMP.h>
#include <asn1/algidex.h>

#if defined _WIN32 && !defined CRYPTCP && !defined OCSP_STATIC
#   if defined OCSP_DLL
#	define OCSP_CLASS __declspec(dllexport)
#	define OCSP_API __declspec(dllexport)
#	define OCSP_DATA __declspec(dllexport)
#	define OCSP_EXTERN_TEMPLATE
#   else // defined OCSP_DLL
#	define OCSP_CLASS __declspec(dllimport)
#       define OCSP_API __declspec(dllimport)
#	define OCSP_DATA __declspec(dllimport)
#       define OCSP_EXTERN_TEMPLATE extern
#       ifndef CP_IGNORE_PRAGMA_MANIFEST
#include<pki_ocsp_assembly.h>
#           ifdef _WIN64
#               pragma comment(linker,"/manifestdependency:\"type='win32' " \
                "name='" PKI_OCSP_ASSEMBLY_NAME_X64 "' " \
                "version='" PKI_OCSP_ASSEMBLY_VERSION_X64 "' " \
                "processorArchitecture='amd64' " \
                "language='*' " \
                "publicKeyToken='" PKI_OCSP_ASSEMBLY_PUBLICKEYTOKEN_X64 "'\"")
#           else
#               pragma comment(linker,"/manifestdependency:\"type='win32' " \
                "name='" PKI_OCSP_ASSEMBLY_NAME_X86 "' " \
                "version='" PKI_OCSP_ASSEMBLY_VERSION_X86 "' " \
                "processorArchitecture='x86' " \
                "language='*' " \
                "publicKeyToken='" PKI_OCSP_ASSEMBLY_PUBLICKEYTOKEN_X86 "'\"")
#           endif
#       endif
#   endif // !defined OCSP_DLL
#else // defined _WIN32 && !defined CRYPTCP && !defined OCSP_STATIC
#   define OCSP_CLASS
#   define OCSP_API
#   define OCSP_DATA
#   define OCSP_EXTERN_TEMPLATE
#   define NO_EXPIMP_CDLLLIST_ITERATORS
#endif // !defined _WIN32

namespace CryptoPro {
namespace PKI {
namespace OCSP {

/**
 * \mainpage �������������� ��������� ��������� OCSP
 *
 * ���������� OCSP ������������� �������������� ��������� ��� ������ � 
 * ���������� OCSP (Online Certificate Status Protocol, RFC 2560, 
 * draft-ietf-pkix-ocspv2-ext-01).

 * �������������� ��������� �� ������� ��������� OCSP SDK ������������ ��� ������ � ���������� �������� ������� ������������ (OCSP). ������������� ������� ���������� �������� ���������� ����� OCSP � ������ ��������� ����������� ������ � ������������ �������.
 * 
 * �������������� ��������� ������������ ����� ���������� ������� C++.
 *
 * � ���������� ����������� ��������� �������� ������, ��������� � RFC 2560 � draft-ietf-pkix-ocspv2-ext-01.
 *
 * \section contents ������
 *
 * ���������� ������������� ������ ��� ������ � OCSP ��������� � ��������:
 *  - \link CryptoPro::PKI::OCSP::CRequestMessage CRequestMessage\endlink - OCSP ������
 *  - \link CryptoPro::PKI::OCSP::CResponseMessage CResponseMessage\endlink - OCSP �����
 *
 * ����� ��������������� ��������������� ������:
 *  - \link CryptoPro::PKI::OCSP::CSingleResponse CSingleResponse\endlink - ������ ������� ���������� �����������;
 *  - \link CryptoPro::PKI::OCSP::CCertID CCertID\endlink - ������������� ����������� (�� ���� ����� � ���������� ����� ��������,
 *		    � ����� ��������� ������ �����������);
 *  - \link CryptoPro::PKI::OCSP::CCertIdWithSignature CCertIdWithSignature\endlink - ������������� ����������� (�� ����� ��������, ��������� ������
 *		    � ������� �����������);
 *  - \link CryptoPro::PKI::OCSP::CReqCert CReqCert\endlink - ���������, ���������� ������������� �����������;
 *  - \link CryptoPro::PKI::OCSP::CBasicResponse CBasicResponse\endlink - ������� �����, ������������ � OCSP_ResponseMessage;
 *  - \link CryptoPro::PKI::OCSP::CSingleResponse CSingleResponse\endlink - ����� �� ���� ������ � ������� ����������� (OCSP_SingleResponse)
 *  - \link CryptoPro::PKI::OCSP::CCertStatus CCertStatus\endlink - ������ �����������
 *
 * \section usage �����������
 *
 * ������ � ����� �������� � ���������� �������������� ��������� ��������:
 * - ���� ���� ������������, �� ��� ��������������� � ������������ ��� ������
 *   �� ������. ��� ������ ���c��������� ������ �� ����� ����� �������. ����� ����, ���
 *   ��������� ���������� �������, ���������� ���� ������ ������������;
 * - ���� ���� ������������, �� ��� ��������������� � ������������ ��� ���������
 *   �� ������. ���� ��������� ����� NULL, ��� ��������, ��� ���� �����������.
 *
 * �������� ������ ���������� (�������, ������) �������� ������ encode()/decode(),
 * ����������� �������� ����������� � DER-������������� � ������������� �� ����. ������, ����������
 * �� �����������, ������� �������� ������� (\link CryptoPro::PKI::OCSP::CRequestMessage CRequestMessage\endlink,
 * \link CryptoPro::PKI::OCSP::CBasicResponse CBasicResponse\endlink), 
 * ������������ �������� ������� � �������� ������� (sign()/verify()), � ����� ������ 
 * � ���������� � ������� (SignerInfo).
 * ��������� ����������� �� ���������, ����� ������� ������ ������, ��� ������������ ������ ������� decode(). �� ���� ��������� �������, ���� ���������� ����������� � �����������, ������������� ������������ �� ��������� �� �������������, ��� ��� ����� ������� encode() ��� ������������ ���� ��������� ������ ���� ������������������� ����������� ����������. ������������ � ����������� ��������� ��� ���� ��� �������� �������, � ������������ �� ��������� - ���, ��� ��������� ����������� ����, ��� ������ �� ����� ��������� ������������������ ����� ������� encode(). 
 *
 * ������������� �������� � ���� DER - Distinguished Encoding Rules, ������������ ���
 * �� ��������������� ����� �������� � ��������. ����� �������, ���� ��� ��������
 * ������ � �������� ����������:
 *    - �������� ��������� (������� ��� ������) � ��� ����������� � DER ��� ����������� 
 *	��������;
 *    - ��������� ��������� � DER-�������������, ��� ������������� � ���������� ������������
 *      � ��� ����������.
 *
 * ��� ������������� ������ ������ ������� ������ ���������� 
 * ����� ������������ ��������� ���� ����������: std::exception � ATL::CAtlException.
 *
 * \section s1 �������� ���������
 *
 * �������� ����� �������� ���������:
 *	-# �������� �������
 *	-# ���������� ����� � ������ ������������� (���������� ������������ ��� ���������
 *	   ������������, �������� �� ���������)
 *	-# � ������, ���� ��������� ��������� �������, ����� ������ sign()
 *	-# ����� ������ encode() ��� ��������� DER-������������� ������� � ���� �����
 *	   �������� ������
 * 
 * ������ (�������� OCSP �������):
 * \dontinclude ocsp_sample.cpp
 * \skip example_3_begin
 * \skip �������� ������ ��������
 * \until CBlob encodedRequestMessage = message.encode()
 * 
 * �������� ������ ������������� ���������:
 *	-# �������� ������� ������������� �� ���������
 *	-# ����� ������ decode(), ���������� �������� �������� DER-������������� ���������
 *	-# ����� ������� get_...() ��� ��������� ����� ���������.
 * 
 * ������ (�������� OCSP ������):
 * \dontinclude ocsp_sample.cpp
 * \skip example_4_begin
 * \skip �������� ������ �������
 * \until CBlob encodedResponseMessage = response.encode()
 */

#define sz_id_kp_OCSPSigning "1.3.6.1.5.5.7.3.9"
#define sz_id_pkix_ocsp_basic "1.3.6.1.5.5.7.48.1.1"
#define sz_id_pkix_ocsp_crl "1.3.6.1.5.5.7.48.1.3"
#define sz_id_pkix_ocsp_nonce "1.3.6.1.5.5.7.48.1.2"
#define sz_id_pkix_ocsp_service_locator "1.3.6.1.5.5.7.48.1.7"
#define sz_id_pkix_ocsp_response "1.3.6.1.5.5.7.48.1.4"
#define sz_id_pkix_ocsp_archive_cutoff "1.3.6.1.5.5.7.48.1.6"
#define sz_id_CryptoPro_ocsp_treats_exp_key_or_exp_cert_rev "1.2.643.2.2.47.1"
#define sz_id_CryptoPro_ocsp_crl_locator "1.2.643.2.2.47.2"
#define sz_id_CryptoPro_ocsp_instant_revocation_indicator "1.2.643.2.2.47.3"
#define sz_id_CryptoPro_ocsp_revocation_announcement_reference "1.2.643.2.2.47.4"
#define sz_id_CryptoPro_ocsp_historical_request "1.2.643.2.2.47.5"

/// ������ OCSP (RFC 2560, ������ 4.1.1)
enum Version
{
    Version_1 = 0,
    Version_2 = 1
};

/// C������ OCSP ������ (RFC 2560, ������ 4.2.1)
enum ResponseStatus
{
    /// ������ ��������� �������
    ResponseStatus_successful = 0,
    /// ������������ ������
    ResponseStatus_malformedRequest =  1,
    /// ������ �� ��������� ��-�� ���������� ������
    ResponseStatus_internalError = 2,
    /// ������ �������� �� ����� ��������, ���������� �����
    ResponseStatus_tryLater = 3,
    /// ������ ������ ���� ��������
    ResponseStatus_sigRequired = 5,
    /// ����������� ������� �� ����������� ������������ ����� ������
    ResponseStatus_unauthorized = 6,
    /// ������ ��� ��������� CRL
    ResponseStatus_badCRL = 8
};

class CSingleRequestList;
class CSingleRequest;

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CSingleRequest, OCSP_EXTERN_TEMPLATE, OCSP_CLASS);

class CReqCert;

/**
 * \class CRequestMessage
 * \brief ������ �� �������� ������� �����������(��) (RFC 2560 ������ 4.1.1)
 *
 * ����������� ASN.1 ��������� OCSPRequest. ������������� �������� ������� sign() �
 * �������� ������� verify(). ������� �����������, �� ���� ������������ � ������������
 * ������ ����� ��� � ������� sign() ��� � ��� ����. � ������ ������ ������ ����� �����������,
 * �� ������ - ���.
 * \sa CSingleRequest, CDllList
 */
class OCSP_CLASS CRequestMessage
{
public:
    /// ������� ������ ������
    CRequestMessage();
    /// ���������� ������
    ~CRequestMessage();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CRequestMessage( const CRequestMessage& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CRequestMessage& operator=( const CRequestMessage& src);

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encodedRequest);

    /**
     * \brief ������� �������
     *
     * \param hCryptProv [in] �������� ����������������, �������� �� �������� ����� ������
     * \param dwKeySpec [in] ���������� �����
     * \param signatureAlgorithm [in] ��������, ������� ����� �������������� ��� ������� ������
     * \param additionalCertificates [in] �������������� �����������, ������������ � ������
     *
     * \remark ������ ������� ������ ���������� ����� ���������� ���� �����, ���������������
     *		����� ������������ �������
     * \sa verify()
     */
    void sign(
	HCRYPTPROV hCryptProv,
	DWORD dwKeySpec,
	const ASN1::CAlgorithmIdentifierEx& signatureAlgorithm,
	const ASN1::CEncodedCertificateList* additionalCertificates = 0);
    /// �������� ������� ��������� (�����: ������� ����� �� ����)
    /**
     * \brief �������� ������� �������
     * 
     * \param encodedCertificate [in] �������������� �������� ������������� 
     * ����������� ��������������� ��� �������� �������
     *
     * \return true, ���� ������� ��������� �������, ����� false
     * \remark ��� ��� ������� �����������, �� ����� ������� �������
     * ���������� ��������, ��� ������ ��������. � ������ ������� ���������
     * ������������� ������ ������������ ����������.
     */
    bool verify(
	const CBlob& encodedCertificate) const;

    // get (������� ��������� ���������� ������������ �������)
    /// ���������� ������ �������
    Version get_version() const;
    /// ���������� �������������� ��� ����������� ������� (������������ ����)
    const CBlob* get_requestorName() const;
    /// ���������� ������ �������� �� ������ ��������� ������������
    const CSingleRequestList& get_requestList() const;
    /// ���������� ������ ����������, ��������� � ������
    const ASN1::CExtensions* get_requestExtensions() const;
    // ������������ ��������� ������������� ��� ������ sign()
    /**
     * \brief ���������� �������� �������
     * \remark ��� ������������ ���� ����������� ����� ������ sign()
     */
    const ASN1::CAlgorithmIdentifierEx* get_signatureAlgorithm() const;
    /**
     * \brief ���������� �������� �������� �������
     * \remark ��� ������������ ���� ����������� ����� ������ sign()
     */
    const CBlob* get_signature() const;
    /**
     * \brief ���������� ��������� � ������ �����������
     * \remark ��� ������������ ���� ����������� ����� ������ sign()
     */
    const ASN1::CEncodedCertificateList* get_signatureCerts() const;
    // set (������ ������������ ���������, NULL ������� �������)
    /// ������������� ��� ����������� ������� (������������ ����)
    void put_requestorName( const CBlob* encodedName);
    /// ������������� ������ �������� �� ������ ��������� ������������
    void put_requestList( const CSingleRequestList& requestList);
    /// ������������� ������ ���������� ��������� � ������
    void put_requestExtensions( const ASN1::CExtensions* extensions);    
private:
    void clear();
    class Impl;
    Impl* pImpl_;
};

/**
 * \brief ������ �� ������ ������ ����������� (RFC 2560, ������ 4.1.1)
 *
 * ASN.1 ��������� Request. �������� ������������� �����������, ������
 * �������� �������������, � ����������� ������ ����������.
 * \sa CRequestMessage, CReqCert
 */
class OCSP_CLASS CSingleRequest
{
public:
    CSingleRequest();
    /**
     * \brief ������� � �������������� ������
     * \param reqCert [in] ������������� �����������
     */
    CSingleRequest( const CReqCert& reqCert);

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CSingleRequest( const CSingleRequest& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CSingleRequest& operator=( const CSingleRequest& src );

    /// ���������� ������
    ~CSingleRequest();

    // get (������� ��������� ���������� ������������ �������)
    /// ���������� ������������� �����������
    const CReqCert& get_reqCert() const;
    /// ���������� ������ ����������, ������������ � ������� (������������ ����)
    const ASN1::CExtensions* get_singleRequestExtensions() const;
    // set (������ ������������ ���������, NULL ������� �������)
    /// ������������� ������ ����������, ������������ � ������� (������������ ����)
    void put_singleRequestExtensions( const ASN1::CExtensions* extensions);
private:
    void clear();
    class Impl;
    Impl* pImpl_;
};

/**
 * \class CSingleRequestList
 * \brief ������ �������� CSingleRequest
 *
 * \sa CSingleRequest, CDllList
 */
class OCSP_CLASS CSingleRequestList: public CDllList<CSingleRequest>
{
};

/**
 * \brief ASN.1 ��������� CertID. ������������� ����������� (RFC 2560, ������ 4.1.1).
 *
 * ���������� ���������������� ������ ����� � ��������� ����� �������� �����������,
 * � ����� �������� �������.
 * \remark ��� ��� � �������������� ��������� ��� ��������� ����� ��������, �� ��� ��������
 * ������ �������������� ����������� ���������� ����� ����� � ���������� ��������.
 * \sa CReqCert, CCertIdWithSignature
 */
class OCSP_CLASS CCertID
{
public:
    /// ������� ������ ������
    CCertID();
    /**
     * \brief ������� � �������������� ������
     * \param hashAlgorithm [in] �������� ������������ � �������������� �����
     * \param issuerNameHash [in] �������� ���� �������������� ����� �������� �����������
     * \param issuerKeyHash [in] �������� ���� ��������� ����� �������� �����������
     * \param serialNumber [in] �������� ����� �����������
     */
    CCertID(
	const ASN1::CAlgorithmIdentifier& hashAlgorithm,
	const CBlob& issuerNameHash,
	const CBlob& issuerKeyHash,
	const ASN1::CBigInteger& serialNumber);
    /**
     * \brief ������� � �������������� ������
     * \param hashAlgorithm [in] �������� ������������ � �������������� �����
     * \param certificate [in] �������������� ����������, ������������� �������� ���������
     * \param issuerCertificate [in] �������������� ���������� ��������
     */
    CCertID(
	const ASN1::CAlgorithmIdentifierEx& hashAlgorithm,
	const CBlob& certificate,
	const CBlob& issuerCertificate);
    /// ���������� ������
    ~CCertID();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CCertID( const CCertID& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CCertID& operator=( const CCertID& src);

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);

    //get
    /// ���������� ���� hashAlgorithm
    const ASN1::CAlgorithmIdentifier& get_hashAlgorithm() const;
    /// ���������� ���� issuerNameHash
    const CBlob& get_issuerNameHash() const;
    /// ���������� ���� issuerKeyHash
    const CBlob& get_issuerKeyHash() const;
    /// ���������� ���� serialNumber
    const ASN1::CBigInteger& get_serialNumber() const;
    //set
    /// ������������� ���� hashAlgorithm
    void put_hashAlgorithm(
	const ASN1::CAlgorithmIdentifier& hashAlgorithm);
    /// ������������� ���� issuerNameHash
    void put_issuerNameHash( const CBlob& issuerNameHash);
    /// ������������� ���� issuerKeyHash
    void put_issuerKeyHash( const CBlob& issuerKeyHash);
    /// ������������� ���� serialNumber
    void put_serialNumber( const ASN1::CBigInteger& serialNumber);
private:
    ASN1::CAlgorithmIdentifier hashAlgorithm_;
    CBlob issuerNameHash_;
    CBlob issuerKeyHash_;
    ASN1::CBigInteger serialNumber_;
};

/// ��������� ������� �� ���������
OCSP_API bool operator==( const CCertID& lhs, const CCertID& rhs);
/// ��������� ������� �� �����������
OCSP_API bool operator!=( const CCertID& lhs, const CCertID& rhs);

/**
 * \brief ASN.1 ��������� CertIdWithSignature. ������������� ����������� (draft-ietf-pkix-ocspv2-ext-01.txt, ������ 5.1.1).
 *
 * ���������� ���������������� ����� ��������������� ���� tbsCertificate
 * �����������, � �������������� ��������� ���� ���������������� ��������� �������
 * �����������, ��������� �������, ������ �������� � �������� �������.
 * \sa CReqCert, CCertID
 */
class OCSP_CLASS CCertIdWithSignature
{
public:
    /// ������� ������ ������
    CCertIdWithSignature();
    /**
     * \brief ������� � �������������� ������
     * \param issuer [in] �������������� ��� ��������
     * \param serialNumber [in] �������� �����
     * \param tbsCertificateHash [in] �������� ���� ��������������� ���� tbsCertificate
     * \param signatureAlgorithm [in] �������� �������
     * \param signatureValue [in] �������� �������
     */
    CCertIdWithSignature(
	const CBlob& issuer,
	const ASN1::CBigInteger& serialNumber,
	const CBlob& tbsCertificateHash,
	const ASN1::CAlgorithmIdentifier& signatureAlgorithm,
	const CBlob& signatureValue);
    /**
     * \brief ������� � �������������� ������
     * \param certificate [in] �������������� ����������, ������������� �������� ���������
     */
    CCertIdWithSignature( const CBlob& certificate);
    /// ���������� ������
    ~CCertIdWithSignature();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CCertIdWithSignature( const CCertIdWithSignature& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CCertIdWithSignature& operator=( 
	const CCertIdWithSignature& src);

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);

    //get
    /// ���������� �������������� ��� �������� �����������
    const CBlob& get_issuer() const;
    /// ���������� �������� ����� �����������
    const ASN1::CBigInteger& get_serialNumber() const;
    /// ���������� ��� ��������������� ���� tbsCertificate �����������
    const CBlob& get_tbsCertificateHash() const;
    /// ���������� �������� ������� �����������
    const ASN1::CAlgorithmIdentifier& get_signatureAlgorithm() const;
    /// ���������� ��������  ������� �����������
    const CBlob& get_signatureValue() const;
    //set
    /// ������������� �������� ��������������� ����� ������� �����������
    void put_issuer( const CBlob& issuer);
    /// ������������� �������� ��������� ������ �����������
    void put_serialNumber( const ASN1::CBigInteger& serialNumber);
    /// ������������� �������� ���� ���� tbsCertificate �����������
    void put_tbsCertificateHash( const CBlob& tbsCertificateHash);
    /// ������������� �������� ��������� ������� �����������
    void put_signatureAlgorithm( 
	const ASN1::CAlgorithmIdentifier& signatureAlgorithm);
    /// ������������� �������� ������� �����������
    void put_signatureValue( const CBlob& signatureValue);
private:
    CBlob issuer_;
    ASN1::CBigInteger serialNumber_;
    CBlob tbsCertificateHash_;
    ASN1::CAlgorithmIdentifier signatureAlgorithm_;
    CBlob signatureValue_;
};

/// ��������� ������� �� ���������
OCSP_API bool operator==( 
    const CCertIdWithSignature& lhs, const CCertIdWithSignature& rhs);
/// ��������� ������� �� �����������
OCSP_API bool operator!=(
    const CCertIdWithSignature& lhs, const CCertIdWithSignature& rhs);

/**
 * \brief ASN.1 ��������� ReqCert (draft-ietf-pkix-ocspv2-ext-01.txt, ������ 5.1.1)
 *
 * ����� ��� ���� �����������: CCertID, CCertIdWithSignature
 * � ������ ���������� � �������������� ����(fullCertificate). ��� �����������
 * ���������� ������ OCSP. ���� � ��������� ��� �������������� ���� CCertID, ��
 * ������ ����� v1, ���� ������������ ���� �� ���� ������������� �������
 * ����, �� ������ ����� v2.
 */
class OCSP_CLASS CReqCert
{
public:
    /// ��� �����������
    enum fullCertificateType 
    { 
	/// ���������� ��������� �����
	Certificate, 
	/// ���������� �������
	AttributeCertificate 
    };

    CReqCert();
    /**
     * \brief ������� � �������������� ������
     * \param certId [in] ������������� ����������� ���� CCertID
     */
    CReqCert( const CCertID& certId);
    /**
     * \brief ������� � �������������� ������
     * \param type [in] ��� �����������
     * \param encodedCertificate [in] �������������� ����������
     */
    CReqCert( fullCertificateType type, const CBlob& encodedCertificate);
    /**
     * \brief ������� � �������������� ������
     * \param certIdWithSignature [in] ������������� ����������� ���� CCertIdWithSignature
     */
    CReqCert( const CCertIdWithSignature& certIdWithSignature);

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CReqCert( const CReqCert& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CReqCert& operator=( const CReqCert& src);

    /// ���������� ������
    ~CReqCert();

    //get (������� ��������� ���������� ������������ �������)
    // �� ������� get �� 0 ���������� ������ ��������������
    // ���� �������������� ������������� � �������
    /// ���������� ������������� ����������� ���� CCertID ���� �� ���������� � ���������, ����� - 0
    const CCertID* get_certID() const;
    /// ���������� ���������� ���� �� ���������� � ���������, ����� - 0
    const CBlob* get_fullCert() const;
    /// ���������� ��� ����������� ���� �� ���������� � ���������, ����� - 0
    const fullCertificateType* get_fullCertType() const;
    /// ���������� ������������� ����������� ���� CCertIdWithSignature, ���� �� ���������� � ���������, ����� - 0
    const CCertIdWithSignature* get_certIdWithSignature() const;
    //set (��������� �������������� �����������)
    /// ��������� ��������� �������� ���� CCertID
    void put_certID( const CCertID& certId);
    /**
     * \brief ��������� ��������� �������������� �������������� �����������
     * \param type [in] ��� �����������
     * \param encodedCertificate [in] �������������� ����������
     */
    void put_fullCert( fullCertificateType type, const CBlob& encodedCertificate);
    /// ��������� ��������� �������� ���� CCertIdWithSignature
    void put_certIdWithSignature( const CCertIdWithSignature& certIdWithSignature);
public:
    class Impl;
private:
    void clear();
    Impl* pImpl_;
};

// response
class CCertStatus;
/**
 * \brief ASN.1 ��������� SingleResponse (RFC 2560, ������ 4.2.1)
 * 
 * ����� �� ��������� ������ �� �������� ����������� �� �����.
 * �������� ������������� ����������� (���� reqCert), ������������ ������
 * ����������� (���� certStatus) � �����, �� ������� ��� ����������
 * ���� ������ (���� thisUpdate). ����� ����� ����� ��������� �����
 * ���������� ���������� (���� nextUpdate) � ��������������
 * ���������� (���� singleExtensions).
 * 
 * \sa CResponseMessage, CBasicResponse, CSingleRequest
 */
class OCSP_CLASS CSingleResponse
{
public:
    /// ������� ������ ������
    CSingleResponse();
    /**
     * \brief ������� � �������������� ������
     * \param reqCert [in] ������������� �����������
     * \param certStatus [in] ������ �����������
     * \param thisUpdate [in] �����, �� ������� ���� ������������� ���������� � ������
     */
    CSingleResponse(
	const CReqCert& reqCert,
	const CCertStatus& certStatus,
	const CDateTime& thisUpdate);
    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CSingleResponse( const CSingleResponse& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CSingleResponse& operator=( const CSingleResponse& src);

    /// ���������� ������
    ~CSingleResponse();

    // get (������� ��������� ���������� ������������ �������)
    /// ���������� ������������� �����������
    const CReqCert& get_reqCert() const;
    /// ���������� ������ �����������
    const CCertStatus& get_certStatus() const;
    /// ���������� �����, �� ������� ���� ������������� ���������� � ������
    const CDateTime& get_thisUpdate() const;
    /// ���������� �����, ����� ����� �������� ����� ������ ���������� � ������� ����� ����������� (������������ ����)
    const CDateTime* get_nextUpdate() const;
    /// ���������� ������ ����������, ������������ � ������ (������������ ����)
    const ASN1::CExtensions* get_singleExtensions() const;
    // set (������ ������������ ���������, NULL ������� �������)
    /// ������������� �����, ����� ����� �������� ����� ������ ���������� �� ������� ����������� (������������ ����)
    void put_nextUpdate( const CDateTime* nextUpdate);
    /// ������������� ������ ���������� (������������ ����)
    void put_singleExtensions( const ASN1::CExtensions* extensions);
private:
    void clear();
    class Impl;
    Impl* pImpl_;
};

enum UnknownInfo { ocspUINull = 0xffff };

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CSingleResponse, OCSP_EXTERN_TEMPLATE, OCSP_CLASS);

/**
 * \class CSingleResponseList
 * \brief ������ �������� CSingleResponse
 *
 * \sa CSingleResponse, CDllList
 */
class OCSP_CLASS CSingleResponseList: public CDllList<CSingleResponse>
{
};
class CBasicResponse;
class CCertStatus;
class CResponderID;

/**
 * \brief OCSP ����� (RFC 2560, ������ 4.2.1)
 * 
 * ASN.1 ��������� OCSPResponse. �������� � ���� ������ ������, ��� ������, ���������� OID'��
 * (���� responseType) � �������������� ����� (���� response), �������. ���� responseType � 
 * response �����������, � �� ���������� � ������ ��� ��������� ��������� �������.
 * \sa BasicResponse
 */
class OCSP_CLASS CResponseMessage
{
public:
    /**
     * \brief ������� ������ ������
     * \remark responseStatus �� ��������� internalError
     */
    CResponseMessage();

    /// ���������� ������
    ~CResponseMessage();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CResponseMessage( const CResponseMessage& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CResponseMessage& operator=( const CResponseMessage& src);

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    void decode( const CBlob& encodedResponse);

    // get (������� ��������� ���������� ������������ �������)
    /// ���������� ���� responseStatus
    ResponseStatus get_responseStatus() const;
    /// ���������� ���� responseType
    const char* get_responseType() const;
    /// ���������� ���� response
    const CBlob* get_response() const;
    // set 
    /// ������������� ���� responseStatus
    void put_responseStatus(ResponseStatus status);
    /**
     * \brief ������������� �������� ������
     * \param responseType [in] OID ���� ������
     * \param response [in] �������������� ������������� ������
     */
    void put_response(const char *responseType, const CBlob *response);
private:
    void clear();
    class Impl;
    Impl* pImpl_;
};

/**
 * \brief ASN.1 ��������� BasicOCSPResponse (RFC 2560, ������ 4.2.1)
 * 
 * OCSP ����� ���� sz_id_pkix_ocsp_basic. �������� ������ ������� �� �������
 * �������� ������������ (���� responses) � �������������� ���������� � ������� 
 * �������� ������ (���� producedAt) � � ����������� ��������� (���� responderID).
 * � ������ ����� ����� ����������� �������������� ����������. ����� ������ ���� ��������,
 * ��� ����� ��������������� ������� �������� � �������� ������� (sign()/verify()).
 * 
 * \sa CResponseMessage, CSingleResponse
 */
class OCSP_CLASS CBasicResponse
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param producedAt [in] ����� �������� ������
     * \param responderId [in] ������������� ���������
     */
    CBasicResponse( 
	const CDateTime& producedAt,
	const CResponderID& responderId);

    /// ������� ������ ������
    CBasicResponse();

    /// ���������� ������
    ~CBasicResponse();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CBasicResponse( const CBasicResponse& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CBasicResponse& operator=( const CBasicResponse& src);

    /**
     * \brief �������� ������ � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encodedResponse);

    /**
     * \brief ������� ������
     *
     * \param hCryptProv [in] �������� ����������������, �������� �� �������� ����� ������
     * \param dwKeySpec [in] ���������� �����
     * \param signatureAlgorithm [in] ��������, ������� ����� �������������� ��� ������� ������
     *
     * \remark ������ ������� ������ ���������� ����� ���������� ���� �����, ���������������
     *		����� ������������ ������.
     * \sa verify()
     */
    void sign(
	HCRYPTPROV hCryptProv,
	DWORD dwKeySpec,
	const ASN1::CAlgorithmIdentifierEx& signatureAlgorithm);
    /**
     * \brief �������� ������� ������
     * 
     * \param encodedCertificate [in] �������������� �������� ������������� 
     * ����������� ��������������� ��� �������� �������
     *
     * \return true, ���� ������� ��������� �������, ����� false
     */
    bool verify( 
	const CBlob& encodedCertificate) const;

    // get (������� ��������� ���������� ������������ �������)
    /// ���������� ������ ������
    Version get_version() const;
    /// ���������� ����� �������� ������
    const CDateTime& get_producedAt() const;
    /// ���������� ������������� ���������
    const CResponderID& get_responderID() const;
    // signature � signatureAlgorithm ����������� ������� sign()
    /**
     * \brief ���������� �������� �������
     * \remark ����������� ������� sign()
     */
    const ASN1::CAlgorithmIdentifierEx* get_signatureAlgorithm() const;
    /**
     * \brief ���������� �������� �������
     * \remark ����������� ������� sign()
     */
    const CBlob* get_signature() const;
    /// ���������� ������ ������� �� �������� �� ����� ��������� ������������
    const CSingleResponseList& get_responses() const;
    /// ���������� ������ ������������ ��������� � ����� (������������ ����)
    const ASN1::CEncodedCertificateList* get_certs() const;
    /// ���������� ������ ���������� ��������� � ����� (������������ ����)
    const ASN1::CExtensions* get_responseExtensions() const;
    // set (������ ������������ ���������, NULL ������� �������)
    /// ������������� ������ ������� �� �������� ������� �� �������� ������ ������������
    void put_responses( const CSingleResponseList& responses);
    /// ������������� ������ ������������ ������������ � �����
    void put_certs( const ASN1::CEncodedCertificateList* certs);
    /// ������������� ������ ���������� ������������ � �����
    void put_responseExtensions( const ASN1::CExtensions* extensions);
    /// ���������� ���������� ������ � ������� ����� ������
    /// ��� ����� thisUpdate, nextUpdate, producedAt
    void put_clockPrecisionDigits( int count );
private:
    void clear();
    class Impl;
    Impl* pImpl_;
};


/**
 * \brief ASN.1 ��������� CertStatus (RFC 2560, ������ 4.2.1)
 * 
 * ���������� � ������� �����������. ������ ����������� ������������
 * ����� ����������� - � ������ ���� Good ���������� �� �������, �
 * ������ Revoked - �������, � ������ Unknown - ������ �� ���������.
 * � ������, ���� ���������� �������, ��������������� ����� ������ �
 * (�����������) ������� ������.
 * 
 * \sa CSingleResponse
 */
class OCSP_CLASS CCertStatus
{
public:
    /// ��� ������� �����������
    enum Type 
    {
	/// ���������� �� �������
	Good,
	/// ���������� �������
	Revoked, 
	/// ������ ����������� ����������
	Unknown 
    };
    
    /**
     * \brief ������� ������ ������
     * \remark �� ��������� ������ - Unknown
     */
    CCertStatus();
    /**
     * \brief ������� � �������������� ������ (������ Revoked)
     * \param revocationTime [in] ����� ������
     * \param revocationReason [in] ������� ������ (�����������)
     */
    CCertStatus(
	const CDateTime& revocationTime,
	const ASN1::CrlReason* revocationReason = 0);

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CCertStatus( const CCertStatus& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CCertStatus& operator=( const CCertStatus& src);

    /// ���������� ������
    ~CCertStatus();

    //get (������� ��������� ���������� ������������ �������)
    /// ���������� true ���� ������ Good, ����� false
    bool isGood() const;
    /// ���������� true ���� ������ Revoked, ����� false
    bool isRevoked() const;
    /// ���������� true ���� ������ Unknown, ����� false
    bool isUnknown() const;
    /// ���������� ������
    Type get_type() const;
    /// ���� ������ Revoked, ���������� ����� ������, ����� 0
    const CDateTime* get_revocationTime() const;
    /// ���� ������ Revoked, ���������� ����� ������, ����� 0 (������������ ����)
    const ASN1::CrlReason* get_revocationReason() const;
    //set (��� ������� ������� ���� ����� ����������,
    // ��������� ���������� ������������ ��������)
    /// ������������� ������ Good
    void put_good();
    /** 
     * \brief ������������� ������ Revoked
     * \param revocationTime [in] ����� ������
     * \param revocationReason [in] ������� ������ (������������ ����)
     */
    void put_revoked(
	const CDateTime& revocationTime,
	const ASN1::CrlReason* revocationReason = 0);
    /// ������������� ������ Unknown
    void put_unknown();
private:
    void clear();
    class Impl;
    Impl* pImpl_;
};

/**
* \brief ASN.1 ��������� ResponderID (RFC 2560, ������ 4.2.1)
* 
* ������������� ��������� ������ OCSP (������). ������ �����
* ����������������� �� ����� (ByName) ��� �� SHA1 ���� ���������
* �����.
*
* \sa CBasicResponse
*/
class OCSP_CLASS CResponderID
{
public:
    /// ��� ������������� ��������� - �� ����� ��� �� ���� ��������� �����
    enum Type 
    {
	/// ������������� �� �����
	ByName,
	/// ������������� �� ���� ��������� �����
	ByHash 
    };

    /**
    * \brief ������� � �������������� ������
    * \param type [in] ��� ��������������
    * \param value [in] �������������� ������������� ��������� (���������� ������� �� ����)
    */
    CResponderID( 
	Type type,
	const CBlob &value);

    /// ������� ������ ������
    CResponderID();

    /**
    * \brief ������� ������������� �� ������ �����������
    * \param type [in] ��� ��������������
    * \param encodedCertificate [in] �������������� ����������
    */
    static CResponderID fromCert( Type type,
	const CBlob &encodedCertificate );

    /// ���������� ������
    ~CResponderID();

    /**
    * \brief ������� ����� ��������� �������.
    * \param src [in] ������, ����� �������� ���������
    */
    CResponderID( const CResponderID& src);
    /**
    * \brief �������� �������� ������ � �������.
    * \param src [in] ������, ������� ���������� � �������
    * \return ������ �� ������� ������.
    */
    CResponderID& operator=( const CResponderID& src);

    /**
    * \brief �������� ������ � ������� ASN.1 DER � ����������
    * ������������ �������� ������������������
    * \sa decode()
    */
    CBlob encode() const;
    /**
    * \brief �������������� ������ �� �������� �������������� �������� ������������������
    * \sa encode()
    */
    void decode( const CBlob& encoded);

    /// ���������� ��� ��������������
    Type get_type() const;
    /// ���������� �������� ��������������
    const CBlob& get_value() const;

    /// ������������� �������� ��������������
    void put_value( Type type, const CBlob& value);
private:
    Type type_;
    CBlob value_;
};

/// ��������� ������� �� ���������
OCSP_API bool operator==( const CResponderID& lhs, const CResponderID& rhs);
/// ��������� ������� �� �����������
OCSP_API bool operator!=( const CResponderID& lhs, const CResponderID& rhs);

// ����������

// CRL Reference

class CCrlIDImpl;

/**
 * \brief ���������� CRL Reference (RFC 2560, ������ 4.4.2)
 * 
 * �������� ������ �� CRL � ������� ��� ������ ���������� ���
 * ���������������� CRL
 * 
 * \sa CExtValue, CExtension
 */
class OCSP_CLASS CExtCrlID : public ASN1::CExtValue
{
public:
    /// ������� ������ ������
    CExtCrlID();
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� ������������� ����������
     */
    CExtCrlID( const CBlob& value);

    /// ���������� ������
    ~CExtCrlID();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CExtCrlID( const CExtCrlID& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CExtCrlID& operator=( const CExtCrlID& src);

    //get
    /// ���������� ���� crlUrl
    const char * get_crlUrl() const;
    /// ���������� ���� crlNum
    const DWORD* get_crlNum() const;
    /// ���������� ���� crlTime
    const CDateTime* get_crlTime() const;
    //set
    /// ������������� ���� crlUrl
    void put_crlUrl( const char * crlUrl);
    /// ������������� ���� crlNum
    void put_crlNum( const DWORD* crlNum);
    /// ������������� ���� crlTime
    void put_crlTime( const CDateTime* crlTime);
private:
    void clear();
    CCrlIDImpl* pImpl_;
};

/**
 * \brief ���������� Historical Request
 * 
 * ������ ��������� ����������� �� ������������ ������ � �������.
 * 
 * \sa CExtValue, CExtension
 */
class OCSP_CLASS CExtHistoricalRequest : public ASN1::CExtValue
{
public:
    /// ������� ������ ������
    CExtHistoricalRequest();
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� ������������� ����������
     */
    CExtHistoricalRequest( const CBlob& value);

    /// ���������� ������
    ~CExtHistoricalRequest();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CExtHistoricalRequest( const CExtHistoricalRequest& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CExtHistoricalRequest& operator=( const CExtHistoricalRequest& src);

    //get
    /// ���������� ���� crlUrl
    const char * get_crlUrl() const;
    /// ���������� ���� crlNum
    const DWORD* get_crlNum() const;
    /// ���������� ���� crlTime
    const CDateTime* get_crlTime() const;
    //set
    /// ������������� ���� crlUrl
    void put_crlUrl( const char * crlUrl);
    /// ������������� ���� crlNum
    void put_crlNum( const DWORD* crlNum);
    /// ������������� ���� crlTime
    void put_crlTime( const CDateTime* crlTime);
private:
    CCrlIDImpl* pImpl_;
};

// CRL Locator

/**
 * \brief ���������� CRL Locator (draft-ietf-pkix-ocspv2-ext-01.txt, ������ 6)
 * 
 * ������ �� �����, ��� ����� CRL �� �������� ������������ ������ �����������.
 * 
 * \sa CExtValue, CExtension
 */
class OCSP_CLASS CExtCRLLocator: public ASN1::CExtValue
{
public:
    /// ������� ������ ������
    CExtCRLLocator();
    /**
     * \brief ������� � �������������� ������
     * \param distributionPoints [in] ������ ����� ��������������� CRL
     */
    CExtCRLLocator( 
	const ASN1::CCRLDistPointsSyntax& distributionPoints);
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� ������������� ����������
     */
    CExtCRLLocator( const CBlob& value);

    /// ���������� ������
    ~CExtCRLLocator();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CExtCRLLocator( const CExtCRLLocator& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CExtCRLLocator& operator=( const CExtCRLLocator& src);

    //get
    /// ���������� ������ ����� ��������������� CRL
    const ASN1::CCRLDistPointsSyntax& get_distributionPoints() const;
    //set
    /// ������������� ������ ����� ��������������� CRL
    void put_distributionPoints( 
	const ASN1::CCRLDistPointsSyntax& distributionPoints);
private:
    ASN1::CCRLDistPointsSyntax distributionPoints_;
    void encode();
    void decode();
};

// Nonce

/**
 * \brief ���������� Nonce (RFC 2560, ������ 4.4.1)
 * 
 * ������� ��������� ����� ��� ����������� ������������ ������ �������.
 * 
 * \sa CExtValue, CExtension
 */
class OCSP_CLASS CExtNonce: public ASN1::CExtValue
{
public:
    /// ������� ������ ������
    CExtNonce();
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� ������������� ����������
     */
    CExtNonce( const CBlob& value);

    /// ���������� ������
    ~CExtNonce();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CExtNonce( const CExtNonce& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CExtNonce& operator=( const CExtNonce& src);

    //get
    /// ���������� �������� �����.
    const CBlob& get_nonce() const;
    //set
    /// ������������� �������� �����.
    void put_nonce( const CBlob& nonce);
};

// Instant revocation indicator

/**
 * \brief ���������� Instant Revocation Indicator
 * 
 * ���������� ��������� � ���, ��� ���������� ��� ������� ����������
 * ������ OCSP.
 * 
 * \sa CExtValue, CExtension
 */
class OCSP_CLASS CExtInstantRevocationIndicator: public ASN1::CExtValue
{
public:
    /// ������� ������ ������
    CExtInstantRevocationIndicator();
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� ������������� ����������
     */
    CExtInstantRevocationIndicator( const CBlob& value);

    /// ���������� ������
    ~CExtInstantRevocationIndicator();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CExtInstantRevocationIndicator( 
	const CExtInstantRevocationIndicator& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CExtInstantRevocationIndicator& operator=(
	const CExtInstantRevocationIndicator& src);
};

// Revocation announcement reference

/**
 * \brief ���������� Revocation Announcement Reference
 * 
 * ����� ������, ������� ������������� 
 * ��� ����������� ������� �����������.
 * 
 * \sa CExtValue, CExtension
 */
class OCSP_CLASS CExtRevocationAnnouncementReference: public ASN1::CExtValue
{
public:
    /// ������� ������ ������
    CExtRevocationAnnouncementReference();
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� ������������� ����������
     */
    CExtRevocationAnnouncementReference( const CBlob& value);

    /// ���������� ������
    ~CExtRevocationAnnouncementReference();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CExtRevocationAnnouncementReference( 
	const CExtRevocationAnnouncementReference& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CExtRevocationAnnouncementReference& operator=(
	const CExtRevocationAnnouncementReference& src);
};

// Service locator

class CExtServiceLocatorImpl;
/**
 * \brief ���������� Service Locator (RFC 2560, ������ 4.4.6)
 * 
 * ��������� �� ������, ������� ����� ����������
 * ������ �����������.
 * 
 * \sa CExtValue, CExtension
 */
class OCSP_CLASS CExtServiceLocator: public ASN1::CExtValue
{
public:
    /// ������� ������ ������
    CExtServiceLocator();
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� ������������� ����������
     */
    CExtServiceLocator( const CBlob& value);

    /// ���������� ������
    ~CExtServiceLocator();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CExtServiceLocator( const CExtServiceLocator& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CExtServiceLocator& operator=( const CExtServiceLocator& src);

    //get
    /// ���������� ���� issuer
    const CBlob& get_issuer() const;
    /// ���������� ���� locator (������������ ����)
    const ASN1::CAuthorityInfoAccessSyntax* get_locator() const;
    //set
    /// ������������� ���� issuer
    void put_issuer( const CBlob& issuer);
    /// ������������� ���� locator (������������ ����)
    void put_locator( const ASN1::CAuthorityInfoAccessSyntax* locator);
private:
    CExtServiceLocatorImpl *pImpl_;
    void encode();
    void decode();
};

// Acceptable responses

/**
 * \brief ������ OID'�� ���������� ����� ������� (RFC 2560, ������ 4.4.3)
 * 
 * ����������� ������� ������ �������� ����� CExtAcceptableResponses.
 */
typedef CStringList CAcceptableResponses;

/**
 * \brief ���������� Acceptable Responses (RFC 2560, ������ 4.4.3)
 * 
 * ������ OID'�� ����� ������� ������� �������� ������.
 * 
 * \sa CExtValue, CExtension
 */
class OCSP_CLASS CExtAcceptableResponses: public ASN1::CExtValue
{
public:
    /// ������� ������ ������
    CExtAcceptableResponses();
    /**
     * \brief ������� � �������������� ������
     * \param acceptableResponses [in] ������ OID'�� ���������� �������
     */
    CExtAcceptableResponses( 
	const CAcceptableResponses& acceptableResponses);
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� ������������� ����������
     */
    CExtAcceptableResponses( const CBlob& value);

    /// ���������� ������
    ~CExtAcceptableResponses();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CExtAcceptableResponses( const CExtAcceptableResponses& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CExtAcceptableResponses& operator=( const CExtAcceptableResponses& src);

    //get
    /// ���������� ������ OID'�� ���������� �������
    const CAcceptableResponses& get_acceptableResponses() const;
    //set
    /// ������������� ������ OID'�� ���������� �������
    void put_acceptableResponses( 
	const CAcceptableResponses& acceptableResponses);
private:
    CAcceptableResponses acceptableResponses_;
    void encode();
    void decode();
};

// Archive Cutoff

/**
 * \brief ���������� Archive Cutoff (RFC 2560, ������ 4.4.4)
 * 
 * �����, �� �������� �������� ����� ������ OCSP
 * 
 * \sa CExtValue, CExtension
 */
class OCSP_CLASS CExtArchiveCutoff: public ASN1::CExtValue
{
public:
    /// ������� ������ ������
    CExtArchiveCutoff();
    /**
     * \brief ������� � �������������� ������
     * \param archiveCutoff [in] ����� �� �������� �������� ����� ������ OCSP
     */
    CExtArchiveCutoff( 
	const CDateTime& archiveCutoff);
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� ������������� ����������
     */
    CExtArchiveCutoff( const CBlob& value);

    /// ���������� ������
    ~CExtArchiveCutoff();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CExtArchiveCutoff( const CExtArchiveCutoff& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CExtArchiveCutoff& operator=( const CExtArchiveCutoff& src);

    //get
    /// ���������� ����� �� �������� �������� ����� ������ OCSP
    const CDateTime& get_archiveCutoff() const;
    //set
    /// ������������� ����� �� �������� �������� ����� ������ OCSP
    void put_archiveCutoff( 
	const CDateTime& archiveCutoff);
private:
    CDateTime archiveCutoff_;
    void encode();
    void decode();
};

} // namespace OCSP
} // namespace PKI
} // namespace CryptoPro

#endif // _OCSP_H_INCLUDED
