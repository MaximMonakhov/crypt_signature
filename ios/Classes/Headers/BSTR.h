#ifndef __BSTR_H__
#define __BSTR_H__

#include <vector>

#ifdef _WIN32
#   include <comutil.h>
    
    using _com_util::ConvertBSTRToString;
    using _com_util::ConvertStringToBSTR;
#endif //_WIN32

#ifdef UNIX
#include <cstdarg>
#include <wchar.h>
#include<CSP_WinDef.h>
typedef wchar_t* BSTR;

// Utility functions to work with BSTR
/*! \ingroup EnrollAPI_support
 *  \brief �������������� ����-��������������� ������ wchar_t � BSTR
 *
 *  \param str [in] ����-��������������� ������ wchar_t
 *
 *  \return ���������� BSTR ������ ������ ���� ����������� �������� 
 *	    SysFreeString()
 */
BSTR SysAllocString( const wchar_t* str);

// Utility functions to work with BSTR
/*! \ingroup EnrollAPI_support
 *  \brief �������������� ����-��������������� ������ wchar_t � BSTR
 *
 *  \param str [in] ����-��������������� ������ wchar_t ��� 0
 *  \param cch [in] ���������� �������� � ������
 *
 *  \return ���������� BSTR ������ ������ ���� ����������� �������� 
 *	    SysFreeString()
 */

BSTR SysAllocStringLen( const wchar_t *str, UINT cch);

/*! \ingroup EnrollAPI_support
 *  \brief ������������ BSTR ������
 *
 *  \param bStr [in] BSTR ������
 */
void SysFreeString( BSTR bStr);

/*! \ingroup EnrollAPI_support
 *  \brief ������������ BSTR ������
 *
 *  \param bStr [in] BSTR ������
    \return ����� ������
 */

UINT SysStringLen(BSTR bStr);

/*! \ingroup EnrollAPI_support
 *  \brief �������������� ����-��������������� ������ � BSTR
 *
 *  \param str [in] ����-��������������� ������
 *
 *  \return ���������� BSTR ������ ������ ���� ����������� �������� 
 *	    SysFreeString()
 */

BSTR ConvertStringToBSTR( const char* str);

/*! \ingroup EnrollAPI_support
 *  \brief �������������� BSTR � ����-��������������� ������
 *
 *  \param bStr [in] BSTR ������
 *
 *  \return ���������� ������ ���� char *, ������ ���� 
 *	    ����������� ���������� delete[] 
 */
char* ConvertBSTRToString( BSTR bStr);

#endif //UNIX

/*! \ingroup EnrollAPI_support
 *  \brief �������������� ����-��������������� ������ � BSTR
 *
 *  \param str [in] ����-��������������� ������
 *  \param encoding [in] int ��������� ������� ������
 *
 *  \return ���������� BSTR ������ ������ ���� ����������� �������� 
 *	    SysFreeString()
 */

BSTR ConvertStringToBSTREx( const char* str, int encoding);

/*! \ingroup EnrollAPI_support
 *  \brief �������������� BSTR � ����-��������������� ������
 *
 *  \param bStr [in] BSTR ������
 *  \param encoding [in] int ��������� ������� ������
 *
 *  \return ���������� ������ ���� char *, ������ ���� 
 *	    ����������� ���������� delete[] 
 */

char* ConvertBSTRToStringEx( BSTR bStr, int encoding);

HRESULT ConvertBinToBSTR(const std::vector<BYTE>& encodedRequest, BSTR * bStr);
HRESULT ConvertBSTRToBin(BSTR msg, std::vector<BYTE>& ret);

#endif //__BSTR_H__

