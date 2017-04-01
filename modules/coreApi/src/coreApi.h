#ifndef _CORE_API_H_
#define _CORE_API_H_

#include "linkedList.h"
#include "function.h"
#include "core.h"

#define TCA_MODULE_NAME "coreApi"
#define TCA_MODULE_VERSION_MAJOR 0
#define TCA_MODULE_VERSION_MINOR 0

void tca_setPool(tc_ModulePool *pool);
int tca_getIsActive(void);
void tca_shutdown(void);
int tca_getFunction(const char*, int, const char*, tmf_Function*);

int tca_loadModule(const char*);
int tca_unloadModule(int);

#endif /* _CORE_API_H_ */
