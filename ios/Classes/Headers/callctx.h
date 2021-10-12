#ifndef CALLCTX_H_INCLUDED
#define CALLCTX_H_INCLUDED 1

#include<BaseArithmDef_64.h>
#include<compiler_attributes.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct _CP_CALL_CTX_ CP_CALL_CTX, *pCP_CALL_CTX;
typedef struct _CRYPT_CSP_ CRYPT_CSP, * LPCRYPT_CSP;

typedef struct _CRYPT_CSP_THREAD_		CRYPT_CSP_THREAD,		*LPCRYPT_CSP_THREAD;
typedef struct _CSP_THREAD_TEMP_DATA		CSP_THREAD_TEMP_DATA,		*LPCSP_THREAD_TEMP_DATA;
typedef struct _CSP_THREAD_TEMP_CIPHER_DATA	CSP_THREAD_TEMP_CIPHER_DATA,	*LPCSP_THREAD_TEMP_CIPHER_DATA;
typedef struct _CSP_THREAD_TEMP_HASH_DATA	CSP_THREAD_TEMP_HASH_DATA,	*LPCSP_THREAD_TEMP_HASH_DATA;
typedef struct _CSP_THREAD_TEMP_PRSG_DATA	CSP_THREAD_TEMP_PRSG_DATA,	*LPCSP_THREAD_TEMP_PRSG_DATA;
typedef struct _CSP_THREAD_VTB_MP		CSP_THREAD_VTB_MP,		*LPCSP_THREAD_VTB_MP;

typedef struct _CP_ASTACK_ CP_ASTACK;



/* ��������������� ��������� ���. */
struct RND_CONTEXT_;

/*! \internal
* \brief ��������� �� ������� ��������� ��������� �����.
*
* \param context [in/out] �������� ���, ������� ���������� ��������� �� �����
*  ������ ��������� ���������.
* \param buffer [out] �����, �� ������ ����������� ��������� �������������������.
* \param length [in] ������ ������ ��� ��������� ������������������.
* \return TRUE, ��������� ������������������ ��������, FALSE �����.
*/
typedef CSP_BOOL(*GetRandomFunction)(pCP_CALL_CTX pCallCtx, struct RND_CONTEXT_ *context, LPBYTE buffer, uint32_t length, uint32_t flags);


/*! \internal
* \brief ��������� �� ������� �������� �������������������� ���.
*
* \param context [in/out] �������� ���, ������� ���������� ��������� �� �����
*  ������ ��������� ���������.
* \return TRUE, ��������� ������������������ ����� ���� �������� (��� ���������������),
*  FALSE �����.
*/
typedef CSP_BOOL(*IsRandomInitedFunction)(struct RND_CONTEXT_ *context);

/*! \internal
* \brief ��������� �� ������� ��������� ��������� ���.
*
* \param context [in/out] �������� ���, ������� ���������� ��������� �� �����
*  ������ ��������� ���������.
* \param seed [out] ���������������� ������������������.
*/
typedef CSP_BOOL(*GetRandomSeedFunction)(struct RND_CONTEXT_ *context, LPBYTE seed, size_t length);

/*! \internal
* \brief ��������� �� ������� ��������� ���������������� ������������������.
*
* \param context [in/out] �������� ���, ������� ���������� ��������� �� �����
*  ������ ��������� ���������.
* \param seed [in] ���������������� ������������������.
*/
typedef CSP_BOOL(*SetRandomSeedFunction)(pCP_CALL_CTX pCallCtx, struct RND_CONTEXT_ *context, const LPBYTE seed, size_t length);
/*! \internal
* \brief ������� ������������� ��������� �� �������� ���������,
*  � ��������� � �������������� ������� CPSetProvParam(), PP_RANDOM.
*/
#define RND_INITED 0x00000001


/*! \internal
* \brief �������� ������� ��������� ��������� ������������������.
*/
typedef struct RND_CONTEXT_ {
    GetRandomFunction make_random; /*!< ��������� �� ������� ��������� ���������� �����. */
    IsRandomInitedFunction is_inited; /*!< ��������� �� ������� �������� �������������������� ���. */
    GetRandomSeedFunction get_random_seed; /*!< ��������� �� ������� ��������� random seed. */
    SetRandomSeedFunction set_random_seed; /*!< ��������� �� ������� ��������� random_seed. */
    DWORD Flags;			    /*!< ���� ��������� ���������.*/
} RND_CONTEXT, *LPRND_CONTEXT;

/* ��������������� �������� CSP_SetLastError/CSP_GetLastError */
void	rCSP_SetLastError	(pCP_CALL_CTX pCallCtx, DWORD err);
DWORD	rCSP_GetLastError	(pCP_CALL_CTX pCallCtx) ATTR_USERES;

#ifdef USE_STATIC_ANALYZER
#define rAllocMemory(pCallCtx,dwSize,dwMemPoolId) (pCallCtx, dwMemPoolId,calloc(dwSize, 1))
#define rFreeMemory(pCallCtx,pMem,dwMemPoolId)  (pCallCtx, dwMemPoolId,free(pMem))
#else
/* ��������������� �������� AllocMemory/FreeMemory */
LPVOID	rAllocMemory	(pCP_CALL_CTX pCallCtx, size_t dwSize, DWORD dwMemPoolId) ATTR_USERES;
void	rFreeMemory	(pCP_CALL_CTX pCallCtx, VOID *pMem, DWORD dwMemPoolId);
#endif

/*! ������������� ������ */
CSP_BOOL	rInitMemory	(pCP_CALL_CTX pCallCtx) ATTR_USERES;

#if !defined UNIX
/*! ����������� ���� ��� */
void	rDoneMemory	(pCP_CALL_CTX pCallCtx);
#endif /* !UNIX */
/*! �������� ����������� ��� */
void	rValidateMemory	(pCP_CALL_CTX pCallCtx);

void	rInitCallCtx	(pCP_CALL_CTX pCallCtx, LPCRYPT_CSP hCSP);


struct _CP_CALL_CTX_
{
    LPCRYPT_CSP			hCSP;
    LPCRYPT_CSP_THREAD		hCSPthread; // ��������, ��� ������ ��� ���������� � ��������� hCSP ����� hCSPthread
    LPRND_CONTEXT		ThreadPRSG; // ����� ����� ���� ��������� ��� � ������� MakeRandom
    DWORD			dwError;
    DWORD			dwThreadId;
    DWORD			dwCommonKArrayLength;
    BYTE                       *pbCommonKArray; 
    CSP_BOOL			bOwnFPU;
    int				iCntFPU;
    DWORD			dwFPUOpType;
	// ASSERT - ����� �������� �� FPUAllignValue
    struct cp_vtb_28147_89     *pVTB;
    CP_ASTACK	       *pAStk;
};


#ifdef __cplusplus
}
#endif

#endif /* CALLCTX_H_INCLUDED */
