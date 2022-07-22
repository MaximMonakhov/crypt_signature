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

#define DECLARE_CHECKSUM_VARIABLE(name) \
struct { \
uint32_t size; \
uint8_t checksum[32]; \
} name \
__attribute__ ((used)) \
__attribute__ ((visibility("default"))) \
__attribute__ ((section ("__DATA, __const")))

#define DECLARE_CONTROL_SUM() DECLARE_CHECKSUM_VARIABLE(program_control_sum)

#if defined( __cplusplus )
extern "C" {
#endif
const void * bio_gui_rndm_get_table( void );
const void * gemalto_media_get_table(void);
const void * default_reader_get_table( void );
const void * default_reader_get_group_table(void);
const void * pcsc_reader_get_table(void);
const void * pcsc_reader_get_group_table(void);
const void * cryptoki_reader_get_table(void);
const void * cryptoki_reader_get_group_table(void);
const void * rutokenfkc_media_get_table(void);
const void * jacarta_media_get_table(void);
const void * jacarta_lt_media_get_table(void);
const void * rutokennfc_media_get_table(void);
const void * rutokenlite_media_get_table(void);
const void * rutokenecp_media_get_table(void);
const void * rutokenlitesc2_media_get_table(void);
const void * rutokenecpsc_media_get_table(void);
const void * rutoken_media_get_table(void);
const void * rutokenpinpad_media_get_table(void);
const void * rutokenfkcold_media_get_table(void);
const void * rutokenecpm_media_get_table(void);
const void * rutokenecpmsc_media_get_table(void);
const void * cloud_reader_get_table(void);
const void * hvisdef_hvis_get_table(void);
#if defined( __cplusplus )
}
#endif
  
#endif //__CPROCSP_IOS_H__
