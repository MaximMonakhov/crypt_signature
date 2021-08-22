// This is a part of the Active Template Library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the	
// Active Template Library product.

#ifndef __ATLTRACE_H__
#define __ATLTRACE_H__

// ORIG: #pragma once

#include <atldef.h>
#include <atlconv.h>

#ifdef _DEBUG
#include <stdio.h>
#include <stdarg.h>
#endif

#ifdef _DEBUG
#include <atldebugapi.h>

// ORIG: extern "C" IMAGE_DOS_HEADER __ImageBase;
#endif  // _DEBUG
 

#if defined(AIX)
#pragma pack( 8 /* _ATL_PACKING */)
#elif !defined(SOLARIS) && !defined(FREEBSD)
#pragma pack(push, 8 /* _ATL_PACKING */)
#endif
namespace ATL
{

// Declare a global instance of this class to automatically register a custom trace category at startup
class CTraceCategory
{
public:
	explicit CTraceCategory( LPCTSTR pszCategoryName, UINT nStartingLevel = 0 ) throw();

#ifdef _DEBUG
	UINT GetLevel() const throw();
	void SetLevel( UINT nLevel ) throw();
	ATLTRACESTATUS GetStatus() const throw();
	void SetStatus( ATLTRACESTATUS eStatus) throw();
#endif

	operator DWORD_PTR() const throw();

public:
#ifdef _DEBUG
	DWORD_PTR m_dwCategory;
#endif
};

#ifdef _DEBUG

extern "C"
{
typedef int (__cdecl *fnCrtDbgReport_t)(int,const char *,int,const char *,const char *,...);
}
// ORIG: private:
class CTrace
{
public:
	CTrace(
#ifdef _ATL_NO_DEBUG_CRT
		fnCrtDbgReport_t pfnCrtDbgReport = NULL)
#else
		fnCrtDbgReport_t pfnCrtDbgReport = _CrtDbgReport)
#endif
// ORIG:		: m_hInst(reinterpret_cast<HINSTANCE>(0&__ImageBase)),
		: m_hInst(0),
			m_dwModule( 0 )
	{
		m_dwModule = AtlTraceRegister(m_hInst, pfnCrtDbgReport);
	}

	~CTrace()
	{
		AtlTraceUnregister(m_dwModule);
	}

public:
	bool ChangeCategory(DWORD_PTR dwCategory, UINT nLevel, ATLTRACESTATUS eStatus)
	{
		return 0 !=
			AtlTraceModifyCategory(0, dwCategory, nLevel, eStatus);
	}

#if defined _WIN32
	bool GetCategory(DWORD_PTR dwCategory, UINT *pnLevel, ATLTRACESTATUS *peStatus)
	{
		ATLASSERT(pnLevel && peStatus);
		return 0 != AtlTraceGetCategory(0, dwCategory, pnLevel, peStatus);
	}
#endif /* _WIN32 */

#if defined _WIN32
	UINT GetLevel()
	{
		ATLTRACESTATUS eStatus;
		UINT nLevel;
		AtlTraceGetModule(0, m_dwModule, &nLevel, &eStatus);

		return nLevel;
	}
#endif /* _WIN32 */

#if defined _WIN32
	void SetLevel(UINT nLevel)
	{
		AtlTraceModifyModule(0, m_dwModule, nLevel, ATLTRACESTATUS_ENABLED);
	}
#endif /* _WIN32 */

#if defined _WIN32
	ATLTRACESTATUS GetStatus()
	{
		ATLTRACESTATUS eStatus;
		UINT nLevel;
		AtlTraceGetModule(0, m_dwModule, &nLevel, &eStatus);

		return eStatus;
	}
#endif /* _WIN32 */

#if defined _WIN32
	void SetStatus(ATLTRACESTATUS eStatus)
	{
		ATLTRACESTATUS eOldStatus;
		UINT nLevel;
		AtlTraceGetModule(0, m_dwModule, &nLevel, &eOldStatus);
		AtlTraceModifyModule(0, m_dwModule, nLevel, eStatus);
	}
#endif /* _WIN32 */

	void __cdecl TraceV(const char *pszFileName, int nLine,
		DWORD_PTR dwCategory, UINT nLevel, LPCSTR pszFmt, va_list args) const;

#if !defined UNIX
	void __cdecl TraceV(const char *pszFileName, int nLine,
		DWORD_PTR dwCategory, UINT nLevel, LPCWSTR pszFmt, va_list args) const;
#endif /* !UNIX */

