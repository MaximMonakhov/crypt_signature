#ifndef __CPROCSP_IOS_H__
#define __CPROCSP_IOS_H__

#ifndef UNIX
#  define UNIX 1
#endif

#ifndef IOS
#  define IOS 1
#endif

#ifndef SIZEOF_VOID_P 
#    define SIZEOF_VOID_P 4
#endif //SIZEOF_VOID_P

#ifndef HAVE_STDLIB_H
#  define HAVE_STDLIB_H 1
#endif

#ifndef HAVE_STDINT_H
#  define HAVE_STDINT_H 1
#endif

#include"CSP_WinCrypt.h"
#include"WinCryptEx.h"
#include"CSP_Sspi.h"
#include"reader/support.h"
#include"CSP_SChannel.h"

#endif //__CPROCSP_IOS_H__
