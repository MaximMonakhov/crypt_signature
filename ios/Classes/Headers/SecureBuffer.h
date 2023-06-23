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
 * \version $Revision: 200060 $
 * \date $Date:: 2019-10-01 02:24:09 -0700#$
 * \author $Author: sagafyin $ (Original author: halaud) 
 *
 * \brief ����� ��� �������� PIN � �������
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
    size_t tmpcnt = (cnt)*sizeof(*ptr); /* ��������� ������ *ptr �� ������ ���� 1 */ \
    while (tmpcnt) { *vptr = 0; vptr++; tmpcnt--; } } while(0)
#endif // SecureZeroMemory

/*! \ingroup EnrollAPI
 *  \brief ����� � ���������� � �����������
 *
 *  \xmlonly <locfile><header>SecureBuffer.h</header> <ulib>libenroll.so</ulib></locfile>\endxmlonly
 *
 *  \note
 *  ��������� ����� ���� ������ � ������������� ������.
 *  ������������� ��� ����� ������� �������� 1 �� �������������.
 */
template <typename T>
class CSecureBufferT
{
public:
    /*!
     *  \brief �����������
     *
     *  \param byteLen [in] ������ ������ � ������
     *
     *  \note
     *  ��������: byteLen ������ ���� ������ sizeof(T)
     */
    CSecureBufferT( size_t byteLen = 0 ) : _ptr(0), _len(byteLen) {
        if(0 != _len) {
            _ptr = new unsigned char[byteLen]; // throws bad_alloc if allocation fails
        }
    }

    /*!
     *  \brief ������ ������ � ������
     *
     *  \return ������ ������ � ������(!), � �� ���������
     */
    size_t len() const {
        return _len;
    }

    /*!
     *  \brief ��������� �� ����� ��� ������
     *
     *  \return ��������� �� �����
     *
     *  \note
     *  ��������: ��������� �� ����� ����� ���� 0
     */
    const T * ptr() const {
        return (const T*)_ptr;
    }

    /*!
     *  \brief ������� �������
     *
     *  \return ������� �������
     */
    bool empty() const {
        return (0 == _len);
    }

    /*!
     *  \brief ��������� �� ����� ��� ������
     *
     *  \return ��������� �� �����
     */
    T * ptr_rw() {
        if(empty()) {
            throw std::runtime_error("_ptr is null, can't be writable");
        }
        return (T*)_ptr;
    }

    /*!
     *  \brief �������� �����
     */
    void clean() {
        if(!empty()) {
            SecureZeroMemory(ptr_rw(),len());
        }
    }

    /*!
     *  \brief ����������� �����
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
     *  \brief �������� �����
     */
    void swap( CSecureBufferT<T>& obj) {
        if( this == &obj ) {
            return;
        }
        std::swap(this->_ptr, obj._ptr);
        std::swap(this->_len, obj._len);
    }

    /*!
     *  \brief ���������� � �������� ������
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
 *  \brief ����� char � ���������� � �����������
 *
 *  \xmlonly <locfile><header>SecureBuffer.h</header> <ulib>libenroll.so</ulib></locfile>\endxmlonly
 *
 *  \note
 *  ���� ��������� ����� ��������
 */
typedef CSecureBufferT<char> CSecurePin;

#endif // _SECUREBUFFER_H_INCLUDED

