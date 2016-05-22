#include <stdio.h>
#include <stdlib.h>

#include "calc.h"
#include "../../../src/module.h"
#include "../../../lib/linkedListLibrary/src/linkedList.h"

#define calc_module_NAME "calculator"
#define calc_module_VERSION_MAJOR 0
#define calc_module_VERSION_MINOR 0

#define ABORT 2
#define WARNING 1
#define SUCCESS 0

tcore_Metadata *calc_module;

int onLoad() {
    // build calc_module
	calc_module = malloc(sizeof(tcore_Metadata));
	calc_module->name = calc_module_NAME;
	calc_module->version.major = calc_module_VERSION_MAJOR;
	calc_module->version.minor = calc_module_VERSION_MINOR;
	calc_module->dependencies = calloc(1, sizeof(lll_List));
	calc_module->interfaces = calloc(1, sizeof(lll_List));

	// addition
	tcore_Interface *additionInterface = calloc(1, sizeof(tcore_Interface));
	additionInterface->name = "addition";
	additionInterface->prototype = "int addition (int, int)";
	additionInterface->man = "int addition (int x, int y)\n\
\tint x\tThe first number.\n\
\tint y\tThe second number.\n\
\treturns\tThe two numbers added.\n";		
	additionInterface->function = (void (*) ())addition;
	lll_Element *additionElement = malloc(sizeof(lll_Element));
	additionElement->value = additionInterface;
	lll_add(calc_module->interfaces, additionElement);

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
    free(calc_module->dependencies);
    lll_Element *additionElement = lll_elementAtIndex(*calc_module->interfaces, 0);
    free(additionElement->value);
    free(additionElement);
    free(calc_module->interfaces);
    free(calc_module);
    calc_module = NULL;
	return SUCCESS;
}


