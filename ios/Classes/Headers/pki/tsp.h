/*
 * Copyright(C) 2004-2006 Проект ИОК
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
 * \brief Классы для работы с TSP (Time-Stamp Protocol)
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
 * \mainpage Низкоуровневый интерфейс КриптоПро TSP
 *
 * Низкоуровневый интерфейс из состава КриптоПро TSP SDK предназначен 
 * для работы со штампами времени. Использование данного интерфейса упрощает 
 * реализацию служб штампов и делает возможным встраивание службы в 
 * существующую систему.
 * 
 * Низкоуровневый интерфейс представляет собой библиотеку классов C++. 
 *
 * В библиотеке реализована поддержка структур данных, описанных в RFC 3161, 
 * и штампов времени, используемых Microsoft для подписи исполняемых файлов 
 * (в технологии Authenticode).
 * 
 * \section contents Состав
 *
 * Для поддержки протокола штампов времени, описанного в RFC 3161, 
 * предоставляются следующие классы:
 * - \link CryptoPro::PKI::TSP::CRequest CRequest\endlink - запрос на 
 * штамп времени
 * - \link CryptoPro::PKI::TSP::CResponse CResponse\endlink - ответ 
 * службы штампов времени
 * - \link CryptoPro::PKI::TSP::CToken CToken\endlink - штамп времени
 *
 * Для поддержки штампов времени Microsoft предоставляются классы:
 * - \link CryptoPro::PKI::TSP::CMSRequest CMSRequest\endlink - запрос на 
 * штамп времени Microsoft
 * - \link CryptoPro::PKI::TSP::CMSStamp CMSStamp\endlink - штамп времени 
 * Microsoft
 *
 * \section usage Особенности
 *
 * Доступ к полям структур в библиотеке осуществляется следующим способом:
 * - если поле обязательное, то оно устанавливается и возвращается как 
 * ссылка на объект. Эта ссылка дейcтвительна только на время жизни объекта. 
 * После того, как отработал деструктор объекта, содержание этой ссылки 
 * неопределено;
 * - если поле опциональное, то оно устанавливается и возвращается как 
 * указатель на объект. Если указатель равен NULL, это означает, что поле 
 * отсутствует.
 *
 * Основные классы библиотеки (запросы, ответы, штампы) содержат методы 
 * encode()/decode(), выполняющие операцию кодирования в 
 * ASN.1 DER-представление и декодирования из него. Классы, работающие со 
 * структурами, которые содержат подпись (CToken, CMSStamp), обеспечивают 
 * операции подписи и проверки подписи (sign()/verify()), а также доступ 
 * к информации о подписи (SignerInfo).
 * Используя конструктор по умолчанию, можно создать пустой объект, 
 * для последующего вызова функции decode(). Во всех остальных случаях, 
 * если существует конструктор с аргументами, использование конструктора 
 * по умолчанию не рекомендуется, так как перед вызовом encode() все 
 * обязательные поля структуры должны быть проинициализированы корректными 
 * значениями. Конструкторы с аргументами заполняют эти поля при создании 
 * объекта, а конструкторы по умолчанию - нет, что допускает вероятность 
 * того, что объект не будет правильно проинициализирован перед вызовом 
 * encode(). 
 *
 * Представление объектов в виде ASN.1 DER, используется для их 
 * транспортировки между клиентом и сервером. Таким образом, есть два 
 * типичных сценария работы с классами библиотеки:
 *    - создание сообщения (запроса или ответа) и его кодирование 
 * в ASN.1 DER для последующей отправки;
 *    - получение сообщения в ASN.1 DER-представлении, его декодирование 
 * и извлечение содержащейся в нем информации.
 *
 * При возникновении ошибок методы классов данной библиотеки 
 * могут генерировать следующие виды исключений: std::exception и ATL::CAtlException.
 *
 * \section s1 Создание сообщения
 *
 * Основные этапы создания сообщения:
 *	-# Создание объекта
 *	-# Заполнение полей в случае необходимости (добавление 
 * опциональных или изменение обязательных, заданных по умолчанию)
 *	-# В случае, если сообщение содержить подпись, вызов метода 
 * sign()
 *	-# Вызов метода encode() для получения ASN.1 DER-представления 
 * объекта в виде блока бинарных данных
 * 
 * Пример (создание запроса на штамп времени):
 * \dontinclude TspSample.cpp
 * \skip example_5_begin
 * \skip создание запроса на штамп времени
 * \until return tsRequest.encode()
 *
 * Пример (создание штампа времени Microsoft):
 * \dontinclude TspSample.cpp
 * \skip example_1_begin
 * \skip содание штампа времени
 * \until return timeStamp.encode()
 *
 * \section s2 Декодирование сообщения
 *
 * Основные методы декодирования сообщения:
 *	-# Создание объекта конструктором по умолчанию
 *	-# Вызов метода decode(), аргументом которого является ASN.1 DER-представление сообщения
 *	-# Вызов методов get_...() для получения полей сообщения.
 * 
 * Пример (создание штампа времени):
 * \dontinclude TspSample.cpp
 * \skip example_6_begin
 * \skip OID политики
 * \until return tsToken

 * Пример (разбор полученного штампа времени Microsoft):
 * \dontinclude TspSample.cpp
 * \skip example_2_begin
 * \skip CMSStamp
 * \until timeStamp.get_certificates()
 */

