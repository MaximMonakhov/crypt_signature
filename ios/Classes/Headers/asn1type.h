/*
 * Copyright (C) 1997-2003 by Objective Systems, Inc.
 *
 * This software is furnished under a license and may be used and copied
 * only in accordance with the terms of such license and with the
 * inclusion of the above copyright notice. This software or any other
 * copies thereof may not be provided or otherwise made available to any
 * other person. No title to and ownership of the software is hereby
 * transferred.
 *
 * The information in this software is subject to change without notice
 * and should not be construed as a commitment by Objective Systems, Inc.
 *
 * PROPRIETARY NOTICE
 *
 * This software is an unpublished work subject to a confidentiality agreement
 * and is protected by copyright and trade secret law.  Unauthorized copying,
 * redistribution or other use of this work is prohibited.
 *
 * The above notice of copyright on this source code product does not indicate
 * any actual or intended publication of such source code.
 *
 *****************************************************************************/
/*
// CHANGE LOG
// Date         Init    Description
// 04/24/02     ED      Added ASN_E_INVCHAR & ASN_E_XMLSTATE error codes
// 04/24/02     ED      Move XD_ macros to asn1intl.h
// 04/24/02     ED      Remove #include of asn1intl.h
// 05/03/02     AB      Remove all BER-related prototypes
// 05/06/02     AB      More only-BER things moved
// 05/08/02     AB      Sync with 5.32
// 05/15/02     AB      Removed Print functions prototypes
// 05/27/02     AB      rtUTF8Len & rtUTF8CharSize added
// 06/02/02     AB      rtMemRealloc, rtMemFreePtr, rtDListFreeNodes, 
//                        rtDListFreeAll, rtFreeBigInt added
// 06/05/02     AB      rtAddOID added
// 06/15/02     AB      ASN1UINT64 added, ASN1OID64 subid type changed 
//                        to ASN1UINT64
// 06/18/02     AB      MemBuf functions added
// 07/09/02     AB      rtCompareBigIntStr added
// 08/05/02     AB      some BigInt funcs are renamed
// 09/16/02     AB      ALLOC_ASN1ELEMNODE, rtDListAppendNode added
// 10/05/02     ED      Added rtFileReadBinary function
// 10/13/02     AB      Some more rtMem* funcs added
// 10/23/02     AP      Added ASN_ID_EPDV tag for EmbeddedPDV type
// 10/27/02     AB      ASN1I64CONST/ASN1UI64CONST macros are added
// 10/29/03     CZ      Added text for main page.
// 11/12/03     CZ      Removed end tags from some doxygen groups
//
////////////////////////////////////////////////////////////////////////////
*/

 /*The following is the text for the main C/C++ Runtime index page.*/
 /*! \mainpage C/C++ Common Runtime Classes and Library Functions
 *
 * The <B>ASN.1 C++ run-time classes</B> are wrapper classes that provide an 
 * object-oriented interface to the ASN.1 C run-time library functions. The 
 * categories of classes provided are as follows:
 * <UL>
 * <LI>Context Management classes manage the ASN1CTXT structure used to keep
 * track of the working variables required to encode or decode ASN.1 
 * messages.</LI>
 * <LI>Exception classes define exceptions that can be thrown from the C++ 
 * runtime classes.</LI>
 * <LI>Message Buffer classes are used to manage message buffers.</LI>
 * <LI>ASN1C Control Base classes are wrapper classes that are used as the 
 * base for compiler-generated ASN1C_ classes, including Date and Time 
 * Run-time classes.</LI>
 * <LI>ASN.1 Type (ASN1T_) Base classes are used as the base for compiler-
 * generated ASN1T_ C++ data structures. </LI>
 * <LI>ASN.1 Stream classes are used to read and write ASN.1 messages from 
 * and to files, sockets, memory buffer, etc.</LI> 
 * <LI>TCP/IP or UDP Socket classes provide utility methods for doing socket 
 * I/O. <LI>%Asn1NamedEventHandler classes include the base classes for 
 * user-defined error handler and event handler classes.</LI> </UL>
 *
 * The <B>C run-time common library</B> contains common C functions used by  
 * the encoding rules (BER/DER, PER, and XER) low-level encode/decode
 * functions. These functions are identified by their <I>rt</I> prefixes. 
 * The categories of functions provided are as follows:<UL>
 * <LI>Memory Allocation macros and functions handle memory 
 * management for the ASN1C run-time.</LI> 
 * <LI>Context Management functions handle the allocation, 
 * initialization, and destruction of ASN.1 context variables
 * (variables of type ASN1CTXT) that handle the working data used 
 * during encoding or decoding a message.</LI>
 * <LI>Diagnostic Trace functions allow the output of trace messages
 * to standard output that trace the execution of complier generated 
 * functions.</LI> 
 * <LI>Error Formatting and Print functions allow information about 
 * the encode/decode errors to be added to a context block structure 
 * and printed out.</LI>
 * <LI>Memory Buffer Management functions handle the allocation, 
 * expansion, and de-allocation of dynamic memory buffers used by some
 * encode/decode functions.</LI> 
 * <LI>Object Identifier Helper functions provide assistance in working
 * with the object identifier ASN.1 type. </LI>
 * <LI>Linked List and Stack Utility functions are used to maintain
 * linked lists and stacks used within the ASN.1 run-time library
 * functions.</LI>
 * <LI>REAL Helper functions - REAL helper functions provide assistance
 * in working with the REAL ASN.1 type. Two functions are provided to 
 * obtain the plus and minus infinity special values.  </LI>
 * <LI>Formatted Printing functions allow raw ASN.1 data fields to be
 * formatted and printed to standard output and other output devices.</LI>
 * <LI>Binary Coded Decimal (BCD) helper functions provide assistance in 
 * working with BCD numbers.</LI>
 * <LI>Character String Conversion functions convert between standard 
 * null-terminated C strings and different ASN.1 string types.</LI>
 * <LI>Big Integer Helper functions are arbitrary-precision integer 
 * manipulating functions used to maintain big integers used within the 
 * ASN.1 run-time functions. </LI>
 * <LI>Comparison functions allow comparison of the values of primitive 
 * ASN.1 types.  They make it possible to compare complex structures and 
 * determine what elements within those structures are different.</LI> 
 * <LI>Comparison to Standard Output functions do the same actions as the 
 * other comparison functions, but print the comparison results to standard 
 * output instead of to the buffer. </LI>
 * <LI>Copy functions - This group of functions allows copying values of 
 * primitive ASN.1 types. </LI>
 * <LI>Print Values to Standard Output functions print the output in a 
 * "name=value" format, where the value format is obtained by calling
 *  one of the ToString functions with the given value.</LI>
 * </UL>
 */ 


/** 
 * @file asn1type.h 
 * Common ASN.1 runtime constants, data structure definitions, and run-time
 * functions to support the BER/DER/PER/XER as defined in the ITU-T standards.
 */
#ifndef _ASN1TYPE_H_
#define _ASN1TYPE_H_

#if !defined NO_ASN1_RT_REDUNDANT
#   define NO_ASN1_RT_REDUNDANT
#endif /* !NO_ASN1_RT_REDUNDANT */

#ifdef HAVE_CONFIG_H
#include<myconfig.h>
#endif
#if defined DEVL
# define CSP_LITE 1
#endif

#ifdef CSP_LITE
#ifndef CSP_DRIVER
typedef int FILE; /* Or it will be too much to fix all around */
#include<csplitecrt.h>
#endif
#else /* CSP_LITE */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <setjmp.h>
# include <limits.h>
# include <stddef.h>
#endif /* CSP_LITE */


#ifdef _NUCLEUS
#ifndef NUCLEUS
#include <nucleus.h>
#endif /* NUCLEUS */
#else

#if defined UNIX && !defined CSP_LITE
#   include <wchar.h>
#endif /* UNIX && !CSP_LITE */

#endif /* _NUCLEUS */

/** 
 * @defgroup cruntime C Runtime Common Functions 
 * @{
 */

/* Set this #define to use an internal tag type of 32 bits instead      */
/* of 16 bits.  This will allow ID codes up to 2 ^ 29 (536870912)       */ 
/* instead of the default representation of 2 ^ 13 (8192).              */

#define ASN1C_EXPANDED_TAGS

/* Tagging Value and Mask Constants */

/* tag class value constants */

#define TV_UNIV         0       /* universal                    */
#define TV_APPL         1       /* application-wide             */
#define TV_CTXT         2       /* context-specific             */
#define TV_PRIV         3       /* private-use                  */

/* tag form value constants */

#define TV_PRIM         0       /* primitive                    */
#define TV_CONS         1       /* constructor                  */

/* tag mask values - these can be logically or'd together to    */
/* form tags compatible with the ASNTAG structure..             */

#ifdef ASN1C_EXPANDED_TAGS

#define TM_UNIV         0x00000000  /* universal class          */
#define TM_APPL         0x40000000  /* application-wide class   */
#define TM_CTXT         0x80000000  /* context-specific class   */
#define TM_PRIV         0xC0000000  /* private-use class        */

#define TM_PRIM         0x00000000  /* primitive form           */
#define TM_CONS         0x20000000  /* constructor form         */
#define TM_IDCODE       0x1FFFFFFF  /* ID code mask             */

#define ASN_K_BADTAG    0xFFFFFFFF  /* invalid tag code         */
#define ASN_K_NOTAG     0xFFFFFFFF  /* no tag input parameter   */

#else

#define TM_UNIV         0x0000  /* universal class              */
#define TM_APPL         0x4000  /* application-wide class       */
#define TM_CTXT         0x8000  /* context-specific class       */
#define TM_PRIV         0xC000  /* private-use class            */

#define TM_PRIM         0x0000  /* primitive form               */
#define TM_CONS         0x2000  /* constructor form             */
#define TM_IDCODE       0x1FFF  /* ID code mask                 */
                                                                
#define ASN_K_BADTAG    0xFFFF  /* invalid tag code             */
#define ASN_K_NOTAG     0xFFFF  /* no tag input parameter       */

#endif

#define TM_CLASS        0xC0    /* class mask                   */
#define TM_FORM         0x20    /* form mask                    */
#define TM_CLASS_FORM   0xE0    /* class/form mask              */
#define TM_B_IDCODE     0x1F    /* id code mask (byte)          */

#ifndef FALSE
#define FALSE           0
#define TRUE            1
#endif

#define MINMSGLEN       8       /* minimum message length               */

/* Error Code Constants */

#define ASN_OK            0      /* normal completion status             */
#define ASN_OK_FRAG       2      /* message fragment detected            */
#define ASN_E_BUFOVFLW   -1      /* encode buffer overflow               */
#define ASN_E_ENDOFBUF   -2      /* unexpected end of buffer on decode   */
#define ASN_E_IDNOTFOU   -3      /* identifer not found                  */
#define ASN_E_INVOBJID   -4      /* invalid object identifier            */
#define ASN_E_INVLEN     -5      /* invalid field length                 */
#define ASN_E_INVENUM    -6      /* enumerated value not in defined set  */
#define ASN_E_SETDUPL    -7      /* duplicate element in set             */
#define ASN_E_SETMISRQ   -8      /* missing required element in set      */
#define ASN_E_NOTINSET   -9      /* element not part of set              */
#define ASN_E_SEQOVFLW   -10     /* sequence of field overflow           */
#define ASN_E_INVOPT     -11     /* invalid option encountered in choice */
#define ASN_E_NOMEM      -12     /* no dynamic memory available          */
#define ASN_E_INVHEXS    -14     /* invalid hex string                   */
#define ASN_E_INVBINS    -15     /* invalid binary string                */
#define ASN_E_INVREAL    -16     /* invalid real value                   */
#define ASN_E_STROVFLW   -17     /* octet or bit string field overflow   */
#define ASN_E_BADVALUE   -18     /* invalid value specification          */
#define ASN_E_UNDEFVAL   -19     /* no def found for ref'd defined value */
#define ASN_E_UNDEFTYP   -20     /* no def found for ref'd defined type  */
#define ASN_E_BADTAG     -21     /* invalid tag value                    */
#define ASN_E_TOODEEP    -22     /* nesting level is too deep            */
#define ASN_E_CONSVIO    -23     /* value constraint violation           */
#define ASN_E_RANGERR    -24     /* invalid range (lower > upper)        */
#define ASN_E_ENDOFFILE  -25     /* end of file on file decode           */
#define ASN_E_INVUTF8    -26     /* invalid UTF-8 encoding               */
#define ASN_E_CONCMODF   -27     /* Concurrent list modification         */
#define ASN_E_ILLSTATE   -28     /* Illegal state error                  */
#define ASN_E_OUTOFBND   -29     /* out of bounds (of array, etc)        */
#define ASN_E_INVPARAM   -30     /* invalid parameter                    */
#define ASN_E_INVFORMAT  -31     /* invalid time string format           */
#define ASN_E_NOTINIT    -32     /* not initialized                      */
#define ASN_E_TOOBIG     -33     /* value is too big for given data type */
#define ASN_E_INVCHAR    -34     /* invalid character (not in char set)  */
#define ASN_E_XMLSTATE   -35     /* XML state error                      */
#define ASN_E_XMLPARSE   -36     /* XML parse error                      */
#define ASN_E_SEQORDER   -37     /* SEQUENCE elements not in order       */
#define ASN_E_INVINDEX   -38     /* invalid index for TC id              */
#define ASN_E_INVTCVAL   -39     /* invalid value for TC field           */
#define ASN_E_FILNOTFOU  -40     /* file not found                       */
#define ASN_E_FILEREAD   -41     /* error occurred reading file          */
#define ASN_E_FILEWRITE  -42     /* error occurred writing file          */
#define ASN_E_INVBASE64  -43     /* invalid base64 encoding              */
#define ASN_E_INVSOCKET  -44     /* invalid socket operation             */
#define ASN_E_XMLLIBNFOU -45     /* XML library is not found             */
#define ASN_E_XMLLIBINV  -46     /* XML library is invalid               */
#define ASN_E_NOTSUPP    -99     /* non-supported ASN construct          */
#define ASN_K_INDEFLEN   -9999   /* indefinite length message indicator  */

/* universal built-in type ID code value constants */

#define ASN_ID_EOC      0       /* end of contents              */
#define ASN_ID_CSP_BOOL     1       /* boolean                      */
#define ASN_ID_INT      2       /* integer                      */
#define ASN_ID_BITSTR   3       /* bit string                   */
#define ASN_ID_OCTSTR   4       /* byte (octet) string          */
#define ASN_ID_NULL     5       /* null                         */
#define ASN_ID_OBJID    6       /* object ID                    */
#define ASN_ID_OBJDSC   7       /* object descriptor            */
#define ASN_ID_EXTERN   8       /* external type                */
#define ASN_ID_REAL     9       /* real                         */
#define ASN_ID_ENUM     10      /* enumerated value             */
#define ASN_ID_EPDV     11      /* EmbeddedPDV type             */
#define ASN_ID_RELOID   13      /* relative object ID           */
#define ASN_ID_SEQ      16      /* sequence, sequence of        */
#define ASN_ID_SET      17      /* set, set of                  */

#define ASN_SEQ_TAG     0x30    /* SEQUENCE universal tag byte  */
#define ASN_SET_TAG     0x31    /* SET universal tag byte       */

/* Restricted character string type ID's */

#define ASN_ID_NumericString    18
#define ASN_ID_PrintableString  19
#define ASN_ID_TeletexString    20
#define ASN_ID_T61String        ASN_ID_TeletexString
#define ASN_ID_VideotexString   21
#define ASN_ID_IA5String        22
#define ASN_ID_UTCTime          23
#define ASN_ID_GeneralTime      24
#define ASN_ID_GraphicString    25
#define ASN_ID_VisibleString    26
#define ASN_ID_GeneralString    27
#define ASN_ID_UniversalString  28
#define ASN_ID_BMPString        30

/* flag mask values */

#define XM_SEEK         0x01    /* seek match until found or end-of-buf */
#define XM_ADVANCE      0x02    /* advance pointer to contents on match */
#define XM_DYNAMIC      0x04    /* alloc dyn mem for decoded variable   */
#define XM_SKIP         0x08    /* skip to next field after parsing tag */

