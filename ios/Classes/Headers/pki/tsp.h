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
 * \brief ������ ��� ������ � TSP (Time-Stamp Protocol)
 */

#ifndef _TSP_H_INCLUDED
#define _TSP_H_INCLUDED

#include <cplib/Blob.h>
#include <asn1/Types.h>
#include <asn1/CMP.h>
#include <asn1/CMS.h>
#include <asn1/algidex.h>

#if !defined TSP_DLL_DEFINES
#   define TSP_DLL_DEFINES
#   if defined _WIN32 && !defined CRYPTCP && !defined TSP_STATIC
#	if defined TSP_DLL
#	    define TSP_CLASS __declspec(dllexport)
#	    define TSP_API __declspec(dllexport)
#	    define TSP_DATA __declspec(dllexport)
#	    define TSP_EXTERN_TEMPLATE
#	else // defined TSP_DLL
#	    define TSP_CLASS __declspec(dllimport)
#	    define TSP_API __declspec(dllimport)
#	    define TSP_DATA __declspec(dllimport)
#	    define TSP_EXTERN_TEMPLATE extern
#	    ifndef CP_IGNORE_PRAGMA_MANIFEST
#	        include "pki_tsp_assembly.h"
#	        ifdef _WIN64
#	            pragma comment(linker,"/manifestdependency:\"type='win32' " \
 	            "name='" PKI_TSP_ASSEMBLY_NAME_X64 "' " \
 	            "version='" PKI_TSP_ASSEMBLY_VERSION_X64 "' " \
 	            "processorArchitecture='amd64' " \
 	            "language='*' " \
 	            "publicKeyToken='" PKI_TSP_ASSEMBLY_PUBLICKEYTOKEN_X64 "'\"")
#	        else
#	            pragma comment(linker,"/manifestdependency:\"type='win32' " \
 	            "name='" PKI_TSP_ASSEMBLY_NAME_X86 "' " \
 	            "version='" PKI_TSP_ASSEMBLY_VERSION_X86 "' " \
 	            "processorArchitecture='x86' " \
 	            "language='*' " \
 	            "publicKeyToken='" PKI_TSP_ASSEMBLY_PUBLICKEYTOKEN_X86 "'\"")
# 	        endif
#	    endif
#	endif // !defined TSP_DLL
#   else
#	define TSP_CLASS
#	define TSP_API
#	define TSP_DATA
#	define TSP_EXTERN_TEMPLATE
#       define NO_EXPIMP_CDLLLIST_ITERATORS
#   endif // !defined _WIN32 || defined CRYPTCP || defined TSP_STATIC
#endif // !defined TSP_DLL_DEFINES

