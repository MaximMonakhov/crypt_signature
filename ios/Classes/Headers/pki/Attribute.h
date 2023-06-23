/*
 * Copyright(C) 2004 ������ ���
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
 * \brief ������ ����������.
 */

#ifndef _ATTRIBUTE_H_INCLUDED
#define _ATTRIBUTE_H_INCLUDED

#include <cplib/Blob.h>
#include <cplib/DateTime.h>
#include <cplib/StringProxy.h>

#if !defined CPASN1_DLL_DEFINES
#   define CPASN1_DLL_DEFINES
#   if defined _WIN32 && !defined CRYPTCP && !defined CPASN1_STATIC
#	ifdef CPASN1_DLL
#	    define CPASN1_CLASS __declspec(dllexport)
#	    define CPASN1_API __declspec(dllexport)
#	    define CPASN1_DATA __declspec(dllexport)
#	    define CPASN1_EXTERN_TEMPLATE
#	else // defined CPASN1_DLL
#	    define CPASN1_CLASS __declspec(dllimport)
#	    define CPASN1_API __declspec(dllimport)
#	    define CPASN1_DATA __declspec(dllimport)
#	    define CPASN1_EXTERN_TEMPLATE extern
#	    ifndef CP_IGNORE_PRAGMA_MANIFEST
#	        include "asn1_assembly.h"
#	        ifdef _WIN64
#	            pragma comment(linker,"/manifestdependency:\"type='win32' " \
 	            "name='" ASN1_ASSEMBLY_NAME_X64 "' " \
 	            "version='" ASN1_ASSEMBLY_VERSION_X64 "' " \
 	            "processorArchitecture='amd64' " \
 	            "language='*' " \
 	            "publicKeyToken='" ASN1_ASSEMBLY_PUBLICKEYTOKEN_X64 "'\"")
#	        else
#	            pragma comment(linker,"/manifestdependency:\"type='win32' " \
 	            "name='" ASN1_ASSEMBLY_NAME_X86 "' " \
 	            "version='" ASN1_ASSEMBLY_VERSION_X86 "' " \
 	            "processorArchitecture='x86' " \
 	            "language='*' " \
 	            "publicKeyToken='" ASN1_ASSEMBLY_PUBLICKEYTOKEN_X86 "'\"")
# 	        endif
#	    endif
#	endif // !defined CPASN1_DLL
#   else // defined _WIN32 && !defined CRYPTCP && !defined CPASN1_STATIC
#	define CPASN1_CLASS
#	define CPASN1_API
#	define CPASN1_DATA
#	define CPASN1_EXTERN_TEMPLATE
#       define NO_EXPIMP_CDLLLIST_ITERATORS
#   endif // !defined _WIN32 || defined CRYPTCP || defined CPASN1_STATIC
#endif // !defined CPASN1_DLL_DEFINES

#pragma warning(push)
#pragma warning(disable: 4251)

