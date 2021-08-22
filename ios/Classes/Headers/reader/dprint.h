#ifndef DPRINT_H_INCLUDED
#define DPRINT_H_INCLUDED 1

#include<support.h>

/* Before including this file one can set something like this: */

// ������� �������������� (��������� � �-���� �������������):
// ERRO (eprint_func)
//   Unix: Sys Log (LOG_ERR)
//   Windows: Debugger Log
//   Mobile: Debugger Log
//
// NORM (dprint_func)
//   Unix: Sys Log (LOG_INFO)
//   Windows: Debugger Log
//   Mobile: Debugger Log
//
// CONS (cprint_func)
//   Unix: Console
//   Windows: Console
//   Mobile: Console
//
// ELOG (elprint_func)
//   Unix: = ERRO = Sys Log (LOG_ERR)
//   Windows: Event Log
//   Mobile: = ERRO = Debugger Log
//
// EXCL (NULL)
//   Unix: None
//   Windows: None
//   Mobile: None
//
// TODO: �����, ��� � ������� ���������� ���� ����������:
// � ������� �� Unix �� Windows ��� �������� ������� � Event Log.
// ����� ������� ������� ELOG � ������� ������������� �� Windows
// ��������� �� DEBUG:
//   � Release - �� � Event Log �� ERRO � NORM - � ������� ���������
//   � Debug - �� � Debugger Log - ��� ������
// ��� ���� � ������ ���������� ���� �������� ��������� ELOG,
// ������� ����� ��������������� ��� ������ ���������.

#ifndef DB_ERROR
# if defined _DEBUG
// � Debug ����� �� � Debugger Log - ��� ����������� �������
#    if defined IOS
#      define DB_ERROR CONS
#      define DB_TRACE CONS
#      define DB_CALL CONS
#      define DB_LOG CONS
#      define DB_WARN CONS
#    else // IOS
#      define DB_ERROR ERRO
#      define DB_TRACE NORM
#      define DB_CALL NORM
#      define DB_LOG NORM
#      define DB_WARN NORM
#    endif // IOS
# else // � Release ����� ����� �� � Event Log
#  if defined IOS
#      define DB_WARN CONS
#      define DB_LOG CONS
#      define DB_ERROR CONS
#  elif defined UNIX
#      define DB_WARN NORM
#      define DB_LOG NORM
#      define DB_ERROR ELOG
#  else
#   ifdef CSP_LITE//�� Windows � �������� ����� ����� ��� � UNIX
#      define DB_WARN NORM
#      define DB_LOG NORM
#      define DB_ERROR ELOG
#   else
#      define DB_WARN ELOG
#      define DB_LOG ELOG
#      define DB_ERROR ELOG
#   endif
#  endif
#      define DB_TRACE EXCL
#      define DB_CALL EXCL
# endif /* _DEBUG */
#endif

#ifdef _DEBUG
#define SUPPORT_DB_LEVEL_DEFAULT N_DB_ERROR 
#else
#define SUPPORT_DB_LEVEL_DEFAULT 0
#endif

#define SUPPORT_DBFMT_MODULE 1
#define SUPPORT_DBFMT_THREAD 2
#define SUPPORT_DBFMT_FLINE 4
#define SUPPORT_DBFMT_FUNC 8
#define SUPPORT_DBFMT_TEXT 0x10
#define SUPPORT_DBFMT_HEX 0x20
#define SUPPORT_DBFMT_ERR 0x40

#define SUPPORT_DBFMT_ALL 0x7F
#define SUPPORT_DBFMT_DEFAULT (SUPPORT_DBFMT_ALL)
#define SUPPORT_DBFMT_CLEAN 0x38
#define SUPPORT_DBLEVEL_ALL 0xffffffffU

#define NCOUNT(x) x
#define CONCAT_COUNT(x,y) NCOUNT(x)##NCOUNT(y)
#define CONCAT(x,y) x##y

#define __STR2WSTR(str)	L##str
#define _STR2WSTR(str)	__STR2WSTR(str)

#if defined( _MSC_VER ) 
# if defined UNICODE
#   define SFUNC _STR2WSTR(__FUNCTION__)
# else
#   define SFUNC __FUNCTION__
# endif
#elif defined(__GNUC__)
#   define SFUNC __func__
#else /*defined( _MSC_VER ) */
#   define SFUNC __func__
#endif /*defined( _MSC_VER ) */