namespace CryptoPro {
namespace PKI {
namespace TSP {

class CToken;
struct CAccuracy;

#define sz_id_ct_TSTInfo "1.2.840.113549.1.9.16.1.4"
#define sz_id_kp_timeStamping "1.3.6.1.5.5.7.3.8"
#define sz_id_timestampCountersignature "1.3.6.1.4.1.311.3.2.1"

/**
 * \mainpage �������������� ��������� ��������� TSP
 *
 * �������������� ��������� �� ������� ��������� TSP SDK ������������ 
 * ��� ������ �� �������� �������. ������������� ������� ���������� �������� 
 * ���������� ����� ������� � ������ ��������� ����������� ������ � 
 * ������������ �������.
 * 
 * �������������� ��������� ������������ ����� ���������� ������� C++. 
 *
 * � ���������� ����������� ��������� �������� ������, ��������� � RFC 3161, 
 * � ������� �������, ������������ Microsoft ��� ������� ����������� ������ 
 * (� ���������� Authenticode).
 * 
 * \section contents ������
 *
 * ��� ��������� ��������� ������� �������, ���������� � RFC 3161, 
 * ��������������� ��������� ������:
 * - \link CryptoPro::PKI::TSP::CRequest CRequest\endlink - ������ �� 
 * ����� �������
 * - \link CryptoPro::PKI::TSP::CResponse CResponse\endlink - ����� 
 * ������ ������� �������
 * - \link CryptoPro::PKI::TSP::CToken CToken\endlink - ����� �������
 *
 * ��� ��������� ������� ������� Microsoft ��������������� ������:
 * - \link CryptoPro::PKI::TSP::CMSRequest CMSRequest\endlink - ������ �� 
 * ����� ������� Microsoft
 * - \link CryptoPro::PKI::TSP::CMSStamp CMSStamp\endlink - ����� ������� 
 * Microsoft
 *
 * \section usage �����������
 *
 * ������ � ����� �������� � ���������� �������������� ��������� ��������:
 * - ���� ���� ������������, �� ��� ��������������� � ������������ ��� 
 * ������ �� ������. ��� ������ ���c��������� ������ �� ����� ����� �������. 
 * ����� ����, ��� ��������� ���������� �������, ���������� ���� ������ 
 * ������������;
 * - ���� ���� ������������, �� ��� ��������������� � ������������ ��� 
 * ��������� �� ������. ���� ��������� ����� NULL, ��� ��������, ��� ���� 
 * �����������.
 *
 * �������� ������ ���������� (�������, ������, ������) �������� ������ 
 * encode()/decode(), ����������� �������� ����������� � 
 * ASN.1 DER-������������� � ������������� �� ����. ������, ���������� �� 
 * �����������, ������� �������� ������� (CToken, CMSStamp), ������������ 
 * �������� ������� � �������� ������� (sign()/verify()), � ����� ������ 
 * � ���������� � ������� (SignerInfo).
 * ��������� ����������� �� ���������, ����� ������� ������ ������, 
 * ��� ������������ ������ ������� decode(). �� ���� ��������� �������, 
 * ���� ���������� ����������� � �����������, ������������� ������������ 
 * �� ��������� �� �������������, ��� ��� ����� ������� encode() ��� 
 * ������������ ���� ��������� ������ ���� ������������������� ����������� 
 * ����������. ������������ � ����������� ��������� ��� ���� ��� �������� 
 * �������, � ������������ �� ��������� - ���, ��� ��������� ����������� 
 * ����, ��� ������ �� ����� ��������� ������������������ ����� ������� 
 * encode(). 
 *
 * ������������� �������� � ���� ASN.1 DER, ������������ ��� �� 
 * ��������������� ����� �������� � ��������. ����� �������, ���� ��� 
 * �������� �������� ������ � �������� ����������:
 *    - �������� ��������� (������� ��� ������) � ��� ����������� 
 * � ASN.1 DER ��� ����������� ��������;
 *    - ��������� ��������� � ASN.1 DER-�������������, ��� ������������� 
 * � ���������� ������������ � ��� ����������.
 *
 * ��� ������������� ������ ������ ������� ������ ���������� 
 * ����� ������������ ��������� ���� ����������: std::exception � ATL::CAtlException.
 *
 * \section s1 �������� ���������
 *
 * �������� ����� �������� ���������:
 *	-# �������� �������
 *	-# ���������� ����� � ������ ������������� (���������� 
 * ������������ ��� ��������� ������������, �������� �� ���������)
 *	-# � ������, ���� ��������� ��������� �������, ����� ������ 
 * sign()
 *	-# ����� ������ encode() ��� ��������� ASN.1 DER-������������� 
 * ������� � ���� ����� �������� ������
 * 
 * ������ (�������� ������� �� ����� �������):
 * \dontinclude TspSample.cpp
 * \skip example_5_begin
 * \skip �������� ������� �� ����� �������
 * \until return tsRequest.encode()
 *
 * ������ (�������� ������ ������� Microsoft):
 * \dontinclude TspSample.cpp
 * \skip example_1_begin
 * \skip ������� ������ �������
 * \until return timeStamp.encode()
 *
 * \section s2 ������������� ���������
 *
 * �������� ������ ������������� ���������:
 *	-# �������� ������� ������������� �� ���������
 *	-# ����� ������ decode(), ���������� �������� �������� ASN.1 DER-������������� ���������
 *	-# ����� ������� get_...() ��� ��������� ����� ���������.
 * 
 * ������ (�������� ������ �������):
 * \dontinclude TspSample.cpp
 * \skip example_6_begin
 * \skip OID ��������
 * \until return tsToken

 * ������ (������ ����������� ������ ������� Microsoft):
 * \dontinclude TspSample.cpp
 * \skip example_2_begin
 * \skip CMSStamp
 * \until timeStamp.get_certificates()
 */

/**
 * \brief ������ �� ����� ������� (RFC 3161, ������ 2.4.1)
 *
 * ����� CRequest ������������� ������ �� ��������� ������ �������.
 * ������������ ��� ��������, ����������� � ������������� �� ASN.1 DER �������������
 * ������� �� ����� �������.
 *
 * ������ �������� ������ (�� ���������������), ��� � �������� ���� ������,
 * �� ������� �������� ����� ������� (hashAlgorithm, hashedMessage). 
 * ������������� ������ ��������:
 *  - reqPolicy - ������������� �������� ������ ������� �������;
 *  - nonce - ���������� ������� ��������� ����� ��� �������� ������������
 *	    ������� ������;
 *  - certReq - ���� ��� ���� ����� true, ������ ������� ������ �������
 *	    ���������� �� ������� ������������� ������� ������ � �������� �����;
 *  - extensions - �������������� ����������.
 */
class TSP_CLASS CRequest
{
public:
    /**
     * \brief ������� � �������������� ������
     *
     * � ������������ �������� ������ ������������ �������� �������.
     *
     * \param hashAlgorithm [in] �������� ����
     * \param hashedMessage [in] ��� ������ ��� ������� ������������� �����
     *        �������
     * \param certReq [in] ����, ������������ ����� �� �������� ����������
     *        ������ ������� ������� � ����� �� ������
     */
    CRequest(
	const ASN1::CAlgorithmIdentifierEx& hashAlgorithm,
	const CBlob& hashedMessage,
	bool certReq = false);
    /// ������� ������ ������
    CRequest();
    /**
    * \brief ������� ����� ��������� �������.
    * \param src [in] ������, ����� �������� ���������
    */
    CRequest( const CRequest& src);
    /**
    * \brief �������� �������� ������ � �������.
    *
    * \param src [in] ������, ������� ���������� � �������
    * \return ������ �� ������� ������.
    */
    CRequest& operator=( const CRequest& src);
    /// ���������� ������
    ~CRequest();
    // ������ get ��� ������������ ���������
    // ���������� ������ �� ������
    /**
     * \brief ���������� ������ �������
     *
     * \return ����� ������
     */
    DWORD get_version() const;
    /**
     * \brief ���������� �������� ����, ��������������� ��� ����������� ������.
     *
     * \return ������������� ���������
     */
    const ASN1::CAlgorithmIdentifierEx& get_hashAlgorithm() const;
    /**
     * \brief ���������� �������� ���� ������, �� ������� ���������� ����� �������
     *
     * \return ���� ������, ���������� �������� ����
     */
    const CBlob& get_hashedMessage() const;
    /**
     * \brief ���������� �������� ����� certReq
     *
     * \remarks ���� certReq ������� � ���, ����� �� ���������� ����������,
     * ������� ����� �������������� ��� ������� ������ ������� � ����� �������.
     * ���� �� ����� �������� false, ���������� �� ������ ������������ � �����,
     * ���� true - ������.
     * \return true ��� false
     */
    bool get_certReq() const;
    // ������ get ��� ������������ ���������.
    // ���������� ��������� �� ����������� �������. ���� ��������� �������,
    // �� ������ ������� �� �����.
    /**
     * \brief ���������� ������������� �������� ������� �������.
     *
     * \return ��������� �� OID. 
     *
     * \remarks ������������ ����. ���� ����������� NULL, �� ������ ����
     * �� ��������� � �����������.
     */
    const char * get_reqPolicy() const;
    /**
     * \brief ���������� ���� nonce ������� �� ����� �������
     *
     * \return ��������� �� ������, �������������� ������� ����� �����
     *
     * \remarks ������������ ����. ���� ����������� NULL, �� ������ ����
     * �� ��������� � �����������.
     */
    const ASN1::CBigInteger* get_nonce() const;
    /**
     * \brief ���������� ������ ��������� ��������� � ������
     * 
     * \return ��������� �� ������ ����������
     *
     * \remarks ������������ ����. ���� ����������� NULL, �� ������ ����
     * �� ��������� � �����������.
     */
    const ASN1::CExtensions* get_extensions() const;