/* Sizing Constants */

#define ASN_K_MAXDEPTH  32      /* maximum nesting depth for messages   */
#define ASN_K_MAXSUBIDS 128     /* maximum sub-id's in an object ID     */
#define ASN_K_MAXENUM   100     /* maximum enum values in an enum type  */
#define ASN_K_MAXERRP   5       /* maximum error parameters             */
#define ASN_K_MAXERRSTK 8       /* maximum levels on error ctxt stack   */

#ifndef ASN_K_ENCBUFSIZ
#define ASN_K_ENCBUFSIZ 16*1024 /* dynamic encode buffer extent size    */
#endif

#ifndef ASN_K_MEMBUFSEG
#define ASN_K_MEMBUFSEG 1024    /* memory buffer extent size            */
#endif

/* Constants for encoding/decoding real values */

#define ASN1_K_PLUS_INFINITY    0x40
#define ASN1_K_MINUS_INFINITY   0x41

#define REAL_BINARY             0x80
#define REAL_SIGN               0x40
#define REAL_EXPLEN_MASK        0x03
#define REAL_EXPLEN_1           0x00
#define REAL_EXPLEN_2           0x01
#define REAL_EXPLEN_3           0x02
#define REAL_EXPLEN_LONG        0x03
#define REAL_FACTOR_MASK        0x0c
#define REAL_BASE_MASK          0x30
#define REAL_BASE_2             0x00
#define REAL_BASE_8             0x10
#define REAL_BASE_16            0x20
#define REAL_ISO6093_MASK       0x3F

/* ASN.1 Primitive Type Definitions */

typedef char            ASN1CHAR;
typedef unsigned char   ASN1OCTET;
typedef ASN1OCTET       ASN1CSP_BOOL;
typedef signed char     ASN1INT8;
typedef unsigned char   ASN1UINT8;
typedef int             ASN1INT;
typedef unsigned int    ASN1UINT;
typedef ASN1INT         ASN1ENUM;
typedef double          ASN1REAL;

#include <float.h>
#define ASN1REALMAX    (ASN1REAL)DBL_MAX  
#define ASN1REALMIN    (ASN1REAL)-DBL_MAX

typedef short           ASN1SINT;
typedef unsigned short  ASN1USINT;
#ifdef ASN1C_EXPANDED_TAGS
typedef ASN1UINT        ASN1TAG;
#define ASN1TAG_LSHIFT  24
#else
typedef ASN1USINT       ASN1TAG;
#define ASN1TAG_LSHIFT  8
#endif
typedef ASN1USINT       ASN116BITCHAR;
typedef ASN1UINT        ASN132BITCHAR;
typedef void*           ASN1ANY;

#define ASN1UINT_MAX    4294967295U
#define ASN1INT_MAX     ((ASN1INT)2147483647L)
#define ASN1INT_MIN     ((ASN1INT)(-ASN1INT_MAX-1))

/* 64-bit long integer type */

#ifndef ASN1INT64
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__)
#define ASN1INT64 __int64
#define ASN1UINT64 unsigned __int64
#define ASN1INT64FMT  "%I64d"
#define ASN1UINT64FMT "%I64u"
#define ASN1INT64FMTX "%I64x"
#define ASN1INT64MAX  _I64_MAX
#define ASN1UINT64MAX _UI64_MAX
#define ASN1INT64MIN  _I64_MIN
#define ASN1I64CONST(val)  val##i64  
#define ASN1UI64CONST(val) val##ui64  
#elif defined(__IBMC__) || defined(__GNUC__) || defined(__SUNPRO_C) || \
defined(__SUNPRO_CC) || defined(__CC_ARM)
#define ASN1INT64 long long
#define ASN1UINT64 unsigned long long
#define ASN1INT64FMT  "%lld"
#define ASN1UINT64FMT "%llu"
#define ASN1INT64FMTX "%llx"
#define ASN1I64CONST(val)  val##LL  
#define ASN1UI64CONST(val) val##ULL  
#if defined(__IBMC__)
#define ASN1INT64MAX  LONGLONG_MAX
#define ASN1UINT64MAX ULONGLONG_MAX
#define ASN1INT64MIN  LONGLONG_MIN
#elif defined(__SUNPRO_CC) || defined(__SUNPRO_C)
#define ASN1INT64MAX  LONG_MAX
#define ASN1UINT64MAX ULONG_MAX
#define ASN1INT64MIN  LONG_MIN
#elif defined(__CC_ARM) || defined(__FreeBSD__)
#define ASN1INT64MAX  LLONG_MAX
#define ASN1UINT64MAX ULLONG_MAX
#define ASN1INT64MIN  LLONG_MIN
#else
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#define ASN1INT64MAX  LONG_LONG_MAX
#define ASN1UINT64MAX ULONG_LONG_MAX
#define ASN1INT64MIN  LONG_LONG_MIN
#endif
#else
#define ASN1INT64 long
#define ASN1UINT64 unsigned long
#define ASN1INT64FMT  "%ld"
#define ASN1UINT64FMT "%lu"
#define ASN1INT64FMTX "%lx"
#define ASN1INT64MAX  LONG_MAX
#define ASN1UINT64MAX ULONG_MAX
#define ASN1INT64MIN  LONG_MIN
#define ASN1I64CONST(val)  val##L  
#define ASN1UI64CONST(val) val##UL  
#endif
#endif

typedef enum { ASN1IMPL, ASN1EXPL } ASN1TagType;
typedef enum { ASN1HEX, ASN1BIN, ASN1CHR } ASN1StrType;
typedef enum { ASN1ENCODE, ASN1DECODE } ASN1ActionType;

typedef const char* ASN1ConstCharPtr;
typedef const ASN1OCTET* ASN1ConstOctetPtr;
typedef const void* ASN1ConstVoidPtr;
typedef const ASN116BITCHAR* ASN1Const16BitCharPtr;
#define ASN1Const const

typedef struct {        /* object identifier */
   ASN1UINT     numids;
   ASN1UINT     subid[ASN_K_MAXSUBIDS];
} ASN1OBJID;

typedef struct {        /* object identifier with 64-bit arcs */
   ASN1UINT     numids;
   ASN1UINT64   subid[ASN_K_MAXSUBIDS];
} ASN1OID64;

typedef union {         /* double floating point (encode/decode real) */
   ASN1OCTET    byte[10];
   ASN1USINT    word[4];
   double       value;
} ASN1_DFLOAT;

typedef struct {        /* generic octet string structure */
   ASN1UINT     numocts;
   ASN1OCTET    data[1];
} ASN1OctStr;

typedef struct {        /* generic octet string structure (dynamic) */
   ASN1UINT     numocts;
   ASN1ConstOctetPtr data;
} ASN1DynOctStr;

typedef struct {        /* generic bit string structure (dynamic) */
   ASN1UINT     numbits;
   ASN1ConstOctetPtr data;
} ASN1DynBitStr;

typedef struct {                /* generic sequence of structure        */
   ASN1UINT     n;
   void*        elem;
} ASN1SeqOf;

typedef struct {                /* sequence of OCTET STRING             */
   ASN1UINT     n;
   ASN1DynOctStr* elem;
} ASN1SeqOfOctStr;

typedef struct _ASN1ListElem {  /* generic linked list structure        */
   struct _ASN1ListElem* next;
   void*        data_p;
} ASN1ListElem;

typedef struct {                /* generic open type data structure     */
   ASN1UINT     numocts;
   ASN1ConstOctetPtr data;
} ASN1OpenType;

typedef struct {                /* generic table constraint value holder */
   ASN1OpenType encoded;
   void*        decoded;                                    
   int          index;          /* table index */
} Asn1Object;

typedef Asn1Object ASN1Object;

/* ASN.1 useful type definitions */

typedef struct {
   ASN1UINT       nchars;
   ASN116BITCHAR* data;
} Asn116BitCharString;

typedef struct {
   ASN1UINT       nchars;
   ASN132BITCHAR* data;
} Asn132BitCharString;

typedef ASN1ConstCharPtr   ASN1GeneralizedTime;
typedef ASN1ConstCharPtr   ASN1GeneralString;
typedef ASN1ConstCharPtr   ASN1GraphicString;
typedef ASN1ConstCharPtr   ASN1IA5String;
typedef ASN1ConstCharPtr   ASN1ISO646String;
typedef ASN1ConstCharPtr   ASN1NumericString;
typedef ASN1ConstCharPtr   ASN1ObjectDescriptor;
typedef ASN1ConstCharPtr   ASN1PrintableString;
typedef ASN1ConstCharPtr   ASN1TeletexString;
typedef ASN1ConstCharPtr   ASN1T61String;
typedef ASN1ConstCharPtr   ASN1UTCTime;
typedef ASN1ConstCharPtr   ASN1UTF8String;
typedef ASN1ConstCharPtr   ASN1VideotexString;
typedef ASN1ConstCharPtr   ASN1VisibleString;

typedef Asn116BitCharString ASN1BMPString;
typedef Asn132BitCharString ASN1UniversalString;

/* ASN.1 constrained string structures */

typedef struct {
   int          nchars;
   char         data[255];
} Asn1CharArray;

typedef struct {
   Asn1CharArray charSet;
   ASN1ConstCharPtr canonicalSet;
   int          canonicalSetSize;
   unsigned     canonicalSetBits;
   unsigned     charSetUnalignedBits;
   unsigned     charSetAlignedBits;
} Asn1CharSet;

typedef struct {
   Asn116BitCharString charSet;
   ASN1USINT    firstChar, lastChar;
   unsigned     unalignedBits;
   unsigned     alignedBits;
} Asn116BitCharSet;

typedef struct {
   Asn132BitCharString charSet;
   ASN1UINT     firstChar, lastChar;
   unsigned     unalignedBits;
   unsigned     alignedBits;
} Asn132BitCharSet;

/* Big Integer */

typedef struct ASN1BigInt {
   int       numocts;           /* number of used octets in mag         */
   ASN1OCTET *mag;              /* magnitude                            */
   int       sign;              /* sign, can be -1, 0, 1                */

   int       allocated;         /* number of allocated octets for mag   */
   ASN1CSP_BOOL  dynamic;           /* is buffer dynamic?                   */
} ASN1BigInt;

/* Singly-linked list */

typedef struct _Asn1RTSListNode {
   void* data;
   struct _Asn1RTSListNode* next;
} Asn1RTSListNode;

struct ASN1CTXT;

typedef struct _Asn1RTSList {
   ASN1UINT count;
   Asn1RTSListNode* head;
   Asn1RTSListNode* tail;
   struct ASN1CTXT* pctxt;
} Asn1RTSList;

/* Doubly-linked list */

typedef struct _Asn1RTDListNode {
   void* data;
   struct _Asn1RTDListNode* next;
   struct _Asn1RTDListNode* prev;
} Asn1RTDListNode;

typedef struct _Asn1RTDList {
   ASN1UINT count;
   Asn1RTDListNode* head;
   Asn1RTDListNode* tail;
} Asn1RTDList;

/* Stack */

typedef struct _Asn1RTStack {
   int level;
   void* data[ASN_K_MAXDEPTH];
} Asn1RTStack;

/* ASN.1 size constraint structure */

typedef struct _Asn1SizeCnst {
   ASN1CSP_BOOL     extended;
   ASN1UINT     lower;
   ASN1UINT     upper;
   struct _Asn1SizeCnst* next;
} Asn1SizeCnst;

/* ASN.1 encode/decode buffer info structure */

typedef struct {
   ASN1OCTET*   data;           /* pointer to start of data buffer      */
   ASN1UINT     byteIndex;      /* byte index                           */
   ASN1UINT     size;           /* current buffer size                  */
   ASN1SINT     bitOffset;      /* current bit offset (8 - 1)           */
   ASN1CSP_BOOL     dynamic;        /* is buffer dynamic?                   */
   ASN1CSP_BOOL     aligned;        /* is buffer byte aligned?              */
} ASN1BUFFER;

/* This structure is used to save the current state of the buffer */

typedef struct {
   ASN1UINT     byteIndex;      /* byte index                           */
   ASN1SINT     bitOffset;      /* current bit offset (8 - 1)           */
   ASN1USINT    flags;          /* flag bits                            */
} ASN1BUFSAVE;

/* ASN.1 context control block - this structure is used to keep track   */
/* of pointer and length context values when decoding sets or sequence  */
/* of constructs.                                                       */

#define ASN1_K_CCBMaskSize      32
#define ASN1_K_NumBitsPerMask   16
#define ASN1_K_MaxSetElements   (ASN1_K_CCBMaskSize*ASN1_K_NumBitsPerMask)

typedef struct {                /* context control block        */
   ASN1OCTET*   ptr;            /* constructor pointer          */
   int          len;            /* constructor length           */
   int          seqx;           /* sequence element index       */
   unsigned short mask[ASN1_K_CCBMaskSize];  /* set mask value  */
   ASN1UINT     bytes;          /* bytes processed before block (for stream) */
} ASN1CCB;

/* ASN.1 run-time error info structures */

typedef struct {
   ASN1ConstCharPtr module;
   int          lineno;
} ASN1ErrLocn;

typedef struct {
   ASN1ErrLocn  stack[ASN_K_MAXERRSTK];
   int          stkx;
   int          status;
   int          parmcnt;
   ASN1ConstCharPtr parms[ASN_K_MAXERRP];
} ASN1ErrInfo;

#define XM_K_MEMBLKSIZ  (4*1024)

/* Flag mask constant values */

#if !defined NO_ASN1_RT_REDUNDANT
#define ASN1DYNCTXT     0x8000
#endif	/* !NO_ASN1_RT_REDUNDANT */
#define ASN1INDEFLEN    0x4000
#define ASN1TRACE       0x2000
#define ASN1LASTEOC     0x1000
#define ASN1FASTCOPY    0x0800  /* turns on the "fast copy" mode        */
#define ASN1CONSTAG     0x0400  /* form of last parsed tag              */
#define ASN1CANXER      0x0200  /* canonical XER                        */
#define ASN1SAVEBUF     0x0100  /* do not free dynamic encode buffer    */
#define ASN1OPENTYPE    0x0080  /* item is an open type field           */
#define CP_ASN1NOLENCHECK 0x0040 /* extension: allow partial bufferts for stream decoding */

/* ASN.1 encode/decode context block structure */

typedef struct ASN1CTXT {       /* ASN.1 context block                  */
   void*        pMsgMemHeap;    /* internal message memory heap         */
   void*        pTypeMemHeap;   /* memory heap                          */
   ASN1BUFFER   buffer;         /* data buffer                          */
   struct OSRTStream* pStream;  /* Stream */
   ASN1BUFSAVE  savedInfo;      /* saved buffer info                    */
   ASN1ErrInfo  errInfo;        /* run-time error info                  */
   Asn1RTSList  fieldList;      /* PER field list                       */
   Asn1SizeCnst* pSizeConstraint;  /* Size constraint list              */
   ASN1ConstCharPtr pCharSet;   /* String of permitted characters       */
   Asn1RTStack  nameStack;      /* Element name stack                   */
   Asn1RTSList  evtHndlrList;   /* Event handler object list            */
   void*        errHndlrCB;     /* Error handler callback function      */
   ASN1UINT     initCode;       /* code double word to indicate init    */
   ASN1USINT    flags;          /* flag bits                            */
   ASN1OCTET    level;          /* nesting level                        */
   ASN1OCTET    xerState;       /* XER state                            */
   void*	pCSP;	/* Memory Arena				*/
#if defined _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4324)
#endif /* _MSC_VER */
#ifndef CSP_LITE
   jmp_buf      jmpMark;        /* Jump buff for setjmp/longjmp (XER C) */
#endif /* CSP_LITE */
#if defined _MSC_VER
#pragma warning (pop)
#endif /* _MSC_VER */
} ASN1CTXT;

#define OSRTISSTREAM(pctxt) ((pctxt)->pStream != 0)

/* ASN.1 memory buffer */