#define DCHAR TCHAR
#define __DTEXT(x) _TEXT(x)
#define DTEXT(x) __DTEXT(x)
#if defined _WIN32 && defined UNICODE
#   define __DFILE__ _STR2WSTR(__FILE__)
#   define D2A "%S"
#   define D2W "%s"
#else
#   define __DFILE__ __FILE__
#   define D2A "%s"
#   define D2W "%S"
#endif

//��� ������ TCHAR * � ASCII �������
#ifdef _UNICODE
#define _T2A "%S"
#else
#define _T2A "%s"
#endif

#if defined _WIN32
#define DBSTR(x) x
#define DBSTRA(x) x
#define DBSTRW(x) x
#else
#define DBSTR(x) (x?x:_TEXT("null"))
#define DBSTRA(x) (x?x:"null")
#define DBSTRW(x) (x?x:L"null")
#endif

#define SUPPORT_DBFTEXT_(x) x, __DFILE__, __LINE__, SFUNC
#define SUPPORT_DBFTEXTR_(x) x, DTEXT(""), __LINE__, SFUNC

#if defined _DEBUG
#define FTEXT(ctx,a) ctx,SUPPORT_DBFTEXT_(DTEXT(a))
#define FTEXT2(ctx,a,b) ctx,SUPPORT_DBFTEXT_(DTEXT(a) DTEXT(b))
#define FTEXT3(ctx,a,b,c) ctx,SUPPORT_DBFTEXT_(DTEXT(a) DTEXT(b) DTEXT(c))
#define FTEXT4(ctx,a,b,c,d) ctx,SUPPORT_DBFTEXT_(DTEXT(a) DTEXT(b) DTEXT(c) DTEXT(d))
#define FTEXT5(ctx,a,b,c,d,e) ctx,SUPPORT_DBFTEXT_(DTEXT(a) DTEXT(b) DTEXT(c) DTEXT(d) DTEXT(e))
#else
#define FTEXT(ctx,a) ctx,SUPPORT_DBFTEXTR_(DTEXT(a))
#define FTEXT2(ctx,a,b) ctx,SUPPORT_DBFTEXTR_(DTEXT(a) DTEXT(b))
#define FTEXT3(ctx,a,b,c) ctx,SUPPORT_DBFTEXTR_(DTEXT(a) DTEXT(b) DTEXT(c))
#define FTEXT4(ctx,a,b,c,d) ctx,SUPPORT_DBFTEXTR_(DTEXT(a) DTEXT(b) DTEXT(c) DTEXT(d))
#define FTEXT5(ctx,a,b,c,d,e) ctx,SUPPORT_DBFTEXTR_(DTEXT(a) DTEXT(b) DTEXT(c) DTEXT(d) DTEXT(e))
#endif

// ������ �����������
typedef enum DBType_ {
	N_DB_ERROR = 1,
	N_DB_TRACE = 2,
	N_DB_CALL = 4,
	N_DB_LOG = 8,
	N_DB_WARN = 0x20
} DBType;

