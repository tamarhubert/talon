#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "../../../src/module.h"
#include "../../../lib/linkedListLibrary/src/linkedList.h"

#define CLI_MODULE_NAME "cli"
#define CLI_MODULE_VERSION_MAJOR 0
#define CLI_MODULE_VERSION_MINOR 0

tcore_Metadata *cli_module;

int onLoad() {
    // build cli_module
	cli_module = malloc(sizeof(tcore_Metadata));
	cli_module->name = CLI_MODULE_NAME;
	cli_module->version.major = CLI_MODULE_VERSION_MAJOR;
	cli_module->version.minor = CLI_MODULE_VERSION_MINOR;
	cli_module->dependencies = lll_newList();
	cli_module->interfaces = lll_newList();

	// cli
	tcore_Interface *cliInterface = malloc(sizeof(tcore_Interface));
	cliInterface->name = "cli";
	cliInterface->prototype = "void cli (void)";
	cliInterface->man = "void cli (void)\n\
\tAllows execution of other cli_modules interfaces.\n";		
	cliInterface->function = (void (*) ())cli;
	lll_add(cli_module->interfaces, cliInterface);

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
    lll_freeList(cli_module->dependencies);
    void *cliInterface = NULL;
    lll_elementAtIndex(cli_module->interfaces, 0, &cliInterface);
    lll_removeAtIndex(cli_module->interfaces, 0);
    free(cliInterface);
    lll_freeList(cli_module->interfaces);
    free(cli_module);
    cli_module = NULL;
	return SUCCESS;
}


