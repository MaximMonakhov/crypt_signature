#include<common.h>

#if defined DEBUG && !defined _DEBUG
    #define _DEBUG 1
#endif

#if !defined( UNIX ) 

    #if !defined( CSP_LITE )

       	#ifdef _CPKERB_STATUS_
	    #define WIN32_NO_STATUS
       	#endif // _CPKERB_STATUS_

	#define RPC_USE_NATIVE_WCHAR 1

       	// ������ ������ �������������� C4201
       	// (nonstandard extension used : nameless struct/union)
       	// �.�. ��� ������� ������������ � ��������� ����������,
       	// � ��������������� ��� ������ � ��� ��������� - ������ NONAMELESSUNION
       	// �� �������� � ������ ������.
	#pragma warning(disable:4201)
	
	#include <winsock2.h>
       	#include <windows.h>
       	#ifdef _CPKERB_STATUS_
	    #undef WIN32_NO_STATUS
	    #include <ntstatus.h>
	    #define SECURITY_WIN32
	    #include <security.h>
	    #include <wincred.h>
	    #include <ntsecapi.h>
       	#endif /* _CPKERB_STATUS */

	#include <crtdbg.h>

    #else /* CSP_LITE */

       	#include "CSP_WinDef.h"
       	#include "CSP_WinCrypt.h"
       	#include "CSP_WinError.h"

    #endif /* CSP_LITE */

#else /* UNIX */

    #ifndef CSP_LITE
       	#if !defined _GNU_SOURCE
	    #define _GNU_SOURCE
       	#endif /* !_GNU_SOURCE */
       	#include <string.h>
    #endif
#include<CSP_WinDef.h>
    #define CPCSP_USE_NON_STANDART_OIDS
#include<WinCryptEx.h>
#include<wincsp.h>
#include<CSP_WinError.h>

    #if !defined(_ASSERTE)
	#if !defined (MODULE) && !defined(KERNEL)
	    #include <assert.h>
	    #define _ASSERTE(x) assert(x)
	#else
	    #define _ASSERTE(x) (x)
	#endif
    #endif

#endif /* UNIX */

#define ADDRESSIZE sizeof(unsigned long*)
#define MASK32BIT 0xffffffff