    // ������ set ��� ������������ ���������.
    // E��� �������� NULL - �� ����� �������� ������������
    // �������� ��������� � ������� ���������� �� ��������.
    /**
     * \brief ������������� ������������� �������� ������� �������
     * 
     * \param reqPolicy [in] ��������� �� OID ��������
     * 
     * \remarks ������������ ����. ���� �������� NULL, �� ������ ����
     * ���������� �� ����������� � ����������� � �������.
     */
    void put_reqPolicy( const char * reqPolicy);
    /**
     * \brief ������������� �������� ���� nonce
     * 
     * \param nonce [in] ��������� ������, �������������� ������� ����� �����
     * 
     * \remarks ������������ ����. ���� �������� NULL, �� ������ ����
     * ���������� �� ����������� � ����������� � �������.
     */
    void put_nonce( const ASN1::CBigInteger* nonce);
    /**
     * \brief ���������� ���������� � ������ �� ����� �������
     *
     * \param extensions [in] ��������� �� ������ ����������
     *
     * \remarks ������������ ����. ���� �������� NULL, �� ������ ����
     * ���������� �� ����������� � ����������� � �������.
     */
    void put_extensions( const ASN1::CExtensions* extensions); 

    /**
     * \brief �������� ������ � ASN.1 DER �������������.
     *
     * \return  ���� ������ ���������� �������������� �������������
     *		������� �� ����� �������
     */
    CBlob encode() const;
    /**
     * \brief ���������� ������� �� ��� ��������������� ASN.1 DER �������������
     *
     * \param encodedRequest [in] ���� ������ ���������� �������������� der-�������������
     *				    ������� �� ����� �������
     */
    void decode( const CBlob& encodedRequest);
private:
    void clear();
    class Impl;
    Impl* pImpl_;
};

/**
 * \brief ����� �� ������ �� ����� ������� (RFC 3161, ������ 2.4.2)
 *
 * ����� CResponse ������������� ����� ������ ������� �������
 * �� ������. ��������� ���������, ���������� � ������������ �����,
 * ���������� ������ �, � ������ ���� ������ �������������, ����� �������. 
 * 
 */
class TSP_CLASS CResponse
{
public:
    /**
     * \brief ������� ������ ������
     * 
     * \remarks �� ��������� ������ ������ - PKI_STATUS_GRANTED
     */
    CResponse();
    /**
    * \brief ������� ����� ��������� �������.
    * \param src [in] ������, ����� �������� ���������
    */
    CResponse( const CResponse& src);
    /**
    * \brief �������� �������� ������ � �������.
    *
    * \param src [in] ������, ������� ���������� � �������
    * \return ������ �� ������� ������.
    */
    CResponse& operator=( const CResponse& src);
    /// ���������� ������
    ~CResponse();

