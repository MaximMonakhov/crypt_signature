/*
 * Copyright(C) 2000-2006 ������ ���
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
 * \version $Revision: 207546 $
 * \date $Date:: 2020-03-02 17:00:35 +0400#$
 * \author $Author: frolov $
 *
 * \brief XXX
 *
 * XXX
 */
#ifndef _WINCSPC_H_INCLUDED
#define _WINCSPC_H_INCLUDED

#include<WinCryptEx.h>
#include<cspvtable.h>
#include<cspmm.h>

#if defined(UNIX) && defined(UNICODE)
#error "CryptoPro CSP provides only ANSI version of the kernel level interface for UNIX"
#endif // defined(UNIX) && defined(UNICODE)

#if defined(_WIN32) && !defined(UNICODE)
#error "CryptoPro CSP provides only Unicode version of the kernel level interface for Windows"
#endif // defined(_WIN32) && !defined(UNICODE)

/*
// CPCSP-10322: TRACK_LOCKS_USAGE ������ ������ ��������� �� gcc 3.x
// ��-�� ������������ �������� �������
#if defined(DEBUG)
#define TRACK_LOCKS_USAGE
#endif // defined(DEBUG)
*/

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

typedef struct _timeval CPC_timeval;
typedef struct CPC_CONFIG_ CPC_CONFIG, *LPCPC_CONFIG;
typedef struct CPC_CONFIG2_ CPC_CONFIG2, *LPCPC_CONFIG2;
typedef struct CPC_FUNCTION_TABLE_ CPC_FUNCTION_TABLE, *HCRYPTMODULE;

typedef struct CPC_RWLOCK_ CPC_RWLOCK, *LPCPC_RWLOCK;

//=============================================================================
// ������� ������������� ����������������
typedef DWORD CPCAPI CPCCreateProvider_t(
    /* [out] */ HCRYPTMODULE* hCSP,
    /* [in] */ LPCPC_CONFIG pConfig);

typedef DWORD CPCAPI CPCGetDefaultConfig_t(
    /* [in, out] */ LPCPC_CONFIG pConfig,
    /* [in] */ LPVOID pvReserved);

//=============================================================================
// ������� ������ � ����������������� ���������� CPC
typedef DWORD CPCAPI CPCAcquireContext_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [out] */ HCRYPTPROV *phProv,
    /* [string][in] */ CHAR *pszContainer,
    /* [in] */ DWORD dwFlags,
    /* [in] */ PVTABLEPROVSTRUC pVTable);

typedef DWORD CPCAPI CPCReleaseContext_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ DWORD dwFlags);

typedef DWORD CPCAPI CPCGetProvParam_t( 
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ DWORD dwParam,
    /* [size_is][out] */ BYTE *pbData,
    /* [out][in] */ DWORD *pdwDataLen,
    /* [in] */ DWORD dwFlags);

typedef DWORD CPCAPI CPCSetProvParam_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ DWORD dwParam,
    /* [size_is][in] */ BYTE *pbData,
    /* [in] */ DWORD dwFlags);

typedef DWORD CPCAPI CPCGenKey_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ ALG_ID AlgId,
    /* [in] */ DWORD dwFlags,
    /* [out] */ HCRYPTKEY *phKey);

typedef DWORD CPCAPI CPCDestroyKey_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTKEY hKey);

typedef DWORD CPCAPI CPCCreateHash_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ ALG_ID AlgId,
    /* [in] */ HCRYPTKEY hKey,
    /* [in] */ DWORD dwFlags,
    /* [out] */ HCRYPTHASH *phHash);

typedef DWORD CPCAPI CPCDestroyHash_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTHASH hHash);

typedef DWORD CPCAPI CPCEncrypt_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTKEY hKey,
    /* [in] */ HCRYPTHASH hHash,
    /* [in] */ CSP_BOOL Final,
    /* [in] */ DWORD dwFlags,
    /* [size_is][out][in] */ BYTE *pbData,
    /* [out][in] */ DWORD *pdwDataLen,
    /* [in] */ DWORD dwBufLen);

