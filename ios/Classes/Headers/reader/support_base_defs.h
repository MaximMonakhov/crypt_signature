#ifndef SUPPORT_BASE_DEFS_H_INCLUDED
#define SUPPORT_BASE_DEFS_H_INCLUDED
#include"../common.h"
#include"tchar.h"

/* --------------- INCLUDE --------------- */
#if defined(CSP_LITE)       	
#include<CSP_WinDef.h>
#include<CSP_WinError.h>
#elif defined _WIN32
#   include <stdlib.h>
#   include <malloc.h>
#   pragma warning( push )
#   pragma warning( disable: 4100 4115 4201 4214 )
#   include <windows.h>
#   include <time.h>
#   pragma warning( pop )
#elif defined UNIX
#   include <wchar.h>
#include"../CSP_WinDef.h"
#include"../CSP_WinError.h"
#   include <stdlib.h>
#   include <stdarg.h>
# ifdef HAVE_STDINT_H
#   include <stdint.h>
# elif defined(HAVE_INTTYPES_H)
#   include <inttypes.h>
# elif defined(HAVE_SYS_INTTYPES_H)
#   include <sys/inttypes.h>
# endif //HAVE_STDINT_H
#   include <time.h>
#   include <sys/time.h>
#   include <pthread.h>
#   include <nl_types.h>
#include"ubi_mutex.h"
#else
#   error !UNIX && !_WIN32
#endif //CSP_LITE

#include"std_decl.h"
#endif //SUPPORT_BASE_DEFS_H_INCLUDED