	DWORD_PTR RegisterCategory(LPCSTR pszCategory)
		{return(AtlTraceRegisterCategoryA(m_dwModule, pszCategory));}
#ifdef _UNICODE
	DWORD_PTR RegisterCategory(LPCWSTR pszCategory)
		{return(AtlTraceRegisterCategoryU(m_dwModule, pszCategory));}
#endif

#if defined _WIN32
	bool LoadSettings(LPCTSTR pszFileName = NULL) const
		{return 0 != AtlTraceLoadSettings(pszFileName);}
	void SaveSettings(LPCTSTR pszFileName = NULL) const
		{AtlTraceSaveSettings(pszFileName);}
#endif /* _WIN32 */

public:
	static CTrace s_trace;

protected:
	HINSTANCE m_hInst;
	DWORD_PTR m_dwModule;
};

#ifdef SOLARIS
CTrace CTrace::s_trace;
#pragma weak "__1cDATLGCTraceHs_trace_"
#else
CTrace CTrace::s_trace __attribute__((weak));
#endif

    inline void __cdecl CTrace::TraceV(const char *pszFileName, int nLine,
		DWORD_PTR dwCategory, UINT nLevel, LPCSTR pszFmt, va_list args) const
	{
		AtlTraceVA(m_dwModule, pszFileName, nLine, dwCategory, nLevel, pszFmt, args);
	}

#if defined _WIN32
	inline void __cdecl CTrace::TraceV(const char *pszFileName, int nLine,
		DWORD_PTR dwCategory, UINT nLevel, LPCWSTR pszFmt, va_list args) const
	{
		AtlTraceVU(m_dwModule, pszFileName, nLine, dwCategory, nLevel, pszFmt, args);
	}
#endif /* _WIN32 */

extern CTraceCategory atlTraceGeneral;

class CTraceFileAndLineInfo
{
public:
	CTraceFileAndLineInfo(const char *pszFileName, int nLineNo)
		: m_pszFileName(pszFileName), m_nLineNo(nLineNo)
	{}

#pragma warning(push)
#pragma warning(disable : 4793)
	void __cdecl operator()(DWORD_PTR dwCategory, UINT nLevel, const char *pszFmt, ...) const
	{
		va_list ptr; va_start(ptr, pszFmt);
		ATL::CTrace::s_trace.TraceV(m_pszFileName, m_nLineNo, dwCategory, nLevel, pszFmt, ptr);
		va_end(ptr);
	}
#pragma warning(pop)

#if !defined UNIX
#pragma warning(push)
#pragma warning(disable : 4793)
	void __cdecl operator()(DWORD_PTR dwCategory, UINT nLevel, const wchar_t *pszFmt, ...) const
	{
		va_list ptr; va_start(ptr, pszFmt);
		ATL::CTrace::s_trace.TraceV(m_pszFileName, m_nLineNo, dwCategory, nLevel, pszFmt, ptr);
		va_end(ptr);
	}
#pragma warning(pop)
#endif /* !UNIX */

#pragma warning(push)
#pragma warning(disable : 4793)
	void __cdecl operator()(const char *pszFmt, ...) const
	{
		va_list ptr; va_start(ptr, pszFmt);
		ATL::CTrace::s_trace.TraceV(m_pszFileName, m_nLineNo, atlTraceGeneral, 0, pszFmt, ptr);
		va_end(ptr);
	}
#pragma warning(pop)

#if !defined UNIX
#pragma warning(push)
#pragma warning(disable : 4793)
	void __cdecl operator()(const wchar_t *pszFmt, ...) const
	{
		va_list ptr; va_start(ptr, pszFmt);
		ATL::CTrace::s_trace.TraceV(m_pszFileName, m_nLineNo, atlTraceGeneral, 0, pszFmt, ptr);
		va_end(ptr);
	}
#pragma warning(pop)
#endif /* !UNIX */

private:
	/* unimplemented */
	CTraceFileAndLineInfo &__cdecl operator=(const CTraceFileAndLineInfo &right);

	const char *const m_pszFileName;
	const int m_nLineNo;
};

#endif  // _DEBUG

#ifdef _DEBUG

inline CTraceCategory::CTraceCategory( LPCTSTR pszCategoryName, UINT nStartingLevel ) throw() :
	m_dwCategory( 0 )
{
	m_dwCategory = ATL::CTrace::s_trace.RegisterCategory( pszCategoryName );
	ATL::CTrace::s_trace.ChangeCategory( m_dwCategory, nStartingLevel, ATLTRACESTATUS_INHERIT);
}

