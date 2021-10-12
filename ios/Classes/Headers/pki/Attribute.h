/*
 * Copyright(C) 2004 Проект ИОК
 *
 * Этот файл содержит информацию, являющуюся
 * собственностью компании Крипто Про.
 *
 * Любая часть этого файла не может быть скопирована,
 * исправлена, переведена на другие языки,
 * локализована или модифицирована любым способом,
 * откомпилирована, передана по сети с или на
 * любую компьютерную систему без предварительного
 * заключения соглашения с компанией Крипто Про.
 */

/*!
 * \file $RCSfile$
 * \version $Revision: 194763 $
 * \date $Date:: 2019-06-17 17:39:27 +0400#$
 * \author $Author: sdenis $
 *
 * \brief Классы аттрибутов.
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

/// Список закодированных сертификатов
typedef CBlobList CEncodedCertificateList;
/// Список закодированных списков отзыва сертификатов (СОС)
typedef CBlobList CEncodedCrlList;

/**
 * \class CAttrValue Attribute.h <asn1/Attribute.h>
 * \brief Значение атрибута.
 *
 * Хранение закодированного в ASN.1 DER значения атрибута 
 * в виде двоичной последовательностьи
 * и типа атрибута в виде OID.
 * \sa CAttrValueList, CAttribute, CAttributes
 */
class CPASN1_CLASS CAttrValue
{    
public:
    /// Создает пустой объект
    CAttrValue();
    /**
     * \brief Создает и инициализирует объект
     * \param oid [in] OID, обозначающий тип атрибута
     */
    CAttrValue(const char * oid);
    /**
     * \brief Создает и инициализирует объект
     * \param oid [in] OID, обозначающий тип атрибута
     * \param value [in] закодированное атрибут
     */
    CAttrValue(const char * oid, const CBlob& value);
    /**
     * \brief Создает копию заданного объекта.
     *
     * \param src [in] объект, копия которого создается
     */
    CAttrValue(const CAttrValue& src);
    /// Возвращает OID типа атрибута
    const char * get_oid() const;
    /// Возвращает закодированное значение атрибута
    const CBlob& get_value() const;
protected:
    CBlob& value();
private:
    CStringProxy oid_;
    CBlob value_;
};

/// Проверка на равенство значений атрибутов
CPASN1_API bool operator==(
    const CAttrValue& lhs,
    const CAttrValue& rhs );
/// Проверка на неравенство значений атрибутов
CPASN1_API bool operator!=(
    const CAttrValue& lhs,
    const CAttrValue& rhs );