typedef struct ASN1MemBuf {
   ASN1CTXT*    pctxt;
   ASN1UINT     segsize;        /* segment size                     */
   ASN1UINT     startidx;       /* start index of useful info       */
   ASN1UINT     usedcnt;        /* used byte count                  */
   ASN1UINT     bufsize;        /* buffer size                      */
   ASN1UINT     bitOffset;      /* bit offset                       */
   ASN1UINT     userState ;     /* user state - any value, 0 is initial */
   ASN1OCTET*   buffer;         /* memory buffer                    */
   ASN1CSP_BOOL     isDynamic;      /* is buffer allocated dynamically? */
} ASN1MemBuf;

/* Date & Time structure */
#define OSDT_MAXSECFRAC 20
typedef struct _OSDATETIME {
   short mYear;
   short mMonth;       /* 1 - Jan, ... 12 - Dec */
   short mDay;         /* day of month, 1..31 (or 28,29,30) */
   short mHour;        /* 0..23 */
   short mMinute;      /* 0..59 */
   short mSecond;      /* 0..59 */
   short mDiffHour;    /* -12 .. +12 */
   short mDiffMin;     /* -59 .. 0 .. +59 */
   char  mSecondFrac[OSDT_MAXSECFRAC + 1]; /* > 0.000 */
   ASN1CSP_BOOL mUtcFlag;  /* is Z flag present or not */
} OSDATETIME;

#define ASN1MEMBUFPTR(pmb)    ((pmb)->buffer + (pmb)->startidx)
#define ASN1MEMBUFENDPTR(pmb) ((pmb)->buffer + (pmb)->startidx + (pmb)->usedcnt)
#define ASN1MEMBUFUSEDSIZE(pmb) ((size_t)(pmb)->usedcnt)

#if !defined NO_ASN1_RT_REDUNDANT
#define ASN1MBAPPENDSTR(pmb,str) \
rtMemBufAppend(pmb,(ASN1OCTET*)str,strlen(str))

#define ASN1MBAPPENDUTF8(pmb,str) \
rtMemBufAppend(pmb,(ASN1OCTET*)str,rtxUTF8LenBytes(str))
#endif	/* !NO_ASN1_RT_REDUNDANT */

/* ASN.1 dump utility callback function definition */

typedef int (*ASN1DumpCbFunc) (ASN1ConstCharPtr text_p, void* cbArg_p);

/* ASNLIB function macros and prototypes */

#ifndef ASN1MAX
#define ASN1MAX(a,b)        (((a)>(b))?(a):(b))
#endif

#ifndef ASN1MIN
#define ASN1MIN(a,b)        (((a)<(b))?(a):(b))
#endif

#if defined (ACVERSION) && ACVERSION <= 530
#define MIN ASN1MIN
#define MAX ASN1MAX
#endif

/**
 * @defgroup rtmem Memory Allocation Macros and Functions 
 * @ingroup cruntime
 *
 * Memory allocation functions and macros handle memory management for the
 * ASN1C run-time. Special algorithms are used for allocation and deallocation
 * of memory to improve the run-time performance. @{
 */
/**
 * Allocate a dynamic array. This macro allocates a dynamic array of records of
 * the given type. This version of the macro will return the ASN_E_NOMEM error
 * status if the memory request cannot be fulfilled.
 *
 * @param pctxt        - Pointer to a context block
 * @param pseqof       - Pointer to a generated SEQUENCE OF array structure.
 *                       The <i>n</i> member variable must be set to the number
 *                       of records to allocate.
 * @param type         - Data type of an array record
 */
#define ALLOC_ASN1ARRAY(pctxt,pseqof,type) do {\
if (sizeof(type)*(pseqof)->n < (pseqof)->n) return ASN_E_NOMEM; \
if (((pseqof)->elem = (type*) rtMemHeapAlloc \
(&(pctxt)->pTypeMemHeap, sizeof(type)*(pseqof)->n)) == 0) return ASN_E_NOMEM; \
} while (0)

/**
 * Allocate a dynamic array. This macro allocates a dynamic array of records of
 * the given type. This version of the macro will set the internal parameters
 * of the SEQUENCE OF structure to NULL if the memory request cannot be
 * fulfilled.
 *
 * @param pctxt        - Pointer to a context block
 * @param pseqof       - Pointer to a generated SEQUENCE OF array structure.
 *                       The <i>n</i> member variable must be set to the number
 *                       of records to allocate.
 * @param type         - Data type of an array record
 */
#define ALLOC_ASN1ARRAY1(pctxt,pseqof,type) do {\
if (sizeof(type)*(pseqof)->n < (pseqof)->n) (pseqof)->elem = 0; \
else (pseqof)->elem = (type*) rtMemHeapAlloc \
(&(pctxt)->pTypeMemHeap, sizeof(type)*(pseqof)->n); \
} while (0)

/**
 * Allocate a dynamic array. This macro allocates a dynamic array of records of
 * the given type. This version returns the pointer to the allocated array
 * directly to the caller. It does not use a generated SEQUENCE OF structure.
 *
 * @param pctxt        - Pointer to a context block
 * @param n            - Number of records to allocate
 * @param type         - Data type of an array record
 */
#define ALLOC_ASN1ARRAY2(pctxt,n,type) \
((type*) ((sizeof(type)*n < n) ? 0 : \
rtMemHeapAlloc (&(pctxt)->pTypeMemHeap, sizeof(type)*n)))

/**
 * Allocate and zero an ASN.1 element. This macro allocates and zeros a single
 * element of the given type.
 *
 * @param pctxt        - Pointer to a context block
 * @param type         - Data type of record to allocate
 */
#define ALLOC_ASN1ELEM(pctxt,type) \
(type*) rtMemHeapAllocZ (&(pctxt)->pTypeMemHeap, sizeof(type))

#define ALLOC_ASN1ELEMDNODE(pctxt,type) \
(type*) (((char*)rtMemHeapAllocZ (&(pctxt)->pTypeMemHeap, sizeof(type) + \
sizeof(Asn1RTDListNode))) + sizeof(Asn1RTDListNode))

#define ALLOC_ASN1ELEMSNODE(pctxt,type) \
(type*) (((char*)rtMemHeapAllocZ (&(pctxt)->pTypeMemHeap, sizeof(type) + \
sizeof(Asn1RTSListNode))) + sizeof(Asn1RTSListNode))

/**
 * Get array size. This macro returns the number of elements in an array.
 *
 * @param x            - Array varaible
 */
#define ASN1ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))

/**
 * Allocate memory. This macro allocates the given number of bytes. It is
 * similar to the C \c malloc run-time function.
 *
 * @param pctxt        - Pointer to a context block
 * @param nbytes       - Number of bytes of memory to allocate
 * @return             - Void pointer to allocated memory or NULL if
 *                       insufficient memory was available to fulfill the
 *                       request.
 */
#define ASN1MALLOC(pctxt,nbytes) \
rtMemHeapAlloc(&(pctxt)->pTypeMemHeap, nbytes)

#define ASN1MALLOCZ(pctxt,nbytes) \
rtMemHeapAllocZ(&(pctxt)->pTypeMemHeap, nbytes)

/**
 * Reallocate memory. This macro reallocates a memory block (either expands or
 * contracts) to the given number of bytes. It is similar to the C \c realloc
 * run-time function.
 *
 * @param pctxt        - Pointer to a context block
 * @param pmem         - Pointer to memory block to reallocate. This must have
 *                       been allocated using the ASN1MALLOC macro or the
 *                       rtMemHeapAlloc function.
 * @param nbytes       - Number of bytes of memory to which the block is to be
 *                       resized.
 * @return             - Void pointer to allocated memory or NULL if
 *                       insufficient memory was available to fulfill the
 *                       request. This may be the same as the pmem pointer that
 *                       was passed in if the block did not need to be
 *                       relocated.
 */
#define ASN1REALLOC(pctxt,pmem,nbytes) \
rtMemHeapRealloc(&(pctxt)->pTypeMemHeap, pmem, nbytes)

/**
 * Reallocate an array. This macro reallocates an array (either expands or
 * contracts) to hold the given number of elements. The number of elements is
 * specified in the <i>n</i> member variable of the pseqof argument.
 *
 * @param pctxt        - Pointer to a context block
 * @param pseqof       - Pointer to a generated SEQUENCE OF array structure.
 *                       The <i>n</i> member variable must be set to the number
 *                       of records to allocate.
 * @param type         - Data type of an array record
 */
#define REALLOC_ASN1ARRAY(pctxt,pseqof,type) /*do*/ {\
if (sizeof(type)*(pseqof)->n < (pseqof)->n) return ASN_E_NOMEM; \
if (((pseqof)->elem = (type*) rtMemHeapRealloc \
(&(pctxt)->pTypeMemHeap, (pseqof)->elem, sizeof(type)*(pseqof)->n)) == 0) \
return ASN_E_NOMEM; \
} /*while (0)*/

/**
 * Free memory associated with a context. This macro frees all memory held
 * within a context. This is all memory allocated using the ASN1MALLOC (and
 * similar macros) and the rtMem memory allocation functions using the given
 * context variable.
 *
 * @param pctxt        - Pointer to a context block
 */
#if !defined NO_ASN1_RT_REDUNDANT
#define ASN1MEMFREE(pctxt) \
rtMemHeapFreeAll(&(pctxt)->pTypeMemHeap)
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * Free memory pointer. This macro frees memory at the given pointer. The
 * memory must have been allocated using the ASN1MALLOC (or similar) macros or
 * the rtMem memory allocation functions. This macro is similar to the C \c
 * free function.
 *
 * @param pctxt        - Pointer to a context block
 * @param pmem         - Pointer to memory block to free. This must have been
 *                       allocated using the ASN1MALLOC macro or the
 *                       rtMemHeapAlloc function.
 */
#define ASN1MEMFREEPTR(pctxt,pmem)  \
rtMemHeapFreePtr(&(pctxt)->pTypeMemHeap, (void*)pmem)

/**
 * Reset memory associated with a context. This macro resets all memory held
 * within a context. This is all memory allocated using the ASN1MALLOC (and
 * similar macros) and the rtMem memory allocation functions using the given
 * context variable.
 *
 * <p>The difference between this and the ASN1MEMFREE macro is that the memory
 * blocks held within the context are not actually freed. Internal pointers are
 * reset so the existing blocks can be reused. This can provide a performace
 * improvement for repetitive tasks such as decoding messages in a loop.
 *
 * @param pctxt        - Pointer to a context block
 */
#define ASN1MEMRESET(pctxt) \
rtMemHeapReset(&(pctxt)->pTypeMemHeap)
/**
 * @}
 */
#define ASN1BUFCUR(cp)          (cp)->buffer.data[(cp)->buffer.byteIndex]
#define ASN1BUFPTR(cp)          &(cp)->buffer.data[(cp)->buffer.byteIndex]
#define ASN1BUF_INDEFLEN(cp)    (((cp)->flags&ASN1INDEFLEN)!=0)
#define ASN1BUF_PTR(cp)         ASN1BUFPTR(cp)

#define ASN1NUMOCTS(nbits)      ((nbits>0)?(((nbits-1)/8)+1):0)

#ifdef _TRACE
#define RTDIAG1(msg)                            rtdiag(msg)
#define RTDIAG2(msg,a)                          rtdiag(msg,a)
#define RTDIAG3(msg,a,b)                        rtdiag(msg,a,b)
#define RTDIAG4(msg,a,b,c)                      rtdiag(msg,a,b,c)
#define RTDIAG5(msg,a,b,c,d)                    rtdiag(msg,a,b,c,d)
#define RTDIAG6(msg,a,b,c,d,e)                  rtdiag(msg,a,b,c,d,e)
#define RTDIAG7(msg,a,b,c,d,e,f)                rtdiag(msg,a,b,c,d,e,f)
#define RTDIAG8(msg,a,b,c,d,e,f,g)              rtdiag(msg,a,b,c,d,e,f,g)
#define RTDIAG9(msg,a,b,c,d,e,f,g,h)            rtdiag(msg,a,b,c,d,e,f,g,h)
#define RTDIAG10(msg,a,b,c,d,e,f,g,h,i)         rtdiag(msg,a,b,c,d,e,f,g,h,i)  
#define RTHEXDUMP(buffer,numocts)               rtDiagHexDump(buffer,numocts)
#else
#define RTDIAG1(msg)
#define RTDIAG2(msg,a)
#define RTDIAG3(msg,a,b)
#define RTDIAG4(msg,a,b,c)
#define RTDIAG5(msg,a,b,c,d)
#define RTDIAG6(msg,a,b,c,d,e)
#define RTDIAG7(msg,a,b,c,d,e,f)
#define RTDIAG8(msg,a,b,c,d,e,f,g)
#define RTDIAG9(msg,a,b,c,d,e,f,g,h)
#define RTDIAG10(msg,a,b,c,d,e,f,g,h,i)
#define RTHEXDUMP(buffer,numocts)
#endif

#define HEXCHARTONIBBLE(ch,b) \
if (ch >= '0' && ch <= '9') b = (unsigned char)(ch - '0'); \
else if (ch >= 'a' && ch <= 'f') b = (unsigned char)((ch - 'a') + 10); \
else if (ch >= 'A' && ch <= 'F') b = (unsigned char)((ch - 'A') + 10); \
else b = 0xFF;

#define NIBBLETOHEXCHAR(b,ch) \
if (b >= 0 && b <= 9) ch = (char)(b + '0'); \
else if (b >= 0x0a && b <= 0x0f) ch = (char)((b - 10)+ 'a'); \
else ch = '?';

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EXTERN
#ifdef ASN1DLL
#define EXTERN __declspec(dllexport)
#elif defined (USEASN1DLL)
#define EXTERN __declspec(dllimport)
#else
#define EXTERN
#endif /* ASN1DLL */
#endif /* EXTERN */

#ifndef EXTERNRT
#ifdef BUILDASN1RTDLL
#define EXTERNRT __declspec(dllexport)
#elif defined (USEASN1RTDLL)
#define EXTERNRT __declspec(dllimport)
#else
#define EXTERNRT
#endif /* BUILDASN1RTDLL */
#endif /* EXTERNRT */

#ifdef USEASN1RTDLL
#define DLLNOINLINERT __declspec(noinline)
#else
#define DLLNOINLINERT
#endif // USEASN1RTDLL

#ifndef _NO_MALLOC
#define ASN1CRTMALLOC0(nbytes)       malloc(nbytes)
#define ASN1CRTFREE0(ptr)            free(ptr)
#else

#ifdef _NO_THREADS
extern EXTERNRT ASN1CTXT g_ctxt;

#define ASN1CRTMALLOC0(nbytes)       rtMemAlloc(&g_ctxt,(nbytes))
#define ASN1CRTFREE0(ptr)            rtMemFreePtr(&g_ctxt,(ptr))
#else
#define ASN1CRTMALLOC0(nbytes)       ((void*)0)
#define ASN1CRTFREE0(ptr)            (void)((void*)0)

#endif /* _NO_THREADS */
#endif /* _NO_MALLOC */

#define ASN1CRTMALLOC ASN1MALLOC
#define ASN1CRTFREE   ASN1MEMFREEPTR

/* run-time error and diagnostic functions */

extern int g_debug;

EXTERNRT int rtBase64EncodeData (ASN1CTXT* pctxt, ASN1ConstOctetPtr pSrcData, 
                                 int srcDataSize, ASN1OCTET** ppDstData);

EXTERNRT int rtBase64DecodeData (ASN1CTXT* pctxt, ASN1ConstOctetPtr pSrcData, 
                                 int srcDataSize, ASN1OCTET** ppDstData);

EXTERNRT int  rtCheckBuffer (ASN1CTXT* pctxt, ASN1UINT nbytes);

EXTERNRT void rtCopyContext (ASN1CTXT* pdest, ASN1CTXT* psrc);

#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT void rtXchgContext (ASN1CTXT* pdest, ASN1CTXT* psrc);
#endif	/* !NO_ASN1_RT_REDUNDANT */

EXTERNRT void rtCtxtSetFlag (ASN1CTXT* pctxt, ASN1USINT mask);

#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT void rtCtxtClearFlag (ASN1CTXT* pctxt, ASN1USINT mask);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/* Context management functions */

/**
 * @defgroup cmfun Context Management Functions 
 * @{
 *
 * Context initialization functions handle the allocation, initialization, and
 * destruction of ASN.1 context variables (variables of type ASN1CTXT). These
 * variables hold all of the working data used during the process of encoding
 * or decoding a message. The context provides thread safe operation by
 * isolating what would otherwise be global variables within this structure.
 * The context variable is passed from function to function as a message is
 * encoded or decoded and maintains state information on the encoding or
 * decoding process.
 */