    // ������ get
    /**
     * \brief ���������� ������ ������ ������������ � ������
     *
     * \return ���������, ���������� ���������� � ������� ������
     */
    const ASN1::CPKIStatusInfo& get_status() const;
    /**
     * \brief ���������� ����� ������� ������������ � ������
     * 
     * \return ��������� �� ����� �������
     * 
     * \remarks ������������ ����. ���� ����������� NULL, �� ������ ����
     * �� ��������� � �����������.
     */
    const CToken* get_timeStampToken() const;

    // ������ set
    /**
     * \brief ��������� ���� ������ ������� � ������ �� ������
     *
     * \param token [in] ��������� �� ����� �������
     *
     * \remarks ������������ ����. ���� �������� NULL, �� ������ ����
     * ���������� �� ����������� � ����������� � ������.
     */
    void put_timeStampToken( const CToken* token);
    /**
     * \brief ������������� ������ ������ �� ������
     *
     * \param errorInfo [in] ���������, ���������� ���������� � ������� ������
     *
     */
    void put_status( const ASN1::CPKIStatusInfo& errorInfo);

    /**
     * \brief �������� ����� �� ������ � ASN.1 DER �������������
     *
     * \return  ���� ������ ���������� �������������� �������������
     *		������ �� ������ �� ����� �������
     */
    CBlob encode() const;
    /**
     * \brief ���������� ������ �� ������ �� ��� ��������������� ASN.1 DER �������������
     *
     * \param encodedResponse [in] ���� ������ ���������� �������������� �������������
     *				  ������ �� ������ �� ����� �������
     */
    void decode( const CBlob& encodedResponse);
private:
    void clear();
    class Impl;
    Impl* pImpl_;
};

/**
 * \brief ����� ������� (RFC 3161, ������ 2.4.2).
 *
 * ����� ��������� ���������, ���������� � ������������ ����� �������.
 * ����� ������� ������������ ����� ����������� CMS ���������
 * (ContentInfo ���������� SignerInfo, ����� ����������� eContentType
 * ������ id-ct-TSTInfo). �����, �������������� ������� ���������, �����
 * �������� ����� ���������� ���� �������������� �����.
 *
 */
class TSP_CLASS CToken
{
public:
    /**
     * \brief ������� � �������������� ������
     * 
     * � ������������ �������� ������ ������������ �������� �������.
     *
     * \param policy [in] OID �������� ������ ������� �������
     * \param hashAlgorithm [in] �������� ����
     * \param hashedMessage [in] ��� ������ ��� ������� ������������� �����
     *        �������
     * \param serialNumber [in] ���������� �������� ����� ������ �������
     * \param genTime [in] ����� �������� ������ ������� (UTC)
     * \param ordering [in] ����, ������������ ����� �� ������������� �������
     *			    �� �������� ���� accuracy
     */
    CToken(
	const char * policy,
	const ASN1::CAlgorithmIdentifierEx& hashAlgorithm,
	const CBlob& hashedMessage,
	const ASN1::CBigInteger& serialNumber,
	const CDateTime& genTime,
	bool ordering = false);
    /// ������� ������ ������
    CToken();
    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CToken( const CToken& src);
    /**
    * \brief �������� �������� ������ � �������.
    *
    * \param src [in] ������, ������� ���������� � �������
    * \return ������ �� ������� ������.
    */
    CToken& operator=( const CToken& src);