// VS2008 bug/feature: Экспорт инстанцированных шаблонов вложенных классов
// (здесь - итераторов) должен предварять экспорт инстанцированного шаблона
// внешнего класса (здесь - CDllList<>), иначе из DLL не будут экспортированы
// методы вложенных классов.
EXPIMP_CDLLLIST_ITERATORS(CAttrValue, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \class CAttrValueList Attribute.h <asn1/Attribute.h>
 * \brief Cписок значений атрибутов.
 * \sa CAttrValue, CAttribute, CAttributes
 */
class CPASN1_CLASS CAttrValueList: public CDllList<CAttrValue>
{
    friend CPASN1_API bool operator==(
	const CAttrValueList& lhs,
	const CAttrValueList& rhs );
};

/// Проверка списков значений атрибутов на равенство
CPASN1_API bool operator==(
    const CAttrValueList& lhs,
    const CAttrValueList& rhs );
/// Проверка списков значений атрибутов на неравенство
CPASN1_API bool operator!=(
    const CAttrValueList& lhs,
    const CAttrValueList& rhs );

class CAttributeImpl;
/**
 * \class CAttribute Attribute.h <asn1/Attribute.h>
 * \brief Атрибут (RFC 3280).
 *
 * Тип атрибута определяется OID'ом. Каждый атрибут имеет список значений,
 * причем все значения - одного типа.
 * \sa CAttrValue, CAttrValueList, CAttributes
 */
class CPASN1_CLASS CAttribute
{
public:
    typedef CAttrValueList ValueList;
    typedef ValueList::iterator value_iterator;
    typedef ValueList::const_iterator const_value_iterator;
public:
    /// Создает пустой объект
    CAttribute();
    /**
     * \brief Создает и инициализирует объект
     * \param oid [in] OID типа атрибута
     */
    CAttribute(const char * oid);
    /// Уничтожает объект
    ~CAttribute();

    /**
     * \brief Создает копию заданного объекта.
     * \param src [in] объект, копия которого создается
     */
    CAttribute(const CAttribute& src);
    /**
     * \brief Копирует заданный объект в текущий.
     * \param src [in] объект, который копируется в текущий
     * \return Ссылка на текущий объект.
     */
    CAttribute& operator=( const CAttribute& src);

    /// возвращает OID типа атрибута
    const char * get_oid() const;

    /// возвращает итератор, указывающий на начало списка значений атрибута
    const_value_iterator begin() const;
    /// возвращает итератор, указывающий на элемент, следующий за последним элементом списка
    const_value_iterator end() const;
    /// возвращает итератор, указывающий на начало списка значений атрибута
    value_iterator begin();
    /// возвращает итератор, указывающий на элемент, следующий за последним элементом списка
    value_iterator end();
    /**
     * \brief Добавляет закодированное значение атрибута в список значений
     * \param encodedValue [in] закодированное значение атрибута
     */
    void add( const CBlob& encodedValue);
    /**
     * \brief Добавляет значение атрибута в список значений
     * \param value [in] значение атрибута
     */
    void add( const CAttrValue& value);
    /**
     * \brief Удаляет значение атрибута из указанной позиции
     * \param position [in] итератор, указывающий на удаляемый элемент
     */
    void erase( value_iterator position);
    /// Возвращает размер списка значений атрибута
    size_t size() const;
    /**
     * \brief Кодирует атрибут в формате ASN.1 DER и возвращает
     * получившуюся двоичную последовательность
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief Инициализирует объект из заданной закодированной двоичной последовательности
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

/// Проверка атрибутов на равенство
CPASN1_API bool operator==(
    const CAttribute& lhs,
    const CAttribute& rhs );
/// Проверка атрибутов на неравенство
CPASN1_API bool operator!=(
    const CAttribute& lhs,
    const CAttribute& rhs );

// VS2008 bug/feature: Экспорт инстанцированных шаблонов вложенных классов
// (здесь - итераторов) должен предварять экспорт инстанцированного шаблона
// внешнего класса (здесь - CDllList<>), иначе из DLL не будут экспортированы
// методы вложенных классов.
EXPIMP_CDLLLIST_ITERATORS(CAttribute, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \class CAttributes Attribute.h <asn1/Attribute.h>
 * \brief Список атрибутов (RFC 3280).
 *
 * \sa CAttrValue, CAttrValueList, CAttribute, CDllList
 */
class CPASN1_CLASS CAttributes: public CDllList<CAttribute>
{
public:
    /**
     * \brief Удаляет атрибут заданного типа из списка
     * \param oid [in] OID типа атрибута
     */
    void erase(const char * oid);
    /**
     * \brief Находит атрибут с заданным типом в списке
     * \param oid [in] OID типа атрибута
     * \return Итератор, указывающий на найденный объект, либо на
     * элемент списка следующий за последним если объект не найден.
     */
    iterator find( const char * oid );
    /**
     * \brief Находит атрибут с заданным типом в списке
     * \param oid [in] OID типа атрибута
     * \return Итератор, указывающий на найденный объект, либо на
     * элемент списка следующий за последним если объект не найден.
     */
    const_iterator find( const char * oid ) const;
    /**
     * \brief Кодирует список атрибутов в формате ASN.1 DER и возвращает
     * получившуюся двоичную последовательность
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief Инициализирует объект из заданной закодированной двоичной последовательности
     * \sa encode()
     */
    void decode( const CBlob& encoded);
};

/**
 * \class CAttrStringValue Attribute.h <asn1/Attribute.h>
 * \brief Базовый класс для значений атрибутов имеющих строковое представление
 *
 * Предназначен для атрибутов, участвующих в именах субъектов (Distinguished Name)
 * \sa CName
 */
class CPASN1_CLASS CAttrStringValue: public CAttrValue
{
public:
    /**
     * \brief Создает и инициализирует объект
     * \param oid [in] OID типа атрибута
     * \param str [in] строковое представление атрибута
     */
    CAttrStringValue(const char * oid, const char * str);
    /**
     * \brief Создает и инициализирует объект
     * \param oid [in] OID типа атрибута
     * \param str [in] строковое представление атрибута
     */
    CAttrStringValue(const char * oid, const wchar_t * str);
};

/**
 * \class CAttrCommonName Attribute.h <asn1/Attribute.h>
 * \brief Значение атрибута CommonName (CN) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrCommonName: public CAttrStringValue
{
public:
    /**
     * \brief Создает и инициализирует объект
     * \param str [in] строковое представление атрибута
     */
    CAttrCommonName( const char * str);
};

/**
 * \class CAttrSurname Attribute.h <asn1/Attribute.h>
 * \brief Значение атрибута Surname (SN) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrSurname: public CAttrStringValue
{
public:
    /**
     * \brief Создает и инициализирует объект
     * \param str [in] строковое представление атрибута
     */
    CAttrSurname( const char * str);
};

