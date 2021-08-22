
#ifndef _SSP_MAP_
#define _SSP_MAP_

typedef struct SCHANNEL_MAPPER_t SCHANNEL_MAPPER;

#ifdef WIN32
typedef HRESULT (WINAPI *MapperCreateInstanceFunc) (SCHANNEL_MAPPER ** pphMapper);
typedef DWORD (WINAPI *MapperReferenceMapperFunc) (SCHANNEL_MAPPER * pphMapper);
typedef DWORD (WINAPI *MapperDeReferenceMapperFunc) (SCHANNEL_MAPPER * pphMapper);
typedef DWORD (WINAPI *MapperMapCredentialFunc) (SCHANNEL_MAPPER * pphMapper, DWORD One, PCCERT_CONTEXT pCertContext, DWORD Reserved, HANDLE *phToken);
typedef DWORD (WINAPI *MapperGetIssuerListFunc) (SCHANNEL_MAPPER * pphMapper, DWORD Reserved1, DWORD Reserved2, void *);
typedef DWORD (WINAPI *MapperGetChallengeFunc) (SCHANNEL_MAPPER * pphMapper);
typedef DWORD (WINAPI *MapperGetAccessTokenFunc) (SCHANNEL_MAPPER * pphMapper, HANDLE hToken, HANDLE * phCopy);
typedef DWORD (WINAPI *MapperCloseLocatorFunc) (SCHANNEL_MAPPER * pphMapper, HANDLE hToken);
typedef DWORD (WINAPI *MapperQueryMappedCredentialAttributesFunc) (SCHANNEL_MAPPER * pphMapper, HANDLE hToken, DWORD unkn_1, HANDLE * phResult, DWORD * cbResult);

#define MAPPER_CREATE_INSTANCE_NAME "CreateInstance"

typedef struct SCHANNEL_MAPPER_FUNCS_t
{
    MapperReferenceMapperFunc	ReferenceMapper;
    MapperDeReferenceMapperFunc	DeReferenceMapper;
    MapperGetIssuerListFunc	GetIssuerList;
    MapperGetChallengeFunc	GetChallenge;
    MapperMapCredentialFunc	MapCredential;
    MapperGetAccessTokenFunc	GetAccessToken;
    MapperCloseLocatorFunc	CloseLocator;
    MapperQueryMappedCredentialAttributesFunc	QueryMappedCredentialAttributes;
} SCHANNEL_MAPPER_FUNCS;

#pragma warning (push)
#pragma warning( disable:4201)
struct SCHANNEL_MAPPER_t//модифицирую слегка для прозрачных колбэков
{
    SCHANNEL_MAPPER_FUNCS   * vtable;
    union
    {
	SCHANNEL_MAPPER*	    UserMapper;//сохраним юзермодный
	DWORD unused[2];//во втором лежат флаги валидации кредов сдвинутые до старшего байта.
    };
    ULONG_PTR	    nRef;
    ULONG_PTR	    unused2;
#if 0
    DWORD unused_a_00000003;
    DWORD unused_b_00000001;
    HMODULE MapperDll; /* "inetserv\\iiscrmap" */
    DWORD unused_c_00000001;
    DWORD unused_d_00000001;
#endif
};
#pragma warning (pop)


#ifdef _CP_SSP_AP_
SCHANNEL_MAPPER* 
WINAPI 
CreateLsaModeMapper(SCHANNEL_MAPPER* UserMapper);

DWORD WINAPI MyReferenceMapper 
		(SCHANNEL_MAPPER * pphMapper);
DWORD WINAPI MyDeReferenceMapper
		(SCHANNEL_MAPPER * pphMapper);
DWORD WINAPI MyGetIssuerList
		(SCHANNEL_MAPPER * pphMapper, DWORD Reserved1, DWORD Reserved2, void *);
DWORD WINAPI MyGetChallenge
		(SCHANNEL_MAPPER * pphMapper);
DWORD WINAPI MyMapCredential
		(SCHANNEL_MAPPER * pphMapper, DWORD One, PCCERT_CONTEXT pCertContext, DWORD Reserved, HANDLE *phToken);
DWORD WINAPI MyGetAccessToken
		(SCHANNEL_MAPPER * pphMapper, HANDLE hToken, HANDLE * phCopy);
DWORD WINAPI MyCloseLocator
		(SCHANNEL_MAPPER * pphMapper, HANDLE hToken);
DWORD WINAPI MyQueryMappedCredentialAttributes
		(SCHANNEL_MAPPER * pphMapper, HANDLE hToken, DWORD unkn_1, HANDLE * phResult, DWORD * cbResult);

SECURITY_STATUS
SEC_ENTRY
ReferenceMapperCallback(
			ULONG_PTR Argument1,
			ULONG_PTR Argument2,
			PSecBuffer InputBuffer,
			PSecBuffer OutputBuffer);
#define REFERENCE_MAPPER		64

SECURITY_STATUS
SEC_ENTRY
DeReferenceMapperCallback(
			ULONG_PTR Argument1,
			ULONG_PTR Argument2,
			PSecBuffer InputBuffer,
			PSecBuffer OutputBuffer);
#define DEREFERENCE_MAPPER		65

SECURITY_STATUS
SEC_ENTRY
MapCredentialCallback(
			ULONG_PTR Argument1,
			ULONG_PTR Argument2,
			PSecBuffer InputBuffer,
			PSecBuffer OutputBuffer);
#define MAP_CREDENTIAL			66

SECURITY_STATUS
SEC_ENTRY
GetAccessTokenCallback(
			ULONG_PTR Argument1,
			ULONG_PTR Argument2,
			PSecBuffer InputBuffer,
			PSecBuffer OutputBuffer);
#define GET_ACCESS_TOKEN		67

SECURITY_STATUS
SEC_ENTRY
CloseLocatorCallback(
			ULONG_PTR Argument1,
			ULONG_PTR Argument2,
			PSecBuffer InputBuffer,
			PSecBuffer OutputBuffer);
#define CLOSE_LOCATOR			68


#endif /*_CP_SSP_AP_*/
#endif // WIN32

#endif /* _SSP_MAP_ */