namespace CryptoPro
{

namespace ASN1
{

#define sz_emailAddress "1.2.840.113549.1.9.1"
#define sz_id_at_commonName "2.5.4.3"
#define sz_id_at_surname "2.5.4.4"
#define sz_id_at_serialNumber "2.5.4.5"
#define sz_id_at_countryName "2.5.4.6"
#define sz_id_at_localityName "2.5.4.7"
#define sz_id_at_stateOrProvinceName "2.5.4.8"
#define sz_id_at_organizationName "2.5.4.10"
#define sz_id_at_organizationalUnitName "2.5.4.11"
#define sz_id_at_title "2.5.4.12"
#define sz_id_at_givenName "2.5.4.42"
#define sz_id_at_ogrn "1.2.643.100.1"
#define sz_id_at_ogrnip "1.2.643.100.5"
#define sz_id_at_snils "1.2.643.100.3"
#define sz_id_at_inn "1.2.643.3.131.1.1"
#define sz_id_at_street_address "2.5.4.9"
#define sz_id_at_initials "2.5.4.43"
#define sz_id_at_pseudonym "2.5.4.65"
#define sz_id_contentType "1.2.840.113549.1.9.3"
#define sz_id_aa_signingCertificate "1.2.840.113549.1.9.16.2.12"
#define sz_id_aa_signingCertificateV2 "1.2.840.113549.1.9.16.2.47"
#define sz_id_aa_ets_otherSigCert "1.2.840.113549.1.9.16.2.19"
#define sz_id_signingTime "1.2.840.113549.1.9.5"
#define sz_id_messageDigest "1.2.840.113549.1.9.4"
#define sz_id_aa_signatureTimeStampToken "1.2.840.113549.1.9.16.2.14"
#define sz_id_aa_ets_escTimeStamp "1.2.840.113549.1.9.16.2.25"
#define sz_id_aa_ets_contentTimestamp "1.2.840.113549.1.9.16.2.20"
#define sz_id_aa_ets_certValues "1.2.840.113549.1.9.16.2.23"

class COtherCertIDList;
class CPolicyInformationList;
class CESSCertIDList;
class CESSCertIDv2List;

/// ������ �������������� ������������
typedef CBlobList CEncodedCertificateList;
/// ������ �������������� ������� ������ ������������ (���)
typedef CBlobList CEncodedCrlList;

/**
 * \class CAttrValue Attribute.h <asn1/Attribute.h>
 * \brief �������� ��������.
 *
 * �������� ��������������� � ASN.1 DER �������� �������� 
 * � ���� �������� �������������������
 * � ���� �������� � ���� OID.
 * \sa CAttrValueList, CAttribute, CAttributes
 */
class CPASN1_CLASS CAttrValue
{    
public:
    /// ������� ������ ������
    CAttrValue();
    /**
     * \brief ������� � �������������� ������
     * \param oid [in] OID, ������������ ��� ��������
     */
    CAttrValue(const char * oid);
    /**
     * \brief ������� � �������������� ������
     * \param oid [in] OID, ������������ ��� ��������
     * \param value [in] �������������� �������
     */
    CAttrValue(const char * oid, const CBlob& value);
    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CAttrValue(const CAttrValue& src);
    /// ���������� OID ���� ��������
    const char * get_oid() const;
    /// ���������� �������������� �������� ��������
    const CBlob& get_value() const;
protected:
    CBlob& value();
private:
    CStringProxy oid_;
    CBlob value_;
};

/// �������� �� ��������� �������� ���������
CPASN1_API bool operator==(
    const CAttrValue& lhs,
    const CAttrValue& rhs );
/// �������� �� ����������� �������� ���������
CPASN1_API bool operator!=(
    const CAttrValue& lhs,
    const CAttrValue& rhs );

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CAttrValue, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \class CAttrValueList Attribute.h <asn1/Attribute.h>
 * \brief C����� �������� ���������.
 * \sa CAttrValue, CAttribute, CAttributes
 */
class CPASN1_CLASS CAttrValueList: public CDllList<CAttrValue>
{
    friend CPASN1_API bool operator==(
	const CAttrValueList& lhs,
	const CAttrValueList& rhs );
};

/// �������� ������� �������� ��������� �� ���������
CPASN1_API bool operator==(
    const CAttrValueList& lhs,
    const CAttrValueList& rhs );
/// �������� ������� �������� ��������� �� �����������
CPASN1_API bool operator!=(
    const CAttrValueList& lhs,
    const CAttrValueList& rhs );

class CAttributeImpl;
/**
 * \class CAttribute Attribute.h <asn1/Attribute.h>
 * \brief ������� (RFC 3280).
 *
 * ��� �������� ������������ OID'��. ������ ������� ����� ������ ��������,
 * ������ ��� �������� - ������ ����.
 * \sa CAttrValue, CAttrValueList, CAttributes
 */
class CPASN1_CLASS CAttribute
{
public:
    typedef CAttrValueList ValueList;
    typedef ValueList::iterator value_iterator;
    typedef ValueList::const_iterator const_value_iterator;
public:
    /// ������� ������ ������
    CAttribute();
    /**
     * \brief ������� � �������������� ������
     * \param oid [in] OID ���� ��������
     */
    CAttribute(const char * oid);
    /// ���������� ������
    ~CAttribute();