/**
 * \class CAttrSerialNumber Attribute.h <asn1/Attribute.h>
 * \brief Значение атрибута SerialNumber (SERIALNUMBER) (RFC 4519)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrSerialNumber: public CAttrStringValue
{
public:
    /**
     * \brief Создает и инициализирует объект
     * \param str [in] строковое представление атрибута
     */
    CAttrSerialNumber( const char * str);
};

/**
 * \class CAttrCountry Attribute.h <asn1/Attribute.h>
 * \brief Значение атрибута Country (C) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrCountry: public CAttrStringValue
{
public:
    /**
     * \brief Создает и инициализирует объект
     * \param str [in] строковое представление атрибута
     */
    CAttrCountry( const char * str);
};

/**
 * \class CAttrLocality Attribute.h <asn1/Attribute.h>
 * \brief Значение атрибута Locality (L) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrLocality: public CAttrStringValue
{
public:
    /**
     * \brief Создает и инициализирует объект
     * \param str [in] строковое представление атрибута
     */
    CAttrLocality( const char * str);
};

/**
 * \class CAttrStateOrProvinceName Attribute.h <asn1/Attribute.h>
 * \brief Значение атрибута StateOrProvinceName (ST) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrStateOrProvinceName: public CAttrStringValue
{
public:
    /**
     * \brief Создает и инициализирует объект
     * \param str [in] строковое представление атрибута
     */
    CAttrStateOrProvinceName( const char * str);
};

/**
 * \class CAttrOrganizationName Attribute.h <asn1/Attribute.h>
 * \brief Значение атрибута OrganizationName (O) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrOrganizationName: public CAttrStringValue
{
public:
    /**
     * \brief Создает и инициализирует объект
     * \param str [in] строковое представление атрибута
     */
    CAttrOrganizationName( const char * str);
};

/**
 * \class CAttrOrganizationalUnitName Attribute.h <asn1/Attribute.h>
 * \brief Значение атрибута OrganizationalUnitName (OU) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrOrganizationalUnitName: public CAttrStringValue
{
public:
    /**
     * \brief Создает и инициализирует объект
     * \param str [in] строковое представление атрибута
     */
    CAttrOrganizationalUnitName( const char * str);
};

/**
 * \class CAttrTitle Attribute.h <asn1/Attribute.h>
 * \brief Значение атрибута Title (T) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrTitle: public CAttrStringValue
{
public:
    /**
     * \brief Создает и инициализирует объект
     * \param str [in] строковое представление атрибута
     */
    CAttrTitle( const char * str);
};

/**
 * \class CAttrGivenName Attribute.h <asn1/Attribute.h>
 * \brief Значение атрибута GivenName (GN) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrGivenName: public CAttrStringValue
{
public:
    /**
     * \brief Создает и инициализирует объект
     * \param str [in] строковое представление атрибута
     */
    CAttrGivenName( const char * str);
};

/**
 * \class CAttrInitials Attribute.h <asn1/Attribute.h>
 * \brief Значение атрибута Initials (I) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrInitials: public CAttrStringValue
{
public:
    /**
     * \brief Создает и инициализирует объект
     * \param str [in] строковое представление атрибута
     */
    CAttrInitials( const char * str);
};

/**
 * \class CAttrPseudonym Attribute.h <asn1/Attribute.h>
 * \brief Значение атрибута Pseudonym (PS) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrPseudonym: public CAttrStringValue
{
public:
    /**
     * \brief Создает и инициализирует объект
     * \param str [in] строковое представление атрибута
     */
    CAttrPseudonym( const char * str);
};