/**
 * \brief Запрос на штамп времени (RFC 3161, раздел 2.4.1)
 *
 * Класс CRequest инкапсулирует запрос на получение штампа времени.
 * Используется для создания, кодирования и декодирования из ASN.1 DER представления
 * запроса на штамп времени.
 *
 * Запрос содержит версию (не устанавливается), хэш и алгоритм хэша данных,
 * на которые выдается штамп времени (hashAlgorithm, hashedMessage). 
 * Опциональными полями являются:
 *  - reqPolicy - запрашиваемая политика службы штампов времени;
 *  - nonce - достаточно большое случайное число для проверки соответствия
 *	    запроса ответу;
 *  - certReq - если это поле равно true, служба штампов должна вложить
 *	    сертификат на котором производилась подпись штампа в выданный штамп;
 *  - extensions - дополнительные расширения.
 */
class TSP_CLASS CRequest
{
public:
    /**
     * \brief Создает и инициализирует объект
     *
     * В конструкторе задаются только обязательные атрибуты запроса.
     *
     * \param hashAlgorithm [in] алгоритм хэша
     * \param hashedMessage [in] хэш данных для которых запрашивается штамп
     *        времени
     * \param certReq [in] флаг, определяющий нужно ли включать сертификат
     *        службы штампов времени в ответ на запрос
     */
    CRequest(
	const ASN1::CAlgorithmIdentifierEx& hashAlgorithm,
	const CBlob& hashedMessage,
	bool certReq = false);
    /// Создает пустой объект
    CRequest();
    /**
    * \brief Создает копию заданного объекта.
    * \param src [in] объект, копия которого создается
    */
    CRequest( const CRequest& src);
    /**
    * \brief Копирует заданный объект в текущий.
    *
    * \param src [in] объект, который копируется в текущий
    * \return Ссылка на текущий объект.
    */
    CRequest& operator=( const CRequest& src);
    /// Уничтожает объект
    ~CRequest();
    // Методы get для обязательных атрибутов
    // Возвращают объекы по ссылке
    /**
     * \brief Возвращает версию запроса
     *
     * \return Номер версии
     */
    DWORD get_version() const;
    /**
     * \brief Возвращает алгоритм хэша, использованного при хэшировании данных.
     *
     * \return Идентификатор алгоритма
     */
    const ASN1::CAlgorithmIdentifierEx& get_hashAlgorithm() const;
    /**
     * \brief Возвращает значение хэша данных, на которые получается штамп времени
     *
     * \return Блок данных, содержащий значение хэша
     */
    const CBlob& get_hashedMessage() const;
    /**
     * \brief Возвращает значение флага certReq
     *
     * \remarks Флаг certReq говорит о том, нужно ли вкладывать сертификат,
     * который будет использоваться для подписи штампа времени в штамп времени.
     * Если он имеет значение false, сертификат не должен вкладываться в штамп,
     * если true - должен.
     * \return true или false
     */
    bool get_certReq() const;
    // Методы get для опциональных атрибутов.
    // Возвращают указатель на константный атрибут. Если указатель нулевой,
    // то данный атрибут не задан.
    /**
     * \brief Возвращает запрашиваемую политику штампов времени.
     *
     * \return Указатель на OID. 
     *
     * \remarks Опциональное поле. Если возвращаеся NULL, то данное поле
     * не заполнено и отсутствует.
     */
    const char * get_reqPolicy() const;
    /**
     * \brief Возвращает поле nonce запроса на штамп времени
     *
     * \return Указатель на объект, представляющий большое целое число
     *
     * \remarks Опциональное поле. Если возвращаеся NULL, то данное поле
     * не заполнено и отсутствует.
     */
    const ASN1::CBigInteger* get_nonce() const;
    /**
     * \brief Возвращает список расшрений вложенных в запрос
     * 
     * \return Указатель на список расширений
     *
     * \remarks Опциональное поле. Если возвращаеся NULL, то данное поле
     * не заполнено и отсутствует.
     */
    const ASN1::CExtensions* get_extensions() const;