typedef DWORD CPCAPI CPCDecrypt_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTKEY hKey,
    /* [in] */ HCRYPTHASH hHash,
    /* [in] */ CSP_BOOL Final,
    /* [in] */ DWORD dwFlags,
    /* [full][size_is][out][in] */ BYTE *pbData,
    /* [out][in] */ DWORD *pdwDataLen);

typedef DWORD CPCAPI CPCDeriveKey_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ ALG_ID AlgId,
    /* [in] */ HCRYPTHASH hBaseData,
    /* [in] */ DWORD dwFlags,
    /* [out] */ HCRYPTKEY *phKey);

typedef DWORD CPCAPI CPCDuplicateKey_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTKEY hKey,
    /* [full][in] */ DWORD *pdwReserved,
    /* [in] */ DWORD dwFlags,
    /* [out] */ HCRYPTKEY *phKey);

typedef DWORD CPCAPI CPCDuplicateHash_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTHASH hHash,
    /* [full][in] */ DWORD *pdwReserved,
    /* [in] */ DWORD dwFlags,
    /* [out] */ HCRYPTHASH *phHash);

typedef DWORD CPCAPI CPCExportKey_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTKEY hKey,
    /* [in] */ HCRYPTKEY hExpKey,
    /* [in] */ DWORD dwBlobType,
    /* [in] */ DWORD dwFlags,
    /* [full][size_is][out][in] */ BYTE *pbData,
    /* [out][in] */ DWORD *pdwDataLen);

typedef DWORD CPCAPI CPCGenRandom_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ DWORD dwLen,
    /* [size_is][out][in] */ BYTE *pbBuffer);

typedef DWORD CPCAPI CPCGetHashParam_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTHASH hHash,
    /* [in] */ DWORD dwParam,
    /* [full][size_is][out][in] */ BYTE *pbData,
    /* [out][in] */ DWORD *pdwDataLen,
    /* [in] */ DWORD dwFlags);

typedef DWORD CPCAPI CPCGetKeyParam_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTKEY hKey,
    /* [in] */ DWORD dwParam,
    /* [full][size_is][out][in] */ BYTE *pbData,
    /* [out][in] */ DWORD *pdwDataLen,
    /* [in] */ DWORD dwFlags);

typedef DWORD CPCAPI CPCGetUserKey_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ DWORD dwKeySpec,
    /* [out] */ HCRYPTKEY *phUserKey);

typedef DWORD CPCAPI CPCHashData_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTHASH hHash,
    /* [full][size_is][in] */ CONST BYTE *pbData,
    /* [in] */ DWORD dwDataLen,
    /* [in] */ DWORD dwFlags);

typedef DWORD CPCAPI CPCHashSessionKey_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTHASH hHash,
    /* [in] */ HCRYPTKEY hKey,
    /* [in] */ DWORD dwFlags);

typedef DWORD CPCAPI CPCImportKey_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [full][size_is][in] */ CONST BYTE *pbData,
    /* [in] */ DWORD dwDataLen,
    /* [in] */ HCRYPTKEY hImpKey,
    /* [in] */ DWORD dwFlags,
    /* [out] */ HCRYPTKEY *phKey);

typedef DWORD CPCAPI CPCSetHashParam_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTHASH hHash,
    /* [in] */ DWORD dwParam,
    /* [size_is][in] */ BYTE *pbData,
    /* [in] */ DWORD dwFlags);

typedef DWORD CPCAPI CPCSetKeyParam_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTKEY hKey,
    /* [in] */ DWORD dwParam,
    /* [size_is][in] */ BYTE *pbData,
    /* [in] */ DWORD dwFlags);

typedef DWORD CPCAPI CPCSignHash_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTHASH hHash,
    /* [in] */ DWORD dwKeySpec,
    /* [string][full][in] */ LPCWSTR sDescription,
    /* [in] */ DWORD dwFlags,
    /* [size_is][out][in] */ BYTE *pbSignature,
    /* [out][in] */ DWORD *pdwSigLen);