    /// ���������� ������
    ~CToken();
    // ������ get ��� ������������ ���������
    // ���������� ������ �� ����������� ������
    /**
     * \brief ���������� ������ ������
     *
     * \return ����� ������
     */
    DWORD get_version() const;
    /**
     * \brief ���������� �������� �� ������� ������� �����
     *
     * \return OID �������� 
     */
    const char * get_policy() const;
    /**
     * \brief ���������� �������� ����, ��������������� ��� ����������� ������.
     *
     * \return ������������� ���������
     */
    const ASN1::CAlgorithmIdentifierEx& get_hashAlgorithm() const;
    /**
     * \brief ���������� �������� ���� ������, �� ������� ����� ����� �������
     *
     * \return ���� ������, ���������� �������� ����
     */
    const CBlob& get_hashedMessage() const;
    /**
     * \brief ���������� �������� ����� ������ �������
     *
     * \return ������, �������������� ������� ����� �����
     */
    const ASN1::CBigInteger& get_serialNumber() const;
    /**
     * \brief ���������� ����� ������ ������
     *
     * \return ����� ������ ������
     */
    CDateTime get_genTime() const;
    /**
     * \brief ���������� ����� ������ ������ � ���� ������ � �������
     *	      GeneralizedTime
     *
     * ���������� ����� ������ ������ � ���� ������ � �������
     * GeneralizedTime � ����� ����� ����, � ����� ����� ��������
     * � ������.
     *
     * \return ������ � ������� GeneralizedTime
     */
    const char* get_genTimeZ() const;
    /**
     * \brief ���������� �������� ���� ordering
     *
     * \return true ��� false
     */
    bool get_ordering() const;
    /**
     * \brief ���������� ��������� SignerInfo (���������� � ����������)
     *
     * \return ���������, ���������� ���������� � ���������� (SignerInfo, RFC 3161)
     */
    const ASN1::CSignerInfo& get_signerInfo() const;
    // ������ get ��� ������������ ���������.
    // ���������� ��������� �� ����������� �������. ���� ��������� �������,
    // �� ������ ������� �� �����.
    /**
     * \brief ���������� ��������, � ������� ������� ����� �������
     *
     * \return ��������� �� ���������, ���������� ������ � ��������
     *		�� ������� � ������� ����� �����
     *    
     * \remarks ������������ ����. ���� ����������� NULL, �� ������ ����
     * �� ��������� � �����������.
     */
    const CAccuracy* get_accuracy() const;
    /**
     * \brief ���������� ���� nonce ������� �� ����� �������
     *
     * \return ��������� �� ������, �������������� ������� ����� �����
     *
     * \remarks ������������ ����. ���� ����������� NULL, �� ������ ����
     * �� ��������� � �����������.
     */
    const ASN1::CBigInteger* get_nonce() const;
    /**
     * \brief ���������� �������������� ��� ������ ������� �������
     * 
     * \return ��������� �� �����, ���������� ���������� � ������
     *		������� �������
     *
     * \remarks ������������ ����. ���� ����������� NULL, �� ������ ����
     * �� ��������� � �����������.
     */
    const ASN1::CGeneralName* get_tsa() const;
    /**
     * \brief ���������� ������ ����������, ��������� � �����
     *
     * \return ��������� �� ������ ����������, ��������� � ����� �������
     *
     * \remarks ������������ ����. ���� ����������� NULL, �� ������ ����
     * �� ��������� � �����������.
     */
    const ASN1::CExtensions* get_extensions() const;
    /**
     * \brief ���������� ������ ����������� ����������, ��������� � ����� �������
     *
     * \return ��������� �� ������ ����������
     *
     * \remarks ������������ ����. ���� ����������� NULL, �� ������ ����
     * �� ��������� � �����������.
     */
    const ASN1::CAttributes* get_signedAttributes() const;
    /**
     * \brief ���������� ������ ������������� ����������, ��������� � ����� �������
     *
     * \return ��������� �� ������ ����������
     *
     * \remarks ������������ ����. ���� ����������� NULL, �� ������ ����
     * �� ��������� � �����������.
     */
    const ASN1::CAttributes* get_unsignedAttributes() const;
    /**
     * \brief ���������� ����������� ��������� � ����� �������
     *
     * \return ��������� �� ������ �������������� ������������
     *
     * \remarks ������������ ����. ���� ����������� NULL, �� ������ ����
     * �� ��������� � �����������.
     */
    const ASN1::CEncodedCertificateList* get_certificates() const;

