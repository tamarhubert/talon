#include <stdio.h>
#include <stdlib.h>

#include "calc.h"
#include "../../core/module.h"
#include "../../lib/lll/LinkedList.h"

#define MODULE_NAME "calculator"
#define MODULE_VERSION_MAJOR 0
#define MODULE_VERSION_MINOR 0

#define ABORT 2
#define WARNING 1
#define SUCCESS 0

tcore_ModuleDefinition *module;

int onLoad() {
    // build module
	module = malloc(sizeof(tcore_ModuleDefinition));
	module->name = MODULE_NAME;
	module->version.major = MODULE_VERSION_MAJOR;
	module->version.minor = MODULE_VERSION_MINOR;
	module->dependencies = malloc(sizeof(lll_List));
	module->interfaces = malloc(sizeof(lll_List));

	// addition
	tcore_Interface *additionInterface = malloc(sizeof(tcore_Interface));
	additionInterface->name = "addition";
	additionInterface->man = "int addition (int x, int y)\n\
			\tint x\tThe first number.\n\
			\tint y\tThe second number.\n\
			\treturns\tThe two numbers added.\n";		
	additionInterface->function = (void (*) ())addition;
	lll_Element *additionElement = malloc(sizeof(lll_Element));
	additionElement->value = additionInterface;
	lll_add(module->interfaces, additionElement);

	return SUCCESS;
}

tcore_ModuleDefinition* getDefinition(){
	return module;
}

int init(){
	return SUCCESS;
}

int deinit(){
	return SUCCESS;
}

int onUnload(){
    free(module->dependencies);
    lll_Element *additionElement = lll_elementAtIndex(*module->interfaces, 0);
    free(additionElement->value);
    free(additionElement);
    free(module->interfaces);
    free(module);
    module = NULL;
	return SUCCESS;
}


