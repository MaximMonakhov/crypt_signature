/*
 * Copyright(C) 2000 Проект ИОК
 *
 * Этот файл содержит информацию, являющуюся
 * собственностью компании Крипто Про.
 *
 * Любая часть этого файла не может быть скопирована,
 * исправлена, переведена на другие языки,
 * локализована или модифицирована любым способом,
 * откомпилирована, передана по сети с или на
 * любую компьютерную систему без предварительного
 * заключения соглашения с компанией Крипто Про.
 */

/*
 * \file $RCSfile$
 * \version $Revision: 127051 $
 * \date $Date:: 2015-09-09 05:08:20 -0700#$
 * \author $Author: pav $
 */
/*!
 * \brief Интерфейс безблокировочного (lock-free) менеджера памяти.
 *
 * Содержит прототипы функций безблокировочного менеджера памяти уровня CPC.
 */
#ifndef _LFMM_H_INCLUDED
#define _LFMM_H_INCLUDED

#include <wincspc.h>

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

typedef struct CPC_LFMM_CONFIG_ {
    CPC_INTERLOCKED_FUNCS   interlockedFuncs;
    LPVOID		    Buffer;
    LONG		    Size;
    CSP_BOOL		    fSMP;
    CSP_BOOL		    fStat;
    LONG 		    *PoolSizes;
    DWORD		    nPools;
    DWORD		    nCPUs;
} CPC_LFMM_CONFIG, * LPCPC_LFMM_CONFIG;

typedef DWORD CPCAPI CPCInitMemoryLF_t(
    /* [out] */ LPCPC_MEMORY_ARENA* pArena,
    /* [in] */ LPCPC_LFMM_CONFIG pCfg
);

#if !defined(CSP_LITE) || defined(LINUX) || defined(SOLARIS)
	// При использовании библиотек, а так же в Linux и Solaris
	// Символы доступны прямо.
#elif defined(FREEBSD)
    // ?????
    #define LFMM_SEPARATE_NAMESPACE_BINDING 1
#elif !defined(UNIX)
    // #include "cpdrvlib.h"
    // IOCTL_GETCPCINITMEMORYLF
    #define LFMM_SEPARATE_NAMESPACE_BINDING 1
#endif

#if !defined(LFMM_SEPARATE_NAMESPACE_BINDING)
    CPCInitMemoryLF_t CPCInitMemoryLF;
#endif

#if defined(__cplusplus)
} // extern "C"
#endif // defined(__cplusplus)

#endif /* _LFMM_H_INCLUDED */