    // ������ set ��� ������������ ���������.
    // E��� �������� NULL - �� ����� �������� ������������
    // �������� ��������� � ������� ���������� �� ��������.
    /**
     * \brief ������������� �������� ���� accuracy (�������� � ������� ����� �����)
     *
     * \param accuracy [in] ��������� �� ���������, ���������� ������ � ��������
     *		�� ������� � ������� ����� �����
     *
     * \remarks ������������ ����. ���� �������� NULL, �� ������ ����
     * ���������� �� ����������� � ����������� � ������.
     */
    void put_accuracy( const CAccuracy* accuracy);
    /**
     * \brief ������������� �������� ���� nonce
     *
     * \param nonce [in] ������, �������������� ������� ����� �����
     *
     * \remarks ������������ ����. ���� �������� NULL, �� ������ ����
     * ���������� �� ����������� � ����������� � ������.
     */
    void put_nonce( const ASN1::CBigInteger* nonce);
    /**
     * \brief ������������� �������� ����� ������ ������� �������, �������� �����
     *
     * \param tsa [in] ��������� �� �����, ���������� ����������
     *		� ������ ������� �������
     *
     * \remarks ������������ ����. ���� �������� NULL, �� ������ ����
     * ���������� �� ����������� � ����������� � ������.
     */
    void put_tsa( const ASN1::CGeneralName* tsa);
    /**
     * \brief ���������� ���������� � ����� �������
     *
     * \param extensions [in] ��������� �� ������ ����������
     *
     * \remarks ������������ ����. ���� �������� NULL, �� ������ ����
     * ���������� �� ����������� � ����������� � ������.
     */
    void put_extensions( const ASN1::CExtensions* extensions);
    /**
     * \brief ���������� ����������� �������� � ����� �������
     *
     * \param attributes [in] ��������� �� ������ ���������
     *
     * \remarks ������������ ����. ���� �������� NULL, �� ������ ����
     * ���������� �� ����������� � ����������� � ������.
     */
    void put_signedAttributes( const ASN1::CAttributes* attributes);
    /**
     * \brief ���������� ������������� �������� � ����� �������
     *
     * \param attributes [in] ��������� �� ������ ���������
     *
     * \remarks ������������ ����. ���� �������� NULL, �� ������ ����
     * ���������� �� ����������� � ����������� � ������.
     */
    void put_unsignedAttributes( const ASN1::CAttributes* attributes);
    /**
     * \brief ���������� �������������� ����������� � ����� �������
     *
     * \param certificateList [in] ������ �������������� ������������
     *
     * \remarks ������������ ����. ���� �������� NULL, �� ������ ����
     * ���������� �� ����������� � ����������� � ������.
     */
    void put_certificates( const ASN1::CEncodedCertificateList* certificateList);

    /**
     * \brief �������� ����� ������� � ASN.1 DER �������������
     *
     * \return  ���� ������ ���������� �������������� �������������
     *		������ �������
     */
    CBlob encode() const;
    /**
     * \brief ���������� ����� ������� �� ��� ��������������� ASN.1 DER �������������
     *
     * \param encodedTSToken [in] ���� ������ ���������� �������������� �������������
     *				  ������ �������
     */
    void decode( const CBlob& encodedTSToken);
    /**
     * \brief ����������� ����� �������
     *
     * \param hCryptProv [in] �������� ����������������, �������� �� �������� ����� ������
     * \param dwKeySpec [in] ���������� �����
     * \param encodedCert [in] �������������� ���������� ����������
     * \param hashAlgorithm [in] ��������, ������� ����� �������������� ��� ����������� ������
     *
     * \remarks ������ ������� ������ ���������� ����� ���������� ���� �����, ���������������
     *		����� ������������ ������.
     *
     * �������� ��������, ��� ������ ����� �������� �������������� � �� ���������
     * ������� � ������������ ���������� ���������, ��������� � RFC 3161 (��������,
     * �������� SigningCertificate ��� ��� ��������).
     *		
     */
    void sign(
	HCRYPTPROV hCryptProv,
	DWORD dwKeySpec,
	const CBlob& encodedCert,
	const ASN1::CAlgorithmIdentifierEx& hashAlgorithm);
    /**
     * \brief ��������� ������� ������ �������
     * 
     * \param encodedTSACertificate [in] ����������, �������������� ��� �������� �������
     *
     * \return true, ���� ������� ��������� �������, ����� false
     *
     * �������� ��������, ��� ������ ����� ��������� ������ ������� ������ �������
     * � �� ��������� ������� � ������������ ���������� ���������, ��������� � RFC 3161
     * (��������, �������� SigningCertificate ��� ��� ��������).
     */
    bool verify( const CBlob& encodedTSACertificate) const;
private:
    void clear();
    class Impl;
    Impl* pImpl_;
};

/**
 * \brief �������� �� ������� (RFC 3161, ������ 2.4.2).
 *
 * ������ ��������� ������������ ��� �������� ��������, � �������
 * ������ ������� ������� ��������� ������ �������.
 */
struct TSP_CLASS CAccuracy
{
    /**
     * \brief ������� � �������������� ������
     *
     * \param seconds_ [in] �������� �� ��������
     * \param millis_ [in] �������� �� �������������
     * \param micros_ [in] �������� �� �������������
     */
    CAccuracy( unsigned seconds_ = 0, unsigned millis_ = 0, unsigned micros_ = 0)
    {
	micros = micros_ % 1000;
	millis_ += (micros_ / 1000);
	millis = millis_ % 1000;
	seconds_ += (millis_ / 1000);
	seconds = seconds_;
    }
    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CAccuracy( const CAccuracy& src)
	: seconds(src.seconds), millis(src.millis), micros(src.micros) {}
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CAccuracy& operator=( const CAccuracy& src)
    { seconds = src.seconds; millis = src.millis; micros = src.micros; return *this; }