typedef DWORD CPCAPI CPCVerifySignature_t(
    /* [in] */ HCRYPTMODULE hCSP,
    /* [in] */ HCRYPTPROV hProv,
    /* [in] */ HCRYPTHASH hHash,
    /* [size_is][in] */ CONST BYTE *pbSignature,
    /* [in] */ DWORD dwSigLen,
    /* [in] */ HCRYPTKEY hPubKey,
    /* [string][full][in] */ LPCWSTR sDescription,
    /* [in] */ DWORD dwFlags);

typedef DWORD CPCAPI CPCDestroyProvider_t(
    /* [in] */ HCRYPTMODULE hCSP);

//=============================================================================
// ������� ��������� ������ ���������� CPC
typedef void CPCAPI CPC_print_str_Callback(
    /* [in] */ void *callback_arg,
    /* [in] */ const TCHAR *str);

typedef unsigned long CPCAPI CPC_get_thread_id_Callback(void);

typedef DWORD CPCAPI CPC_InitRWLock_Callback (
    /* [out] */ LPCPC_RWLOCK pSection,
    /* [in] */ DWORD cbSection,
    /* [in] */ LPVOID lpArg);

typedef VOID CPCAPI CPC_DestroyRWLock_Callback(
    /* [in][out] */ LPCPC_RWLOCK pSection);

typedef VOID CPCAPI CPC_RDLockRWLock_Callback(
    /* [in][out] */ LPCPC_RWLOCK pSection);

typedef VOID CPCAPI CPC_WRLockRWLock_Callback(
    /* [in][out] */ LPCPC_RWLOCK pSection);

typedef VOID CPCAPI CPC_UnlockRWLock_Callback(
    /* [in][out] */ LPCPC_RWLOCK pSection);

typedef DWORD CPCAPI CPC_GetTimeOfDay_Callback(
    /* [out] */ CPC_timeval *pTV,
    /* [in] */ LPVOID lpArg);

typedef DWORD CPCAPI CPC_RDTSC_Callback(
    /* [out] */ ULONGLONG *pTSC,
    /* [in] */ LPVOID lpArg);

typedef DWORD CPCAPI CPC_RandomGenerate_Callback(
    /* [in] */ LPVOID lpCtx,
    /* [in] */ DWORD length,
    /* [out] */ PBYTE data);

typedef VOID CPCAPI CPC_RandomCleanup_Callback(
    /* [in] */ LPVOID lpCtx);

typedef LONG CPCAPI CPC_InterlockedExchangeAdd_Callback(
    /* [in][out] */ LONG volatile * dest, 
    /* [in] */ LONG incr);

typedef CSP_BOOL CPCAPI CPC_InterlockedCASL_Callback(
    /* [in][out] */ LONG volatile * dest,
    /* [in] */ LONG xchg,
    /* [in] */ LONG compare);

typedef CSP_BOOL CPCAPI CPC_InterlockedCASLL_Callback(
    /* [in][out] */ LONGLONG volatile * dest,
    /* [in] */ LONGLONG xchg,
    /* [in] */ LONGLONG compare);

//=============================================================================
// ��������� ���������� CPC
struct CPC_FUNCTION_TABLE_ {
	CPCAcquireContext_t	*AcquireContext;
	CPCReleaseContext_t     *ReleaseContext;
	CPCGetProvParam_t       *GetProvParam;
	CPCSetProvParam_t       *SetProvParam;
	CPCGenKey_t             *GenKey;
	CPCDestroyKey_t         *DestroyKey;
	CPCCreateHash_t         *CreateHash;
	CPCDestroyHash_t        *DestroyHash;
	CPCEncrypt_t            *Encrypt;
	CPCDecrypt_t            *Decrypt;
	CPCDeriveKey_t          *DeriveKey;
	CPCDuplicateKey_t       *DuplicateKey;
	CPCDuplicateHash_t      *DuplicateHash;
	CPCExportKey_t          *ExportKey;
	CPCGenRandom_t          *GenRandom;
	CPCGetHashParam_t       *GetHashParam;
	CPCGetKeyParam_t        *GetKeyParam;
	CPCGetUserKey_t         *GetUserKey;
	CPCHashData_t           *HashData;
	CPCHashSessionKey_t     *HashSessionKey;
	CPCImportKey_t          *ImportKey;
	CPCSetHashParam_t       *SetHashParam;
	CPCSetKeyParam_t        *SetKeyParam;
	CPCSignHash_t           *SignHash;
	CPCVerifySignature_t    *VerifySignature;
	CPCDestroyProvider_t	*DestroyProvider;
};

