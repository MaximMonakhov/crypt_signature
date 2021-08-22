#ifndef CPRO_SUPPORT_H
#define CPRO_SUPPORT_H

#ifdef UNIX

#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_VERSION
#undef PACKAGE_TARNAME

#include<support.h>
#include<CSP_WinCrypt.h>
#include<CSP_SChannel.h>
#include<CSP_Sspi.h>

#ifdef PROV_RSA_FULL
#undef PROV_RSA_FULL
#endif
#define PROV_RSA_FULL PROV_GOST_2012_256

#ifdef PROV_RSA_AES
#undef PROV_RSA_AES
#endif
#define PROV_RSA_AES PROV_GOST_2012_256

#define SECURITY_LIB_NAME _TEXT("libssp.so")
#define LIBLOAD(name) support_load_library_registry(name, SUP_LOAD_LIBRARY_DEFAULT | SUP_LOAD_LIBRARY_SEPARATE | SUP_LOAD_LIBRARY_LAZY)
#define LIBCLOSE(name) support_unload_library_registry(name)
#define LIBFUNC(lib, name) support_load_library_getaddr(lib, name)

// �� ����� ������� ���������, ����� �������� �������� ������.
TCHAR * cpro_tcsdup( TCHAR * tcs );
#define _tcsdup(x) cpro_tcsdup( x )
#define Curl_load_library(x) (HMODULE)LIBLOAD(SECURITY_LIB_NAME)
#define GetProcAddress(x, f) LIBFUNC(x, f)
#define FreeLibrary(name) LIBCLOSE(name)
#define _tcsnccmp(str1, str2, len) _tcsncmp(str1, str2, len)
#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif // min

/* Version condition */
typedef enum {
  VERSION_LESS_THAN,
  VERSION_LESS_THAN_EQUAL,
  VERSION_EQUAL,
  VERSION_GREATER_THAN_EQUAL,
  VERSION_GREATER_THAN
} VersionCondition;

/* Platform identifier */
typedef enum {
  PLATFORM_DONT_CARE,
  PLATFORM_WINDOWS,
  PLATFORM_WINNT
} PlatformIdentifier;

// ��������� ��������� ����� ����� �����
#define Curl_verify_windows_version(majorVersion, minorVersion, platform, condition) \
(\
    (condition == VERSION_LESS_THAN || \
    condition == VERSION_LESS_THAN_EQUAL || \
    condition == VERSION_EQUAL) ? \
    FALSE : \
    TRUE \
)

#endif // UNIX
#endif // CPRO_SUPPORT_H