/**
 * This function assigns a buffer to an ASN1CTXT block. The block should have
 * been previously initialized by rtInitContext.
 *
 * @param ctxt_p       The pointer to the context structure variable to be
 *                       initialized.
 * @param bufaddr      For encoding, the address of a memory buffer to receive
 *                       and encode a message. For decoding the address of a
 *                       buffer that contains the message data to be decoded.
 *                       This address will be stored within the context
 *                       structure. For encoding it might be zero, the dynamic
 *                       buffer will be used in this case.
 * @param bufsiz       The size of the memory buffer. For encoding, it might be
 *                       zero; the dynamic buffer will be used in this case.
 * @return             Completion status of operation:
 *                       - 0 (ASN_OK) = success,
 *                       - negative return value is error.
 */
EXTERNRT int   rtInitContextBuffer (ASN1CTXT* ctxt_p, 
                                    ASN1ConstOctetPtr bufaddr, 
                                    ASN1UINT bufsiz);

/**
 * This function initializes an ASN1CTXT block. It makes sure that if the block
 * was not previoiusly initialized, that all key working parameters are set to
 * thier correct initial state values (i.e. declared within a function as a
 * normal working variable), it is required that they invoke this function
 * before using it.
 *
 * @param ctxt_p       The pointer to the context structure variable to be
 *                       initialized.
 * @return             Completion status of operation:
 *                       - 0 (ASN_OK) = success,
 *                       - negative return value is error.
 */
EXTERNRT int   rtInitContext (ASN1CTXT* ctxt_p, void *pCSP);

#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT int   rtInitSubContext (ASN1CTXT* ctxt_p, ASN1CTXT* psrc);
#endif	/* !NO_ASN1_RT_REDUNDANT */

  /* кроме прототипа от неё нет ничего EXTERNRT int   rtInitContextExt (ASN1CTXT* ctxt_p); */

/**
 * This function allocates a new ASN1CTXT block and initializes it. Although
 * the block is allocated from the standard heap, it should not be freed using
 * free. The rtFreeContext function should be used because this frees items
 * allocated within the block before freeing the block itself.
 *
 * This is the preferred way of setting up a new encode or decode context
 * because it ensures the block is properly initialized before using it. If a
 * context variable is declared on the stack, the user must first remember to
 * invoke the rtInitContext function on it. This can be a source of errors.
 * This function can be called directly when setting up BER context or it will
 * be invoked from within the pu_newContext call for PER.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT ASN1CTXT* rtNewContext (void);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function frees all dynamic memory associated with a context. This
 * includes all memory inside the block (in particular, the list of memory
 * blocks used by the rtMem functions) as well as the block itself if allocated
 * with the rtNewContext function
 *
 * @param ctxt_p       A pointer to a context structure.
 */
EXTERNRT void  rtFreeContext (ASN1CTXT* ctxt_p);

EXTERNRT int   rtReadNextByte (ASN1CTXT* pCtxt);

/**
 * This function is deprecated, use ::rtSetFastCopy.
 */ 
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT void  rtSetCopyValues (ASN1CTXT* ctxt_p, ASN1CSP_BOOL value);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function sets the ASN1FASTCOPY flag in the specified context. This flag
 * has effect only if decoding is being performed. If this flag is set then
 * some decoded data (some BIT STRINGs, OCTET STRINGs or OPEN TYPEs) may be not
 * copied, just the pointer is set to the appropriate place in the decoding
 * buffer. It may improve decoding performance, but this flag should be used
 * carefully. If the decoding buffer is destroyed, then all uncopied data will
 * be lost as well. Use it only if sure that buffer will not be destroyed while
 * decoded data is necessary. By default this flag is not set.
 *
 * @param ctxt_p       Pointer to context block structure.
 * @param value        Boolean value of the flag to set.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT void  rtSetFastCopy (ASN1CTXT* ctxt_p, ASN1CSP_BOOL value);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/** 
 * @} cmfun
 */
/**
 * @defgroup llfuns Linked List Utility Functions
 *
 * Linked list and stack utility functions are used to maintain linked lists
 * and stacks used within the ASN.1 run-time library functions. @{
 */
/**
 * This function appends an item to the linked list structure. The data item is
 * passed into the function as a void pointer that can point to any object of
 * any type. The rtMemAlloc function is used to allocated the memory for the
 * list node structure; therefore, all internal list memory will be released
 * whenever rtMemFree is called. The pointer to the data item itself is stored
 * in the node structure - a copy is not made.
 *
 * @param ctxt_p       A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pList        A pointer to a linked list structure onto which the data
 *                       item is to be appended. A pointer to an updated linked
 *                       list structure.
 * @param pData        A pointer to a data item to be appended to the list.
 * @return             A pointer to an allocated node structure used to link
 *                       the given data value into the list.
 */ 
EXTERNRT Asn1RTDListNode* rtDListAppend (ASN1CTXT* ctxt_p, 
                                         Asn1RTDList* pList, void* pData);

/**
 * This function initializes a doubly linked list structure. It sets the number
 * of elements to zero and sets al internal pointer values to NULL. A doubly
 * linked-list structure is described by the Asn1RTDList type defined in
 * asn1type.h. Nodes of the list are of type Asn1RTDListNode.
 *
 * Memory for the structures is allocated using the rtMemAlloc run-time
 * function and is maintained within the context structure that is a required
 * parameter to all rtDList functions. This memory is released when rtMemFree
 * is called or the Context is released. Unless otherwise noted, all data
 * passed into the list functions is simply stored on the list by value (i.e. a
 * deep-copy of the data is not done).
 *
 * @param pList        A pointer to a linked list structure to be initialized.
 */
EXTERNRT void  rtDListInit (Asn1RTDList* pList);

/**
 * This function inserts an item into the linked list structure. The data item
 * is passed into the function as a void pointer that can point to an object of
 * any type. The rtMemAlloc function is used to allocate the memory for the
 * list node structure; therefore, all internal list memory will be released
 * whenever the rtMemFree is called.
 *
 * @param ctxt_p       A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pList        A pointer to a linked list structure onto which the data
 *                       item is to be appended. A pointer to an updated linked
 *                       list structure.
 * @param index        An index at which the specified item is to be inserted.
 * @param pData        A pointer to a data item to be inserted to the list.
 * @return             A pointer to an allocated node structure used to link
 *                       the given data value into the list.
 */
EXTERNRT Asn1RTDListNode* rtDListInsert (ASN1CTXT* ctxt_p,
                                         Asn1RTDList* pList, 
                                         int ind, void* pData);

/**
 * This function inserts an item into a linked list structure before a
 * specified node. The data item is passed into the function as a void pointer
 * that can point to an object of any type. The rtMemAlloc function is used to
 * allocate the memory for the list node structure; therefore, all internal
 * list memory will be released whenever the rtMemFree is called.
 *
 * @param ctxt_p       A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pList        A pointer to a linked list structure onto which the data
 *                       item is to be appended. A pointer to an updated linked
 *                       list structure.
 * @param node         A pointer to the node before which the specified item is
 *                       to be inserted. It should already be in the linked
 *                       list structure.
 * @param pData        A pointer to a data item to be inserted to the list.
 * @return             A pointer to an allocated node structure used to link
 *                       the given data value into the list.
 */
EXTERNRT Asn1RTDListNode* rtDListInsertBefore (ASN1CTXT* ctxt_p,
                                               Asn1RTDList* pList, 
                                               Asn1RTDListNode* node, 
                                               void* pData);

/**
 * This function inserts an item into a linked list structure after a specified
 * node. The data item is passed into the function as a void pointer that can
 * point to any type. The rtMemAlloc function is used to allocate the memory
 * for the list structure; therefore, all internal list memory will be released
 * whenever the rtMemFree is called.
 *
 * @param ctxt_p       A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pList        A pointer to a linked list structure onto which the data
 *                       item is to be appended. A pointer to an updated linked
 *                       list structure.
 * @param node         A pointer to the node after which the specified item is
 *                       to be inserted. It should already be in the linked
 *                       list structure.
 * @param pData        A pointer to a data item to be inserted to the list.
 * @return             A pointer to an allocated node structure used to link
 *                       the given data value into the list
 */
EXTERNRT Asn1RTDListNode* rtDListInsertAfter (ASN1CTXT* ctxt_p,
                                              Asn1RTDList* pList, 
                                              Asn1RTDListNode* node, 
                                              void* pData);

/**
 * This function gets a node from a linked list structure at a specified index.
 *
 * @param pList        A pointer to a linked list structure onto which the data
 *                       item is to be appended.
 * @param index        A relative zero-based index of the node in the list to
 *                       be returned.
 * @return             The pointer to the found node structure. NULL, if the
 *                       node is not found.
 */
EXTERNRT Asn1RTDListNode* rtDListFindByIndex (Asn1RTDList* pList, int ind);

/**
 * This function gets a node from a linked list structure that contains a
 * specific data value. The comparison is done on the pointer values, not the
 * data objects themselves.
 *
 * @param pList        A pointer to a linked list structure onto which the data
 *                       item is to be appended.
 * @param data         A pointer to the data item to be found in the list.
 * @return             A pointer to the found node structure. NULL is returned
 *                       if a matching node could be found.
 */
EXTERNRT Asn1RTDListNode* rtDListFindByData (Asn1RTDList* pList, void* data);

/** 
 * This function gets a node's index from a linked list structure that contains
 * a specific data value. The comparison is done on the pointer values, not the
 * data objects themselves.
 *
 * @param pList        A pointer to a linked list structure onto which the data
 *                       item is to be appended.
 * @param data         A pointer to the data item to be found in the list.
 * @return             The index of the node that contains specified data.
 *                       Negative one (-1) is returned if matching node could
 *                       not be found.
 */ 
EXTERNRT int   rtDListFindIndexByData (Asn1RTDList* pList, void* data);

/**
 * This function removes a node from the linked list structure. The rtMemAlloc
 * function was used to allocate the memory for the list node structure,
 * therefore, all internal list memory will be released whenever rtMemFree or
 * rtMemFreePtr is called.
 *
 * @param pList        A pointer to a linked list structure onto which the data
 *                       item is to be appended. A pointer to an updated linked
 *                       list structure.
 * @param node         A pointer to the node that is to be removed. It should
 *                       already be in the linked list structure.
 */
EXTERNRT void  rtDListRemove (Asn1RTDList* pList, Asn1RTDListNode* node);

/**
 * This function removes all nodes from the linked list and releases the memory
 * that was allocated for storing nodes' structures (Asn1RTDListNode). The data
 * will not be released.
 *
 * @param ctxt_p       A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pList        A pointer to a linked list structure onto which the data
 *                       item is to be appended. A pointer to an updated linked
 *                       list structure.
 */
EXTERNRT void  rtDListFreeNodes (ASN1CTXT* ctxt_p, Asn1RTDList* pList);

/** 
 * This function removes all nodes from the linked list structure and releases
 * the memory that was allocated for storing nodes' structures
 * (Asn1RTDListNode) and for data. The memory for data in each node must have
 * been previously allocated with calls to rtMemAlloc, rtMemAllocZ, or
 * rtMemRealloc functions.
 *
 * @param ctxt_p       A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pList        A pointer to a linked list structure onto which the data
 *                       item is to be appended. A pointer to an updated linked
 *                       list structure. A pointer to an empty linked list
 *                       structure.
 */
EXTERNRT void  rtDListFreeAll (ASN1CTXT* ctxt_p, Asn1RTDList* pList);

/** 
 * This function converts a doubly linked list to an array.
 *
 * @param ctxt_p       A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pList        A pointer to a linked list structure. A pointer to an
 *                       updated linked list structure.
 * @param ppArray      A pointer to a pointer to a destination array. A pointer
 *                       to filled destination array.
 * @param pElements    A pointer to the number of elements already allocated in
 *                       ppArray. If pElements is NULL, or pElements is less
 *                       than the number of nodes in the list, then a new array
 *                       is allocated and pointer is stored into ppArray.
 *                       Memory is allocated via calls to the rtMemAlloc
 *                       function. If not NULL, the pointer to the total number
 *                       in the ppArray after the additional items were
 *                       appended.
 * @param elemSize     The size of one element in the array. Use sizeof()
 *                       operator to pass this parameter.
 * @return             The number of elements in the returned array.
 */
EXTERNRT int   rtDListToArray (ASN1CTXT* ctxt_p, Asn1RTDList* pList, 
                               void** ppArray, ASN1UINT* pElements, 
                               int elemSize);

/**
 * This function appends an array items' pointers into a doublly linked list
 * structure.
 *
 * @param ctxt_p       A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pList        A pointer to a linked list structure. A pointer to an
 *                       updated linked list structure. The elements from the
 *                       array will be appended to the end of the list.
 * @param pArray       A pointer to the source array to be converted.
 * @param numElements  The number of elements in the array.
 * @param elemSize     The size of one element in the array. Use sizeof()
 *                       operator to pass this parameter.
 */
EXTERNRT void  rtDListAppendArray (ASN1CTXT* ctxt_p, Asn1RTDList* pList, 
                                   ASN1ConstVoidPtr pArray, 
                                   ASN1UINT numElements, int elemSize);

/**
 * This function appends a copy of an array's items into a doubly linked list
 * structure. This memory for copies is allocated via calls to rtMemAlloc.
 *
 * @param ctxt_p       A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pList        A pointer to a linked list structure. A pointer to an
 *                       updated linked list structure. The elements from the
 *                       array will be appended to the end of the list.
 * @param pArray       A pointer to the source array to be converted.
 * @param numElements  The number of elements in the array.
 * @param elemSize     The size of one element in the array. Use sizeof()
 *                       operator to pass this parameter.
 */
EXTERNRT void  rtDListAppendArrayCopy (ASN1CTXT* ctxt_p, Asn1RTDList* pList, 
                                       ASN1ConstVoidPtr pArray, 
                                       ASN1UINT numElements, int elemSize);

/*
 * This function appends an item to a linked list structure. In cotrast to
 * rtDListAppend, this function does not allocate the memory for the node
 * strcture. The memory for node structure is taken by subtracting
 * sizeof(Asn1RTDListNode) from the pData pointer. Thus, the memory for the
 * data should be allocated using ALLOC_ASN1ELEMDNODE macro. This function
 * works faster than rtDListAppend because one memory allocation is used.
 *
 * @param ctxt_p       A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pList        A pointer to a linked list structure onto which the data
 *                       item is to be appended. A pointer to the updated
 *                       linked list structure.
 * @param pData        A pointer to the data item to be appended to the list.
 * @return             A pointer to the allocated node used to link the given
 *                       data value into the list.
 */
EXTERNRT Asn1RTDListNode* rtDListAppendNode (ASN1CTXT* ctxt_p, 
                                             Asn1RTDList* pList, void* pData);
/**
 * @}llfuns
 */
/**
 * @defgroup diag Diagnostic Trace Functions 
 * @{
 *
 * Diagnostic trace functions allow the output of trace messages to stdout that
 * trace the execution of complier generated functions. The primary function is
 * rtdiag, a printf-like function that checks a global trace flag before
 * writing to the standard output.
 */

/**
 * This function conditionally outputs diagnostic trace messages to stdout. The
 * ASN1C compiler embeds calls to this function into the generated source code
 * when the -trace option is specified on the command line (note: it may embed
 * the macro version of these calls - RTDIAGx - so that these calls can be
 * compiled out of the final code.
 *
 * @param fmtspec      A printf-like format specification string describing the
 *                       message to be printed (for example, "string %s, ivalue
 *                       %d\n").
 * @param             ... A variable list of arguments.
 */
#if !defined _COMPACT
EXTERNRT void  rtdiag (ASN1ConstCharPtr fmtspec, ...);
#endif

#if !defined _COMPACT
EXTERNRT void  rtDiagHexDump (ASN1ConstOctetPtr data, ASN1UINT numocts);
#endif

/**
 * This function turns diagnostic tracing on of off.
 *
 * @param value        - Value indiciating whether to enable or disable
 *                       tracing.
 */