    /**
     * \brief ������� ����� ��������� �������.
     * \param src [in] ������, ����� �������� ���������
     */
    CAttribute(const CAttribute& src);
    /**
     * \brief �������� �������� ������ � �������.
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CAttribute& operator=( const CAttribute& src);

    /// ���������� OID ���� ��������
    const char * get_oid() const;

    /// ���������� ��������, ����������� �� ������ ������ �������� ��������
    const_value_iterator begin() const;
    /// ���������� ��������, ����������� �� �������, ��������� �� ��������� ��������� ������
    const_value_iterator end() const;
    /// ���������� ��������, ����������� �� ������ ������ �������� ��������
    value_iterator begin();
    /// ���������� ��������, ����������� �� �������, ��������� �� ��������� ��������� ������
    value_iterator end();
    /**
     * \brief ��������� �������������� �������� �������� � ������ ��������
     * \param encodedValue [in] �������������� �������� ��������
     */
    void add( const CBlob& encodedValue);
    /**
     * \brief ��������� �������� �������� � ������ ��������
     * \param value [in] �������� ��������
     */
    void add( const CAttrValue& value);
    /**
     * \brief ������� �������� �������� �� ��������� �������
     * \param position [in] ��������, ����������� �� ��������� �������
     */
    void erase( value_iterator position);
    /// ���������� ������ ������ �������� ��������
    size_t size() const;
    /**
     * \brief �������� ������� � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);

    friend CPASN1_API bool operator==(
	const CAttribute& lhs,
	const CAttribute& rhs );
    friend CPASN1_API bool operator!=(
	const CAttribute& lhs,
	const CAttribute& rhs );
private:
    CAttributeImpl *pImpl_;
};

/// �������� ��������� �� ���������
CPASN1_API bool operator==(
    const CAttribute& lhs,
    const CAttribute& rhs );
/// �������� ��������� �� �����������
CPASN1_API bool operator!=(
    const CAttribute& lhs,
    const CAttribute& rhs );

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CAttribute, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \class CAttributes Attribute.h <asn1/Attribute.h>
 * \brief ������ ��������� (RFC 3280).
 *
 * \sa CAttrValue, CAttrValueList, CAttribute, CDllList
 */
class CPASN1_CLASS CAttributes: public CDllList<CAttribute>
{
public:
    /**
     * \brief ������� ������� ��������� ���� �� ������
     * \param oid [in] OID ���� ��������
     */
    void erase(const char * oid);
    /**
     * \brief ������� ������� � �������� ����� � ������
     * \param oid [in] OID ���� ��������
     * \return ��������, ����������� �� ��������� ������, ���� ��
     * ������� ������ ��������� �� ��������� ���� ������ �� ������.
     */
    iterator find( const char * oid );
    /**
     * \brief ������� ������� � �������� ����� � ������
     * \param oid [in] OID ���� ��������
     * \return ��������, ����������� �� ��������� ������, ���� ��
     * ������� ������ ��������� �� ��������� ���� ������ �� ������.
     */
    const_iterator find( const char * oid ) const;
    /**
     * \brief �������� ������ ��������� � ������� ASN.1 DER � ����������
     * ������������ �������� ������������������
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief �������������� ������ �� �������� �������������� �������� ������������������
     * \sa encode()
     */
    void decode( const CBlob& encoded);
};

/**
 * \class CAttrStringValue Attribute.h <asn1/Attribute.h>
 * \brief ������� ����� ��� �������� ��������� ������� ��������� �������������
 *
 * ������������ ��� ���������, ����������� � ������ ��������� (Distinguished Name)
 * \sa CName
 */
class CPASN1_CLASS CAttrStringValue: public CAttrValue
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param oid [in] OID ���� ��������
     * \param str [in] ��������� ������������� ��������
     */
    CAttrStringValue(const char * oid, const char * str);
    /**
     * \brief ������� � �������������� ������
     * \param oid [in] OID ���� ��������
     * \param str [in] ��������� ������������� ��������
     */
    CAttrStringValue(const char * oid, const wchar_t * str);
};

/**
 * \class CAttrCommonName Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� CommonName (CN) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrCommonName: public CAttrStringValue
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param str [in] ��������� ������������� ��������
     */
    CAttrCommonName( const char * str);
};

/**
 * \class CAttrSurname Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� Surname (SN) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrSurname: public CAttrStringValue
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param str [in] ��������� ������������� ��������
     */
    CAttrSurname( const char * str);
};