    // Методы set для опциональных атрибутов.
    // Eсли аргумент NULL - то ранее заданный опциональный
    // атритбут удаляется и атрибут становится не заданным.
    /**
     * \brief Установливает запрашиваемую политику штампов времени
     * 
     * \param reqPolicy [in] указатель на OID политики
     * 
     * \remarks Опциональное поле. Если аргумент NULL, то данное поле
     * становится не заполненным и отсутствует в запросе.
     */
    void put_reqPolicy( const char * reqPolicy);
    /**
     * \brief Установливает значение поля nonce
     * 
     * \param nonce [in] указатель объект, представляющий большое целое число
     * 
     * \remarks Опциональное поле. Если аргумент NULL, то данное поле
     * становится не заполненным и отсутствует в запросе.
     */
    void put_nonce( const ASN1::CBigInteger* nonce);
    /**
     * \brief Вкладывает расширения в запрос на штамп времени
     *
     * \param extensions [in] указатель на список расширений
     *
     * \remarks Опциональное поле. Если аргумент NULL, то данное поле
     * становится не заполненным и отсутствует в запросе.
     */
    void put_extensions( const ASN1::CExtensions* extensions); 

    /**
     * \brief Кодирует запрос в ASN.1 DER представление.
     *
     * \return  блок данных содержащий закодированное представление
     *		запроса на штамп времени
     */
    CBlob encode() const;
    /**
     * \brief Декодирует запроса из его закодированного ASN.1 DER представления
     *
     * \param encodedRequest [in] блок данных содержащий закодированное der-представление
     *				    запроса на штамп времени
     */
    void decode( const CBlob& encodedRequest);
private:
    void clear();
    class Impl;
    Impl* pImpl_;
};

/**
 * \brief Ответ на запрос на штамп времени (RFC 3161, раздел 2.4.2)
 *
 * Класс CResponse инкапсулирует ответ службы штампов времени
 * на запрос. Позволяет создавать, кодировать и декодировать ответ,
 * содержащий статус и, в случае если статус положительный, штамп времени. 
 * 
 */
class TSP_CLASS CResponse
{
public:
    /**
     * \brief Создает пустой объект
     * 
     * \remarks По умолчанию статус ответа - PKI_STATUS_GRANTED
     */
    CResponse();
    /**
    * \brief Создает копию заданного объекта.
    * \param src [in] объект, копия которого создается
    */
    CResponse( const CResponse& src);
    /**
    * \brief Копирует заданный объект в текущий.
    *
    * \param src [in] объект, который копируется в текущий
    * \return Ссылка на текущий объект.
    */
    CResponse& operator=( const CResponse& src);
    /// Уничтожает объект
    ~CResponse();

    // методы get
    /**
     * \brief Возвращает статус ошибки содержащийся в ответе
     *
     * \return Структура, содержащая информацию о статусе ответа
     */
    const ASN1::CPKIStatusInfo& get_status() const;
    /**
     * \brief Возвращает штамп времени содержащийся в ответе
     * 
     * \return Указатель на штамп времени
     * 
     * \remarks Опциональное поле. Если возвращаеся NULL, то данное поле
     * не заполнено и отсутствует.
     */
    const CToken* get_timeStampToken() const;

