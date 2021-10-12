#include<support.h>

int DisableIntegrityCheck(){
    return support_registry_put_bool("\\config\\Parameters\\DisableIntegrity", 1);
}