#if !defined _COMPACT
EXTERNRT void  rtSetDiag (int value);
#endif

/**
 * The rtHexDump function outputs a hexadecimal dump of the current buffer
 * contents to stdout. There is also a macro associated with rtHexDump. This
 * macro is RTHEXDUMP and is defined in the asn1type.h header file. It allows a
 * dump function to be complied in or out of the object code generated by the
 * C/C++ complier by using a preprocessor variable (_TRACE).
 *
 * @param data         The pointer to a buffer to be displayed.
 * @param numocts      The number of octets to be displayed.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT void  rtHexDump (ASN1ConstOctetPtr data, ASN1UINT numocts);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function outputs a hexadecimal dump of the current buffer contents to
 * stdout, but it may display the dump as an array or bytes, words, or double
 * words.
 *
 * @param data         The pointer to a buffer to be displayed.
 * @param numocts      The number of octets to be displayed.
 * @param bytesPerUnit The number of bytes in one unit. May be 1 (byte), 2
 *                       (word), or 4 (double word).
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT void  rtHexDumpEx (ASN1ConstOctetPtr data, ASN1UINT numocts, 
                            int bytesPerUnit);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function outputs a hexadecimal dump of the current buffer contents to a
 * file.
 *
 * @param fp           A pointer to FILE structure. The file should be opened
 *                       for writing.
 * @param data         The pointer to a buffer to be displayed.
 * @param numocts      The number of octets to be displayed
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT void  rtHexDumpToFile (FILE* fp, ASN1ConstOctetPtr data, 
                                ASN1UINT numocts);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function outputs a hexadecimal dump of the current buffer to a file,
 * but it may output the dump as an array of bytes, words, or double words.
 *
 * @param fp           A pointer to FILE structure. The file should be opened
 *                       for writing.
 * @param data         The pointer to a buffer to be displayed.
 * @param numocts      The number of octets to be displayed.
 * @param bytesPerUnit The number of bytes in one unit. May be 1 (byte), 2
 *                       (word), or 4 (double word).
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT void  rtHexDumpToFileEx (FILE* fp, ASN1ConstOctetPtr data, 
                                  ASN1UINT numocts, int bytesPerUnit);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function formats a hexadecimal dump of the current buffer contents to a
 * string.
 *
 * @param data         The pointer to a buffer to be displayed.
 * @param numocts      The number of octets to be displayed.
 * @param buffer       The destination string buffer.
 * @param bufferIndex  The starting position in the destination buffer. The
 *                       formatting of the dump will begin at this position.
 * @param bufferSize   The total size of the destination buffer.
 * @return             The length of the final string.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT int   rtHexDumpToString (ASN1ConstOctetPtr data, ASN1UINT numocts, 
                                  char* buffer, 
                                  int bufferIndex, int bufferSize);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This fucntion formats a hexadecimal dump of the current buffer contents to a
 * string, but it may output the dump as an array of bytes, words, or double
 * words.
 *
 * @param data         The pointer to a buffer to be displayed.
 * @param numocts      The number of octets to be displayed.
 * @param buffer       The destination string buffer.
 * @param bufferIndex  The starting position in the destination buffer. The
 *                       formatting of the dump will begin at this position.
 * @param bufferSize   The total size of the destination buffer.
 * @param bytesPerUnit The number of bytes in one unit. May be 1 (byte), 2
 *                       (word), or 4 (double word).
 * @return             The length of the final string.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT int   rtHexDumpToStringEx (ASN1ConstOctetPtr data, ASN1UINT numocts, 
                                    char* buffer, int bufferIndex, 
                                    int bufferSize, int bytesPerUnit);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/** 
 * @} diag
 */


/**
 * @defgroup errfp Error Formatting and Print Functions 
 * @{
 *
 * Error formatting and print functions allow information about the
 * encode/decode errors to be added to a context block structure and then
 * printed out when the error is propagated to the top level.
 */

/**
 * This function adds an integer parameter to an error information structure.
 * Parameter substitution is done in much the same way as it is done in C
 * printf statments. The base error message specification that goes along with
 * a particular status code may have variable fields built in using '%'
 * modifiers. These would be replaced with actual parameter data.
 *
 * @param pErrInfo     A pointer to a structure containing information on the
 *                       error to be printed. Typically, the error info
 *                       structure referred to is the one inside the ASN1CTXT
 *                       structure. (i.e. &ctxt_p->errInfo).
 * @param errParm      The typed error parameter.
 * @return             The status of the operation.
 */
EXTERNRT int   rtErrAddIntParm (ASN1ErrInfo* pErrInfo, int errParm);

/**
 * This function adds an string parameter to an error information structure.
 * Parameter substitution is done in much the same way as it is done in C
 * printf statments. The base error message specification that goes along with
 * a particular status code may have variable fields built in using '%'
 * modifiers. These would be replaced with actual parameter data.
 *
 * @param pErrInfo     A pointer to a structure containing information on the
 *                       error to be printed. Typically, the error info
 *                       structure referred to is the one inside the ASN1CTXT
 *                       structure. (i.e. &ctxt_p->errInfo).
 * @param errprm_p     The typed error parameter.
 * @return             The status of the operation.
 */
EXTERNRT int   rtErrAddStrParm (ASN1ErrInfo* pErrInfo, 
                                ASN1ConstCharPtr errprm_p);

/**
 * This function adds an tag parameter to an error information structure.
 * Parameter substitution is done in much the same way as it is done in C
 * printf statments. The base error message specification that goes along with
 * a particular status code may have variable fields built in using '%'
 * modifiers. These would be replaced with actual parameter data.
 *
 * @param pErrInfo     A pointer to a structure containing information on the
 *                       error to be printed. Typically, the error info
 *                       structure referred to is the one inside the ASN1CTXT
 *                       structure. (i.e. &ctxt_p->errInfo).
 * @param errParm      The typed error parameter.
 * @return             The status of the operation.
 */
EXTERNRT int   rtErrAddTagParm (ASN1ErrInfo* pErrInfo, ASN1TAG errParm);

/**
 * This function adds an unsigned integer parameter to an error information
 * structure. Parameter substitution is done in much the same way as it is done
 * in C printf statments. The base error message specification that goes along
 * with a particular status code may have variable fields built in using '%'
 * modifiers. These would be replaced with actual parameter data.
 *
 * @param pErrInfo     A pointer to a structure containing information on the
 *                       error to be printed. Typically, the error info
 *                       structure referred to is the one inside the ASN1CTXT
 *                       structure. (i.e. &ctxt_p->errInfo).
 * @param errParm      The typed error parameter.
 * @return             The status of the operation.
 */
EXTERNRT int   rtErrAddUIntParm (ASN1ErrInfo* pErrInfo, unsigned int errParm);


EXTERNRT int   rtErrCopyData (ASN1ErrInfo* pSrcErrInfo, 
                              ASN1ErrInfo* pDestErrInfo);

/**
 * This function frees memory associated with the storage of parameters
 * associated with an error message. These parameters are maintained on an
 * internal linked list maintained within the error information structure. The
 * list memory must be freed when error processing is complete. This function
 * is called from within rtErrPrint after teh error has been printed out. It is
 * also called in teh pu_freeContext function.
 *
 * @param pErrInfo     A pointer to a structure containing information on the
 *                       error to be printed. Typically, the error info
 *                       structure referred to is the one inside the ASN1CTXT
 *                       structure. (i.e. &ctxt_p->errInfo).
 */
EXTERNRT void  rtErrFreeParms (ASN1ErrInfo* pErrInfo);


EXTERNRT char* rtErrFmtMsg (ASN1ErrInfo* pErrInfo, char* bufp);

/**
 * This function gets the text of the error
 *
 * @param ctxt_p       A pointer to a context structure.
 */
EXTERNRT char* rtErrGetText (ASN1CTXT* ctxt_p);

/**
 * This function logs error information using a callback function provided by
 * the user. In many situations, it is not sufficient to write error
 * information to stdout to debug problems. Examples are back-end server
 * applications that fun in the background and write diagnostic information to
 * system log files and front-end applications that log error information to
 * widow displays. This function allows different error output methods to be
 * accommodated.
 *
 * This function is invoked with a line of text from the formatted error output
 * provided in the txt_p argument. The cbArg_p argument is used to pass in a
 * user-defined parameter (specified in the chArg arguemnt of this function).
 * The integer return status is not used at this time. The callback function is
 * invoked once for each formatted line of information in the error holding
 * structure.
 *
 * @param pErrInfo     A pointer to a structure containing information on the
 *                       error to be printed. Typically, the error info
 *                       structure referred to is the one inside the ASN1CTXT
 *                       structure (i.e. &ctxt_p->errInfo).
 * @param cb           A callback function to be invoked for each line of
 *                       formatted error output in the error information
 *                       structure.
 * @param cbArg        User defined callback argument to be passed as a
 *                       parameter to the callback function.
 */
EXTERNRT void  rtErrLogUsingCB (ASN1ErrInfo* pErrInfo, 
                                ASN1DumpCbFunc cb, void* cbArg);

/**
 * This function prints error information to the standard output device. The
 * error information is stored in a structure of type ASN1ErrInfo. A structure
 * of the this type is part f the ASN1CTXT structure. This is where error
 * information is stored within the ASN1C generated and low-level encode/decode
 * functions.
 *
 * @param pErrInfo     A pointer to a structure containing information on the
 *                       error to be printed. Typically, the error info
 *                       structure referred to is the one inside the ASN1CTXT
 *                       structure. (i.e. &ctxt_p->errInfo).
 */
EXTERNRT void  rtErrPrint (ASN1ErrInfo* pErrInfo);

/**
 * This function resets the error information in the error information
 * sturcture.
 *
 * @param pErrInfo     A pointer to a structure containing information on the
 *                       error to be printed. Typically, the error info
 *                       structure referred to is the one inside the ASN1CTXT
 *                       structure. (i.e. &ctxt_p->errInfo).
 */
EXTERNRT int   rtErrReset (ASN1ErrInfo* pErrInfo);

/** 
 * This function sets error information in an error information structure. The
 * information set includes status code, module name, and line number. Location
 * information (i.e. module name and line number) is pushed onto a stack within
 * the error information structure to provide a complete stack trace when the
 * information is printed out.
 *
 * @param pErrInfo     A pointer to a structure containing information on the
 *                       error to be printed. Typically, the error info
 *                       structure referred to is the one inside the ASN1CTXT
 *                       structure. (i.e. &ctxt_p->errInfo).
 * @param status       The error status code. This is one of the negative error
 *                       status codes.
 * @param module       The name of the module (C or C++ source file) in which
 *                       the module occurred. This is typically obtained by
 *                       using the _FILE_ macro.
 * @param lno          The line number at which the error occurred. This is
 *                       typically obtained by using the _LINE_ macro.
 * @return             The status value passed to the operation in the third
 *                       argument. This makes it possible to set the error
 *                       information and return the status value in one line of
 *                       code.
 */
EXTERNRT int   rtErrSetData (ASN1ErrInfo* pErrInfo, int status, 
                             ASN1ConstCharPtr module, int lno);

/** 
 * @} 
 */

#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT int   rtGetIdentByteCount (ASN1UINT ident);
#endif	/* !NO_ASN1_RT_REDUNDANT */
EXTERNRT int   rtGetIdent64ByteCount (ASN1UINT64 ident);

#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT unsigned int rtIntByteCount (ASN1INT val);
#endif	/* !NO_ASN1_RT_REDUNDANT */
EXTERNRT int   rtOctetBitLen (ASN1OCTET w);

/**
 * @defgroup buffermanfun Memory Buffer Management Functions 
 * @{
 *
 * Memory buffer management functions handle the allocation, expansion, and
 * deallocation of dynamic memory buffers used by some encode/decode functions.
 * Dynamic memory buffers are buffers that can grow or shrink to hold variable
 * sized amounts of data. This group of functions allows data to be appended to
 * buffers, to be set within buffers, and to be retrieved from buffers.
 * Currently, these functions are used within the generated XER SAX decode
 * routines to collect data as it is parsed by an XML parser.
 */

/**
 * This function initializes a memory buffer structure. It does not allocate
 * memory; it sets the fields of the structure to the proper states. This
 * function must be called before any operations with the memory buffer.
 *
 * @param pCtxt        A provides a storage area for the function to store all
 *                       working variables that must be maintained between
 *                       function calls.
 * @param pMemBuf      A pointer to the initialized memory buffer structure.
 * @param segsize      The number of bytes in which the memory buffer will be
 *                       expanded incase it is full.
 */
EXTERNRT void  rtMemBufInit (ASN1CTXT* pCtxt, ASN1MemBuf* pMemBuf, 
                             ASN1UINT segsize);

/**
 * This function assigns a static buffer to the memory buffer structure. It
 * does not allocate memory; it sets the pointer to the passed buffer. If
 * additional memory is required (for example, additional data is appended to
 * the buffer using rtMemBufAppend), a dynamic buffer will be allocated and all
 * data copied to the new buffer.
 *
 * @param pCtxt        A pointer to a context structure. This provides a
 *                       storage area for the function t store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pMemBuf      A pointer to a memory buffer structure.
 * @param buf          A pointer to the buffer to be assigned.
 * @param bufsize      The size of the buffer.
 * @param segsize      The number of bytes on which the memory buffer will be
 *                       expanded in case it is full.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT void  rtMemBufInitBuffer (ASN1CTXT* pCtxt, ASN1MemBuf* pMemBuf, 
                                   ASN1OCTET* buf, ASN1UINT bufsize, 
                                   ASN1UINT segsize);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function frees the memory buffer. If memory was allocated then it will
 * be freed. Do not use the memory buffer structure after this function is
 * called.
 *
 * @param pMemBuf      A pointer to a memory buffer structure.
 */
EXTERNRT void  rtMemBufFree (ASN1MemBuf* pMemBuf);

/**
 * This function appends the data to the end of a memory buffer. If the buffer
 * was dynamic and full then the buffer will be reallocated. If it is static
 * (the static buffer was assigned by a call to rtMemBufInitBuffer) or it is
 * empty (no memory previously allocated) then a new buffer will be allocated.
 *
 * @param pMemBuf      A pointer to a memory buffer structure.
 * @param pdata        The pointer to the buffer to be appended. The data will
 *                       be copied at the end of the memory buffer.
 * @param nbytes       The number of bytes to be copied from pData.
 * @return             Completion status of operation:
 *                       - 0 (ASN_OK) = success,
 *                       - negative return value is error.
 */
EXTERNRT int   rtMemBufAppend (ASN1MemBuf* pMemBuf, 
                               ASN1OCTET* pdata, ASN1UINT nbytes);

/**
 * This function cuts off the part of memory buffer. The beginning of the
 * cutting area is specified by offset "fromOffset" and the length is specified
 * by "nbytes". All data in this part will be lost. The data from the offset
 * "fromOffset + nbytes" will be moved to "fromOffset" offset.
 *
 * @param pMemBuf      A pointer to a memory buffer structure.
 * @param fromOffset   The offset of the beginning part, being cut off.
 * @param nbytes       The number of bytes to be cut off from the memory
 *                       buffer.
 * @return             Completion status of operation:
 *                       - 0 (ASN_OK) = success,
 *                       - negative return value is error.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT int rtMemBufCut (ASN1MemBuf* pMemBuf, 
                          ASN1UINT fromOffset, ASN1UINT nbytes);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function resets the memory buffer structure. It does not free memory,
 * just sets the pointer to the beginning and the used length to zero.
 *
 * @param pMemBuf      A pointer to a memory buffer structure.
 */
EXTERNRT void  rtMemBufReset (ASN1MemBuf* pMemBuf);

/**
 * This function trims white space of the memory buffer.
 *
 * @param pMemBuf      A pointer to a memory buffer structure.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT int   rtMemBufTrimW (ASN1MemBuf* pMemBuf);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function sets part of a memory buffer to a specified octet value. The
 * filling is started from the end of the memory buffer. If the buffer is
 * dynamic and full, then the buffer will be reallocated. If it is static (a
 * static buffer was assigned by a call to rtMemBufInitBuffer) or it is empty
 * (no memory previously was allocated) then a new buffer will be allocated.
 *
 * @param pMemBuf      A pointer to a memory buffer structure.
 * @param value        The pointer to the buffer to be appended. The data will
 *                       be copied at the end of the memory buffer.
 * @param nbytes       The number of bytes to be copied from pData.
 * @return             Completion status of operation:
 *                       - 0 (ASN_OK) = success,
 *                       - negative return value is error.
 */