    // методы set
    /**
     * \brief Заполняет поле штампа времени в ответе на запрос
     *
     * \param token [in] указатель на штамп времени
     *
     * \remarks Опциональное поле. Если аргумент NULL, то данное поле
     * становится не заполненным и отсутствует в ответе.
     */
    void put_timeStampToken( const CToken* token);
    /**
     * \brief Устанавливает статус ответа на запрос
     *
     * \param errorInfo [in] структура, содержащая информацию о статусе ответа
     *
     */
    void put_status( const ASN1::CPKIStatusInfo& errorInfo);

    /**
     * \brief Кодирует ответ на запрос в ASN.1 DER представление
     *
     * \return  блок данных содержащий закодированное представление
     *		ответа на запрос на штамп времени
     */
    CBlob encode() const;
    /**
     * \brief Декодирует ответа на запрос из его закодированного ASN.1 DER представления
     *
     * \param encodedResponse [in] блок данных содержащий закодированное представление
     *				  ответа на запрос на штамп времени
     */
    void decode( const CBlob& encodedResponse);
private:
    void clear();
    class Impl;
    Impl* pImpl_;
};

/**
 * \brief Штамп времени (RFC 3161, раздел 2.4.2).
 *
 * Класс позволяет создавать, кодировать и декодировать штамп времени.
 * Штамп времени представляет собой подписанное CMS сообщение
 * (ContentInfo содержащий SignerInfo, типом содержимого eContentType
 * равным id-ct-TSTInfo). Метод, осуществляющий подпись сообщения, нужно
 * вызывать после заполнения всех информационных полей.
 *
 */
class TSP_CLASS CToken
{
public:
    /**
     * \brief Создает и инициализирует объект
     * 
     * В конструкторе задаются только обязательные атрибуты запроса.
     *
     * \param policy [in] OID политики службы штампов времени
     * \param hashAlgorithm [in] алгоритм хэша
     * \param hashedMessage [in] хэш данных для которых запрашивается штамп
     *        времени
     * \param serialNumber [in] уникальный серийный номер штампа времени
     * \param genTime [in] время создания штампа времени (UTC)
     * \param ordering [in] флаг, определяющий можно ли упорядочивать запросы
     *			    не учитывая поле accuracy
     */
    CToken(
	const char * policy,
	const ASN1::CAlgorithmIdentifierEx& hashAlgorithm,
	const CBlob& hashedMessage,
	const ASN1::CBigInteger& serialNumber,
	const CDateTime& genTime,
	bool ordering = false);
    /// Создает пустой объект
    CToken();
    /**
     * \brief Создает копию заданного объекта.
     * \param src [in] объект, копия которого создается
     */
    CToken( const CToken& src);
    /**
    * \brief Копирует заданный объект в текущий.
    *
    * \param src [in] объект, который копируется в текущий
    * \return Ссылка на текущий объект.
    */
    CToken& operator=( const CToken& src);

