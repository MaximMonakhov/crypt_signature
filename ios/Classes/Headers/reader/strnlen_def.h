#ifndef STRNLEN_DEF_H
#define STRNLEN_DEF_H
    #if !defined _WIN32 && defined HAVE_CONFIG_H && !defined HAVE_STRNLEN
	static SUP_INLINE size_t 
	strnlen(const char *s, size_t maxlen)
	{
	    size_t i;
	    
	    for(i = 0; i < maxlen && s[i]; i++)
		;
	    return i;
	}
    #endif /* !_WIN32 && HAVE_CONFIG_H && !HAVE_STRNLEN */
    #if !defined _WIN32 && defined HAVE_CONFIG_H && !defined HAVE_WCSNLEN
	static SUP_INLINE size_t 
	wcsnlen(const wchar_t *ws, size_t maxlen)
	{
	    size_t i;
	    
	    for(i = 0; i < maxlen && ws[i]; i++)
		;
	    return i;
	}
    #endif /* _WIN32 && HAVE_CONFIG_H && !HAVE_WCSNLEN */
#endif //STRNLEN_DEF_H