EXTERNRT int   rtMemBufSet (ASN1MemBuf* pMemBuf, 
                            ASN1OCTET value, ASN1UINT nbytes);

/** 
 * This function returns the pointer to the used part of a memory buffer.
 *
 * @param pMemBuf      A pointer to a memory buffer structure.
 * @param length       The pointer to the length of the used part of the memory
 *                       buffer.
 * @return             The pointer to the used part of the memory buffer.
 */
EXTERNRT ASN1OCTET* rtMemBufGetData (ASN1MemBuf* pMemBuf, int* length);

/** 
 * This function returns the length of the used part of a memory buffer.
 *
 * @param pMemBuf      A pointer to a memory buffer structure.
 * @return             The length of the used part of the buffer.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT int   rtMemBufGetDataLen (ASN1MemBuf* pMemBuf);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function allocates a buffer with a predetermined amount of space.
 *
 * @param pMemBuf      A pointer to a memory buffer structure.
 * @param nbytes       The number of bytes to be copied from pData.
 * @return             Completion status of operation:
 *                       - 0 (ASN_OK) = success,
 *                       - negative return value is error.
 */
EXTERNRT int rtMemBufPreAllocate (ASN1MemBuf* pMemBuf, ASN1UINT nbytes);

/**
 * @} buffermanfun
 */

/**
 * @defgroup objidhelpers Object Identifier Helper Functions 
 * @{
 *
 * Object identifier helper functions provide assistance in working with the
 * object identifier ASN.1 type. Three functions are provided: two to populate
 * an Object Identifier structure and one to print the contents.
 */

/**
 * This function populates an object identifier variable with data. It copies
 * data from a source variable to a target variable. Typically, the source
 * variable is a compiler-generated object identifier constant that resulted
 * from a object identifier value specification within an ASN.1 specification.
 *
 * @param ptarget      A pointer to a target object identifier variable to
 *                       receive object * identifier data. Typically, this is a
 *                       variable within a compiler-generated C structure.
 * @param psource      A pointer to a source object identifier variable to copy
 *                       to a target. Typically, this is a compiler-generated
 *                       variable corresponding to an ASN.1 value specification
 *                       in the ASN.1 source file.
 */
EXTERNRT void  rtSetOID (ASN1OBJID* ptarget, const ASN1OBJID* psource);

/**
 * This function appends one object identifier to another one. It copies the
 * data from a source variable to the end of a target variable. Typically, the
 * source variable is a compiler-generated object identifier constant that
 * resulted from an object identifier value specification within an ASN.1
 * specification.
 *
 * @param ptarget      A pointer to a target object identifier variable to
 *                       receive object identifier data. Typically, this is a
 *                       variable within a compiler-generated C structure.
 * @param psource      A pointer to a source object identifier variable to copy
 *                       to a target. Typically, this is a compiler-generated
 *                       variable corresponding to an ASN.1 value specification
 *                       in the ASN.1 source file.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT void  rtAddOID (ASN1OBJID* ptarget, const ASN1OBJID* psource);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * @}objidhelpers
 */


/**
 * This function sets specified bit in the bit string.
 *
 * @param pBits        Pointer to octets of bit string.
 * @param numbits      Number of bits in the bit string.
 * @param bitIndex     Index of bit to be set. The bit with index 0 is a most
 *                       significant bit in the octet with index 0.
 * @return             If successful, returns the previous state of bit. If bit
 *                       was set the return value is positive, if bit was not
 *                       set the return value is zero. Otherwise, return value
 *                       is an error code:
 *                       - ASN_E_OUTOFBND = bitIndex is out of bound (see
 *                       errno)
 */
EXTERNRT int rtSetBit (ASN1OCTET* pBits, int numbits, int bitIndex);

#define OSSETBIT(bitStr,bitIndex) \
rtSetBit (bitStr.data, bitStr.numbits, bitIndex)

#define OSSETBITP(pBitStr,bitIndex) \
rtSetBit ((pBitStr)->data, (pBitStr)->numbits, bitIndex)

/**
 * This function clears specified bit in the bit string.
 *
 * @param pBits        Pointer to octets of bit string.
 * @param numbits      Number of bits in the bit string.
 * @param bitIndex     Index of bit to be cleared. The bit with index 0 is a
 *                       most significant bit in the octet with index 0.
 * @return             If successful, returns the previous state of bit. If bit
 *                       was set the return value is positive, if bit was not
 *                       set the return value is zero. Otherwise, return value
 *                       is an error code:
 *                       - ASN_E_OUTOFBND = bitIndex is out of bound (see
 *                       errno)
 */
EXTERNRT int rtClearBit (ASN1OCTET* pBits, int numbits, int bitIndex);

#define OSCLEARBIT(bitStr,bitIndex) \
rtClearBit (bitStr.data, bitStr.numbits, bitIndex)

#define OSCLEARBITP(pBitStr,bitIndex) \
rtClearBit ((pBitStr)->data, (pBitStr)->numbits, bitIndex)

/**
 * This function tests specified bit in the bit string.
 *
 * @param pBits        Pointer to octets of bit string.
 * @param numbits      Number of bits in the bit string.
 * @param bitIndex     Index of bit to be tested. The bit with index 0 is a
 *                       most significant bit in the octet with index 0.
 * @return             True if bit set or false if not set or array index is
 *                       beyond range of number of bits in the string.
 */
EXTERNRT ASN1CSP_BOOL rtTestBit (ASN1ConstOctetPtr pBits, 
                             int numbits, int bitIndex);

#define OSTESTBIT(bitStr,bitIndex) \
rtTestBit (bitStr.data, bitStr.numbits, bitIndex)

#define OSTESTBITP(pBitStr,bitIndex) \
rtTestBit ((pBitStr)->data, (pBitStr)->numbits, bitIndex)

/**
 * @defgroup llsutil Linked List and Stack Utility Functions 
 * @{
 *
 * Linked list and stack utility functions are used to maintain linked lists
 * and stacks used within the ASN.1 run-time library functions.
 */

/**
 * Singly linked list structures have only a single link pointer and can
 * therefore only be traversed in a single direction (forward). The node
 * structures consume less memory than those of a doubly linked list.
 *
 * Another difference between the singly linked list implementation and doubly
 * linked lists is that the singly linked list uses conventional memory
 * allocation functions (C malloc and free) for less storage instead of the
 * rtMem functions. Therefore, it is not a requirement to have an initialized
 * context structure to work with these lists. However, performance may suffer
 * if the lists become large due to the use of non-optimized memory management.
 *
 * This function initializes a singly linked list structure. It sets the number
 * of elements to zero and sets all internal pointer values to NULL.
 *
 * @param pList        A pointer to a linked list structure to be initialized.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT void  rtSListInit (Asn1RTSList* pList);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function is similar to rtSListInit but it also sets the pctxt (pointer
 * to a context structure member of Asn1RTSList structure. This context will be
 * used for further memory allocations; otherwise the standard malloc is used.
 *
 * @param pctxt        A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pList        A pointer to a linked list structure to be initialized.
 */
EXTERNRT void  rtSListInitEx (ASN1CTXT* pctxt, Asn1RTSList* pList);

/** 
 * This function removes all nodes from the linked list structure and releases
 * memory that was allocated for storing nodes' structures (Asn1RTSListNode).
 * The data will not be freed.
 *
 * @param pList        A pointer to a linked list onto which the data item is
 *                       to be appended.
 */
EXTERNRT void  rtSListFree (Asn1RTSList* pList);

/** 
 * This function creates a new linked list structure. It allocates memory for
 * the structure and calls rtSListInit to initialize the structure.
 *
 * @return             A pointer to the allocated linked list structure.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT Asn1RTSList* rtSListCreate (void);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * The rtSListAppend function appends an item to linked list structure. The
 * data is passed into the function as a void that can point to an object of
 * any type.
 *
 * @param pctxt        A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @return             A pointer to the allocated linked list structure.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT Asn1RTSList* rtSListCreateEx (ASN1CTXT* pctxt);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function appends an item to a linked list structure. The data item is
 * passed into the function as a void parameter that can point to an object of
 * any type.
 *
 * @param pList        A pointer to a linked list onto which the data item is
 *                       to be appended.
 * @param pData        A pointer to a data item to be appended to the list.
 * @return             A pointer to the allocated linked list structure.
 */
EXTERNRT Asn1RTSListNode* rtSListAppend (Asn1RTSList* pList, void* pData);

/** 
 * This function finds an item in the linked list structure. The data item is
 * passed into the function as a void pointer that can point to an object of
 * any type. If the appropriate node is found in the list this function returns
 * TRUE, otherwise FALSE.
 *
 * @param pList        A pointer to a linked list onto which the data item is
 *                       to be appended.
 * @param pData        A pointer to a data item to be appended to the list.
 * @return             TRUE, if the node is found, otherwise FALSE.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT ASN1CSP_BOOL rtSListFind (Asn1RTSList* pList, void* pData);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function finds an item in the linked list structure and removes it from
 * the list. The data item is passed into the function as a void pointer that
 * can point to an object of any type.
 *
 * @param pList        A pointer to a linked list onto which the data item is
 *                       to be appended.
 * @param pData        A pointer to a data item to be appended to the list.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT void rtSListRemove (Asn1RTSList* pList, void* pData);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/** 
 * This function creates a new stack structure. It allocates memory for the
 * structure and calls rtStackInit to initialize the structure.
 *
 * @return             A pointer to an allocated stack structure.
 */
EXTERNRT Asn1RTStack* rtStackCreate (void);

/** 
 * This function creates a new stack structure. The pctxt will be used for
 * memory management.
 *
 * @param pctxt        A pointer to a context structure.
 * @return             A pointer to an allocated stack structure.
 */
EXTERNRT Asn1RTStack* rtStackCreateEx (ASN1CTXT* pctxt);

/** 
 * This function initializes a stack structure. It sets the number of elements
 * to zero and sets all internal pointer values to NULL.
 *
 * @param pStack       A pointer to a stack structure to be initialized.
 */
EXTERNRT void  rtStackInit (Asn1RTStack* pStack);

/** 
 * This function pops an item off the stack.
 *
 * @param pStack       The pointer to the stack structure from which the value
 *                       is to be popped. Pointer to the updated stack
 *                       structure.
 * @return             The pointer to the item popped from the stack
 */
EXTERNRT void* rtStackPop (Asn1RTStack* pStack);

/**
 * This function pushes an item onto the stack.
 *
 * @param pStack       A pointer to the structure onto which the data item is
 *                       to be pushed. The pointer updated to the stack
 *                       structure
 * @param pData        A pointer to the data item to be pushed on the stack.
 * @return             Completion status of operation:
 *                       - 0 (ASN_OK) = success,
 *                       - negative return value is error.
 */
EXTERNRT int   rtStackPush (Asn1RTStack* pStack, void* pData);


/**
 * @} 
 */


EXTERNRT int   rtWriteBytes (ASN1CTXT* pctxt, 
                             ASN1ConstOctetPtr pdata, ASN1UINT nocts);

/**
 * @defgroup real REAL Helper Functions 
 * @{
 *
 * REAL helper functions provide assistance in working with the REAL ASN.1
 * type. Two functions are provided to obtain the plus and minus infinity
 * special values.
 */

/**
 * This function returns the PLUS-INFINITY special value. The return value may
 * be used for comparing with other ASN1REAL values or for encoding the REAL
 * PLUS_INFINITY value.
 *
 * @return             PLUS-INFINITY special value.
 */
EXTERNRT ASN1REAL rtGetPlusInfinity (void);

/**
 * This function returns the MINUS-INFINITY special value. The return value may
 * be used for comparing with other ASN1REAL values or for encoding the REAL
 * MINUS_INFINITY value.
 *
 * @return             MINUS-INFINITY special value.
 */
EXTERNRT ASN1REAL rtGetMinusInfinity (void);

EXTERNRT ASN1REAL rtGetMinusZero (void);
EXTERNRT ASN1REAL rtGetNaN (void);
EXTERNRT ASN1CSP_BOOL rtIsMinusInfinity (ASN1REAL value);
EXTERNRT ASN1CSP_BOOL rtIsMinusZero (ASN1REAL value);
EXTERNRT ASN1CSP_BOOL rtIsNaN (ASN1REAL value);
EXTERNRT ASN1CSP_BOOL rtIsPlusInfinity (ASN1REAL value);

/**
 * @} real
 */
/* run-time print functions */


/**
 * @defgroup pfun Formatted Printing Functions 
 * @{
 *
 * This group of functions allows raw ASN.1 data fields to be formatted and
 * printed to stdout and other output devices.
 */

/**
 * This function converts an ASN.1 bit string to a string. The output is an
 * ASN.1 value notation for a binary string (for example, '10010'B).
 *
 * @param numbits      The number of bits in the data argument to format.
 * @param data         The buffer containing the bit string to be formatted
 *                       (note : in the case of BER/DER, this refers to the
 *                       actual point in the string where the data starts, not
 *                       where the contents field starts. The contents field
 *                       contains an extra byte at the beginning that specifies
 *                       the number of unused bits in the last byte).
 * @param buffer       A pointer to a buffer to receive the stringified value.
 * @param bufsiz       The size of the buffer to receive the stringified value.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT ASN1ConstCharPtr rtBitStrToString (ASN1UINT numbits, 
                                            ASN1ConstOctetPtr data, 
                                            char* buffer, ASN1UINT bufsiz);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function converts an ASN.1 Boolean value to a string. The string value
 * is one of the keywords TRUE or FALSE.
 *
 * @param value        The value to convert.
 * @return             The converted value. This will be a string literal set
 *                       to either "TRUE" or "FALSE".
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT ASN1ConstCharPtr rtBoolToString (ASN1CSP_BOOL value);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/** 
 * This function converts an ASN.1 integer value to a string.
 *
 * @param value        The value to convert.
 * @param bufsiz       The size of the buffer to receive the stringified value.
 * @param buffer       The pointer to a buffer to receive the stringified
 *                       value.
 * @return             The converted value. This pointer will be equal to the
 *                       buffer argument that was passed in.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT ASN1ConstCharPtr rtIntToString (ASN1INT value, 
                                         char* buffer, int bufsiz);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function converts a 64-bit ASN.1 integer value to a string.
 *
 * @param value        The value to convert.
 * @param buffer       The pointer to a buffer to receive the stringified
 *                       value.
 * @param bufsiz       The size f the buffer to receive the stringified value.
 * @return             The converted value. This pointer will be equal to the
 *                       buffer argument that was passed in.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT ASN1ConstCharPtr rtInt64ToString (ASN1INT64 value, 
                                           char* buffer, int bufsiz);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function converts an ASN.1 integer value to a string. In this case, the
 * ASN.1 value was represented in the C/C++ code as an unsigned integer based
 * on a constraint.
 *
 * @param value        The value to convert.
 * @param buffer       The pointer to a buffer to receive the stringified
 *                       value.
 * @param bufsiz       The size f the buffer to receive the stringified value.
 * @return             The converted value. This pointer will be equal to the
 *                       buffer argument that was passed in.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT ASN1ConstCharPtr rtUIntToString 
   (ASN1UINT value, char* buffer, int bufsiz);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function converts a 64-bit ASN.1 value to a string.
 *
 * @param value        The value to convert.
 * @param buffer       The pointer to a buffer to receive the stringified
 *                       value.
 * @param bufsiz       The size f the buffer to receive the stringified value.
 * @return             The converted value. This pointer will be equal to the
 *                       buffer argument that was passed in.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT ASN1ConstCharPtr rtUInt64ToString 
   (ASN1UINT64 value, char* buffer, int bufsiz);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function converts an ASN.1 OBJECT INDENTIFIER or RELATED-OID value to a
 * string. The output format is the ASN.1 value notation for an object
 * identifier (ex. { 0 1 222 333 }). All subidentifiers are shown as unsigned
 * integer numbers - no attempt is made to map the identifiers to symbolic
 * names.
 *
 * @param numids       The number of subidentifiers in the OID value.
 * @param data         The buffer containing the OID subidentifiers to be
 *                       formatted.
 * @param bufsiz       The size of the buffer to receive the stringified value.
 * @param buffer       The pointer to a buffer to receive the stringified
 *                       value.
 * @return             The converted value. This pointer will be equal to the
 *                       buffer argument that was passed in.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT ASN1ConstCharPtr rtOIDToString (ASN1UINT numids, ASN1UINT* data, 
                                         char* buffer, ASN1UINT bufsiz);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function converts a 64-bit ASN.1 OBJECT INDENTIFIER or RELATED-OID
 * value to a string. The output format is the ASN.1 value notation for an
 * object indentifier (ex. { 0 1 222 333 }). All subidentifiers are shown as
 * unsigned integer numbers - no attempt is made to map the identifiers to
 * symbolic names.
 *
 * @param numids       The number of subidentifiers in the OID value.
 * @param data         The buffer containing the 64-bit OID subidentifiers to
 *                       be formatted.
 * @param bufsiz       The size of the buffer to receive the stringified value.
 * @param buffer       The pointer to a buffer to receive the stringified
 *                       value.
 * @return             The converted value. This pointer will be equal to the
 *                       buffer argument that was passed in.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT ASN1ConstCharPtr rtOID64ToString (ASN1UINT numids, ASN1UINT64* data, 
                                           char* buffer, ASN1UINT bufsiz);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function converts an ASN.1 octet string value to a string. The output
 * format is ASN.1 value notation for a hexadecimal string (for example,
 * '1F8A'H).
 *
 * @param numocts      The number of octets (bytes) in the data argument to
 *                       format.
 * @param data         The buffer containing the octet string to be formatted.
 * @param bufsiz       The size of the buffer to receive the stringified value.
 * @param buffer       The pointer to a buffer to receive the stringified
 *                       value.
 * @return             The converted value. This pointer will be equal to the
 *                       buffer argument that was passed in.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT ASN1ConstCharPtr rtOctStrToString (ASN1UINT numocts, 
                                            ASN1ConstOctetPtr data, 
                                            char* buffer, ASN1UINT bufsiz);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function converts an ANS.1 tag to a string. The tag is represented
 * using the ASN1C internal ASN1CTAG structure. The output is standard ASN.1
 * notation for a tag (for example, [0] = context 0 tag).
 *
 * @param tag          The tag value to be converted.
 * @param buffer       The pointer to a buffer to receive the stringified
 *                       value.
 * @param bufsiz       The size of buffer to receive the stringified value
 * @return             The converted value. This pointer will be equal to the
 *                       buffer argument that was passed in.
 */