    /// Уничтожает объект
    ~CToken();
    // Методы get для обязательных атрибутов
    // Возвращают объекы по константной ссылке
    /**
     * \brief Возвращает версию штампа
     *
     * \return Номер версии
     */
    DWORD get_version() const;
    /**
     * \brief Возвращает политику по которой выпущен штамп
     *
     * \return OID политики 
     */
    const char * get_policy() const;
    /**
     * \brief Возвращает алгоритм хэша, использованного при хэшировании данных.
     *
     * \return Идентификатор алгоритма
     */
    const ASN1::CAlgorithmIdentifierEx& get_hashAlgorithm() const;
    /**
     * \brief Возвращает значение хэша данных, на которые выдан штамп времени
     *
     * \return Блок данных, содержащий значение хэша
     */
    const CBlob& get_hashedMessage() const;
    /**
     * \brief Возвращает серийный номер штампа времени
     *
     * \return Объект, представляющий большое целое число
     */
    const ASN1::CBigInteger& get_serialNumber() const;
    /**
     * \brief Возвращает время выдачи штампа
     *
     * \return Время выдачи штампа
     */
    CDateTime get_genTime() const;
    /**
     * \brief Возвращает время выдачи штампа в виде строки в формате
     *	      GeneralizedTime
     *
     * Возвращает время выдачи штампа в виде строки в формате
     * GeneralizedTime в точно таком виде, в каком время хранится
     * в штампе.
     *
     * \return Строка в формате GeneralizedTime
     */
    const char* get_genTimeZ() const;
    /**
     * \brief Возвращает значение поля ordering
     *
     * \return true или false
     */
    bool get_ordering() const;
    /**
     * \brief Возвращает структуру SignerInfo (информация о подписчике)
     *
     * \return Структура, содержащая информацию о подписчике (SignerInfo, RFC 3161)
     */
    const ASN1::CSignerInfo& get_signerInfo() const;
    // Методы get для опциональных атрибутов.
    // Возвращают указатель на константный атрибут. Если указатель нулевой,
    // то данный атрибут не задан.
    /**
     * \brief Возвращает точность, с которой выпущен штамп времени
     *
     * \return Указатель на структуру, содержащую данные о точности
     *		по времени с которой выдан штамп
     *    
     * \remarks Опциональное поле. Если возвращаеся NULL, то данное поле
     * не заполнено и отсутствует.
     */
    const CAccuracy* get_accuracy() const;
    /**
     * \brief Возвращает поле nonce запроса на штамп времени
     *
     * \return Указатель на объект, представляющий большое целое число
     *
     * \remarks Опциональное поле. Если возвращаеся NULL, то данное поле
     * не заполнено и отсутствует.
     */
    const ASN1::CBigInteger* get_nonce() const;
    /**
     * \brief Возвращает закодированное имя службы штампов времени
     * 
     * \return Указатель на класс, содержащий информацию о службе
     *		штампов времени
     *
     * \remarks Опциональное поле. Если возвращаеся NULL, то данное поле
     * не заполнено и отсутствует.
     */
    const ASN1::CGeneralName* get_tsa() const;
    /**
     * \brief Возвращает списко расширений, вложенных в штамп
     *
     * \return Указатель на список расширений, вложенных в штамп времени
     *
     * \remarks Опциональное поле. Если возвращаеся NULL, то данное поле
     * не заполнено и отсутствует.
     */
    const ASN1::CExtensions* get_extensions() const;
    /**
     * \brief Возвращает список подписанных аттрибутов, вложенных в штамп времени
     *
     * \return Указатель на список аттрибутов
     *
     * \remarks Опциональное поле. Если возвращаеся NULL, то данное поле
     * не заполнено и отсутствует.
     */
    const ASN1::CAttributes* get_signedAttributes() const;
    /**
     * \brief Возвращает список неподписанных аттрибутов, вложенных в штамп времени
     *
     * \return Указатель на список аттрибутов
     *
     * \remarks Опциональное поле. Если возвращаеся NULL, то данное поле
     * не заполнено и отсутствует.
     */
    const ASN1::CAttributes* get_unsignedAttributes() const;
    /**
     * \brief Возвращает сертификаты вложенные в штамп времени
     *
     * \return Указатель на список закодированных сертификатов
     *
     * \remarks Опциональное поле. Если возвращаеся NULL, то данное поле
     * не заполнено и отсутствует.
     */
    const ASN1::CEncodedCertificateList* get_certificates() const;