/**
 * \class CAttrSerialNumber Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� SerialNumber (SERIALNUMBER) (RFC 4519)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrSerialNumber: public CAttrStringValue
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param str [in] ��������� ������������� ��������
     */
    CAttrSerialNumber( const char * str);
};

/**
 * \class CAttrCountry Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� Country (C) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrCountry: public CAttrStringValue
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param str [in] ��������� ������������� ��������
     */
    CAttrCountry( const char * str);
};

/**
 * \class CAttrLocality Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� Locality (L) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrLocality: public CAttrStringValue
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param str [in] ��������� ������������� ��������
     */
    CAttrLocality( const char * str);
};

/**
 * \class CAttrStateOrProvinceName Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� StateOrProvinceName (ST) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrStateOrProvinceName: public CAttrStringValue
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param str [in] ��������� ������������� ��������
     */
    CAttrStateOrProvinceName( const char * str);
};

/**
 * \class CAttrOrganizationName Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� OrganizationName (O) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrOrganizationName: public CAttrStringValue
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param str [in] ��������� ������������� ��������
     */
    CAttrOrganizationName( const char * str);
};

/**
 * \class CAttrOrganizationalUnitName Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� OrganizationalUnitName (OU) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrOrganizationalUnitName: public CAttrStringValue
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param str [in] ��������� ������������� ��������
     */
    CAttrOrganizationalUnitName( const char * str);
};

/**
 * \class CAttrTitle Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� Title (T) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrTitle: public CAttrStringValue
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param str [in] ��������� ������������� ��������
     */
    CAttrTitle( const char * str);
};

/**
 * \class CAttrGivenName Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� GivenName (GN) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrGivenName: public CAttrStringValue
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param str [in] ��������� ������������� ��������
     */
    CAttrGivenName( const char * str);
};

/**
 * \class CAttrInitials Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� Initials (I) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrInitials: public CAttrStringValue
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param str [in] ��������� ������������� ��������
     */
    CAttrInitials( const char * str);
};

/**
 * \class CAttrPseudonym Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� Pseudonym (PS) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrPseudonym: public CAttrStringValue
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param str [in] ��������� ������������� ��������
     */
    CAttrPseudonym( const char * str);
};

/**
 * \class CAttrEmailAddress Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� EmailAddress (E) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrEmailAddress: public CAttrStringValue
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param str [in] ��������� ������������� ��������
     */
    CAttrEmailAddress( const char * str);
};

class CAttrSigningCertificateImpl;
/**
 * \class CAttrSigningCertificate Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� SigningCertificate (RFC 2634, ������ 5.4)
 *
 * \sa CAttrOtherSigningCertificate
 */
class CPASN1_CLASS CAttrSigningCertificate: public CAttrValue
{
public:
    /// ������� ������ ������
    CAttrSigningCertificate();
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� �������� ��������
     */
    CAttrSigningCertificate( const CBlob& value);
    /**
     * \brief ������� � �������������� ������
     * \param certs [in] ������ ��������������� ������������
     */
    CAttrSigningCertificate( const CESSCertIDList& certs);
    /// ���������� ������
    ~CAttrSigningCertificate();

    // get
    /// ���������� ���� certs
    const CESSCertIDList& get_certs() const;
    /// ���������� ���� policies
    const CPolicyInformationList* get_policies() const;
    // set
    /// ������������� ���� certs
    void put_certs( const CESSCertIDList& certs);
    /// ������������� ���� policies
    void put_policies( const CPolicyInformationList* policies);
private:
    CAttrSigningCertificate( const CAttrSigningCertificate& src);
    CAttrSigningCertificate& operator=( const CAttrSigningCertificate& src);

