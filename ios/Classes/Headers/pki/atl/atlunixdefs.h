#ifndef _ATLUNIXDEFS_H_INCLUDED
#define _ATLUNIXDEFS_H_INCLUDED

#if defined DEBUG && !defined _DEBUG
#   define _DEBUG 1
#endif
#if defined _DEBUG && !defined DEBUG
# define DEBUG 1
#endif

#ifdef SOLARIS
#define __FUNCTION__ __func__
#endif

#if !defined _SECURE_ATL
#   define _SECURE_ATL 0
#else
#   if _SECURE_ATL != 0
#       error _SECURE_ATL != 0
#   endif
#endif	/* _SECURE_ATL */

#define _ATL_DISABLE_NOINLINE
#define _CONVERSION_DONT_USE_THREAD_LOCALE
//#define _ATL_NO_DEBUG_CRT

#define __declspec(expr)
#define __stdcall
#define __interface class
#define __pragma(expr)
#define __noop

#if defined(LINUX) || defined(DARWIN) || defined(IOS) || defined(UCLIBC)
#include<stdint.h>
typedef int64_t __int64;
typedef uint64_t __uint64;
#elif AIX
typedef uint64_t __uint64;
#else
typedef int64_t __int64;
typedef uint64_t __uint64;
#endif 
typedef time_t __time64_t;

#define _WCHAR_T_DEFINED 
#define _VA_LIST_DEFINED
#define _SIZE_T_DEFINED
#define _INTPTR_T_DEFINED
#define _UINTPTR_T_DEFINED
#define _PTRDIFF_T_DEFINED
#define _TIME_T_DEFINED
/* Minimum and maximum values a `signed long long int' can hold.  */
#ifndef LLONG_MAX
#   define LLONG_MAX    9223372036854775807LL
#endif
#ifndef LLONG_MIN
#   define LLONG_MIN    (-LLONG_MAX - 1LL)
#endif

/* Maximum value an `unsigned long long int' can hold.  (Minimum is 0.)  */
#ifndef ULLONG_MAX
#   define ULLONG_MAX   18446744073709551615ULL
#endif 

// Из basetsd.h
//
// SIZE_T used for counts or ranges which need to span the range of
// of a pointer.  SSIZE_T is the signed variation.
//
typedef uint32_t UINT32;

// Не хватает в errno.h
#define STRUNCATE       80

// Из stdlib.h
/* Minimum and maximum macros */

#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#define __min(a,b)  (((a) < (b)) ? (a) : (b))

#define lstrlenA(expr) strlen(expr)
#define lstrlenW(expr) wcslen(expr)

extern "C" inline int _CrtDbgReportW(
        int /*_ReportType*/,
        const wchar_t * /*_Filename*/,
        int /*_LineNumber*/,
        const wchar_t * /*_ModuleName*/,
        const wchar_t * /*_Format*/,
        ...) 
{
	return 0;
}

extern "C" inline int _CrtDbgReport(
        int /*_ReportType*/,
        const char * /*_Filename*/,
        int /*_Linenumber*/,
        const char * /*_ModuleName*/,
        const char * /*_Format*/,
        ...)
{
	return 0;
}

extern "C" inline void _CrtDbgBreak( void )
{
	return;
}

#endif // _ATLUNIXDEFS_H_INCLUDED
