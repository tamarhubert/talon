#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "../../core/module.h"
#include "../../lib/linkedListLibrary/LinkedList.h"

#define MODULE_NAME "cli"
#define MODULE_VERSION_MAJOR 0
#define MODULE_VERSION_MINOR 0

#define ABORT 2
#define WARNING 1
#define SUCCESS 0

tcore_ModuleDefinition *module;

int onLoad() {
    printf("loading cli module\n");

    // build module
	module = malloc(sizeof(tcore_ModuleDefinition));
	module->name = MODULE_NAME;
	module->version.major = MODULE_VERSION_MAJOR;
	module->version.minor = MODULE_VERSION_MINOR;
	module->dependencies = malloc(sizeof(lll_List));
	module->interfaces = malloc(sizeof(lll_List));

	// cli
	tcore_Interface *cliInterface = malloc(sizeof(tcore_Interface));
	cliInterface->name = "cli";
	cliInterface->prototype = "void cli (void)";
	cliInterface->man = "void cli (void)\n\
\tAllows execution of other modules interfaces.\n";		
	cliInterface->function = (void (*) ())cli;
	lll_Element *cliElement = malloc(sizeof(lll_Element));
	cliElement->value = cliInterface;
	lll_add(module->interfaces, cliElement);

	return SUCCESS;
}

tcore_ModuleDefinition* getDefinition(){
	return module;
}

int activate(tcore_Interface* (*_getInterface)(const char*, int, const char*)){
    printf("activating cli module\n");
    setResolver(_getInterface);
	return SUCCESS;
}

int deactivate(){
    printf("deactivating cli module\n");
	return SUCCESS;
}

int onUnload(){
    printf("unloading cli module\n");
    free(module->dependencies);
    lll_Element *cliElement = lll_elementAtIndex(*module->interfaces, 0);
    free(cliElement->value);
    free(cliElement);
    free(module->interfaces);
    free(module);
    module = NULL;
	return SUCCESS;
}


