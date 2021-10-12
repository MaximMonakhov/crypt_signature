#ifndef SUPPORT_UTIL_H_INCLUDED
#define SUPPORT_UTIL_H_INCLUDED
#include<reader/support_base_defs.h>

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

    DWORD support_regex_match(const TCHAR* in_string, const TCHAR* in_regex, CSP_BOOL* matches);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //SUPPORT_UTIL_H_INCLUDED
