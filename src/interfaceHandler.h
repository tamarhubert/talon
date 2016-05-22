#ifndef _INTERFACES_HANDLER_H_
#define _INTERFACES_HANDLER_H_

#include "module.h"

int registerInterface(int id, tcore_Metadata *metadata);
int deregisterInterface(int id);
tcore_Interface* getInterface(const char* moduleName, int moduleVersion, const char* interfaceName);
lll_List* getAllRegisterdModules();

#endif /* _INTERFACES_HANDLER_H_ */
