/*
 *
 *  Created by Кондакова Татьяна Андреевна on 09.12.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include <vector>
#include <string>
#include<WinCryptEx.h>

#ifdef __cplusplus
extern "C" {
#endif
unsigned int deletecert(void);
unsigned int delete_gost2001_containers(void);
#ifdef __cplusplus
}
#endif

DWORD EnumCerts(std::vector<std::string>& RDN, std::vector<std::string>& notBefore, 
      std::vector<std::string>& notAfter, std::vector<std::string>& thumbprint );

