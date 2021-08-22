#ifndef SUPPORT_UTIL_H_INCLUDED
#define SUPPORT_UTIL_H_INCLUDED
#include"support_base_defs.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

    DWORD support_regex_match(const TCHAR* in_string, const TCHAR* in_regex, CSP_BOOL* matches);

    //multistring_buf not NULL
    static SUP_INLINE DWORD support_multistring_count_strings(const char* multistring_buf) {
	DWORD res = 0;
	const char* cur_pointer = multistring_buf;
	while (*cur_pointer != '\0') {
	    cur_pointer = cur_pointer + strlen(cur_pointer) + 1;
	    res++;
	}
	return res;
    }

    //multistring_buf not NULL
    static SUP_INLINE const char* support_multistring_enumerate_next_string(const char* multistring_buf) {
	return multistring_buf + strlen(multistring_buf) + 1;
    }

    static SUP_INLINE DWORD support_multistring_from_cstrings_array(const char* in_vec[], size_t n_elem, size_t *buf_len, char* multistring_buf) {
	size_t res_buf_len = 0;
	size_t i = 0;
	char* cur_pointer = NULL;
	if (NULL == in_vec || 0 == n_elem || NULL == buf_len) {
	    return (DWORD)ERROR_INVALID_PARAMETER;
	}
	for (i = 0; i < n_elem; i++) {
	    if (NULL == in_vec[i]) return (DWORD)ERROR_INVALID_PARAMETER;
	    res_buf_len += strlen(in_vec[i]) + 1;
	}
	if (NULL == multistring_buf) {
	    *buf_len = res_buf_len;
	    return ERROR_SUCCESS;
	}
	else if (*buf_len < res_buf_len) {
	    *buf_len = res_buf_len;
	    return (DWORD)ERROR_MORE_DATA;
	}
	cur_pointer = multistring_buf;
	for (i = 0; i < n_elem; i++) {
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4996)
#endif
	    strcpy(cur_pointer, in_vec[i]);
#ifdef _MSC_VER
#pragma warning(pop)
#endif
	    cur_pointer += strlen(cur_pointer) + 1;
	}
	*cur_pointer = '\0';
	*buf_len = res_buf_len;
	return ERROR_SUCCESS;
    }

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //SUPPORT_UTIL_H_INCLUDED