/**
 * \class CAttrEmailAddress Attribute.h <asn1/Attribute.h>
 * \brief Значение атрибута EmailAddress (E) (RFC 2253)
 *
 * \sa CName
 */
class CPASN1_CLASS CAttrEmailAddress: public CAttrStringValue
{
public:
    /**
     * \brief Создает и инициализирует объект
     * \param str [in] строковое представление атрибута
     */
    CAttrEmailAddress( const char * str);
};

class CAttrSigningCertificateImpl;
/**
 * \class CAttrSigningCertificate Attribute.h <asn1/Attribute.h>
 * \brief Значение атрибута SigningCertificate (RFC 2634, раздел 5.4)
 *
 * \sa CAttrOtherSigningCertificate
 */
class CPASN1_CLASS CAttrSigningCertificate: public CAttrValue
{
public:
    /// Создает пустой объект
    CAttrSigningCertificate();
    /**
     * \brief Создает и инициализирует объект
     * \param value [in] закодированное значение атрибута
     */
    CAttrSigningCertificate( const CBlob& value);
    /**
     * \brief Создает и инициализирует объект
     * \param certs [in] список идентификаторов сертификатов
     */
    CAttrSigningCertificate( const CESSCertIDList& certs);
    /// Уничтожает объект
    ~CAttrSigningCertificate();

    // get
    /// возвращает поле certs
    const CESSCertIDList& get_certs() const;
    /// возвращает поле policies
    const CPolicyInformationList* get_policies() const;
    // set
    /// устанавливает поле certs
    void put_certs( const CESSCertIDList& certs);
    /// устанавливает поле policies
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
 * \brief Значение атрибута SigningCertificateV2 (RFC 5035, раздел 3)
 *
 * \sa CAttrOtherSigningCertificate, CAttrSigningCertificate
 */
class CPASN1_CLASS CAttrSigningCertificateV2: public CAttrValue
{
public:
    /// Создает пустой объект
    CAttrSigningCertificateV2();
    /**
     * \brief Создает и инициализирует объект
     * \param value [in] закодированное значение атрибута
     */
    CAttrSigningCertificateV2( const CBlob& value);
    /**
     * \brief Создает и инициализирует объект
     * \param certs [in] список идентификаторов сертификатов
     */
    CAttrSigningCertificateV2( const CESSCertIDv2List& certs);
    /// Уничтожает объект
    ~CAttrSigningCertificateV2();

    // get
    /// возвращает поле certs
    const CESSCertIDv2List& get_certs() const;
    /// возвращает поле policies
    const CPolicyInformationList* get_policies() const;
    // set
    /// устанавливает поле certs
    void put_certs( const CESSCertIDv2List& certs);
    /// устанавливает поле policies
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
 * \brief Значение атрибута OtherSigningCertificate (RFC 3126, раздел 3.8.2)
 *
 * \sa CAttrSigningCertificate
 */
class CPASN1_CLASS CAttrOtherSigningCertificate: public CAttrValue
{
public:
    /// Создает пустой объект
    CAttrOtherSigningCertificate();
    /**
     * \brief Создает и инициализирует объект
     * \param value [in] закодированное значение атрибута
     */
    CAttrOtherSigningCertificate( const CBlob& value);
    /**
     * \brief Создает и инициализирует объект
     * \param certs [in] список идентификаторов сертификатов
     */
    CAttrOtherSigningCertificate( const COtherCertIDList& certs);
    /// Уничтожает объект
    ~CAttrOtherSigningCertificate();

    // get
    /// возвращает поле certs
    const COtherCertIDList& get_certs() const;
    /// возвращает опциональное поле policies
    const CPolicyInformationList* get_policies() const;
    // set
    /// устанавливает поле certs
    void put_certs( const COtherCertIDList& certs);
    /// устанавливает опциональное поле policies
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
 * \brief Значение атрибута SigningTime (RFC 3369, раздел 11.3)
 *
 */
class CPASN1_CLASS CAttrSigningTime: public CAttrValue
{
public:
    /**
     * \brief Создает и инициализирует объект
     * \param time [in] время
     */
    CAttrSigningTime( const CDateTime& time);
    /**
     * \brief Создает и инициализирует объект
     * \param value [in] закодированное значение атрибута
     */
    CAttrSigningTime( const CBlob& value);
    /// Уничтожает объект
    ~CAttrSigningTime();

