/*
 * Copyright(C) 2000 ������ ���
 *
 * ���� ���� �������� ����������, ����������
 * �������������� �������� ������ ���.
 *
 * ����� ����� ����� ����� �� ����� ���� �����������,
 * ����������, ���������� �� ������ �����,
 * ������������ ��� �������������� ����� ��������,
 * ���������������, �������� �� ���� � ��� ��
 * ����� ������������ ������� ��� ����������������
 * ���������� ���������� � ��������� ������ ���.
 */

/*!
 * \file $RCSfile$
 * \version $Revision: 154264 $
 * \date $Date:: 2017-03-15 18:01:24 +0400#$
 * \author $Author: sonina $
 *
 * \brief XXX
 *
 * XXX
 */
#ifndef _CSPMM_H_INCLUDED
#define _CSPMM_H_INCLUDED

#ifdef UNIX
#include<CSP_WinDef.h>
#else // UNIX
    #include <windef.h>
#endif // UNIX
#include<WinCryptEx.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CPC_MEMORY_ARENA_ CPC_MEMORY_ARENA, *LPCPC_MEMORY_ARENA;

typedef struct CPC_MEMORY_STATS_ {
    LONG nBytes;
    LONG nChunks;
    LONG Used;
    LONG Size;
} CPC_MEMORY_STATS, *LPCPC_MEMORY_STATS;

typedef DWORD CPCAPI CPC_AllocMemory_Callback(
    LPCPC_MEMORY_ARENA pArena, 
    CPC_SIZE_T dwSize,
    DWORD dwMemPoolId,
    DWORD dwThreadId,
    LPVOID *pRes
);

typedef DWORD CPCAPI CPC_FreeMemory_Callback(
    LPCPC_MEMORY_ARENA pArena,
    VOID *pMem,
    DWORD dwMemPoolId
);

typedef VOID CPCAPI CPC_StatMemory_Callback(
    LPCPC_MEMORY_ARENA pArena,
    LPCPC_MEMORY_STATS pStats,
    DWORD dwMemPoolId
);

typedef VOID CPCAPI CPC_ValidateMemory_Callback(
    LPCPC_MEMORY_ARENA pArena
);

typedef VOID CPCAPI CPC_DoneMemory_Callback(
    LPCPC_MEMORY_ARENA pArena
);

typedef VOID CPCAPI CPC_MemoryException_Callback(
    LPCPC_MEMORY_ARENA pArena,
    VOID *arg
);

struct CPC_MEMORY_ARENA_ {
    CPC_ValidateMemory_Callback     *pValidateMemory;
    CPC_DoneMemory_Callback	    *pDoneMemory;
    CPC_AllocMemory_Callback	    *pAllocMemory;
    CPC_FreeMemory_Callback	    *pFreeMemory;
    CPC_StatMemory_Callback	    *pStatMemory;
    CPC_MemoryException_Callback    *pHandleException;
    LPVOID			    lpArg;
};

/* �������������� ������� ��� ���������� (memory pool id)
   ��� ������, ����� ������ ����� ���������� � MP_PRIME � 
   ������ ����� ���������� � MP_SEC*/
#define MP_WORK		3
#define MP_PRIME	MP_WORK
#define MP_SEC		MP_WORK
#define MP_PRIME_M	4
#define MP_SEC_M	5
#define MP_WORK_M	6
#if defined ( _WIN32 ) || defined ( _WIN64 )
#define MP_BIG		7
#else
#define MP_BIG		MP_WORK
#endif /* defined ( _WIN32 ) || defined ( _WIN64 ) */

#define NO_ZERO_MEMORY		(0x80000000)

#ifdef __cplusplus
}
#endif

#endif /* _CSPMM_H_INCLUDED */