    // Методы set для опциональных атрибутов.
    // Eсли аргумент NULL - то ранее заданный опциональный
    // атритбут удаляется и атрибут становится не заданным.
    /**
     * \brief Устанавливает значение поля accuracy (точность с которой выдан штамп)
     *
     * \param accuracy [in] указатель на структуру, содержащую данные о точности
     *		по времени с которой выдан штамп
     *
     * \remarks Опциональное поле. Если аргумент NULL, то данное поле
     * становится не заполненным и отсутствует в штампе.
     */
    void put_accuracy( const CAccuracy* accuracy);
    /**
     * \brief Устанавливает значение поля nonce
     *
     * \param nonce [in] объект, представляющий большое целое число
     *
     * \remarks Опциональное поле. Если аргумент NULL, то данное поле
     * становится не заполненным и отсутствует в штампе.
     */
    void put_nonce( const ASN1::CBigInteger* nonce);
    /**
     * \brief Устанавливает значение имени службы штампов времени, выдавшей штамп
     *
     * \param tsa [in] Указатель на класс, содержащий информацию
     *		о службе штампов времени
     *
     * \remarks Опциональное поле. Если аргумент NULL, то данное поле
     * становится не заполненным и отсутствует в штампе.
     */
    void put_tsa( const ASN1::CGeneralName* tsa);
    /**
     * \brief Вкладывает расширения в штамп времени
     *
     * \param extensions [in] указатель на список расширений
     *
     * \remarks Опциональное поле. Если аргумент NULL, то данное поле
     * становится не заполненным и отсутствует в штампе.
     */
    void put_extensions( const ASN1::CExtensions* extensions);
    /**
     * \brief Вкладывает подписанные атрибуты в штамп времени
     *
     * \param attributes [in] указатель на список атрибутов
     *
     * \remarks Опциональное поле. Если аргумент NULL, то данное поле
     * становится не заполненным и отсутствует в штампе.
     */
    void put_signedAttributes( const ASN1::CAttributes* attributes);
    /**
     * \brief Вкладывает неподписанные атрибуты в штамп времени
     *
     * \param attributes [in] указатель на список атрибутов
     *
     * \remarks Опциональное поле. Если аргумент NULL, то данное поле
     * становится не заполненным и отсутствует в штампе.
     */
    void put_unsignedAttributes( const ASN1::CAttributes* attributes);
    /**
     * \brief Вкладывает дополнительные сертификаты в штамп времени
     *
     * \param certificateList [in] список закодированных сертификатов
     *
     * \remarks Опциональное поле. Если аргумент NULL, то данное поле
     * становится не заполненным и отсутствует в штампе.
     */
    void put_certificates( const ASN1::CEncodedCertificateList* certificateList);

    /**
     * \brief Кодирует штамп времени в ASN.1 DER представление
     *
     * \return  блок данных содержащий закодированное представление
     *		штампа времени
     */
    CBlob encode() const;
    /**
     * \brief Декодирует штамп времени из его закодированного ASN.1 DER представления
     *
     * \param encodedTSToken [in] блок данных содержащий закодированное представление
     *				  штампа времени
     */
    void decode( const CBlob& encodedTSToken);
    /**
     * \brief Подписывает штамп времени
     *
     * \param hCryptProv [in] контекст криптопровайдера, открытый на закрытом ключе службы
     * \param dwKeySpec [in] назначение ключа
     * \param encodedCert [in] закодированный сертификат подписчика
     * \param hashAlgorithm [in] алгоритм, который будет использоваться для хэширования данных
     *
     * \remarks Данная функция должна вызываться после заполнения всех полей, непосредственно
     *		перед кодированием штампа.
     *
     * Обратите внимание, что данный метод является низкоуровневым и не проверяет
     * наличие и правильность заполнения атрибутов, указанных в RFC 3161 (например,
     * атрибута SigningCertificate или его аналогов).
     *		
     */
    void sign(
	HCRYPTPROV hCryptProv,
	DWORD dwKeySpec,
	const CBlob& encodedCert,
	const ASN1::CAlgorithmIdentifierEx& hashAlgorithm);
    /**
     * \brief Проверяет подпись штампа времени
     * 
     * \param encodedTSACertificate [in] сертификат, использующийся для проверки подписи
     *
     * \return true, если подпись проверена успешно, иначе false
     *
     * Обратите внимание, что данный метод проверяет только подпись штампа времени
     * и не проверяет наличие и правильность заполнения атрибутов, указанных в RFC 3161
     * (например, атрибута SigningCertificate или его аналогов).
     */
    bool verify( const CBlob& encodedTSACertificate) const;
private:
    void clear();
    class Impl;
    Impl* pImpl_;
};

/**
 * \brief Точность по времени (RFC 3161, раздел 2.4.2).
 *
 * Данная структура используется для хранения точности, с которой
 * служба штампов времени выпускает штампы времени.
 */
struct TSP_CLASS CAccuracy
{
    /**
     * \brief Создает и инициализирует объект
     *
     * \param seconds_ [in] точность по секундам
     * \param millis_ [in] точность по миллисекундам
     * \param micros_ [in] точность по микросекундам
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
     * \brief Создает копию заданного объекта.
     * \param src [in] объект, копия которого создается
     */
    CAccuracy( const CAccuracy& src)
	: seconds(src.seconds), millis(src.millis), micros(src.micros) {}
    /**
     * \brief Копирует заданный объект в текущий.
     * \param src [in] объект, который копируется в текущий
     * \return Ссылка на текущий объект.
     */
    CAccuracy& operator=( const CAccuracy& src)
    { seconds = src.seconds; millis = src.millis; micros = src.micros; return *this; }