    /// возвращает время
    CDateTime get_time() const;
    /// устанавливает время
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
 * \brief Значение атрибута ContentType (RFC 3369, раздел 11.1)
 *
 */
class CPASN1_CLASS CAttrContentType: public CAttrValue
{
public:
    /**
     * \brief Создает и инициализирует объект
     * \param contentType [in] OID типа содержимого
     */
    CAttrContentType( const char * contentType);
    /**
     * \brief Создает и инициализирует объект
     * \param value [in] закодированное значение атрибута
     */
    CAttrContentType( const CBlob& value);

    /// возвращает contentType
    const char * get_contentType() const;
    /// устанавливает contentType
    void put_contentType( const char * contentType);
private:
    CStringProxy contentType_;
    void encode();
    void decode();
};

/**
 * \class CAttrMessageDigest Attribute.h <asn1/Attribute.h>
 * \brief Значение атрибута MessageDigest (RFC 3369, раздел 11.2)
 *
 */
class CPASN1_CLASS CAttrMessageDigest: public CAttrValue
{
public:
    CAttrMessageDigest();
    /**
     * \brief Создает и инициализирует объект
     * \param value [in] закодированное значение атрибута
     */
    CAttrMessageDigest( const CBlob& value);

    /// возвращает хэш сообщения
    const CBlob& get_messageDigest() const;
    /// устанавливает хэш сообщения
    void put_messageDigest( const CBlob& messageDigest);
private:
    CBlob messageDigest_;
    void encode();
    void decode();
};

/// Тип строки
enum StringType
{
    /// использовать значение по умолчанию для данного атрибута
    stDefault,
    /// определено в ASN.1
    stUTF8String,
    /// определено в ASN.1
    stPrintableString,
    /// определено в ASN.1
    stTeletexString,
    /// определено в ASN.1
    stBMPString,
    /// определено в ASN.1
    stIA5String,
    /// определено в ASN.1
    stUniversalString
};

/**
 * \brief Декодирует строку из ASN.1 DER представления
 * \param encoded [in] закодированная строка
 * \return Раскодированная строка.
 */
CPASN1_API CWStringProxy decodeCharString( const CBlob& encoded);
/**
 * \brief Кодирует строку в ASN.1 DER представление
 * \param string [in] строка
 * \param stringType [in] тип ASN.1 строки, в который кодировать
 * \return Закодированная строка.
 */
CPASN1_API CBlob encodeCharString( 
    const wchar_t * string, StringType stringType);

/**
 * \class CAttributeTypeAndValue Attribute.h <asn1/Attribute.h>
 * \brief ASN.1 структура AttributeTypeAndValue (RFC 3280, раздел 4.1.2.4)
 *
 */
class CPASN1_CLASS CAttributeTypeAndValue
{
public:
    /// Создает пустой объект
    CAttributeTypeAndValue();
    /**
     * \brief Создает и инициализирует объект
     * \param attrValue [in] значение атрибута
     */
    CAttributeTypeAndValue( const CAttrValue& attrValue);
    /**
     * \brief Создает и инициализирует объект
     * \param type [in] OID типа атрибута
     * \param value [in] закодированное значение атрибута
     */
    CAttributeTypeAndValue( const char * type, const CBlob& value);
    /**
     * \brief Создает и инициализирует объект
     * \param type [in] OID типа атрибута или его идентификатор ("CN","C","OU")
     * \param value [in] строковое представление значения атрибута
     * \param stringType [in] ASN.1 тип строки значения атрибута
     */
    CAttributeTypeAndValue( 
	const wchar_t * type, const wchar_t * value,
	StringType stringType = stDefault);
    /**
     * \brief Создает и инициализирует объект
     * \param str [in] строковое представление атрибута ("CN=Ivan Ivanov")
     * \param stringType [in] ASN.1 тип строки значения атрибута
     */
    CAttributeTypeAndValue( 
	const wchar_t * str,
	StringType stringType = stDefault);
    /**
     * \brief Создает копию заданного объекта.
     *
     * \param src [in] объект, копия которого создается
     */
    CAttributeTypeAndValue( const CAttributeTypeAndValue& src);
    /**
     * \brief Копирует заданный объект в текущий.
     *
     * \param src [in] объект, который копируется в текущий
     * \return Ссылка на текущий объект.
     */
    CAttributeTypeAndValue& operator=( const CAttributeTypeAndValue& src);

