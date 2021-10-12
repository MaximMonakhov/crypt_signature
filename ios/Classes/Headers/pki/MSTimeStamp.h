#ifndef _MSTIMESTAMP_H_INCLUDED
#define _MSTIMESTAMP_H_INCLUDED

#ifdef __cplusplus
extern "C" {

namespace CryptoPro {
namespace PKI {
namespace TSP {
namespace Client {
#endif

extern CRYPT_DATA_BLOB *GetMSStamp(CRYPT_DATA_BLOB *Signature,
    const wchar_t *Address = NULL, CRYPT_ATTRIBUTES *AuthAttributes = NULL);
extern CSP_BOOL FreeMSStamp(CRYPT_DATA_BLOB *Stamp);

#ifdef __cplusplus
} // namespace Client
} // namespace TSP
} // namespace PKI
} // namespace CryptoPro

}
#endif

#endif /* _MSTIMESTAMP_H_INCLUDED */
