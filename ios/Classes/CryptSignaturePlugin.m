#import "CryptSignaturePlugin.h"
#if __has_include(<crypt_signature/crypt_signature-Swift.h>)
#import <crypt_signature/crypt_signature-Swift.h>
#else
// Support project import fallback if the generated compatibility header
// is not copied when this plugin is created as a library.
// https://forums.swift.org/t/swift-static-libraries-dont-copy-generated-objective-c-header/19816
#import "crypt_signature-Swift.h"
#endif

@implementation CryptSignaturePlugin
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  [SwiftCryptSignaturePlugin registerWithRegistrar:registrar];
}
@end