    /// возвращает OID типа атрибута
    const char * get_type() const;
    /// возвращает строковое представление типа атрибута (варианты: "CN","OU","1.2.4.6")
    CWStringProxy get_type_str() const;
    /// возвращает закодированное значение атрибута
    CBlob get_value() const;
    /// возвращает строковое представление значения атрибута (варианты: "Ivan Ivanov", "#04020102")
    CWStringProxy get_value_str() const;

    /// устанавливает OID типа атрибута
    void put_type( const char * type);
    /**
     * \brief устанавливает тип атрибута
     * \param type [in] строковое представление типа (варианты: "CN","OU","1.2.4.6")
     */
    void put_type_str( const wchar_t * type);
    /**
     * \brief устанавливает значение атрибута
     * \param value [in] закодированное значение атрибута
     */
    void put_value( const CBlob& value);
    /**
     * \brief устанавливает значение атрибута
     * \param value [in] строковое представление значения атрибута (варианты: "Ivan Ivanov", "#04020102")
     * \param stringType [in] ASN.1 тип строки значения атрибута
     */
    void put_value_str(
	const wchar_t * value, 
	StringType stringType = stDefault);

    /**
     * \brief возвращает строковое представление типа и значения атрибута 
     * 
     * Например: "CN=Ivan Ivanov", "1.2.4.6=#04020102"
     */
    CWStringProxy toString() const;
    /**
     * \brief инициализирует объект из строкового представления
     * \param str [in] строковое представление атрибута ("CN=Ivan Ivanov","1.2.4.6=#04020102")
     * \param stringType [in] ASN.1 тип строки значения атрибута
     */
    void fromString( 
	const wchar_t * str,
	StringType stringType = stDefault);

    /**
     * \brief Кодирует объект в формате ASN.1 DER и возвращает
     * получившуюся двоичную последовательность
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief Инициализирует объект из заданной закодированной двоичной последовательности
     * \sa encode()
     */
    void decode( const CBlob& encoded);
private:
    CStringProxy type_;
    CBlob value_;
};

/// проверяет объекты на равенство
CPASN1_API bool operator==(
    const CAttributeTypeAndValue& lhs,
    const CAttributeTypeAndValue& rhs );
/// проверяет объекты на неравенство
CPASN1_API bool operator!=(
    const CAttributeTypeAndValue& lhs,
    const CAttributeTypeAndValue& rhs );

// VS2008 bug/feature: Экспорт инстанцированных шаблонов вложенных классов
// (здесь - итераторов) должен предварять экспорт инстанцированного шаблона
// внешнего класса (здесь - CDllList<>), иначе из DLL не будут экспортированы
// методы вложенных классов.
EXPIMP_CDLLLIST_ITERATORS(CAttributeTypeAndValue, CPASN1_EXTERN_TEMPLATE, CPASN1_CLASS);

/**
 * \class CAttributeTypeAndValueSet Attribute.h <asn1/Attribute.h>
 * \brief Набор объектов СAttributeTypeAndValue
 */
class CPASN1_CLASS CAttributeTypeAndValueSet: public CDllList<CAttributeTypeAndValue>
{
    friend CPASN1_API bool operator==(
	const CAttributeTypeAndValueSet& lhs,
	const CAttributeTypeAndValueSet& rhs );
};

/// проверяет объекты на равенство
CPASN1_API bool operator==(
    const CAttributeTypeAndValueSet& lhs,
    const CAttributeTypeAndValueSet& rhs );
/// проверяет объекты на неравенство
CPASN1_API bool operator!=(
    const CAttributeTypeAndValueSet& lhs,
    const CAttributeTypeAndValueSet& rhs );

/**
 * \class CCertificateValues Attribute.h <asn1/Attribute.h>
 * \brief Набор объектов CCertificateValues
 */
class CPASN1_CLASS CCertificateValues: public CEncodedCertificateList
{
public:
    /**
     * \brief Кодирует объект в формате ASN.1 DER и возвращает
     * получившуюся двоичную последовательность
     * \sa decode()
     */
    CBlob encode() const;
    /**
     * \brief Инициализирует объект из заданной закодированной двоичной последовательности
     * \sa encode()
     */
    void decode( const CBlob& encoded);
};


} // namespace ASN1

} // namespace CryptoPro

#pragma warning(pop)

#endif //_ATTRIBUTE_H_INCLUDED