inline CTraceCategory::operator DWORD_PTR() const throw()
{
	return( m_dwCategory );
}

#if defined _WIN32
inline UINT CTraceCategory::GetLevel() const throw()
{
	UINT nLevel;
	ATLTRACESTATUS eStatus;
	ATL::CTrace::s_trace.GetCategory( m_dwCategory, &nLevel, &eStatus );

	return( nLevel );
}
#endif /* _WIN32 */

inline void CTraceCategory::SetLevel( UINT nLevel ) throw()
{
	ATL::CTrace::s_trace.ChangeCategory( m_dwCategory, nLevel, ATLTRACESTATUS_ENABLED );
}

#if defined _WIN32
inline ATLTRACESTATUS CTraceCategory::GetStatus() const throw()
{
	UINT nLevel;
	ATLTRACESTATUS eStatus;
	ATL::CTrace::s_trace.GetCategory( m_dwCategory, &nLevel, &eStatus );

	return( eStatus );
}
#endif /* _WIN32 */

#if defined _WIN32
inline void CTraceCategory::SetStatus( ATLTRACESTATUS eStatus ) throw()
{
	UINT nLevel;
	ATLTRACESTATUS eOldStatus;
	ATL::CTrace::s_trace.GetCategory( m_dwCategory, &nLevel, &eOldStatus );
	ATL::CTrace::s_trace.ChangeCategory( m_dwCategory, nLevel, eStatus );
}
#endif /* _WIN32 */

#else  // !_DEBUG

inline CTraceCategory::CTraceCategory( LPCTSTR pszCategoryName, UINT nStartingLevel ) throw()
{
	(void)pszCategoryName;
	(void)nStartingLevel;
}

inline CTraceCategory::operator DWORD_PTR() const throw()
{
	return( 0 );
}

#endif  // _DEBUG

}  // namespace ATL
 