    unsigned seconds; //!< �������
    unsigned millis; //!< ������������
    unsigned micros; //!< ������������
};

/// ��������� ������� �� ���������
TSP_API bool operator==( const CAccuracy& lhs, const CAccuracy& rhs);
/// ��������� ������� �� �����������
TSP_API bool operator!=( const CAccuracy& lhs, const CAccuracy& rhs);

class CMSRequestImpl;

/**
 * \brief ������ �� ����� ������� Microsoft.
 *
 * ����� ������ ��� ��������, ����������� � ������������� ������� �� ����� �������
 * Microsoft.
 *
 * \remarks ����� ������������� ����������� ������ ������������ �������� ���� timeStampAlgorithm,
 * , contentInfo � attributes. �� �������� ��� ��������� ������ ������� Microsoft ���� 
 * timeStampAlgorithm ����� �������� sz_id_timestampCountersignature, � contentInfo ����� ���
 * szOID_RSA_data � �������� ������ �� ������� �������� ����� (� ������ � Microsoft - 
 * �������� ������� �����). ���� attributes �� �����������.
 */
class TSP_CLASS CMSRequest
{
public:
    /// ������� ������ ������
    CMSRequest();
    /**
     * \brief ������� � �������������� ������
     *
     * \param timeStampAlgorithm [in] OID ��������� ������ �������
     * \param contentInfo [in] ��������� ContentInfo ���������� ������ ��
     *				������� ������������� �����
     */
    CMSRequest(
	const char * timeStampAlgorithm,
	const ASN1::CContentInfo& contentInfo);
    /**
    * \brief ������� ����� ��������� �������.
    * \param src [in] ������, ����� �������� ���������
    */
    CMSRequest( const CMSRequest& src);
    /**
    * \brief �������� �������� ������ � �������.
    *
    * \param src [in] ������, ������� ���������� � �������
    * \return ������ �� ������� ������.
    */
    CMSRequest& operator=( const CMSRequest& src);
    /// ���������� ������
    ~CMSRequest();

    /**
     * \brief �������� ������ �� ����� ������� Microsoft
     *
     * \return  ���� ������ ���������� �������������� �������������
     *		������� �� ����� ������� Authenticode
     */
    CBlob encode() const;
    /**
     * \brief ���������� ������ �� ����� ������� Microsoft �� ��� ��������������� �������������
     *
     * \param encoded [in] ���� ������ ���������� �������������� �������������
     *				  ������� �� ����� ������� Authenticode
     */
    void decode( const CBlob& encoded);

