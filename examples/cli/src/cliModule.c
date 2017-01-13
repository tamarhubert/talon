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
	// free dependencies
  tcore_Dependency *dependency = NULL;
  int i;
  for(i = 0; i < lll_size(cli_module->dependencies); i++){
    lll_elementAtIndex(cli_module->dependencies, i, (void**)&dependency);
    lll_removeAtIndex(cli_module->dependencies, i);
    free(dependency);
  }
  lll_freeList(cli_module->dependencies);

  // free interfaces
  tcore_Interface *interface = NULL;
  for(i = 0; i < lll_size(cli_module->interfaces); i++){
    lll_elementAtIndex(cli_module->interfaces, i, (void**)&interface);
    lll_removeAtIndex(cli_module->interfaces, i);
    free(interface);
  }
  lll_freeList(cli_module->interfaces);

  free(cli_module);
  cli_module = NULL;

  return SUCCESS;
}
