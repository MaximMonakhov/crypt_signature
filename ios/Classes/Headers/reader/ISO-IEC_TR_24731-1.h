/*
 * Copyright(C) 2009 ������ ���
 *
 * ���� ���� �������� ����������, ����������
 * �������������� �������� ������-���.
 *
 * ����� ����� ����� ����� �� ����� ���� �����������,
 * ����������, ���������� �� ������ �����,
 * ������������ ��� �������������� ����� ��������,
 * ���������������, �������� �� ���� � ��� ��
 * ����� ������������ ������� ��� ����������������
 * ���������� ���������� � ��������� ������-���.
 */

/*!
 * \file $RCSfile$
 * \version $Revision: 174826 $
 * \date $Date:: 2018-05-15 17:27:58 +0400#$
 * \author $Author: ladunoff $
 *
 * \brief �������� ����� ����������� ������ ����������
 */

#ifndef ISO_IEC_TR_24731_1_H_
#define ISO_IEC_TR_24731_1_H_

#include<strnlen_def.h>

#ifndef _len_of
    #define _len_of(a)    (sizeof(a)/sizeof(*(a)))
#endif

#ifdef UNIX
    // MS VS form of ISO/IEC TR 24731-1
    // <http://www.open-std.org/JTC1/SC22/WG14/www/projects#24731-1>
    // See \\cp.ru\dfs\home\lse\doc\C\n1225.pdf
    // See \\cp.ru\dfs\home\lse\doc\C\n1173.pdf
    //
    // strnlen
    
    // wcscpy_s // TODO: check s1 & s2
	#define wcscpy_s(s1, s1max, s2) ( \
			&(s1)[s1max] == wcsncpy((s1), (s2), (s1max)) \
			    ? ((s1)[(s1max)-1] = '\0' ? -1 : -1) \
			    : 0 \
		    )
	#define wcsncpy_s(s1, s1max, s2, n) ( \
			(n) >= (s1max) \
			    ? wcscpy_s((s1), (s1max), (s2)) \
			    : (wcsncpy((s1), (s2), (n)), (s1)[n] = '\0') \
		    )
	
    // strcpy_s // TODO: check s1 & s2
	#define strcpy_s(s1, s1max, s2) ( \
			strncpy((s1), (s2), (s1max)), \
			(s1)[(s1max)-1]  \
			    ? ((s1)[(s1max)-1] = '\0' ? -1 : -1) \
			    : 0 \
		    )
	#define strncpy_s(s1, s1max, s2, n) ( \
			(n) >= (s1max) \
			    ? strcpy_s((s1), (s1max), (s2)) \
			    : (strncpy((s1), (s2), (n)), (s1)[n] = '\0') \
		    )
    // sprintf_s // TODO: check s & format
	#define sprintf_s(s, n, format, ...)  ( \
		       (memset(s,0,n), /* XXX dim: valgrind want to be happy */ \
			0 > snprintf((s), (n), format, ##__VA_ARGS__) \
			? -1 \
			: ( (s)[(n)-1] \
			    ? (s)[(n)-1] = '\0' \
			    : (int)strnlen((s), (n)) \
			  ) \
		       ) \
		    )
    // vsprintf_s // TODO: check s & format
	#define vsprintf_s(s, n, format, arg)  ( \
			( 0 > vsnprintf((s), (n), (format), (arg)) \
			? -1 \
			: ( (s)[(n)-1] \
			    ? (s)[(n)-1] = '\0' \
			    : (int)strnlen((s), (n)) \
			  ) \
			) \
		    )
    // gmtime_s // TODO check TR & MS Doc & __STDC_LIB_EXT1_ _ The integer constant 200509L
	#define gmtime_s(tm, time) ( \
			gmtime_r((time), (tm)) \
		    )
    // asctime_s // TODO check s1 & maxsize < 26
	#define asctime_s(s, maxsize, timerptr) ( \
			strcpy_s((s), (maxsize), asctime(timerptr)) \
		    )
#if 0
	#define strerror_s(buf, num, errnum) ( \
			strerror_r((errnum), (buf), (num)) \
		    )
#endif //0
	#define localtime_s(presult, cptimer) ( \
			localtime_r((cptimer), (presult)) \
			    ? 0 \
			    : errno \
		    )

#endif

#endif /*ISO_IEC_TR_24731_1_H_*/