    unsigned seconds; //!< секунды
    unsigned millis; //!< миллисекунды
    unsigned micros; //!< микросекунды
};

/// проверяет объекты на равенство
TSP_API bool operator==( const CAccuracy& lhs, const CAccuracy& rhs);
/// проверяет объекты на неравенство
TSP_API bool operator!=( const CAccuracy& lhs, const CAccuracy& rhs);

class CMSRequestImpl;

/**
 * \brief Запрос на штамп времени Microsoft.
 *
 * Класс служит для создания, кодирования и декодирования запроса на штамп времени
 * Microsoft.
 *
 * \remarks Класс предоставляет возможность задать произвольное значение поля timeStampAlgorithm,
 * , contentInfo и attributes. На практике при получении штампа времени Microsoft поле 
 * timeStampAlgorithm имеет значение sz_id_timestampCountersignature, а contentInfo имеет тип
 * szOID_RSA_data и содержит данные на которые выдается штамп (в случае с Microsoft - 
 * значение подписи файла). Поле attributes не заполняется.
 */
class TSP_CLASS CMSRequest
{
public:
    /// Создает пустой объект
    CMSRequest();
    /**
     * \brief Создает и инициализирует объект
     *
     * \param timeStampAlgorithm [in] OID алгоритма штампа времени
     * \param contentInfo [in] структура ContentInfo содержащая данные на
     *				которые запрашивается штамп
     */
    CMSRequest(
	const char * timeStampAlgorithm,
	const ASN1::CContentInfo& contentInfo);
    /**
    * \brief Создает копию заданного объекта.
    * \param src [in] объект, копия которого создается
    */
    CMSRequest( const CMSRequest& src);
    /**
    * \brief Копирует заданный объект в текущий.
    *
    * \param src [in] объект, который копируется в текущий
    * \return Ссылка на текущий объект.
    */
    CMSRequest& operator=( const CMSRequest& src);
    /// Уничтожает объект
    ~CMSRequest();

    /**
     * \brief Кодирует запрос на штамп времени Microsoft
     *
     * \return  блок данных содержащий закодированное представление
     *		запроса на штамп времени Authenticode
     */
    CBlob encode() const;
    /**
     * \brief Декодирует запрос на штамп времени Microsoft из его закодированного представления
     *
     * \param encoded [in] блок данных содержащий закодированное представление
     *				  запроса на штамп времени Authenticode
     */
    void decode( const CBlob& encoded);

    //get
    /**
     * \brief Возвращает OID алгоритма штампа времени Microsoft
     *
     * \return Значение OID
     */
    const char * get_timeStampAlgorithm() const;
    /**
     * \brief Возвращает данные на которые запрашивается штамп
     *
     * \return структура ContentInfo, содержащая данные, на которые запрашивается штамп
     */
    const ASN1::CContentInfo& get_contentInfo() const;
    /**
     * \brief Возвращает список аттрибутов, вложенных в запрос на штамп времени Microsoft
     *
     * \return Указатель на список атрибутов, вложенных в запрос
     *
     * \remarks Опциональное поле. Если возвращаеся NULL, то данное поле
     * не заполнено и отсутствует.
     */
    const ASN1::CAttributes* get_attributes() const;
    //set
    /**
     * \brief Устанавливает алгоритм штампа времени Microsoft
     *
     * \param timeStampAlgorithm [in] значение OID
     */
    void put_timeStampAlgorithm( const char * timeStampAlgorithm);
    /**
     * \brief Установливает значение данных на которые запрашивается штамп
     *
     * \param contentInfo [in] структура ContentInfo, содержащая данные, 
     *				на которые запрашивается штамп
     */
    void put_contentInfo( const ASN1::CContentInfo& contentInfo);
    /**
     * \brief Вкладывает в запрос атрибуты
     *
     * \param attributes [in] указатель на список атрибутов
     *
     * \remarks Опциональное поле. Если аргумент NULL, то данное поле
     * становится не заполненным и отсутствует в запросе.
     */
    void put_attributes( const ASN1::CAttributes* attributes);
private:
    void clear();
    CMSRequestImpl* pImpl_;
};

