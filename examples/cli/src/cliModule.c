#include <stdio.h>
#include <stdlib.h>

#include "cli.h"
#include "../../../src/module.h"
#include "../../../lib/linkedListLibrary/src/linkedList.h"
#include "../../../lib/threadingProcessingLibrary/src/threadingProcessingLibrary.h"

#define CLI_MODULE_NAME "cli"
#define CLI_MODULE_VERSION_MAJOR 0
#define CLI_MODULE_VERSION_MINOR 0

tcore_Metadata *cli_module;
tpl_Thread *cli_thread;

int onLoad() {
    // build cli_module
	cli_module = malloc(sizeof(tcore_Metadata));
	cli_module->name = CLI_MODULE_NAME;
	cli_module->version.major = CLI_MODULE_VERSION_MAJOR;
	cli_module->version.minor = CLI_MODULE_VERSION_MINOR;
	cli_module->dependencies = lll_newList();
	cli_module->interfaces = lll_newList();

	// dependencies
	// coreApi
	tcore_Dependency *dCoreApi = calloc(1, sizeof(tcore_Dependency));
	dCoreApi->moduleName = "coreApi";
	dCoreApi->versionMajor = 0;
	lll_add(cli_module->dependencies, dCoreApi);

	// calculator
	tcore_Dependency *dCalc = calloc(1, sizeof(tcore_Dependency));
	dCalc->moduleName = "calculator";
	dCalc->versionMajor = 0;
	lll_add(cli_module->dependencies, dCalc);

	return SUCCESS;
}

tcore_Metadata* getMetadata(){
	return cli_module;
}

int
onActivation(tcore_Interface* (*getInterface)(const char*, int, const char*)){
    tcore_Interface *shutdownInterface
        = getInterface("coreApi", 0, "shutdown");
    if(NULL == shutdownInterface || NULL == shutdownInterface->function){
        printf("--- [ FATAL ] --- Failed to load shutdown interface");
        return FATAL;
    }
    cli_tca_shutdown = (void (*) (void)) shutdownInterface->function;

    tcore_Interface *additionInterface
        = getInterface("calculator", 0, "addition");
    if(NULL == additionInterface || NULL == additionInterface->function){
        printf("--- [ FATAL ] --- Failed to load addition interface");
        return FATAL;
    }

    cli_clc_add = (int (*) (int,int)) additionInterface->function;

    cli_thread = tpl_createThread(cli_main, NULL);
    return SUCCESS;
}

int onDeactivation(){
    tpl_cancelThread(cli_thread);
    tpl_freeThread(cli_thread);
    return SUCCESS;
}

int onUnload(){
    lll_freeList(cli_module->dependencies);
    lll_freeList(cli_module->interfaces);
    free(cli_module);
    cli_module = NULL;

    return SUCCESS;
}
