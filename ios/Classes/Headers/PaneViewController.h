//
//  PaneViewController.h
//  Pane
//
//  Created by Кондакова Татьяна Андреевна on 06.12.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#define CSP_BOOL CSP_CSP_BOOL
#include<reader/support.h>
#include<CSP_WinCrypt.h>
#undef CSP_BOOL

#define URL_RETRIEVER_TIMEOUT 60000

@protocol ModalViewControllerDelegate<NSObject>

-(void) didDismissModalView;

@end

OBJC_EXPORT
@interface PaneViewController : UIViewController<ModalViewControllerDelegate, UINavigationControllerDelegate> {
	__unsafe_unretained id<ModalViewControllerDelegate, UITableViewDelegate> delegate;
	bool needExitButton;
}
@property (nonatomic, weak) IBOutlet UITableView * tableView;
@property (nonatomic, weak) IBOutlet UILabel * label;
@property (nonatomic, assign) id<ModalViewControllerDelegate> delegate;

-(void)getCertificate;
-(void)deleteContainers;
-(void)installCerts;
-(void)downloadAndInstallCRLOrCertificate;
-(void)deletePasswords;
-(DWORD)processPKCS7Certificate:(HCERTSTORE)hStore numberOfInstalledCertificates:(int*)certsNumber numberOfInstalledCRLs:(int*)CRLsNumber;
-(DWORD)processSingleCertificateOrCRL:(CRYPT_DATA_BLOB)blob numberOfInstalledCertificates:(int*)certsNumber numberOfInstalledCRLs:(int*)CRLsNumber;
-(void)inputLicense;
-(DWORD)absorbKey:(HCRYPTKEY)hKey KeySpec:(DWORD)dwKeySpec providerType:(DWORD)dwProvType providerName:(char *)provName containerName:(char *)contName;
-(DWORD)absorbCont:(DWORD)provType providerName:(char *)provName containerName:(char *)contName;
-(void)didDismissModalView;
-(void)selfTest;
-(id)initWithNibName:(NSString*)aNibName bundle:(NSBundle*)aBundle needExitButton: (bool) needExitbutton;
+(bool)parseVersion:(char *) version_string version_out: (NSString **) ver_out build_out: (NSString **) build_out;

@end