class CMSStampImpl;
/**
 * \brief Штамп времени Microsoft
 *
 * Класс предназначен для создания, кодирования и декодирования
 * штампов времени Microsoft. Сам штамп является подписанным CMS
 * сообщением.
 */
class TSP_CLASS CMSStamp
{
public:
    /// Создает пустой объект
    CMSStamp();
    /**
     * \brief Создает и инициализирует объект
     *
     * \param content [in] данные на которые выдается штамп
     * \param signingTime [in] время штампа
     */
    CMSStamp( 
	const CBlob& content,
	const CDateTime& signingTime );
    /**
    * \brief Создает копию заданного объекта.
    * \param src [in] объект, копия которого создается
    */
    CMSStamp( const CMSStamp& src);
    /**
    * \brief Копирует заданный объект в текущий.
    *
    * \param src [in] объект, который копируется в текущий
    * \return Ссылка на текущий объект.
    */
    CMSStamp& operator=( const CMSStamp& src);
    /// Уничтожает объект
    ~CMSStamp();

    /**
     * \brief Кодирует штамп времени Microsoft в ASN.1 DER представление
     *
     * \return  блок данных содержащий закодированное der-представление
     *		штампа времени Microsoft
     */
    CBlob encode() const;
    /**
     * \brief Декодирует штамп времени Microsoft из его закодированного ASN.1 DER представления
     *
     * \param encoded [in] блок данных содержащий закодированное представление
     *				  штампа времени Microsoft
     */
    void decode( const CBlob& encoded);

    /**
     * \brief Подписывает штамп времени Microsoft
     *
     * \param hCryptProv [in] контекст криптопровайдера, открытый на закрытом ключе службы
     * \param dwKeySpec [in] назначение ключа
     * \param certificate [in] закодированный сертификат подписчика
     * \param hashAlgorithm [in] алгоритм, который будет использоваться для хэширования данных
     *
     * \remarks Данная функция должна вызываться после заполнения всех полей, непосредственно
     *		перед кодированием штампа
     */
    void sign(
	HCRYPTPROV hCryptProv,
	DWORD dwKeySpec,
	const CBlob& certificate,
	const ASN1::CAlgorithmIdentifierEx& hashAlgorithm);
    /**
     * \brief Проверяет подпись штампа времени Microsoft
     * 
     * \param certificate [in] сертификат, использующийся для проверки подписи
     *
     * \return true, если подпись проверена успешно, иначе false
     */
    bool verify( const CBlob& certificate) const;

    // get
    /**
     * \brief Возвращает данные на которые выдан штамп времени Microsoft
     *
     * \return Двоичный блок данных
     */
    const CBlob& get_content() const;
    /**
     * \brief Возвращает время из штампа
     *
     * \return Двоичный блок данных
     */
    const CDateTime& get_signingTime() const;
    /**
     * \brief Возвращает информацию о подписчике штампа (SignerInfo)
     *
     * \return Структура, содержащая информацию о подписчике
     */
    ASN1::CSignerInfo get_signerInfo() const;
    /**
     * \brief Возвращает список сертификатов вложенных в штамп времени Microsoft
     *
     * \return Указатель на список закодированных сертификатов
     *
     * \remarks Опциональное поле. Если возвращаеся NULL, то данное поле
     * не заполнено и отсутствует.
     */
    const ASN1::CEncodedCertificateList* get_certificates() const;
    // set
    /**
     * \brief Установливает значение данных на которые выдается штамп времени Microsoft
     *
     * \param content [in] двоичный блок данных
     */
    void put_content( const CBlob& content) const;
    /**
     * \brief Установливает время штампа
     *
     * \param signingTime [in] время штампа
     */
    void put_signingTime( const CDateTime& signingTime);
    /**
     * \brief Добавляет сертификаты в штамп времени
     *
     * \param certificates [in] указатель на список закодированных сертификатов
     *
     * \remarks Опциональное поле. Если аргумент NULL, то данное поле
     * становится не заполненным и отсутствует в штампе.
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
