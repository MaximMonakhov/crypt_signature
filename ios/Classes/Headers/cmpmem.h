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
 * \version $Revision: 210843 $
 * \date $Date:: 2020-04-29 11:24:30 +0400#$
 * \author $Author: ilias $
 *
 * \brief ������� �������� ������.
 *
 * ��������� �������� ������.
 */

#ifndef _CMPMEM_H_INCLUDED
#define _CMPMEM_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

extern int const_memcmp(const void * s1, const void * s2, size_t n);

#define CMPMEMORY_TRUE 0xda61e537
#if !defined( CmpMemory )
#include<compiler_attributes.h>
extern int CmpMemory (LPCVOID pMemAddr1, LPCVOID pMemAddr2, DWORD dwCount) ATTR_USERES;
#endif /* !defined( CmpMemory ) */

#ifdef __cplusplus
}
#endif

#endif /* _CMPMEM_H_INCLUDED */
