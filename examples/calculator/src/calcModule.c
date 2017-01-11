#include <stdio.h>
#include <stdlib.h>

#include "calc.h"
#include "../../../src/module.h"
#include "../../../lib/linkedListLibrary/src/linkedList.h"

#define CALC_MODULE_NAME "calculator"
#define CALC_MODULE_VERSION_MAJOR 0
#define CALC_MODULE_VERSION_MINOR 0

tcore_Metadata *calc_module;

int onLoad() {
    // build calc_module
	calc_module = malloc(sizeof(tcore_Metadata));
	calc_module->name = CALC_MODULE_NAME;
	calc_module->version.major = CALC_MODULE_VERSION_MAJOR;
	calc_module->version.minor = CALC_MODULE_VERSION_MINOR;
	calc_module->dependencies = lll_newList();
	calc_module->interfaces = lll_newList();

	// interfaces
	// addition
	tcore_Interface *additionInterface = calloc(1, sizeof(tcore_Interface));
	additionInterface->name = "addition";
	additionInterface->prototype = "int addition (int, int)";
	additionInterface->man = "int addition (int x, int y)\n\
\tint x\tThe first number.\n\
\tint y\tThe second number.\n\
\treturns\tThe two numbers added.\n";
    additionInterface->function = (void (*) ())addition;
	lll_add(calc_module->interfaces, additionInterface);

	return SUCCESS;
}

tcore_Metadata* getMetadata(){
	return calc_module;
}

int onActivation(tcore_Interface* (*getInterface)(const char*, int, const char*)){
	return SUCCESS;
}

int onDeactivation(){
	return SUCCESS;
}

int onUnload(){
    lll_freeList(calc_module->dependencies);
    void *additionInterface = NULL;
    lll_elementAtIndex(calc_module->interfaces, 0, &additionInterface);
    lll_removeAtIndex(calc_module->interfaces, 0);
    free(additionInterface);
    lll_freeList(calc_module->interfaces);
    free(calc_module);
    calc_module = NULL;
	return SUCCESS;
}