    //get
    /**
     * \brief ���������� OID ��������� ������ ������� Microsoft
     *
     * \return �������� OID
     */
    const char * get_timeStampAlgorithm() const;
    /**
     * \brief ���������� ������ �� ������� ������������� �����
     *
     * \return ��������� ContentInfo, ���������� ������, �� ������� ������������� �����
     */
    const ASN1::CContentInfo& get_contentInfo() const;
    /**
     * \brief ���������� ������ ����������, ��������� � ������ �� ����� ������� Microsoft
     *
     * \return ��������� �� ������ ���������, ��������� � ������
     *
     * \remarks ������������ ����. ���� ����������� NULL, �� ������ ����
     * �� ��������� � �����������.
     */
    const ASN1::CAttributes* get_attributes() const;
    //set
    /**
     * \brief ������������� �������� ������ ������� Microsoft
     *
     * \param timeStampAlgorithm [in] �������� OID
     */
    void put_timeStampAlgorithm( const char * timeStampAlgorithm);
    /**
     * \brief ������������� �������� ������ �� ������� ������������� �����
     *
     * \param contentInfo [in] ��������� ContentInfo, ���������� ������, 
     *				�� ������� ������������� �����
     */
    void put_contentInfo( const ASN1::CContentInfo& contentInfo);
    /**
     * \brief ���������� � ������ ��������
     *
     * \param attributes [in] ��������� �� ������ ���������
     *
     * \remarks ������������ ����. ���� �������� NULL, �� ������ ����
     * ���������� �� ����������� � ����������� � �������.
     */
    void put_attributes( const ASN1::CAttributes* attributes);
private:
    void clear();
    CMSRequestImpl* pImpl_;
};

class CMSStampImpl;
/**
 * \brief ����� ������� Microsoft
 *
 * ����� ������������ ��� ��������, ����������� � �������������
 * ������� ������� Microsoft. ��� ����� �������� ����������� CMS
 * ����������.
 */
class TSP_CLASS CMSStamp
{
public:
    /// ������� ������ ������
    CMSStamp();
    /**
     * \brief ������� � �������������� ������
     *
     * \param content [in] ������ �� ������� �������� �����
     * \param signingTime [in] ����� ������
     */
    CMSStamp( 
	const CBlob& content,
	const CDateTime& signingTime );
    /**
    * \brief ������� ����� ��������� �������.
    * \param src [in] ������, ����� �������� ���������
    */
    CMSStamp( const CMSStamp& src);
    /**
    * \brief �������� �������� ������ � �������.
    *
    * \param src [in] ������, ������� ���������� � �������
    * \return ������ �� ������� ������.
    */
    CMSStamp& operator=( const CMSStamp& src);
    /// ���������� ������
    ~CMSStamp();

    /**
     * \brief �������� ����� ������� Microsoft � ASN.1 DER �������������
     *
     * \return  ���� ������ ���������� �������������� der-�������������
     *		������ ������� Microsoft
     */
    CBlob encode() const;
    /**
     * \brief ���������� ����� ������� Microsoft �� ��� ��������������� ASN.1 DER �������������
     *
     * \param encoded [in] ���� ������ ���������� �������������� �������������
     *				  ������ ������� Microsoft
     */
    void decode( const CBlob& encoded);

    /**
     * \brief ����������� ����� ������� Microsoft
     *
     * \param hCryptProv [in] �������� ����������������, �������� �� �������� ����� ������
     * \param dwKeySpec [in] ���������� �����
     * \param certificate [in] �������������� ���������� ����������
     * \param hashAlgorithm [in] ��������, ������� ����� �������������� ��� ����������� ������
     *
     * \remarks ������ ������� ������ ���������� ����� ���������� ���� �����, ���������������
     *		����� ������������ ������
     */
    void sign(
	HCRYPTPROV hCryptProv,
	DWORD dwKeySpec,
	const CBlob& certificate,
	const ASN1::CAlgorithmIdentifierEx& hashAlgorithm);
    /**
     * \brief ��������� ������� ������ ������� Microsoft
     * 
     * \param certificate [in] ����������, �������������� ��� �������� �������
     *
     * \return true, ���� ������� ��������� �������, ����� false
     */
    bool verify( const CBlob& certificate) const;

    // get
    /**
     * \brief ���������� ������ �� ������� ����� ����� ������� Microsoft
     *
     * \return �������� ���� ������
     */
    const CBlob& get_content() const;
    /**
     * \brief ���������� ����� �� ������
     *
     * \return �������� ���� ������
     */
    const CDateTime& get_signingTime() const;
    /**
     * \brief ���������� ���������� � ���������� ������ (SignerInfo)
     *
     * \return ���������, ���������� ���������� � ����������
     */
    ASN1::CSignerInfo get_signerInfo() const;
    /**
     * \brief ���������� ������ ������������ ��������� � ����� ������� Microsoft
     *
     * \return ��������� �� ������ �������������� ������������
     *
     * \remarks ������������ ����. ���� ����������� NULL, �� ������ ����
     * �� ��������� � �����������.
     */
    const ASN1::CEncodedCertificateList* get_certificates() const;
    // set
    /**
     * \brief ������������� �������� ������ �� ������� �������� ����� ������� Microsoft
     *
     * \param content [in] �������� ���� ������
     */
    void put_content( const CBlob& content) const;
    /**
     * \brief ������������� ����� ������
     *
     * \param signingTime [in] ����� ������
     */
    void put_signingTime( const CDateTime& signingTime);
    /**
     * \brief ��������� ����������� � ����� �������
     *
     * \param certificates [in] ��������� �� ������ �������������� ������������
     *
     * \remarks ������������ ����. ���� �������� NULL, �� ������ ����
     * ���������� �� ����������� � ����������� � ������.
     */
    void put_certificates( const ASN1::CEncodedCertificateList* certificates);
private:
    void clear();
    CMSStampImpl* pImpl_;
};

} // namespace TSP
} // namespace PKI
} // namespace CryptoPro

#endif // _TSP_H_INCLUDED
