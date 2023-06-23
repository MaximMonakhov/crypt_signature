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
 * \version $Revision: 148173 $
 * \date $Date:: 2016-11-07 00:01:43 +0400#$
 * \author $Author: raa $
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

#define CMPMEMORY_TRUE 0xda61e537
#if !defined( CmpMemory )
extern int CmpMemory (LPCVOID pMemAddr1, LPCVOID pMemAddr2, DWORD dwCount);
#endif /* !defined( CmpMemory ) */

#ifdef __cplusplus
}
#endif

#endif /* _CMPMEM_H_INCLUDED */