#define CPC_FUNCTION_TABLE_CHECK( p ) ( p && \
    (p)->AcquireContext && \
    (p)->ReleaseContext && \
    (p)->GetProvParam && \
    (p)->SetProvParam && \
    (p)->GenKey && \
    (p)->DestroyKey && \
    (p)->CreateHash && \
    (p)->DestroyHash && \
    (p)->Encrypt && \
    (p)->Decrypt && \
    (p)->DeriveKey && \
    (p)->DuplicateKey && \
    (p)->DuplicateHash && \
    (p)->ExportKey && \
    (p)->GenRandom && \
    (p)->GetHashParam && \
    (p)->GetKeyParam && \
    (p)->GetUserKey && \
    (p)->HashData && \
    (p)->HashSessionKey && \
    (p)->ImportKey && \
    (p)->SetHashParam && \
    (p)->SetKeyParam && \
    (p)->SignHash && \
    (p)->VerifySignature && \
    (p)->DestroyProvider \
)

typedef struct CPC_LOG_CONFIG_ {
  const TCHAR *name;
  unsigned level;
  unsigned format;
  CPC_print_str_Callback *dprint_str;
  CPC_print_str_Callback *eprint_str;
  CPC_print_str_Callback *cprint_str;
  CPC_print_str_Callback *elprint_str;
  CPC_get_thread_id_Callback *get_thread_id;
  LPVOID lpArg;
} CPC_LOG_CONFIG;

typedef struct CPC_HARDWARE_RNG_ {
  CPC_RandomGenerate_Callback *random_generate;
  CPC_RandomCleanup_Callback *random_cleanup;
  LPVOID lpCtx;
} CPC_HARDWARE_RNG;

typedef struct CPC_LOCK_FUNCS_ {
  CPC_InitRWLock_Callback * rwlock_init;
  CPC_DestroyRWLock_Callback * rwlock_destroy;
  CPC_RDLockRWLock_Callback * rwlock_rdlock;
  CPC_WRLockRWLock_Callback * rwlock_wrlock;
  CPC_UnlockRWLock_Callback * rwlock_unlock;
  LPVOID lpArg;
} CPC_LOCK_FUNCS, *LPCPC_LOCK_FUNCS;

typedef struct CPC_TIME_FUNCS_ {
  CPC_GetTimeOfDay_Callback * get_time_of_day;
  CPC_RDTSC_Callback * read_tsc;
  LPVOID lpArg;
} CPC_TIME_FUNCS, *LPCPC_TIME_FUNCS;

typedef struct CPC_ALG_PARAMS_ {
  CHAR szOID_Hash [64];
  CHAR szOID_Cipher [64];
  CHAR szOID_Sign512_2012[64];
  CHAR szOID_DH512_2012[64];
  CHAR szOID_Sign_2001 [64];
  CHAR szOID_DH_2001 [64];
  CSP_BOOL fNoTables;
} CPC_ALG_PARAMS, *LPCPC_ALG_PARAMS;

typedef struct CPC_INTERLOCKED_FUNCS_ {
  CPC_InterlockedExchangeAdd_Callback * interlocked_exchange_add;
  CPC_InterlockedCASL_Callback * interlocked_casl;
  CPC_InterlockedCASLL_Callback * interlocked_casll;
} CPC_INTERLOCKED_FUNCS, *LPCPC_INTERLOCKED_FUNCS;