EXTERNRT ASN1ConstCharPtr rtTagToString (ASN1TAG tag, char* buffer, 
                                         ASN1UINT bufsiz);


/**
 * @} pfun
 */

/**
 * @defgroup bcdHelper Binary Coded Decimal (BCD) Helper Functions 
 * @{
 *
 * Binary Coded Decimal (BCD) helper functions provide assistance in working
 * with BCD numbers. Two functions are provided: one to convert to a BCD value
 * to a string and one to perform the opposite conversion.
 */

/**
 * This function converts a BCD value to a standard null-terminated string.
 *
 * @param numocts      The number of octets in the BCD value.
 * @param data         The pointer to the BCD value.
 * @param buffer       The destination buffer. Should not be less than buffsiz
 *                       argument is.
 * @param bufsiz       The size of the destination buffer (in octets).
 * @return             The converted null-terminated string. NULL, if error has
 *                       occurred or destination buffer is not enough.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT ASN1ConstCharPtr rtBCDToString (ASN1UINT numocts, 
                                         ASN1ConstOctetPtr data, 
                                         char* buffer, ASN1UINT bufsiz);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/** 
 * This function converts a standard null-terminated string into a BCD value.
 * The source string should contain only characters '0' - '9', 'A' - 'F', or
 * 'a' - 'f'. Otherwise, an error will occur.
 *
 * @param str          The source standard null-terminated string.
 * @param bcdStr       The destination buffer. Should not be less than bufsiz
 *                       is.
 * @param bufsiz       The size of the destination buffer (in octets).
 * @return             The number of octets in the resulting BCD value.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT int rtStringToBCD 
   (ASN1ConstCharPtr str, ASN1OCTET* bcdStr, ASN1UINT bufsiz);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * @} bcdHelper
 */

/**
 * @defgroup charstrcon Character String Conversion Functions 
 * @{
 *
 * Common utility functions are provided to convert between standard
 * null-terminated C strings and different ASN.1 string types.
 */

/* 16-bit character functions */

/**
 * This function converts a BMP string into a null-terminated C string. Any
 * characters that are not 8-bit characters are discarded.
 *
 * @param pBMPString   A pointer to a BMP string structure to be converted.
 * @param cstring      A pointer to a buffer to receive the converted string.
 * @param cstrsize     The size of the buffer to receive the converted string.
 * @return             A pointer to the returned string structure. This is the
 *                       cstring argument parameter value.
 */
EXTERNRT ASN1ConstCharPtr rtBMPToCString (ASN1BMPString* pBMPString, 
                                          char* cstring, ASN1UINT cstrsize);

/**
 * This function converts a BMP string into a null-terminated C string. Any
 * characters that are not 8-bit characters are discarded. This function
 * allocates dynamic memory to hold the converted string using the standard C
 * run-time malloc function. The user is responsible for freeing this memory.
 *
 * @param pBMPString   A pointer to a BMP string structure to be converted.
 * @return             A pointer to the returned string structure. This is the
 *                       cstring argument parameter value.
 */
EXTERNRT ASN1ConstCharPtr rtBMPToNewCString (ASN1BMPString* pBMPString);

/**
 * This function converts a BMP string into a null-terminated C string. Any
 * characters that are not 8-bit characters are discarded. In contrast to
 * rtBMPToNewCString, this function allocates dynamic memory to hold the
 * converted string using the rtMemAlloc function. The rtMemFreePtr should be
 * called to release the allocated memory or the rtmemFree function should be
 * called to release all memory allocated using the specified context block.
 *
 * @param pctxt        A pointer to a context structure.
 * @param pBMPString   A pointer to a BMP string structure to be converted.
 * @return             A pointer to the returned string structure. This is the
 *                       cstring argument parameter value.
 */ 
EXTERNRT ASN1ConstCharPtr rtBMPToNewCStringEx 
   (ASN1CTXT *pctxt, ASN1BMPString* pBMPString);

/**
 * This function converts a null-terminated C string into a 16-bit BMP string
 * structure.
 *
 * @param ctxt_p       A pointer to a context string.
 * @param cstring      A pointer to a null-terminated C string to be converted
 *                       into a BMP string.
 * @param pBMPString   A pointer to a BMP string structure to receive the
 *                       converted string.
 * @param pCharSet     A pointer to a character set structure describing the
 *                       character set currently associated with the BMP
 *                       character string type.
 * @return             A pointer to BMP string structure. This is the
 *                       pBMPString argument parameter value.
 */
EXTERNRT ASN1BMPString* rtCToBMPString (ASN1CTXT* ctxt_p, 
                                        ASN1ConstCharPtr cstring, 
                                        ASN1BMPString* pBMPString,
                                        Asn116BitCharSet* pCharSet);

EXTERNRT ASN1CSP_BOOL rtIsIn16BitCharSet (ASN116BITCHAR ch, 
                                      Asn116BitCharSet* pCharSet);
                              
/* 32-bit character (UCS-4) functions */


/**
 * This function converts a Universal 32-bit string into a null-terminated C
 * string. Any characters that are not 8-bit characters are discarded.
 *
 * @param pUCSString   A pointer to a Universal string structure to be
 *                       converted.
 * @param cstring      A pointer to a buffer to receive a converted string.
 * @param cstrsize     The size of the buffer to receive the converted string.
 * @return             The pointer to the returned string. This is the cstring
 *                       argument parameter value.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT ASN1ConstCharPtr rtUCSToCString (ASN1UniversalString* pUCSString, 
                                          char* cstring, ASN1UINT cstrsize);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function converts a Universal 32-bit string into a null-terminated C
 * string. Any characters that are not 8-bit characters are discarded. This
 * function allocates dynamic memory to hold the converted string using the
 * standard C run-time malloc function. The user is responsible for freeing
 * this memory.
 *
 * @param pUCSString   A pointer to a Universal 32-bit string structure to be
 *                       converted.
 * @return             A pointer to allocated null-terminated string. The user
 *                       is responsible for freeing this memory.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT ASN1ConstCharPtr rtUCSToNewCString (ASN1UniversalString* pUCSString);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function converts a Universal 32-bit string into a null-terminated C
 * string. Any characters that are not 8-bit characters are discarded. In
 * contrast to rtUSCToNewCString this function allocates dynamic memory to hold
 * the converted string using the rtMemAlloc function. The rtMemFreePtr should
 * be called to release the allocated memory or the rtMemFree function should
 * be called to release all memory allocated using the specified context block.
 *
 * @param pctxt        A pointer to a context block.
 * @param pUCSString   A pointer to a Universal 32-bit string structure to be
 *                       converted.
 * @return             A pointer to allocated null-terminated string. The user
 *                       is responsible for freeing this memory.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT ASN1ConstCharPtr rtUCSToNewCStringEx 
(ASN1CTXT* pctxt, ASN1UniversalString* pUCSString);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function converts a null-terminated C string into a 32-bit UCS-4
 * (Universal Character Set, 4 byes) string structure.
 *
 * @param ctxt_p       A pointer to a context structure.
 * @param cstring      A pointer to a null-terminated C string to be converted
 *                       into a Universal string.
 * @param pUCSString   A pointer to a Universal string structure to receive the
 *                       converted string
 * @param pCharSet     A pointer to a character structure describing the
 *                       character set currently associated with the Universal
 *                       character string type.
 * @return             A pointer to a Universal string structure. This is the
 *                       pUCSString argument parameter value.
 */
EXTERNRT ASN1UniversalString* rtCToUCSString (ASN1CTXT* ctxt_p, 
                                              ASN1ConstCharPtr cstring, 
                                              ASN1UniversalString* pUCSString,
                                              Asn132BitCharSet* pCharSet);

#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT ASN1CSP_BOOL rtIsIn32BitCharSet (ASN132BITCHAR ch, 
                                      Asn132BitCharSet* pCharSet);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function converts a 32-bits encoded string to a wide character string.
 *
 * @param pUCSString   A pointer to a Universal string structure.
 * @param wcstring     The pointer to the buffer to receive the converted
 *                       string.
 * @param wcstrsize    The number of wide characters (wchar_t) the outbuffer
 *                       can hold.
 * @return             A character count or error status. This will be negative
 *                       if the conversion fails. If the result is positive,
 *                       the number of characters was written to scstrsize.
 */
EXTERNRT wchar_t* rtUCSToWCSString (ASN1UniversalString* pUCSString, 
                                    wchar_t* wcstring, ASN1UINT wcstrsize);


/**
 * This function converts a wide-character string to a Universal 32-bits
 * encoded string.
 *
 * @param ctxt_p       A pointer to a context structure.
 * @param wcstring     The pointer to the wide-character (Unicode) string to
 *                       convert
 * @param pUCSString   The pointer to the Universal String structure to receive
 *                       the converted string.
 * @param pCharSet     The pointer to the character set structure describing
 *                       the character set currently associated with the
 *                       Universal character string type.
 * @return             If the conversion of the WCS to the UTF-8 was
 *                       successful, the number of bytes in the converted
 *                       string is returned. If the encoding fails, a negative
 *                       status value is returned.
 */
EXTERNRT ASN1UniversalString* rtWCSToUCSString 
(ASN1CTXT* ctxt_p, wchar_t* wcstring, 
 ASN1UniversalString* pUCSString, Asn132BitCharSet* pCharSet);


#ifndef CSP_LITE
/* UTF-8 functions */

/**
 * This function converts a UTF-8 encoded string to a wide-character string.
 *
 * @param pCtxt        A pointer to a context structure.
 * @param inbuf        A pointer to a null-terminated UTF-8 encoded string.
 * @param outbuf       A pointer to a buffer to receive a converted string.
 * @param outbufsiz    The number of wide characters (wchar_t) the outbuffer
 *                       can hold.
 * @return             The character count or an error status. The status will
 *                       be negative if the conversion fails, and positive
 *                       indicating the number of characters written to outbuf.
 */
EXTERNRT int rtUTF8ToWCS (ASN1CTXT* pCtxt, ASN1UTF8String inbuf, 
                          wchar_t* outbuf, size_t outbufsiz);

/**
 * This function converts a wide-character string to a UTF-8 encoded string.
 *
 * @param pCtxt        A pointer to a context structure.
 * @param inbuf        The pointer to a wide-character (Unicode) string to
 *                       convert.
 * @param inlen        The number of character in the Unicode string.
 * @param outbuf       The pointer to a buffer to receive the converted string.
 * @param outbufsiz    The size (in bytes) or the output buffer to receive the
 *                       encoded string.
 * @return             If the conversion of WCS to UTF-8 is successful, the
 *                       number of bytes in the converted string is returned.
 *                       If the encoding fails, a negative status value is
 *                       returned.
 */
EXTERNRT int rtWCSToUTF8 (ASN1CTXT* pCtxt, wchar_t* inbuf, size_t inlen, 
                          ASN1OCTET* outbuf, size_t outbufsiz);

/** 
 * This function will validate a UTF-8 encoded string to ensure that it is
 * encoded correctly.
 *
 * @param pCtxt        A pointer to a context structure.
 * @param inbuf        A pointer to the null-terminated UTF-8 encoded string.
 * @return             Completion status of operation:
 *                       - 0 (ASN_OK) = success,
 *                       - negative return value is error.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT int rtValidateUTF8 (ASN1CTXT* pCtxt, ASN1UTF8String inbuf);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/** 
 * This function will return the length (in characters) of a null-terminated
 * UTF-8 encoded string.
 *
 * @param inbuf        A pointer to the null-terminated UTF-8 encoded string.
 * @return             Number of characters in string. Note that this may be
 *                       different than the number of bytes as UTF-8 characters
 *                       can span multiple-bytes.
 */
EXTERNRT int rtUTF8Len (ASN1UTF8String inbuf);

/** 
 * This function will return the length (in bytes) of a null-terminated UTF-8
 * encoded string.
 *
 * @param inbuf        A pointer to the null-terminated UTF-8 encoded string.
 * @return             Number of bytes in the string.
 */
EXTERNRT int rtUTF8LenBytes (ASN1UTF8String inbuf); 

/** 
 * This function will return the number of bytes needed to encode the given
 * 32-bit universal character value as a UTF-8 character.
 *
 * @param wc           32-bit wide character value.
 * @return             Number of bytes needed to encode as UTF-8.
 */
EXTERNRT int rtUTF8CharSize (ASN132BITCHAR wc);

/** 
 * This function will convert a wide character into an encoded UTF-8 character
 * byte string.
 *
 * @param wc           32-bit wide character value.
 * @param buf          Buffer to receive encoded UTF-8 character value.
 * @param bufsiz       Size of the buffer ot receive the encoded value.
 * @return             Completion status of operation:
 *                       - 0 (ASN_OK) = success,
 *                       - negative return value is error.
 */
EXTERNRT int rtUTF8EncodeChar (ASN132BITCHAR wc, ASN1OCTET* buf, int bufsiz);

EXTERNRT int rtUTF8DecodeChar (ASN1CTXT* pCtxt, 
                               ASN1UTF8String pinbuf, 
                               int* pInsize);

/** 
 * This function creates a duplicate copy of the given UTF-8 character string.
 * It is similar to the C \c strdup function. Memory for the duplicated string
 * is allocated using the \c rtxMemAlloc function.
 *
 * @param pctxt        A pointer to a context structure.
 * @param utf8str      Null-terminated UTF-8 string to be duplicated.
 * @return             Pointer to duplicated string value.
 */
EXTERNRT char* rtUTF8Strdup (ASN1CTXT* pctxt, ASN1UTF8String utf8str);

