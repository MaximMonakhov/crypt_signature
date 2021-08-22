/* [Windows 1251]
 * [Use `iconv -f WINDOWS-1251', if needed]
 */
/*
 * Copyright(C) 2005-2011
 *
 * Этот файл содержит информацию, являющуюся
 * собственностью компании Крипто-Про.
 *
 * Любая часть этого файла не может быть скопирована,
 * исправлена, переведена на другие языки,
 * локализована или модифицирована любым способом,
 * откомпилирована, передана по сети с или на
 * любую компьютерную систему без предварительного
 * заключения соглашения с компанией Крипто-Про.
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
 * \version $Revision: 200060 $
 * \date $Date:: 2019-10-01 13:24:09 +0400#$
 * \author $Author: sagafyin $ (Original author: halaud) 
 *
 * \brief Буфер для хранения PIN и паролей
 *
 */

#ifndef _SECUREBUFFER_H_INCLUDED
#define _SECUREBUFFER_H_INCLUDED

#include <stdexcept>

#ifdef UNIX

// Gcc implements an inline function with a parameter named __out
#ifdef __out
#define __out_our_bug_gcc
#undef __out
#endif

// Gcc implements an inline function with a parameter named __in
#ifdef __in
#define __in_our_bug_gcc
#undef __in
#endif

#include <stdexcept>

#ifdef __out_our_bug_gcc
#define __out
#undef __out_our_bug_gcc
#endif

#ifdef __in_our_bug_gcc
#define __in
#undef __in_our_bug_gcc
#endif

#endif /* UNIX */

#ifdef UNIX
#   include <memory.h>
#else
#   include <windows.h>
#endif // UNIX

#ifndef SecureZeroMemory
#define SecureZeroMemory(ptr,cnt) do { \
    volatile char *vptr = (volatile char *)(ptr); \
    size_t tmpcnt = (cnt)*sizeof(*ptr); /* Формально размер *ptr не обязан быть 1 */ \
    while (tmpcnt) { *vptr = 0; vptr++; tmpcnt--; } } while(0)
#endif // SecureZeroMemory

/*! \ingroup EnrollAPI
 *  \brief Буфер с обнулением в деструкторе
 *
 *  \xmlonly <locfile><header>SecureBuffer.h</header> <ulib>libenroll.so</ulib></locfile>\endxmlonly
 *
 *  \note
 *  Интерфейс может быть изменён в окончательной версии.
 *  Использование для типов размера большего 1 не рекомендуется.
 */
template <typename T>
class CSecureBufferT
{
public:
    /*!
     *  \brief Конструктор
     *
     *  \param byteLen [in] Размер буфера в байтах
     *
     *  \note
     *  ВНИМАНИЕ: byteLen должен быть кратен sizeof(T)
     */
    CSecureBufferT( size_t byteLen = 0 ) : _ptr(0), _len(byteLen) {
        if(0 != _len) {
            _ptr = new unsigned char[byteLen]; // throws bad_alloc if allocation fails
        }
    }

    /*!
     *  \brief Размер буфера в байтах
     *
     *  \return Размер буфера в байтах(!), а не элементах
     */
    size_t len() const {
        return _len;
    }

    /*!
     *  \brief Указатель на буфер для чтения
     *
     *  \return Указатель на буфер
     *
     *  \note
     *  ВНИМАНИЕ: Указатель на буфер может быть 0
     */
    const T * ptr() const {
        return (const T*)_ptr;
    }

    /*!
     *  \brief Признак пустоты
     *
     *  \return Признак пустоты
     */
    bool empty() const {
        return (0 == _len);
    }

    /*!
     *  \brief Указатель на буфер для записи
     *
     *  \return Указатель на буфер
     */
    T * ptr_rw() {
        if(empty()) {
            throw std::runtime_error("_ptr is null, can't be writable");
        }
        return (T*)_ptr;
    }

    /*!
     *  \brief Обнулить буфер
     */
    void clean() {
        if(!empty()) {
            SecureZeroMemory(ptr_rw(),len());
        }
    }

    /*!
     *  \brief Скопировать буфер
     */
    void copy( const CSecureBufferT<T>& src) {
        if( this == &src ) {
            return;
        }

        CSecureBufferT<T> tmp(src.len());
        if(!src.empty() && !tmp.empty() ) {
            memcpy(tmp.ptr_rw(), src.ptr(), tmp.len());
        }
        this->swap(tmp);
        tmp.clean();
        return;
    }

    /*!
     *  \brief Обменять буфер
     */
    void swap( CSecureBufferT<T>& obj) {
        if( this == &obj ) {
            return;
        }
        std::swap(this->_ptr, obj._ptr);
        std::swap(this->_len, obj._len);
    }

    /*!
     *  \brief Деструктор с очисткой буфера
     */
    ~CSecureBufferT() {
        clean();
        if(!empty()) {
            delete[] _ptr;
        }
    }
private:
    CSecureBufferT( const CSecureBufferT<T>&);
    CSecureBufferT<T>& operator=( const CSecureBufferT<T>&);

    unsigned char *_ptr;
    size_t _len;
};

/*! \ingroup EnrollAPI
 *  \brief Буфер char с обнулением в деструкторе
 *
 *  \xmlonly <locfile><header>SecureBuffer.h</header> <ulib>libenroll.so</ulib></locfile>\endxmlonly
 *
 *  \note
 *  Этот интерфейс более стабилен
 */
typedef CSecureBufferT<char> CSecurePin;

#endif // _SECUREBUFFER_H_INCLUDED