namespace ATL
{

#ifdef _DEBUG
#ifdef SOLARIS
// ORIG: #define DECLARE_TRACE_CATEGORY( name ) extern ATL::CTraceCategory name;
#define DECLARE_TRACE_CATEGORY( name ) ATL::CTraceCategory name( _TEXT(#name) );
#pragma weak "__1cDATLKatlTraceQdDI_"
#pragma weak "__1cDATLLatlTraceCOM_"
#pragma weak "__1cDATLLatlTraceMap_"
#pragma weak "__1cDATLMatlTraceSync_"
#pragma weak "__1cDATLMatlTraceTime_"
#pragma weak "__1cDATLMatlTraceUser_"
#pragma weak "__1cDATLMatlTraceUtil_"
#pragma weak "__1cDATLNatlTraceCache_"
#pragma weak "__1cDATLNatlTraceISAPI_"
#pragma weak "__1cDATLNatlTraceUser2_"
#pragma weak "__1cDATLNatlTraceUser3_"
#pragma weak "__1cDATLNatlTraceUser4_"
#pragma weak "__1cDATLOatlTraceSnapin_"
#pragma weak "__1cDATLOatlTraceString_"
#pragma weak "__1cDATLPatlTraceGeneral_"
#pragma weak "__1cDATLPatlTraceHosting_"
#pragma weak "__1cDATLPatlTraceNotImpl_"
#pragma weak "__1cDATLPatlTraceStencil_"
#pragma weak "__1cDATLQatlTraceControls_"
#pragma weak "__1cDATLQatlTraceDBClient_"
#pragma weak "__1cDATLQatlTraceRefcount_"
#pragma weak "__1cDATLQatlTraceSecurity_"
#pragma weak "__1cDATLRatlTraceException_"
#pragma weak "__1cDATLRatlTraceRegistrar_"
#pragma weak "__1cDATLRatlTraceWindowing_"
#pragma weak "__1cDATLSatlTraceAllocation_"
#pragma weak "__1cDATLSatlTraceDBProvider_"
#elif AIX
// ORIG: #define DECLARE_TRACE_CATEGORY( name ) extern ATL::CTraceCategory name;
#define DECLARE_TRACE_CATEGORY( name ) ATL::CTraceCategory name( _TEXT(#name) );
#pragma weak atlTraceQI
#pragma weak atlTraceCOM
#pragma weak atlTraceMap
#pragma weak atlTraceSync
#pragma weak atlTraceTime
#pragma weak atlTraceUser
#pragma weak atlTraceUtil
#pragma weak atlTraceCache
#pragma weak atlTraceISAPI
#pragma weak atlTraceUser2
#pragma weak atlTraceUser3
#pragma weak atlTraceUser4
#pragma weak atlTraceSnapin
#pragma weak atlTraceString
#pragma weak atlTraceGeneral
#pragma weak atlTraceHosting
#pragma weak atlTraceNotImpl
#pragma weak atlTraceStencil
#pragma weak atlTraceControls
#pragma weak atlTraceDBClient
#pragma weak atlTraceRefcount
#pragma weak atlTraceSecurity
#pragma weak atlTraceException
#pragma weak atlTraceRegistrar
#pragma weak atlTraceWindowing
#pragma weak atlTraceAllocation
#pragma weak atlTraceDBProvider
#else
#define DECLARE_TRACE_CATEGORY( name ) __attribute__ ((weak)) ATL::CTraceCategory name( _TEXT(#name) );
#endif /*SOLARIS*/
#else
#define DECLARE_TRACE_CATEGORY( name ) const DWORD_PTR name = 0;
#endif

DECLARE_TRACE_CATEGORY( atlTraceGeneral )
DECLARE_TRACE_CATEGORY( atlTraceCOM )  
DECLARE_TRACE_CATEGORY( atlTraceQI )	
DECLARE_TRACE_CATEGORY( atlTraceRegistrar )
DECLARE_TRACE_CATEGORY( atlTraceRefcount )
DECLARE_TRACE_CATEGORY( atlTraceWindowing )
DECLARE_TRACE_CATEGORY( atlTraceControls )
DECLARE_TRACE_CATEGORY( atlTraceHosting ) 
DECLARE_TRACE_CATEGORY( atlTraceDBClient )  
DECLARE_TRACE_CATEGORY( atlTraceDBProvider )
DECLARE_TRACE_CATEGORY( atlTraceSnapin )
DECLARE_TRACE_CATEGORY( atlTraceNotImpl )   
DECLARE_TRACE_CATEGORY( atlTraceAllocation )
DECLARE_TRACE_CATEGORY( atlTraceException )
DECLARE_TRACE_CATEGORY( atlTraceTime )
DECLARE_TRACE_CATEGORY( atlTraceCache )		
DECLARE_TRACE_CATEGORY( atlTraceStencil )
DECLARE_TRACE_CATEGORY( atlTraceString )
DECLARE_TRACE_CATEGORY( atlTraceMap )	
DECLARE_TRACE_CATEGORY( atlTraceUtil )		
DECLARE_TRACE_CATEGORY( atlTraceSecurity )
DECLARE_TRACE_CATEGORY( atlTraceSync )
DECLARE_TRACE_CATEGORY( atlTraceISAPI )		

// atlTraceUser categories are no longer needed.  Just declare your own trace category using CTraceCategory.
DECLARE_TRACE_CATEGORY( atlTraceUser )
DECLARE_TRACE_CATEGORY( atlTraceUser2 )
DECLARE_TRACE_CATEGORY( atlTraceUser3 )
DECLARE_TRACE_CATEGORY( atlTraceUser4 )

#ifndef AIX
#pragma deprecated( atlTraceUser )
#pragma deprecated( atlTraceUser2 )
#pragma deprecated( atlTraceUser3 )
#pragma deprecated( atlTraceUser4 )
#endif

#ifdef _DEBUG

#if !defined _ATL_NO_DEBUG_CRT && !defined UNIX
extern "C" {
 typedef int(*CrtHookProc_t)(int,char*,int*);
}
class CNoUIAssertHook
{
public:
	CNoUIAssertHook()
	{
		ATLASSERT( s_pfnPrevHook == NULL );
		s_pfnPrevHook = _CrtSetReportHook((CrtHookProc_t)CrtHookProc);
	}
	~CNoUIAssertHook()
	{
		_CrtSetReportHook(s_pfnPrevHook);
		s_pfnPrevHook = NULL;
	}

private:
	static int __cdecl CrtHookProc(__in int eReportType, __in_z char* pszMessage, __out int* pnRetVal)
	{
		
		if (eReportType == _CRT_ASSERT)
		{
// ORIG: 			::OutputDebugStringA( "ASSERTION FAILED\n" );
// ORIG: 			::OutputDebugStringA( pszMessage );
			// Под UNIX это макрос
			OutputDebugStringA( "ASSERTION FAILED\n" );
			OutputDebugStringA( pszMessage );
			//If caller doesn't want retVal, so be it.
			if (pnRetVal != NULL)
			{
				*pnRetVal = 1;
			}
			return TRUE;
		}

		if (s_pfnPrevHook != NULL)
		{
			return s_pfnPrevHook(eReportType, pszMessage, pnRetVal);
		}
		else
		{
			return FALSE;
		}
	}

private:
	static _CRT_REPORT_HOOK s_pfnPrevHook;
};

#ifdef SOLARIS
__declspec( selectany ) _CRT_REPORT_HOOK CNoUIAssertHook::s_pfnPrevHook = NULL;
#pragma weak "__1cDATLPCNoUIAssertHookNs_pfnPrevHook_" 
#else
__declspec( selectany ) _CRT_REPORT_HOOK CNoUIAssertHook::s_pfnPrevHook __attribute__ ((weak)) = NULL;
#endif


#define DECLARE_NOUIASSERT() ATL::CNoUIAssertHook _g_NoUIAssertHook;

#endif  // !_ATL_NO_DEBUG_CRT && !UNIX

#ifndef ATLTRACE
#define ATLTRACE ATL::CTraceFileAndLineInfo(__FILE__, __LINE__)
#define ATLTRACE2 ATLTRACE
#endif

#pragma warning(push)
#pragma warning(disable : 4793)
inline void __cdecl AtlTrace(LPCSTR pszFormat, ...)
{
	va_list ptr;
	va_start(ptr, pszFormat);
	ATL::CTrace::s_trace.TraceV(NULL, -1, atlTraceGeneral, 0, pszFormat, ptr);
	va_end(ptr);
}
#pragma warning(pop)

#if !defined UNIX
#pragma warning(push)
#pragma warning(disable : 4793)
inline void __cdecl AtlTrace(LPCWSTR pszFormat, ...)
{
	va_list ptr;
	va_start(ptr, pszFormat);
	ATL::CTrace::s_trace.TraceV(NULL, -1, atlTraceGeneral, 0, pszFormat, ptr);
	va_end(ptr);
}
#pragma warning(pop)
#endif /* !UNIX */

#pragma warning(push)
#pragma warning(disable : 4793)
inline void __cdecl AtlTrace2(DWORD_PTR dwCategory, UINT nLevel, LPCSTR pszFormat, ...)
{
	va_list ptr;
	va_start(ptr, pszFormat);
	ATL::CTrace::s_trace.TraceV(NULL, -1, dwCategory, nLevel, pszFormat, ptr);
	va_end(ptr);
}
#ifndef UNIX
#pragma warning(pop)
#endif

#if !defined UNIX
#pragma warning(push)
#pragma warning(disable : 4793)
inline void __cdecl AtlTrace2(DWORD_PTR dwCategory, UINT nLevel, LPCWSTR pszFormat, ...)
{
	va_list ptr;
	va_start(ptr, pszFormat);
	ATL::CTrace::s_trace.TraceV(NULL, -1, dwCategory, nLevel, pszFormat, ptr);
	va_end(ptr);
}
#pragma warning(pop)
#endif /* !UNIX */

#define ATLTRACENOTIMPL(funcname)  do { ATLTRACE(ATL::atlTraceNotImpl, 0, _TEXT("ATL: %s not implemented.\n"), funcname); return E_NOTIMPL; } while(0)

#else // !DEBUG

#ifndef UNIX
#pragma warning(push)
#pragma warning(disable : 4793)
#endif
inline void __cdecl AtlTraceNull(...){}
inline void __cdecl AtlTrace(LPCSTR , ...){}
inline void __cdecl AtlTrace2(DWORD_PTR, UINT, LPCSTR , ...){}
inline void __cdecl AtlTrace(LPCWSTR , ...){}
inline void __cdecl AtlTrace2(DWORD_PTR, UINT, LPCWSTR , ...){}
#ifndef UNIX
#pragma warning(pop)
#endif

#ifndef ATLTRACE

#define ATLTRACE(...)            __noop
#define ATLTRACE2(...)           __noop
#endif //ATLTRACE
#define ATLTRACENOTIMPL(funcname)   return E_NOTIMPL
#define DECLARE_NOUIASSERT()

#endif //!_DEBUG

};  // namespace ATL
#if !defined(SOLARIS) && !defined(FREEBSD)
#pragma pack(pop)
#endif

#endif  // __ATLTRACE_H__