/** 
 * This function creates a duplicate copy of the given UTF-8 character string.
 * It is similar to the \c rtUTF8Strdup function except that it allows the
 * number of bytes to convert to be specified. Memory for the duplicated string
 * is allocated using the \c rtMemAlloc function.
 *
 * @param pctxt        A pointer to a context structure.
 * @param utf8str      UTF-8 string to be duplicated.
 * @param nbytes       Number of bytes from \c utf8str to duplicate.
 * @return             Pointer to duplicated string value.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT char* rtUTF8Strndup (ASN1CTXT* pctxt, 
                              ASN1UTF8String utf8str, 
                              int nbytes);
#endif	/* !NO_ASN1_RT_REDUNDANT */
#endif /* CSP_LITE */
/**
 * @} charstrcon
 */

/* BigInt functions */

/**
 * @defgroup bigintf Big Integer Helper Functions 
 * @{
 *
 * Arbitrary-precision integer manipulating functions are used to maintain big
 * integers used within the ASN.1 run-time functions. Big integer variables are
 * passed in and out of ASN.1 C encode and decode functions as character
 * strings. Internally, a special structure is used for performing an
 * arbitrary-precision match.
 */

/**
 * This function initializes a big integer structure. This function should be
 * called before the first use of the big integer.
 *
 * @param pInt         A pointer to the big integer structure to be
 *                       initialized.
 */
EXTERNRT void rtBigIntInit (ASN1BigInt* pInt);

/**
 * This function converts the character string to a big integer structure. The
 * string might contain the prefix to indicate the radix ('0x' - 16, '0o' - 8,
 * '0b' - 2, otherwise 10). In this case the radix argument should be set to 0.
 *
 * @param pCtxt        A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pInt         A pointer to the big integer structure onto which the
 *                       value is to be stored. A pointer to an updated big
 *                       integer structure.
 * @param value        A pointer to a character string to be converted.
 * @param radix        The base value of pString. Must be 0, 2, 8, 10 or 16. If
 *                       radix is 0 then the radix will be set according to
 *                       string prefix ('0x' - 16, '0o' - 8, '0b' - 2,
 *                       otherwise 10).
 * @return             The status value of the operation.
 */
EXTERNRT int  rtBigIntSetStr (ASN1CTXT* pCtxt, ASN1BigInt* pInt, 
                             ASN1ConstCharPtr value, int radix);

/**
 * This function converts the ASNINT64 value to a big integer structure. An
 * ASN1INT64 type is a 64-bit integer if the platform supports 64-bit integers.
 * In the other case, it will be a 32-bit integer.
 *
 * @param pCtxt        A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pInt         A pointer to the big integer structure onto which the
 *                       value is to be stored. A pointer to an updated big
 *                       integer structure.
 * @param value        A pointer to a character string to be converted.
 * @return             The status value of the operation.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT int  rtBigIntSetInt64 
   (ASN1CTXT* pCtxt, ASN1BigInt* pInt, ASN1INT64 value);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function translates an octet array containing the two's complement
 * binary representation of an arbitrary-precision integer into a bigger
 * structure. The input array is assumed to be in big-endian octet-order: the
 * most significant octet is in the zeroth element.
 *
 * @param pCtxt        A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pInt         A pointer to the big integer structure onto which the
 *                       value is to be stored. A pointer to an updated big
 *                       integer structure.
 * @param vallen       The length of the array.
 * @param value        The pointer to an octet array with two's complement
 *                       binary representation of an arbitrary-precision
 *                       integer.
 * @return             The status value of the operation.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT int  rtBigIntSetBytes (ASN1CTXT* pCtxt, ASN1BigInt* pInt, 
                                 ASN1OCTET* value, int vallen);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function returns the number of octets necessary for storing a big
 * integer value in the octet array. This function may be used for calculating
 * the necessary buffer size for the rtBigIntGetData.
 *
 * @param pInt         A pointer to the big integer structure onto which the
 *                       value is to be stored.
 * @return             The number of octets, necessary for storing a big
 *                       integer value in the octet string.
 */
EXTERNRT int  rtBigIntGetDataLen (ASN1BigInt* pInt);

/**
 * This function copies the two's complement binary representation of a big
 * integer into an octet string. The output will be in big-endian octet-order:
 * the most significant octet will be in the zeroth element.
 *
 * @param pCtxt        A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pInt         A pointer to the big integer structure.
 * @param buffer       A pointer to an octet array to receive the two's
 *                       complement binary representation of a
 *                       arbitrary-precision integer.
 * @param bufSize      The length of an octet array.
 * @return             The status value of the operation.
 */
EXTERNRT int  rtBigIntGetData 
   (ASN1CTXT* pCtxt, ASN1BigInt* pInt, ASN1OCTET* buffer, int bufSize);

/**
 * This function returns the approximate number of digits of the big integer
 * value according to the specified radix. This function may be used to
 * calculate the size of the buffer for the rtBigIntToString function. The
 * number of digits might be slightly greater than really necessary, but never
 * less.
 *
 * @param pInt         A pointer to a big integer structure.
 * @param radix        The base of value. Must be 2, 8, 10, or 16.
 * @return             The approximated number of digits of the big integer.
 */
EXTERNRT int  rtBigIntDigitsNum (ASN1BigInt* pInt, int radix);

/**
 * This function copies one big integer structure into another one. The
 * destination big integer structure should not be initialized yet.
 *
 * @param pCtxt        A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pSrc         The source big integer value to copy.
 * @param pDst         The destination big integer value to receive the copied
 *                       value. This should not be initialized.
 * @return             The status value of the operation.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT int  rtBigIntCopy 
   (ASN1CTXT* pCtxt, const ASN1BigInt* pSrc, ASN1BigInt* pDst);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function copies one big structure into another one. The destination big
 * integer structure should be initialized before use of this function. This
 * function might be faster than rtBigIntCopy because if the destination big
 * integer already has enough allocated memory then memory will be reused
 * without allocation.
 *
 * @param pCtxt        A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pSrc         The source big integer value to copy.
 * @param pDst         The destination big integer value to receive the copied
 *                       value. This should be initialized.
 * @return             The status value of the operation.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT int  rtBigIntFastCopy 
   (ASN1CTXT* pCtxt, ASN1BigInt* pSrc, ASN1BigInt* pDst);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function converts a big integer to a string according to the specified
 * radix.
 *
 * @param pCtxt        A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pInt         A pointer to a big integer structure to be converted
 *                       into a string.
 * @param radix        A base value for conversion. It must be 2, 8, 10, or 16.
 * @param strSize      The size of str.
 * @param str          A pointer to the buffer to receive the converted
 *                       character string.
 * @return             The status value of the operation.
 */
EXTERNRT int  rtBigIntToString (ASN1CTXT* pCtxt, ASN1BigInt* pInt, int radix, 
                               char* str, int strSize);

/**
 * This function prints a big integer value to standard output (stdout),
 * according to the specified radix. In general, this function is very similar
 * to the rtBigIntToString function. It simply prints the output value to
 * standard output in a "name = value" format.
 *
 * @param name         The name of the variable to print.
 * @param bigint       The big integer value to print.
 * @param radix        The base value for conversion to print. It must be 2, 8,
 *                       10, or 16.
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT int  rtBigIntPrint 
   (ASN1ConstCharPtr name, ASN1BigInt* bigint, int radix);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function compares two big integer values. The result of comparison can
 * be -1 (first value less than the second one), 0 (both values are equal), and
 * 1 (the first value is greater than the second one).
 *
 * @param arg1         The first big integer value to compare.
 * @param arg2         The second big integer value to compare.
 * @return             The result of the comparison (-1, 0, 1).
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT int  rtBigIntCompare (const ASN1BigInt* arg1, const ASN1BigInt* arg2);
#endif	/* !NO_ASN1_RT_REDUNDANT */

/**
 * This function compares two big integer values, which are represented as
 * strings. The strings might contain prefixes to indicate the actual radix of
 * the big integer value ('0x' - 16, '0o' - 8, '0b' - 2, otherwise 10). The
 * result of comparison can be -1 (first value less than the second one), 0
 * (both values are equal), and 1 (the first value is greater than the second
 * one).
 *
 * @param pCtxt        A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param arg1         The first big integer value to compare.
 * @param arg2         The second big integer value to compare.
 * @return             The result of the comparison (-1, 0, 1).
 */
EXTERNRT int  rtBigIntStrCompare (ASN1CTXT* pCtxt, ASN1ConstCharPtr arg1, 
                                  ASN1ConstCharPtr arg2);

/**
 * This function releases memory if it was called for the current big integer.
 * If the memory was not allocated or static memory was used, this function
 * does nothing. It is recommended to not use the big integer structure after
 * the rtBigIntFree is invoked for it.
 *
 * @param pCtxt        A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param pInt         A pointer to a big integer structure that will be freed.
 */
EXTERNRT void rtBigIntFree (ASN1CTXT* pCtxt, ASN1BigInt* pInt);

/**
 * @}
 */
/* deprecated names of some rtBigInt* functions */

#define rtSetStrToBigInt   rtBigIntSetStr

#define rtGetBigIntLen     rtBigIntGetDataLen
#define rtGetBigInt        rtBigIntGetData

#if !defined NO_ASN1_RT_REDUNDANT
#define rtSetInt64ToBigInt rtBigIntSetInt64
#define rtSetBytesToBigInt rtBigIntSetBytes
#define rtPrintBigInt      rtBigIntPrint
#define rtCompareBigInt    rtBigIntCompare
#endif	/* !NO_ASN1_RT_REDUNDANT */

#define rtCompareBigIntStr rtBigIntStrCompare


/**
 * @defgroup timeutilf Time Helper Functions 
 * @{ 
 * These are helper functions for work with time strings in different formats.
 * rtMake* functions create time strings, rtParse* ones parse time string into
 * the C structure OSDATETIME. There are implementations of these functions for
 * ASN.1 GeneralizedTime, UTCTime and XML dateTime formats.
 */

/**
 * This function creates a time string in ASN.1 GeneralizedTime format as
 * specified in the X.680 ITU-T standard.
 *
 * @param pctxt        A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param dateTime     A pointer to the OSDATETIME structure, that contains
 *                       components of the date and time.
 * @param outdata      A pointer to a pointer to a destination string. If
 *                       outdataSize is non-zero, it should be a pointer to a
 *                       pointer to an actual array. Otherwise, the memory will
 *                       be allocated and the pointer will be stored in the \c
 *                       outdata.
 * @param outdataSize  A size of outdata (in octets). If zero, the memory for
 *                       the \c outdata will be allocated. If not, the \c
 *                       outdata 's size should be big enough to receive the
 *                       generated time string. Otherwise, error code will be
 *                       returned.
 * @return             Completion status of operation:
 *                       - 0 (ASN_OK) = success,
 *                       - negative return value is error.
 */
EXTERNRT int rtMakeGeneralizedTime (ASN1CTXT* pctxt, 
                                    const OSDATETIME* dateTime,
                                    char** outdata, 
                                    int outdataSize);

/**
 * This function creates a time string in ASN.1 UTCTime format as specified in
 * the X.680 ITU-T standard.
 *
 * @param pctxt        A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param dateTime     A pointer to the OSDATETIME structure, that contains
 *                       components of the date and time.
 * @param outdata      A pointer to a pointer to a destination string. If
 *                       outdataSize is non-zero, it should be a pointer to a
 *                       pointer to an actual array. Otherwise, the memory will
 *                       be allocated and the pointer will be stored in the \c
 *                       outdata.
 * @param outdataSize  A size of outdata (in octets). If zero, the memory for
 *                       the \c outdata will be allocated. If not, the \c
 *                       outdata 's size should be big enough to receive the
 *                       generated time string. Otherwise, error code will be
 *                       returned.
 * @return             Completion status of operation:
 *                       - 0 (ASN_OK) = success,
 *                       - negative return value is error.
 */
EXTERNRT int rtMakeUTCTime (ASN1CTXT* pctxt, 
                            const OSDATETIME* dateTime,
                            char** outdata, 
                            int outdataSize);
         
/**
 * This function creates a time string in XML dateTime format as specified in
 * the XML schema W3C Recommendation.
 *
 * @param pctxt        A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param dateTime     A pointer to the OSDATETIME structure, that contains
 *                       components of the date and time.
 * @param outdata      A pointer to a pointer to a destination string. If
 *                       outdataSize is non-zero, it should be a pointer to a
 *                       pointer to an actual array. Otherwise, the memory will
 *                       be allocated and the pointer will be stored in the \c
 *                       outdata.
 * @param outdataSize  A size of outdata (in octets). If zero, the memory for
 *                       the \c outdata will be allocated. If not, the \c
 *                       outdata 's size should be big enough to receive the
 *                       generated time string. Otherwise, error code will be
 *                       returned.
 * @return             Completion status of operation:
 *                       - 0 (ASN_OK) = success,
 *                       - negative return value is error.
 */
EXTERNRT int rtMakeXmlDateTime (ASN1CTXT* pctxt, const OSDATETIME* dateTime,
                                char** outdata, int outdataSize);
         
/**
 * This function parses a time string that is represented in ASN.1
 * GeneralizedTime format as specified in the X.680 ITU-T standard. It stores
 * the parsing result in OSDATETIME C structure.
 *
 * @param pctxt        A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param value        A pointer to the time string to be parsed.
 * @param dateTime     A pointer to the destination OSDATETIME structure.
 * @return             Completion status of operation:
 *                       - 0 (ASN_OK) = success,
 *                       - negative return value is error.
 */
EXTERNRT int rtParseGeneralizedTime (ASN1CTXT *pctxt, 
                                     ASN1ConstCharPtr value, 
                                     OSDATETIME* dateTime);

/**
 * This function parses a time string that is represented in ASN.1 UTCTime
 * format as specified in the X.680 ITU-T standard. It stores the parsing
 * result in OSDATETIME C structure.
 *
 * @param pctxt        A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param value        A pointer to the time string to be parsed.
 * @param dateTime     A pointer to the destination OSDATETIME structure.
 * @return             Completion status of operation:
 *                       - 0 (ASN_OK) = success,
 *                       - negative return value is error.
 */
EXTERNRT int rtParseUTCTime (ASN1CTXT *pctxt, 
                             ASN1ConstCharPtr value, 
                             OSDATETIME* dateTime);

/**
 * This function parses a time string that is represented in XML dateTime
 * format as specified in the XML schema W3C Recommendation. It stores the
 * parsing result in OSDATETIME C structure.
 *
 * @param pctxt        A pointer to a context structure. This provides a
 *                       storage area for the function to store all working
 *                       variables that must be maintained between function
 *                       calls.
 * @param value        A pointer to the time string to be parsed.
 * @param dateTime     A pointer to the destination OSDATETIME structure.
 * @return             Completion status of operation:
 *                       - 0 (ASN_OK) = success,
 *                       - negative return value is error.
 */
EXTERNRT int rtParseXmlDateTime (ASN1CTXT *pctxt, 
                                 ASN1ConstCharPtr value, 
                                 OSDATETIME* dateTime);
/**
 * @} timeutilf
 */

/* file functions */

/**
 * This function reads the entire contents of a binary file into memory. A
 * memory buffer is allocated for the file contents using the ASN1C run-time
 * memory management functions.
 *
 * @param pctxt        Pointer to context block structure.
 * @param filePath     Complete file path name of file to read.
 * @param ppMsgBuf     Pointer to message buffer to receive allocated memory
 *                       pointer.
 * @param pLength      Pointer to integer to receive length of data read.
 * @return             Completion status of operation:
 *                       - 0 (ASN_OK) = success,
 *                       - ASN_E_FILNOTFOU = file not found
 *                       - ASN_E_FILEREAD = file read error (see errno)
 */
#if !defined NO_ASN1_RT_REDUNDANT
EXTERNRT int rtFileReadBinary (ASN1CTXT* pctxt, ASN1ConstCharPtr filePath, 
                               ASN1OCTET** ppMsgBuf, int* pLength);
#endif	/* !NO_ASN1_RT_REDUNDANT */

#ifdef __cplusplus
}
#endif

#if defined (ACVERSION) && ACVERSION <= 530
#include<asn1intl.h>
#endif

#include<rtMemory.h>

#endif 