    CAttrSigningCertificateImpl *pImpl_;

    void encode();
    void decode();
};

class CAttrSigningCertificateV2Impl;
/**
 * \class CAttrSigningCertificateV2 Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� SigningCertificateV2 (RFC 5035, ������ 3)
 *
 * \sa CAttrOtherSigningCertificate, CAttrSigningCertificate
 */
class CPASN1_CLASS CAttrSigningCertificateV2: public CAttrValue
{
public:
    /// ������� ������ ������
    CAttrSigningCertificateV2();
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� �������� ��������
     */
    CAttrSigningCertificateV2( const CBlob& value);
    /**
     * \brief ������� � �������������� ������
     * \param certs [in] ������ ��������������� ������������
     */
    CAttrSigningCertificateV2( const CESSCertIDv2List& certs);
    /// ���������� ������
    ~CAttrSigningCertificateV2();

    // get
    /// ���������� ���� certs
    const CESSCertIDv2List& get_certs() const;
    /// ���������� ���� policies
    const CPolicyInformationList* get_policies() const;
    // set
    /// ������������� ���� certs
    void put_certs( const CESSCertIDv2List& certs);
    /// ������������� ���� policies
    void put_policies( const CPolicyInformationList* policies);
private:
    CAttrSigningCertificateV2( const CAttrSigningCertificateV2& src);
    CAttrSigningCertificateV2& operator=( const CAttrSigningCertificateV2& src);

    CAttrSigningCertificateV2Impl *pImpl_;

    void encode();
    void decode();
};

class CAttrOtherSigningCertificateImpl;
/**
 * \class CAttrOtherSigningCertificate Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� OtherSigningCertificate (RFC 3126, ������ 3.8.2)
 *
 * \sa CAttrSigningCertificate
 */
class CPASN1_CLASS CAttrOtherSigningCertificate: public CAttrValue
{
public:
    /// ������� ������ ������
    CAttrOtherSigningCertificate();
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� �������� ��������
     */
    CAttrOtherSigningCertificate( const CBlob& value);
    /**
     * \brief ������� � �������������� ������
     * \param certs [in] ������ ��������������� ������������
     */
    CAttrOtherSigningCertificate( const COtherCertIDList& certs);
    /// ���������� ������
    ~CAttrOtherSigningCertificate();

    // get
    /// ���������� ���� certs
    const COtherCertIDList& get_certs() const;
    /// ���������� ������������ ���� policies
    const CPolicyInformationList* get_policies() const;
    // set
    /// ������������� ���� certs
    void put_certs( const COtherCertIDList& certs);
    /// ������������� ������������ ���� policies
    void put_policies( const CPolicyInformationList* policies);
private:
    CAttrOtherSigningCertificate( const CAttrOtherSigningCertificate& src);
    CAttrOtherSigningCertificate& operator=( const CAttrOtherSigningCertificate& src);

    CAttrOtherSigningCertificateImpl *pImpl_;

    void encode();
    void decode();
};

class CAttrSigningTimeImpl;
/**
 * \class CAttrSigningTime Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� SigningTime (RFC 3369, ������ 11.3)
 *
 */
class CPASN1_CLASS CAttrSigningTime: public CAttrValue
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param time [in] �����
     */
    CAttrSigningTime( const CDateTime& time);
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� �������� ��������
     */
    CAttrSigningTime( const CBlob& value);
    /// ���������� ������
    ~CAttrSigningTime();

    /// ���������� �����
    CDateTime get_time() const;
    /// ������������� �����
    void put_time( const CDateTime& time);
private:
    CAttrSigningTime( const CAttrSigningTime&);
    CAttrSigningTime& operator=( const CAttrSigningTime&);

    CAttrSigningTimeImpl *pImpl_;

    void encode();
    void decode();
};

