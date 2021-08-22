/*
 * Copyright(C) 2000-2007 ������ ���
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
 * \version $Revision: 197576 $
 * \date $Date:: 2019-08-13 17:00:32 +0400#$
 * \author $Author: dim $
 *
 * \brief ������ �������, �������������� ��������� � ��. �������� ���������.
 */
#ifndef _PLATFORMSTREAM_H
#define _PLATFORMSTREAM_H

#ifdef UNIX
# ifdef CSP_LITE 
#  if !defined htonl && !defined htons
#   ifdef WORDS_BIGENDIAN
#     define htonl(a) (a)
#     define htons(a) (a)
#     define ntohl(a) (a)
#     define ntohs(a) (a)
#   else /* WORDS_BIGENDIAN */
#     define htons(x) \
     ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8))
#     define htonl(x) \
     ((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >>  8) |               \
      (((x) & 0x0000ff00) <<  8) | (((x) & 0x000000ff) << 24))
#     define ntohs(x) htons(x)
#     define ntohl(x) htonl(x)
#   endif /* WORDS_BIGENDIAN */
#  endif
# else /* CSP_LITE */
#   include <netinet/in.h>
# endif /* CSP_LITE */
#endif /* UNIX */

#ifdef __cplusplus
extern "C" {
#endif

#include<BaseArithmDef_64.h>

// ================================================================================================
// ������� htolel_dwbuf(), qwtodw_buf(), dwtoqw_buf(), htoleq_qwbuf(), letohq_qwbuf(), letohl_ref() 
// ������ ���� ������������ ���� � �����������, ���� � ����������������� �������� 
// ================================================================================================

#if !defined(__inline) && !defined(_WIN32)
#   define __inline     inline
#endif // !defined(__inline) && !defined(_WIN32)

#ifdef _WIN32
#define htons fast_htons
#define ntohs htons
#define htonl fast_htonl
#define ntohl htonl

#ifdef _M_IX86

__inline unsigned short
fast_htons (unsigned short hostshort)
{
unsigned short retax = hostshort;
__asm {
		ror retax, 8
	}
return retax;
}

__inline unsigned long
fast_htonl (unsigned long hostlong)
{
    unsigned long reteax=hostlong;
	__asm {
		mov eax, reteax
		bswap eax
		/*ror ax, 8
		ror eax, 16
		ror ax, 8*/
		mov reteax, eax
	}
    return reteax;
}

#else /* ! _M_IX86 */

__inline unsigned short
fast_htons (unsigned short hostshort)
{
    return ( hostshort << 8 ) | ( hostshort >> 8 );
}
__inline unsigned long
fast_htonl (unsigned long hostlong)
{
    return ( hostlong >> 24 ) 
	| ( ( hostlong >> 8 ) & 0xff00 )
	| ( hostlong << 8 ) & 0xff0000
	| ( hostlong << 24 );
}
#endif /* _M_IX86 */
#endif /*_WIN32*/

#define bswapl(A) \
    ((((DWORD)(A) & 0xff000000) >> 24) | \
    (((DWORD)(A) & 0x00ff0000) >> 8) | \
    (((DWORD)(A) & 0x0000ff00) << 8) | \
    (((DWORD)(A) & 0x000000ff) << 24))

#define bytes_rotate(ptr, length) \
{ \
    DWORD bytes_rotate_idx; \
    for (bytes_rotate_idx = 0; bytes_rotate_idx < length / 2; bytes_rotate_idx++) { \
        BYTE swap_tmp = ((BYTE*)ptr)[bytes_rotate_idx]; \
        ((BYTE*)ptr)[bytes_rotate_idx] = ((BYTE*)ptr)[length - 1 - bytes_rotate_idx]; \
        ((BYTE*)ptr)[length - 1 - bytes_rotate_idx] = swap_tmp; \
    }\
}

static __inline
uint32_t
letohl_loc (const unsigned char * pcn)
{
    uint32_t tc = 0;
    tc = (uint32_t)(*(pcn));
    tc ^= ((uint32_t)(*(pcn+1))) << 8;
    tc ^= ((uint32_t)(*(pcn+2))) << 16;
    tc ^= ((uint32_t)(*(pcn+3))) << 24;
    return tc;
}

static __inline
void
htolelxor (unsigned char * pcn, DWORD hostlong)
{
    *(pcn) ^= (unsigned char)(hostlong & (uint32_t)0xff);
    hostlong >>= 8;
    *(pcn+1) ^= (unsigned char)(hostlong & (uint32_t)0xff);
    hostlong >>= 8;
    *(pcn+2) ^= (unsigned char)(hostlong & (uint32_t)0xff);
    hostlong >>= 8;
    *(pcn+3) ^= (unsigned char)(hostlong & (uint32_t)0xff);
}

static __inline
void letohqxor(uint64_t *dest, const uint8_t *src)
{
    uint64_t tmp = 0;
    unsigned i;
    for (i = 0; i != sizeof(tmp); ++i) {
        tmp |= ((uint64_t) src[i]) << (8 * i);
    }
    *dest ^= tmp;
}

static __inline
void letohs_ref(void *pch, const void * pcn)
{
#if defined (WORDS_BIGENDIAN)
    BYTE           t = ((BYTE *)pcn)[0];
    ((BYTE *)pch)[0] = ((BYTE *)pcn)[1];
    ((BYTE *)pch)[1] = t;
#else
    ((BYTE *)pch)[0] = ((BYTE *)pcn)[0];
    ((BYTE *)pch)[1] = ((BYTE *)pcn)[1];
#endif
}

static __inline
void htoles_ref(void * pcn, const void *pch)
{
#if defined (WORDS_BIGENDIAN)
    BYTE           t = ((BYTE *)pch)[0];
    ((BYTE *)pcn)[0] = ((BYTE *)pch)[1];
    ((BYTE *)pcn)[1] = t;
#else
    ((BYTE *)pcn)[0] = ((BYTE *)pch)[0];
    ((BYTE *)pcn)[1] = ((BYTE *)pch)[1];
#endif
}

static __inline
void letohl_ref(void *pch, const void * pcn)
{
#if defined (WORDS_BIGENDIAN)
    BYTE           t = ((BYTE *)pcn)[0];
    ((BYTE *)pch)[0] = ((BYTE *)pcn)[3];
    ((BYTE *)pch)[3] = t;
                   t = ((BYTE *)pcn)[2];
    ((BYTE *)pch)[2] = ((BYTE *)pcn)[1];
    ((BYTE *)pch)[1] = t;
#else
/*    *(DWORD *)pch = *(DWORD *)pcn; */
/* ���� ������ ������� ������� aligned, �� �������������� ���������� ��� ������� '�������� mov'
 * ���� �� aligned, �� ����� ��������� ������ �� ������ �����?
 */
    if(pch!=pcn) /* made valgrind happy */ /* dim: ��� �� � V, � � ���� */
	memcpy(pch, pcn, sizeof(uint32_t));
#endif
}

static __inline
void htolel_ref(void *pcn, const void *pch)
{
#if defined (WORDS_BIGENDIAN)
    BYTE           t = ((BYTE *)pch)[0];
    ((BYTE *)pcn)[0] = ((BYTE *)pch)[3];
    ((BYTE *)pcn)[3] = t;
                   t = ((BYTE *)pch)[2];
    ((BYTE *)pcn)[2] = ((BYTE *)pch)[1];
    ((BYTE *)pcn)[1] = t;
#else
/*    *(DWORD *)pcn = *(DWORD *)pch; */
/* ���� ������ ������� ������� aligned, �� �������������� ���������� ��� ������� '�������� mov'
 * ���� �� aligned, �� ����� ��������� ������ �� ������ �����?
 */
    if (pcn != pch) /* ������ �� ������ ������������ */
	memcpy(pcn, pch, sizeof(uint32_t));
#endif
}

static __inline
void betohl_ref(void *pch, const void * pcn)
{
#if !defined (WORDS_BIGENDIAN)
    BYTE           t = ((BYTE *)pcn)[0];
    ((BYTE *)pch)[0] = ((BYTE *)pcn)[3];
    ((BYTE *)pch)[3] = t;
    t = ((BYTE *)pcn)[2];
    ((BYTE *)pch)[2] = ((BYTE *)pcn)[1];
    ((BYTE *)pch)[1] = t;
#else
    /*    *(DWORD *)pch = *(DWORD *)pcn; */
    /* ���� ������ ������� ������� aligned, �� �������������� ���������� ��� ������� '�������� mov'
    * ���� �� aligned, �� ����� ��������� ������ �� ������ �����?
    */
    if (pch != pcn) /* made valgrind happy */ /* dim: ��� �� � V, � � ���� */
	memcpy(pch, pcn, sizeof(uint32_t));
#endif
}

static __inline
void htobel_ref(void *pcn, const void *pch)
{
#if !defined (WORDS_BIGENDIAN)
    BYTE           t = ((BYTE *)pch)[0];
    ((BYTE *)pcn)[0] = ((BYTE *)pch)[3];
    ((BYTE *)pcn)[3] = t;
    t = ((BYTE *)pch)[2];
    ((BYTE *)pcn)[2] = ((BYTE *)pch)[1];
    ((BYTE *)pcn)[1] = t;
#else
    /*    *(DWORD *)pcn = *(DWORD *)pch; */
    /* ���� ������ ������� ������� aligned, �� �������������� ���������� ��� ������� '�������� mov'
    * ���� �� aligned, �� ����� ��������� ������ �� ������ �����?
    */
    if (pcn != pch) /* ������ �� ������ ������������ */
	memcpy(pcn, pch, sizeof(uint32_t));
#endif
}

static __inline
uint32_t letohl_ptr(const void * pcn)
{
    uint32_t hdw;
    letohl_ref(&hdw, pcn);
    return hdw;
}

static __inline
uint32_t betohl_ptr(const void * pcn)
{
    uint32_t hdw;
    betohl_ref(&hdw, pcn);
    return hdw;
}

static __inline
void htolel_ptr(void *pcn, uint32_t hdw)
{
    htolel_ref(pcn, &hdw);
}

static __inline
void htobel_ptr(void *pcn, uint32_t hdw)
{
    htobel_ref(pcn, &hdw);
}

static __inline
void betohq_ref(void *pch, const void * pcn)
{
#if !defined (WORDS_BIGENDIAN)
    BYTE           t = ((BYTE *)pcn)[0];
    ((BYTE *)pch)[0] = ((BYTE *)pcn)[7];
    ((BYTE *)pch)[7] = t;
    t = ((BYTE *)pcn)[6];
    ((BYTE *)pch)[6] = ((BYTE *)pcn)[1];
    ((BYTE *)pch)[1] = t;
    t = ((BYTE *)pcn)[5];
    ((BYTE *)pch)[5] = ((BYTE *)pcn)[2];
    ((BYTE *)pch)[2] = t;
    t = ((BYTE *)pcn)[4];
    ((BYTE *)pch)[4] = ((BYTE *)pcn)[3];
    ((BYTE *)pch)[3] = t;
#else
    /*    *(uint64_t *)pch = *(uint64_t *)pcn; */
    /* ���� ������ ������� ������� aligned, �� �������������� ���������� ��� ������� '�������� mov'
    * ���� �� aligned, �� ����� ��������� ������ �� ������ �����?
    */
    if (pch != pcn) /* made valgrind happy */ /* dim: ��� �� � V, � � ���� */
	memcpy(pch, pcn, sizeof(uint64_t));
#endif
}

static __inline
uint64_t betohq_ptr(const void * pcn)
{
    uint64_t hqw;
    betohq_ref(&hqw, pcn);
    return hqw;
}

static __inline
void htobeq_ptr(unsigned char *pcn, uint64_t hqw)
{
    betohq_ref(pcn, &hqw);
}

static __inline
void    dw_set(void *pdwdst, uint32_t dwsrc) {
    *(uint32_t *)pdwdst = dwsrc;
}

static __inline
uint32_t   dw_ptr(const void *pdwsrc) {
    return *(uint32_t *)pdwsrc;
}

static __inline
void
htolel_XOR(unsigned char * pcn, uint32_t ln)
{
#ifdef WORDS_BIGENDIAN
    htolelxor(pcn, ln);
#else
    {
	DWORD dwln=ln;
	((BYTE *)pcn)[0] ^= ((BYTE *)&dwln)[0];
	((BYTE *)pcn)[1] ^= ((BYTE *)&dwln)[1];
	((BYTE *)pcn)[2] ^= ((BYTE *)&dwln)[2];
	((BYTE *)pcn)[3] ^= ((BYTE *)&dwln)[3];
    }
#endif
}
 
/*! \defgroup grpLittlEndian2Host ������������ ��������� �������������� ������ 
 * �������������� ������ � � �� Littl� Endian ������������� ������. 
 * ����������������� �������������� ���������� ������ 
 * Littl� Endian ������������� ������. 
 */

/* Needed: dwDWBufLen * sizeof(DWORD) >= dwByteLen*/
/*! \internal 
 * \ingroup grpLittlEndian2Host
 * \brief ������� ����������� ����� � ����� �� ������ Littl� Endian. 
 * ��������� �� ��������� ����������� ���� �� �����.
 * \param pdwBuff [out] ��������� �� ������ ������. 
 * \param pcv [in] ��������� �� �����.
 * \param dwDWBufLen [in] ����� ������ � ������� ������. 
 * \param dwByteLen [in] ����� ������ � ������.
 * Needed: dwDWBufLen * sizeof(DWORD) >= dwByteLen.
 */
static __inline
void
letohl_dwbuf(uint32_t *pdwBuff, const void *pcv, uint32_t dwDWBufLen, uint32_t dwByteLen)
{
    int i=0, j
	,nRest = (int)dwByteLen % (int)sizeof(uint32_t)
	,nFullDW = (int)dwByteLen / (int)sizeof(uint32_t);
    const LPBYTE pcn=(LPBYTE)pcv;
    if(nFullDW) {
	for(i=0;i<nFullDW;i++) {
	    letohl_ref(pdwBuff + i, pcn + i*sizeof(uint32_t));
	}
    }
    if(nRest) {
	uint32_t dw = 0;
	for(j=nRest-1;j>=0;j--){
	    dw <<= 8;
	    dw ^= (uint32_t)(*(pcn+ i*sizeof(uint32_t)+j));
	}
        dw_set(pdwBuff + i, dw);
	i++;
    }
    if(dwDWBufLen - nFullDW) 
	for(;i<(int)dwDWBufLen;i++) dw_set(pdwBuff + i, 0);
}

/*! \internal 
 * \ingroup grpLittlEndian2Host
 * \brief ������� ����������� ����� � ����� �� ������ Littl� Endian. 
 * \param pdwBuff [out] ��������� �� ������ ������. 
 * \param pcn [in] ��������� �� �����.
 * \param dwDWBufLen [in] ����� ������ � ������� ������. 
 */
static __inline
void
letohl_dwbuf3(uint32_t *pdwBuff, const BYTE *pcn, uint32_t dwDWBufLen)
{
    unsigned i;
    for(i=0; i<dwDWBufLen; i++) {
	letohl_ref(pdwBuff + i, pcn + i*sizeof(uint32_t));
    }
}

/* Needed: dwDWBufLen * sizeof(DWORD) = dwByteFull + dwByteLen
 * ��������� �� ��������� ����������� ���� �� �����.
 * 
 * pdwBuff- ��������� �� ����������� �����.
 * pcn - ������� �������� �����.
 * dwByteFull - ����� ����������� ������.
 * dwDWBufLen - ����� ������ pdwBuff � DWORD.
 * dwByteLen - ����� ����������� ������ � ������ pcn, 
 * �.�. dwDWBufLen * sizeof(DWORD) = dwByteFull + dwByteLen.
*/
/*! \internal 
 * \ingroup grpLittlEndian2Host
 * \brief ������� ��������� �� ��������� ����������� 
 * ���� �� ����� �� ������ Littl� Endian. 
 *
 * \param pdwBuff [in] ��������� �� ������ ������. 
 * \param pcn [in] ��������� �� ������� �������� �����.
 * \param dwDWBufLen [in] ����� ������ � ������� ������. 
 * \param dwByteLen [in] ����� ����������� ������ � ������ pcn.
 * Needed: dwDWBufLen * sizeof(DWORD) = dwByteFull + dwByteLen.
 * \return TRUE ��� �������� ����������, FALSE � ��������� ������.
 */
static __inline
CSP_BOOL
letohl_compldwbuf(uint32_t * pdwBuff, const unsigned char * pcn
	    , uint32_t dwDWBufLen, uint32_t dwByteFull, uint32_t dwByteLen)
{
    int i, j
    	,nCompl = (int)dwByteLen % (int)sizeof(uint32_t)
	,nFullDW = (int)dwByteFull / (int)sizeof(uint32_t);
    uint32_t Temp = 0;
    if((dwDWBufLen*sizeof(uint32_t)) != (dwByteFull+dwByteLen))
	return FALSE;
    if(nCompl) {
	for(j=nCompl-1;j>=0;j--){
	    Temp <<= 8;
	    Temp ^= (uint32_t)(*(pcn +j));
	}
	Temp <<= (8*(sizeof(uint32_t)-nCompl));
	pdwBuff[nFullDW] ^= Temp;   /* ?????? */
	nFullDW++;
	pcn+=nCompl;
    }
    if(nFullDW < (int)dwDWBufLen) {
	for(i=nFullDW,j=0;i<(int)dwDWBufLen;i++,j++) {
	    letohl_ref(pdwBuff + i, pcn + j*sizeof(uint32_t));
	}
    }
    return TRUE;
}

#if !defined WORDS_BIGENDIAN
/*! \internal
 * \ingroup grpLittlEndian2Host
 * \brief ������� �������������  ����� � �����. 
 * \param pcn [out] ��������� �� �����.
 * \param pdwBuff [in] ��������� �� ������ ������. 
 * \param dwDWBufLen [in] ����� ������ � ������� ������. 
 */
static __inline
void
htolel_dwbuf(void *pcn, const void *pdwBuff, uint32_t dwDWBufLen)
{
    if(pcn!=pdwBuff)		/* made valgrind happy */
	memcpy(pcn, pdwBuff, sizeof(uint32_t)*dwDWBufLen);
}

static __inline
CSP_BOOL
qwtodw_buf(uint64_t *pcq, const uint32_t *pdwBuff, DWORD dwLen)
{
    if ( dwLen%2 )
	return FALSE;
    if((void*)pcq!=(void*)pdwBuff)		/* made valgrind happy */
	memcpy ( pcq, pdwBuff, sizeof(uint32_t)*dwLen );
    return TRUE;
}

static __inline
void
dwtoqw_buf(uint32_t* pcd, const uint64_t *pqwBuff, uint32_t qwLen)
{
    if(pcd!=(void*)pqwBuff)		/* made valgrind happy */
	memcpy ( pcd, pqwBuff, sizeof(uint64_t)*qwLen );
}

static __inline
void
htoleq_qwbuf(unsigned char *pcn, const uint64_t *pqwBuff, uint32_t qwBufLen)
{
    if((void*)pcn!=(void*)pqwBuff) /* made valgrind happy */
	memcpy ( pcn, pqwBuff, sizeof(uint64_t)*qwBufLen);
}

static __inline
CSP_BOOL
letohq_qwbuf(uint64_t *pqwBuff, const unsigned char *pcn, uint32_t dwByteLen)
{
    if ( dwByteLen%8 )
	return FALSE;

    if((void*)pcn!=(void*)pqwBuff) /* made valgrind happy */
	memcpy ( pqwBuff, pcn, dwByteLen);
    return TRUE;
}
#else /*WORDS_BIGENDIAN*/
static __inline
void
htolel_dwbuf(void *pcn, const void *pdwBuff, uint32_t dwDWBufLen)
{
    uint32_t i;
    for(i=0; i<dwDWBufLen; i++) {
      htolel_ref((char*)pcn + i*sizeof(uint32_t), (char*)pdwBuff + i*sizeof(uint32_t));
    }
}

static __inline
CSP_BOOL
qwtodw_buf(uint64_t *pcq, const uint32_t *pdwBuff, uint32_t dwLen)
{
    if (dwLen % 2)
	return FALSE;

    for (; dwLen; dwLen -= 2)
    {
	uint32_t d[2];
	d[1] = *pdwBuff++;
	d[0] = *pdwBuff++;
	memcpy(pcq++, d, sizeof(uint64_t));
    }
    return TRUE;
}

static __inline
void
dwtoqw_buf(uint32_t* pcd, const uint64_t *pqwBuff, uint32_t qwLen)
{
    for (; qwLen; qwLen--) {
	uint32_t d[2];
	memcpy(d, pqwBuff++, sizeof(uint64_t));
	*pcd++ = d[1];
	*pcd++ = d[0];
    }
}

static __inline
void
htoleq_qwbuf(unsigned char *pcn, const uint64_t *pqwBuff, uint32_t qwBufLen)
{
    for ( ; qwBufLen; qwBufLen-- ) {
	union {
	    uint64_t q;
	    BYTE b[8];
	} t;
	t.q = *pqwBuff++;
	*pcn++ = t.b[7];
	*pcn++ = t.b[6];
	*pcn++ = t.b[5];
	*pcn++ = t.b[4];
	*pcn++ = t.b[3];
	*pcn++ = t.b[2];
	*pcn++ = t.b[1];
	*pcn++ = t.b[0];
    }
}

static __inline
CSP_BOOL
letohq_qwbuf(uint64_t *pqwBuff, const unsigned char *pcn, uint32_t dwByteLen)
{
    uint32_t QW_len = dwByteLen/sizeof(uint64_t);

    if ( dwByteLen%8 )
	return FALSE;
    for ( ; QW_len; QW_len-- ) {
	union {
	    uint64_t q;
	    BYTE b[8];
	} t;
	t.b[7] = *pcn++;
	t.b[6] = *pcn++;
	t.b[5] = *pcn++;
	t.b[4] = *pcn++;
	t.b[3] = *pcn++;
	t.b[2] = *pcn++;
	t.b[1] = *pcn++;
	t.b[0] = *pcn++;
	*pqwBuff++ = t.q;
    }
    return TRUE;
}
#endif /* !WORDS_BIGENDIAN */

#ifdef __cplusplus
}
#endif

#endif /* _PLATFORMSTREAM_H */
