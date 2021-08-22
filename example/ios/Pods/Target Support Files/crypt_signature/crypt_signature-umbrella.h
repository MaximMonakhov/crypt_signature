#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "CryptSignature-Bridging-Header.h"
#import "CryptSignaturePlugin.h"
#import "Wrapper.h"

FOUNDATION_EXPORT double crypt_signatureVersionNumber;
FOUNDATION_EXPORT const unsigned char crypt_signatureVersionString[];

