#ifndef _TSPCLI_H_INCLUDED
#define _TSPCLI_H_INCLUDED

#if defined _WIN32
#   include <prsht.h>
#endif	/* _WIN32 */
#include <list>
#include <cplib/DateTime.h>
#include <cplib/Blob.h>

#if !defined CPTSPCLI_DEFINES
#   define CPTSPCLI_DEFINES
#   if defined _WIN32 && !defined CRYPTCP && !defined TSPCLI_STATIC
#	ifdef _CPTSPCLIDLL
#	    define TSPCLI_CLASS __declspec(dllexport)
#	else
#	    define TSPCLI_CLASS __declspec(dllimport)
#	    ifndef CP_IGNORE_PRAGMA_MANIFEST
#	        include "pki_tsp_client_assembly.h"
#	        ifdef _WIN64
#	            pragma comment(linker,"/manifestdependency:\"type='win32' " \
 	            "name='" PKI_TSP_CLIENT_ASSEMBLY_NAME_X64 "' " \
 	            "version='" PKI_TSP_CLIENT_ASSEMBLY_VERSION_X64 "' " \
 	            "processorArchitecture='amd64' " \
 	            "language='*' " \
 	            "publicKeyToken='" PKI_TSP_CLIENT_ASSEMBLY_PUBLICKEYTOKEN_X64 "'\"")
#	        else
#	            pragma comment(linker,"/manifestdependency:\"type='win32' " \
 	            "name='" PKI_TSP_CLIENT_ASSEMBLY_NAME_X86 "' " \
 	            "version='" PKI_TSP_CLIENT_ASSEMBLY_VERSION_X86 "' " \
 	            "processorArchitecture='x86' " \
 	            "language='*' " \
 	            "publicKeyToken='" PKI_TSP_CLIENT_ASSEMBLY_PUBLICKEYTOKEN_X86 "'\"")
# 	        endif
#	    endif
#	endif // _CPTSPDLL
#   else
#      define TSPCLI_CLASS
#   endif  /* _WIN32 */
#endif /* CPTSPCLI_DEFINES */

typedef enum {
    TSPCLI_SKIP_IE_PROXY_CONFIGURATION = 0x1
} TSPCLI_FLAGS;

namespace CryptoPro {
namespace PKI {
namespace TSP {
namespace Client {

class CRequest;

class TSPCLI_CLASS CStamp
{
public:
    CStamp(void);
    ~CStamp(void);

    // Копирование
    CStamp(const CStamp& Stamp);
    CStamp& operator= (const CStamp& Stamp);

    void Export(unsigned char *pbContent, unsigned long *pdwLen) const;
    void Import(const unsigned char *pbContent, unsigned long dwLen,
	const CRequest *Request = NULL);
    int Compare(const CStamp *Stamp) const;
    HCERTSTORE get_Certificates() const;
    PCCERT_CONTEXT get_TSACertificate(HCERTSTORE *Stores = NULL,
	unsigned long StoresNumber = 0) const;
    int Verify(PCCERT_CONTEXT pCert = NULL,
	char *AllowedCriticalExtensions = NULL) const;
    int VerifyCertificate(PCCERT_CONTEXT pCert = NULL,
	HCERTSTORE *Stores = NULL, unsigned long StoresNumber = 0) const;

    unsigned int get_FailInfo() const;
    unsigned int get_Status() const;
    const wchar_t* get_StatusString() const;

    ALG_ID get_DataHashAlg() const;
    const char * get_DataHashAlgOID() const;
    void get_DataHash(unsigned char *pbContent, unsigned long *pdwLen) const;

    const char * get_PolicyID() const;
    void get_SerialNumber(unsigned char *pbContent, unsigned long *pdwLen) const;
    const CDateTime& get_Time() const;
    long get_Accuracy() const;
    bool get_Ordering() const;
    bool get_HasNonce() const;
    const wchar_t* get_TSA() const;
    void get_TSABlob(unsigned char *pbContent, unsigned long *pdwLen) const;

    void put_DefaultAccuracy(long Value);
    long get_DefaultAccuracy() const;

#if defined _WIN32
    void Display(HWND hWnd = 0, const wchar_t *Title = NULL) const;
    HPROPSHEETPAGE get_PropPage() const;
#endif	/* _WIN32 */

private:
    void clear();
    class Impl;
    Impl *pImpl;
};

class TSPCLI_CLASS CRequest
{
public:
    enum enumAuthTypes
    {
	atAnonymous	= 0x00,
	atBasic		= 0x01,
	atNTLM		= 0x02,
	atDigest	= 0x08,
	atNegotiate	= 0x10
    };

    CRequest(void);
    ~CRequest(void);

    // Копирование
    CRequest(const CRequest& Stamp);
    CRequest& operator= (const CRequest& Stamp);

    void AddData(const unsigned char *pbData, unsigned long dwLen);
    void ResetData();
    void Export(unsigned char *pbContent, unsigned long *pdwLen);
    void Import(unsigned char *pbContent, unsigned long dwLen);

    void put_CertReq(bool Value);
    bool get_CertReq() const;

    void put_UseNonce(bool Value);
    bool get_UseNonce() const;

    void put_PolicyID(const wchar_t *Value);
    void put_PolicyID(const char *Value);
    const char * get_PolicyID() const;

    void put_DataHashAlg(ALG_ID HashAlgorithm);
    void put_DataHashAlg(const wchar_t *HashAlgorithmOID);
    void put_DataHashAlg(const char *HashAlgorithmOID);
    ALG_ID get_DataHashAlg() const;
    const char * get_DataHashAlgOID() const;

    void put_DataHash(const unsigned char *pbContent, unsigned long dwLen);
    void get_DataHash(unsigned char *pbContent, unsigned long *pdwLen) const;

    void put_TSAAuthType(enumAuthTypes Value);
    enumAuthTypes get_TSAAuthType() const;

    void put_TSAAddress(const wchar_t *Value);
    const wchar_t* get_TSAAddress() const;

    void put_TSAUserName(const wchar_t *Value);
    const wchar_t* get_TSAUserName() const;

    void put_TSAPassword(const wchar_t *Value);
    const wchar_t* get_TSAPassword() const;

    void put_ClientCertificate(PCCERT_CONTEXT Value);
    PCCERT_CONTEXT get_ClientCertificate() const;

    void put_ProxyAuthType(enumAuthTypes Value);
    enumAuthTypes get_ProxyAuthType() const;

    void put_ProxyAddress(const wchar_t *Value);
    const wchar_t* get_ProxyAddress() const;

    void put_ProxyUserName(const wchar_t *Value);
    const wchar_t* get_ProxyUserName() const;

    void put_ProxyPassword(const wchar_t *Value);
    const wchar_t* get_ProxyPassword() const;

    void put_Flags(DWORD dwFlags);
    DWORD get_Flags() const;

    CStamp& Send(bool Verify = true);
    CBlob get_Response() const;
    unsigned long get_HTTPStatus() const;

    friend void CStamp::Import(const unsigned char *, unsigned long,
	const CRequest *);

#if defined _WIN32
    void Display(HWND hWnd = 0, const wchar_t *Title = NULL) const;
    HPROPSHEETPAGE get_PropPage() const;
#endif	/* _WIN32 */

private:
    void clear();
    class Impl;
    Impl *pImpl;
};

} // namespace Client
} // namespace TSP
} // namespace PKI
} // namespace CryptoPro

#endif // _TSPCLI_H_INCLUDED