struct _timeval {
    long tv_sec;
    long tv_usec;
};

struct CPC_RWLOCK_ {
  LONGLONG dummy[2*16];
#if defined(TRACK_LOCKS_USAGE)
  // string literals have static storage duration so this pointer is always valid
  const char *location;
#endif /*defined(TRACK_LOCKS_USAGE)*/
};

struct CPC_CONFIG_ {
  DWORD	cbSize;
  LPCPC_MEMORY_ARENA pArena;
  CPC_FAST_CODE	FuncStruct;
  CPC_LOG_CONFIG logConfig;
  CPC_HARDWARE_RNG hardwareRNG;
  CPC_INTERLOCKED_FUNCS interlockedFuncs;
  CPC_LOCK_FUNCS lockFuncs;
  CPC_TIME_FUNCS timeFuncs;
  CPC_ALG_PARAMS algParams;
  DWORD MaxHandles;
  DWORD dwTesterPeriod;
  DWORD dwTesterTimeout;
  CSP_BOOL fNonSMP;
  const TCHAR *license;
};

struct CPC_CONFIG2_ {//::CPC_CONFIG_ ��� ������������� �� ������� ���������
    DWORD	cbSize;
    LPCPC_MEMORY_ARENA pArena;
    CPC_FAST_CODE	FuncStruct;
    CPC_LOG_CONFIG logConfig;
    CPC_HARDWARE_RNG hardwareRNG;
    CPC_INTERLOCKED_FUNCS interlockedFuncs;
    CPC_LOCK_FUNCS lockFuncs;
    CPC_TIME_FUNCS timeFuncs;
    CPC_ALG_PARAMS algParams;
    DWORD MaxHandles;
    DWORD dwTesterPeriod;
    DWORD dwTesterTimeout;
    CSP_BOOL fNonSMP;  
    const TCHAR *license;   
    CSP_BOOL disableIntegrity;  // ��� ���� ���������� � CSP 3.6 R3
    HCRYPTMODULE hGOSTCSP;  // ��� RSA-���������� �� HSM
    CSP_BOOL disableShortcutsUnused; // ���������� ������������� ���������� � ������� ��������� - ����� CSP 4.0 �� ������������.
};


#if !defined(CSP_LITE) || defined(LINUX) || defined(SOLARIS)
	// ��� ������������� ���������, � ��� �� � Linux � Solaris
	// ������� �������� �����.
#elif defined(FREEBSD)
    // ?????
    #define CPC_SEPARATE_NAMESPACE_BINDING 1
#elif !defined(UNIX)
    // #include "cpdrvlib.h"
    // IOCTL_GETCPCCREATEPROVIDER
    // IOCTL_GETCPCGETDEFAULTCONFIG
    #define CPC_SEPARATE_NAMESPACE_BINDING 1
#endif

#if !defined(CPC_SEPARATE_NAMESPACE_BINDING)
    CPCCreateProvider_t		CPCCreateProvider;
    CPCGetDefaultConfig_t	CPCGetDefaultConfig;
#endif

#if defined(__cplusplus)
} // extern "C"
#endif // defined(__cplusplus)

#define ACQUIRE_CONTEXT_ADD_INFO_CARRIER_IDENTIFIER  ((DWORD)0x4321)

/*��������� ������������ ��� �������� �������������� ������� �� �������� ���������.
 ���������� ������������� ����� �������� � ��������� ��������� ����������.
*/
typedef struct ACQUIRECONTEXTADDINFO_ {
    DWORD dwType;
    BYTE pbSessionIdentifier[CARRIER_CLIENT_IDENTIFIER_SIZE];
    DWORD cbAdditionalData;
    BYTE* pbAdditionalData;
} ACQUIRECONTEXTADDINFO, *PACQUIRECONTEXTADDINFO;

#endif /* _WINCSPC_H_INCLUDED */