#define SUPPORT_DB_QPRINT_ERRO(level,param) \
    if( support_print_qis_##level param ) support_eprint_print_ param
#define SUPPORT_DB_QPRINT_NORM(level,param) \
    if( support_print_qis_##level param ) support_dprint_print_ param
#define SUPPORT_DB_QPRINT_CONS(level,param) \
    if( support_print_qis_##level param ) support_cprint_print_ param
#define SUPPORT_DB_QPRINT_ELOG(level,param) \
    if( support_print_qis_##level param ) support_elprint_print_ param
#define SUPPORT_DB_QPRINT_EXCL(level,param)
#define SUPPORT_DB_QPRINT_HEX_ERRO(context,level,file,line,func,msg,buffer,length)\
    if( support_print_qis_##level(context, file) ) support_eprint_hex(context,file,line,func,msg,buffer,length)
#define SUPPORT_DB_QPRINT_HEX_NORM(context,level,file,line,func,msg,buffer,length)\
    if( support_print_qis_##level(context, file) ) support_dprint_hex(context,file,line,func,msg,buffer,length)
#define SUPPORT_DB_QPRINT_HEX_CONS(context,level,file,line,func,msg,buffer,length)\
    if( support_print_qis_##level(context, file) ) support_cprint_hex(context,file,line,func,msg,buffer,length)
#define SUPPORT_DB_QPRINT_HEX_ELOG(context,level,file,line,func,msg,buffer,length)\
    if( support_print_qis_##level(context, file) ) support_elprint_hex(context,file,line,func,msg,buffer,length)
#define SUPPORT_DB_QPRINT_HEX_EXCL(context,level,file,line,func,msg,buffer,length)

#ifdef NO_DB_TRACE
#define DbTrace(level, param) 
#define DbTraceHex(level, ctx, msg, buffer, length) 
#define DbTraceInit(ctx,info,module,level,format)
#define DbTraceDone(ctx) 
#else // !NO_DB_TRACE
#define DbTrace(level, param) CONCAT(SUPPORT_DB_QPRINT_,level)(N_##level,param)  
#if defined _DEBUG
#define DbTraceHex(level, ctx, msg, buffer, length) CONCAT(SUPPORT_DB_QPRINT_HEX_,level)(ctx,N_##level,__DFILE__,__LINE__,SFUNC,msg,buffer,length)
#else
#define DbTraceHex(level, ctx, msg, buffer, length) CONCAT(SUPPORT_DB_QPRINT_HEX_,level)(ctx,N_##level,DTEXT(""),__LINE__,SFUNC,msg,buffer,length)
#endif
#define DbTraceInit(ctx,info,module,level,format) { ctx = support_print_init(info,module,level,format ); }
#define DbTraceDone(ctx) { support_print_done( ctx ); ctx = NULL; }
#endif // !NO_DB_TRACE

#ifdef __cplusplus
extern "C" {
#endif
struct TSupportDbContext_;

typedef struct TSupportDbContext_ TSupportDbContext;

#ifdef SOLARIS
#define SYMBOLIC_SCOPE __symbolic
#else // SOLARIS
#define SYMBOLIC_SCOPE
#endif // SOLARIS
extern SYMBOLIC_SCOPE TSupportDbContext* db_ctx;
#undef SYMBOLIC_SCOPE

/*!
 * \ingroup ProCPCCallbacks
 *
 * \brief Callback-������� ��� ������ ���������.
 *
 * \param callback_arg [in] ��������, ���������� ��� ����������� callback-�������.
 *
 * \param str [in] ������, ������� ����� �������. �� �������� '\\n'.
 */
typedef void _SUPPORT_CALLBACK_CONV support_print_str_callback(void *callback_arg, const DCHAR *str);
typedef void _SUPPORT_CALLBACK_CONV support_print_str_ex_callback(void *callback_arg, const DCHAR *str, size_t data_size, void *raw_data);

/*!
 * \ingroup ProCPCCallbacks
 *
 * \brief Callback-������� ��� ��������� �������������� ������.
 *
 * \return ��� �������� ���������� ������� ���������� ������������� ������, � ���������
 * ������ ���������� 0.
 */
typedef unsigned long _SUPPORT_CALLBACK_CONV support_get_thread_id_callback(void);

/* DebugInfo dprint*/
DWORD _SUPPORT_CALLBACK_CONV
support_print_init_ex(TSupportDbContext* buf, size_t * sz, void *info,
		      const DCHAR *module, unsigned level, unsigned format,
		      support_print_str_callback *dprint_str, 
		      support_print_str_callback *eprint_str,
		      support_print_str_callback *cprint_str,
		      support_print_str_callback *elprint_str,
		      support_print_str_ex_callback *dprint_str_ex, 
		      support_print_str_ex_callback *eprint_str_ex,
		      support_print_str_ex_callback *cprint_str_ex,
		      support_print_str_ex_callback *elprint_str_ex,
		      support_get_thread_id_callback *get_thread_id,
		      void *callback_arg);
TSupportDbContext* _SUPPORT_CALLBACK_CONV
support_print_init(void *info, const DCHAR *module, unsigned level,
		   unsigned format);
DWORD _SUPPORT_CALLBACK_CONV
support_print_done_ex(TSupportDbContext* ctx);
DWORD _SUPPORT_CALLBACK_CONV
support_print_done(TSupportDbContext* ctx);
void* _SUPPORT_CALLBACK_CONV
support_print_callback_arg( TSupportDbContext* ctx );

int _SUPPORT_CALLBACK_CONV
support_print_is(TSupportDbContext* ctx, unsigned when);


#if defined _DEBUG || !defined ( _WIN32 )//�� *nix ���������� ������������� ���� - ����� ��� ������� - �������� �� �������
#define support_print_qis_N_DB_ERROR(ctx, ...) (ctx && support_print_is(ctx, N_DB_ERROR))
#define support_print_qis_N_DB_TRACE(ctx, ...) (ctx && support_print_is(ctx, N_DB_TRACE))
#define support_print_qis_N_DB_CALL(ctx, ...) (ctx && support_print_is(ctx, N_DB_CALL))
#define support_print_qis_N_DB_LOG(ctx, ...) (ctx && support_print_is(ctx, N_DB_LOG))
#define support_print_qis_N_DB_WARN(ctx, ...) (ctx && support_print_is(ctx, N_DB_WARN))
#else /*defined _DEBUG*/
#define support_print_qis_N_DB_ERROR(ctx, ...) (ctx && (*(unsigned*)(ctx)&N_DB_ERROR))
#define support_print_qis_N_DB_TRACE(ctx, ...) (ctx && (*(unsigned*)(ctx)&N_DB_TRACE))
#define support_print_qis_N_DB_CALL(ctx, ...) (ctx && (*(unsigned*)(ctx)&N_DB_CALL))
#define support_print_qis_N_DB_LOG(ctx, ...) (ctx && (*(unsigned*)(ctx)&N_DB_LOG))
#define support_print_qis_N_DB_WARN(ctx, ...) (ctx && (*(unsigned*)(ctx)&N_DB_WARN))
#endif /*defined _DEBUG*/

DWORD
support_cprint_print(TSupportDbContext* ctx, const DCHAR *str,
		     const DCHAR *file, int line, const DCHAR *func,
		     va_list args);
DWORD
support_dprint_print(TSupportDbContext* ctx, const DCHAR *str,
		     const DCHAR *file, int line, const DCHAR *func,
		     va_list args);
DWORD
support_eprint_print(TSupportDbContext* ctx, const DCHAR *str,
		     const DCHAR *file, int line, const DCHAR *func,
		     va_list args);
DWORD
support_elprint_print(TSupportDbContext* ctx, const DCHAR *str,
		      const DCHAR *file, int line, const DCHAR *func,
		      va_list args);
//+V576, function:support_cprint_print_, format_arg:2, ellipsis_arg:6
void
support_cprint_print_(TSupportDbContext* ctx, const DCHAR *str,
		      const DCHAR *file, int line, const DCHAR *func, ...);
//+V576, function:support_dprint_print_, format_arg:2, ellipsis_arg:6
void
support_dprint_print_(TSupportDbContext* ctx, const DCHAR *str, 
		      const DCHAR *file, int line, const DCHAR *func, ...);
//+V576, function:support_eprint_print_, format_arg:2, ellipsis_arg:6
void
support_eprint_print_(TSupportDbContext* ctx, const DCHAR *str,
		      const DCHAR *file, int line, const DCHAR *func, ...);
//+V576, function:support_elprint_print_, format_arg:2, ellipsis_arg:6
void
support_elprint_print_(TSupportDbContext* ctx, const DCHAR *str,
		       const DCHAR *file, int line, const DCHAR *func, ...);
DWORD
_SUPPORT_CALLBACK_CONV
support_dprint_hex(TSupportDbContext *ctx, const DCHAR *file, int line,
		   const DCHAR *func, const DCHAR *msg, void *info, size_t size);
DWORD
_SUPPORT_CALLBACK_CONV
support_cprint_hex(TSupportDbContext *ctx, const DCHAR *file, int line,
		   const DCHAR *func, const DCHAR *msg, void *info, size_t size);
DWORD
_SUPPORT_CALLBACK_CONV
support_eprint_hex(TSupportDbContext *ctx, const DCHAR *file, int line,
		   const DCHAR *func, const DCHAR *msg, void *info, size_t size);
DWORD
_SUPPORT_CALLBACK_CONV
support_elprint_hex(TSupportDbContext *ctx, const DCHAR *file, int line,
		    const DCHAR *func, const DCHAR *msg, void *info, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* DPRINT_H_INCLUDED */
