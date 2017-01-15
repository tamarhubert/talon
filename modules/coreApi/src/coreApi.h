#ifndef _CORE_API_H_
#define _CORE_API_H_

#include "../../../lib/linkedListLibrary/src/linkedList.h"

int tcore_init(void);
int tcore_deinit(void);

int tcore_loadModule(const char*);
int tcore_unloadModule(int);
int tcore_getModules(lll_List**);

#endif /* _CORE_API_H_ */
