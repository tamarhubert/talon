#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "../../../src/module.h"
#include "../../../lib/linkedListLibrary/src/linkedList.h"

#define cli_module_NAME "cli"
#define cli_module_VERSION_MAJOR 0
#define cli_module_VERSION_MINOR 0

#define ABORT 2
#define WARNING 1
#define SUCCESS 0

tcore_Metadata *cli_module;

int onLoad() {
    // build cli_module
	cli_module = malloc(sizeof(tcore_Metadata));
	cli_module->name = cli_module_NAME;
	cli_module->version.major = cli_module_VERSION_MAJOR;
	cli_module->version.minor = cli_module_VERSION_MINOR;
	cli_module->dependencies = malloc(sizeof(lll_List));
	cli_module->interfaces = malloc(sizeof(lll_List));

	// cli
	tcore_Interface *cliInterface = malloc(sizeof(tcore_Interface));
	cliInterface->name = "cli";
	cliInterface->prototype = "void cli (void)";
	cliInterface->man = "void cli (void)\n\
\tAllows execution of other cli_modules interfaces.\n";		
	cliInterface->function = (void (*) ())cli;
	lll_Element *cliElement = malloc(sizeof(lll_Element));
	cliElement->value = cliInterface;
	lll_add(cli_module->interfaces, cliElement);

	return SUCCESS;
}

tcore_Metadata* getMetadata(){
	return cli_module;
}

int onActivation(tcore_Interface* (*_getInterface)(const char*, int, const char*)){
    setResolver(_getInterface);
	return SUCCESS;
}

int onDeactivation(){
	return SUCCESS;
}

int onUnload(){
    free(cli_module->dependencies);
    lll_Element *cliElement = lll_elementAtIndex(*cli_module->interfaces, 0);
    free(cliElement->value);
    free(cliElement);
    free(cli_module->interfaces);
    free(cli_module);
    cli_module = NULL;
	return SUCCESS;
}