/**
 * \class CAttrContentType Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� ContentType (RFC 3369, ������ 11.1)
 *
 */
class CPASN1_CLASS CAttrContentType: public CAttrValue
{
public:
    /**
     * \brief ������� � �������������� ������
     * \param contentType [in] OID ���� �����������
     */
    CAttrContentType( const char * contentType);
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� �������� ��������
     */
    CAttrContentType( const CBlob& value);

    /// ���������� contentType
    const char * get_contentType() const;
    /// ������������� contentType
    void put_contentType( const char * contentType);
private:
    CStringProxy contentType_;
    void encode();
    void decode();
};

/**
 * \class CAttrMessageDigest Attribute.h <asn1/Attribute.h>
 * \brief �������� �������� MessageDigest (RFC 3369, ������ 11.2)
 *
 */
class CPASN1_CLASS CAttrMessageDigest: public CAttrValue
{
public:
    CAttrMessageDigest();
    /**
     * \brief ������� � �������������� ������
     * \param value [in] �������������� �������� ��������
     */
    CAttrMessageDigest( const CBlob& value);

    /// ���������� ��� ���������
    const CBlob& get_messageDigest() const;
    /// ������������� ��� ���������
    void put_messageDigest( const CBlob& messageDigest);
private:
    CBlob messageDigest_;
    void encode();
    void decode();
};

/// ��� ������
enum StringType
{
    /// ������������ �������� �� ��������� ��� ������� ��������
    stDefault,
    /// ���������� � ASN.1
    stUTF8String,
    /// ���������� � ASN.1
    stPrintableString,
    /// ���������� � ASN.1
    stTeletexString,
    /// ���������� � ASN.1
    stBMPString,
    /// ���������� � ASN.1
    stIA5String,
    /// ���������� � ASN.1
    stUniversalString
};

/**
 * \brief ���������� ������ �� ASN.1 DER �������������
 * \param encoded [in] �������������� ������
 * \return ��������������� ������.
 */
CPASN1_API CWStringProxy decodeCharString( const CBlob& encoded);
/**
 * \brief �������� ������ � ASN.1 DER �������������
 * \param string [in] ������
 * \param stringType [in] ��� ASN.1 ������, � ������� ����������
 * \return �������������� ������.
 */
CPASN1_API CBlob encodeCharString( 
    const wchar_t * string, StringType stringType);

/**
 * \class CAttributeTypeAndValue Attribute.h <asn1/Attribute.h>
 * \brief ASN.1 ��������� AttributeTypeAndValue (RFC 3280, ������ 4.1.2.4)
 *
 */
class CPASN1_CLASS CAttributeTypeAndValue
{
public:
    /// ������� ������ ������
    CAttributeTypeAndValue();
    /**
     * \brief ������� � �������������� ������
     * \param attrValue [in] �������� ��������
     */
    CAttributeTypeAndValue( const CAttrValue& attrValue);
    /**
     * \brief ������� � �������������� ������
     * \param type [in] OID ���� ��������
     * \param value [in] �������������� �������� ��������
     */
    CAttributeTypeAndValue( const char * type, const CBlob& value);
    /**
     * \brief ������� � �������������� ������
     * \param type [in] OID ���� �������� ��� ��� ������������� ("CN","C","OU")
     * \param value [in] ��������� ������������� �������� ��������
     * \param stringType [in] ASN.1 ��� ������ �������� ��������
     */
    CAttributeTypeAndValue( 
	const wchar_t * type, const wchar_t * value,
	StringType stringType = stDefault);
    /**
     * \brief ������� � �������������� ������
     * \param str [in] ��������� ������������� �������� ("CN=Ivan Ivanov")
     * \param stringType [in] ASN.1 ��� ������ �������� ��������
     */
    CAttributeTypeAndValue( 
	const wchar_t * str,
	StringType stringType = stDefault);
    /**
     * \brief ������� ����� ��������� �������.
     *
     * \param src [in] ������, ����� �������� ���������
     */
    CAttributeTypeAndValue( const CAttributeTypeAndValue& src);
    /**
     * \brief �������� �������� ������ � �������.
     *
     * \param src [in] ������, ������� ���������� � �������
     * \return ������ �� ������� ������.
     */
    CAttributeTypeAndValue& operator=( const CAttributeTypeAndValue& src);

