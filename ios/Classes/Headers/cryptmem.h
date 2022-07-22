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

/*!
 * \file $RCSfile$
 * \version $Revision: 187153 $
 * \date $Date:: 2019-01-11 04:56:17 -0800#$
 * \author $Author: maxdm $
 *
 * \brief Интерфейс модуля выделения памяти.
 */

#ifndef _CRYPTMEM_H_INCLUDED
#define _CRYPTMEM_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

LPVOID SSPAPAllocMemory (ULONG dwSize);
LPVOID SSPAPAllocZeroMemory(ULONG dwSize);
CSP_BOOL   SSPAPFreeMemory (VOID *pMem);

LPVOID CPSUPAllocMemory (size_t dwSize);
LPVOID CPSUPAllocZeroMemory(size_t dwSize);
CSP_BOOL   CPSUPFreeMemory (VOID *pMem);

CSP_BOOL CPSUPInitMemory (void);
void CPSUPDoneMemory (void);

#ifdef _CP_SSP_AP_
#   define AllocMemory	    SSPAPAllocMemory
#   define AllocZeroMemory  SSPAPAllocZeroMemory
#   define FreeMemory	    SSPAPFreeMemory
#else
#   define AllocMemory CPSUPAllocMemory
#   define AllocZeroMemory CPSUPAllocZeroMemory
#   define FreeMemory  CPSUPFreeMemory
#endif

#define InitMemory CPSUPInitMemory
#define DoneMemory CPSUPDoneMemory

#ifdef __cplusplus
}
#endif

#endif /* _CRYPTMEM_H_INCLUDED */
/* end of file: $Id: cryptmem.h 187153 2019-01-11 12:56:17Z maxdm $ */
