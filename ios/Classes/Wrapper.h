//
//  Wrapper.h
//  KristaCrypt
//
//  Created by Кристофер Кристовский on 27.08.2020.
//  Copyright © 2020 Кристофер Кристовский. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "stdlib.h"
#import "stdio.h"

#ifdef __cplusplus
extern "C" {
#endif
bool initCSP(void);
NSString* addCertificate(NSString* path, NSString* password);
NSString* digest(NSString* alias, NSString* password, NSString* message);
NSString* sign(NSString* alias, NSString* password, NSString* digest);

#ifdef __cplusplus
}
#endif