    /// ���������� OID ���� ��������
    const char * get_type() const;
    /// ���������� ��������� ������������� ���� �������� (��������: "CN","OU","1.2.4.6")
    CWStringProxy get_type_str() const;
    /// ���������� �������������� �������� ��������
    CBlob get_value() const;
    /// ���������� ��������� ������������� �������� �������� (��������: "Ivan Ivanov", "#04020102")
    CWStringProxy get_value_str() const;

    /// ������������� OID ���� ��������
    void put_type( const char * type);
    /**
     * \brief ������������� ��� ��������
     * \param type [in] ��������� ������������� ���� (��������: "CN","OU","1.2.4.6")
     */
    void put_type_str( const wchar_t * type);
    /**
     * \brief ������������� �������� ��������
     * \param value [in] �������������� �������� ��������
     */
    void put_value( const CBlob& value);
    /**
     * \brief ������������� �������� ��������
     * \param value [in] ��������� ������������� �������� �������� (��������: "Ivan Ivanov", "#04020102")
     * \param stringType [in] ASN.1 ��� ������ �������� ��������
     */
    void put_value_str(
	const wchar_t * value, 
	StringType stringType = stDefault);

    /**
     * \brief ���������� ��������� ������������� ���� � �������� �������� 
     * 
     * ��������: "CN=Ivan Ivanov", "1.2.4.6=#04020102"
     */
    CWStringProxy toString() const;
    /**
     * \brief �������������� ������ �� ���������� �������������
     * \param str [in] ��������� ������������� �������� ("CN=Ivan Ivanov","1.2.4.6=#04020102")
     * \param stringType [in] ASN.1 ��� ������ �������� ��������
     */
    void fromString( 
	const wchar_t * str,
	StringType stringType = stDefault);

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
private:
    CStringProxy type_;
    CBlob value_;
};

/// ��������� ������� �� ���������
CPASN1_API bool operator==(
    const CAttributeTypeAndValue& lhs,
    const CAttributeTypeAndValue& rhs );
/// ��������� ������� �� �����������
CPASN1_API bool operator!=(
    const CAttributeTypeAndValue& lhs,
    const CAttributeTypeAndValue& rhs );

// VS2008 bug/feature: ������� ���������������� �������� ��������� �������
// (����� - ����������) ������ ���������� ������� ����������������� �������
// �������� ������ (����� - CDllList<>), ����� �� DLL �� ����� ��������������
// ������ ��������� �������.
EXPIMP_CDLLLIST_ITERATORS(CAttributeTypeAndValue, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \class CAttributeTypeAndValueSet Attribute.h <asn1/Attribute.h>
 * \brief ����� �������� �AttributeTypeAndValue
 */
class CPASN1_CLASS CAttributeTypeAndValueSet: public CDllList<CAttributeTypeAndValue>
{
    friend CPASN1_API bool operator==(
	const CAttributeTypeAndValueSet& lhs,
	const CAttributeTypeAndValueSet& rhs );
};

/// ��������� ������� �� ���������
CPASN1_API bool operator==(
    const CAttributeTypeAndValueSet& lhs,
    const CAttributeTypeAndValueSet& rhs );
/// ��������� ������� �� �����������
CPASN1_API bool operator!=(
    const CAttributeTypeAndValueSet& lhs,
    const CAttributeTypeAndValueSet& rhs );

/**
 * \class CCertificateValues Attribute.h <asn1/Attribute.h>
 * \brief ����� �������� CCertificateValues
 */
class CPASN1_CLASS CCertificateValues: public CEncodedCertificateList
{
public:
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
};


} // namespace ASN1

} // namespace CryptoPro

#pragma warning(pop)

#endif //_ATTRIBUTE_H_INCLUDED
