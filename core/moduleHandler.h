#include "module.h"

#ifndef _MODULE_HANDLER_H_
#define _MODULE_HANDLER_H_

#define MH_ON_LOAD "onLoad"
#define MH_INIT "init"
#define MH_DEFINITION "getDefinition"
#define MH_DEINIT "deinit"
#define MH_ON_UNLOAD "onUnload"

typedef struct tcore_Module tcore_Module;

struct tcore_Module {
    void* handle;
	int (*init) ();
	tcore_ModuleDefinition* (*getDefinition) ();
	int (*deinit) ();
};

tcore_Module* loadModule(const char*);
int unloadModule(tcore_Module*);

#endif /* _MODULE_HANDLER_H_ */
