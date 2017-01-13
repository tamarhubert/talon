#include <stdio.h>
#include <stdlib.h>

#include "coreCli.h"
#include "../../../src/core.h"
#include "../../../src/module.h"
#include "../../../lib/linkedListLibrary/src/linkedList.h"

#define COREAPI_MODULE_NAME "coreCli"
#define COREAPI_MODULE_VERSION_MAJOR 0
#define COREAPI_MODULE_VERSION_MINOR 0

tcore_Metadata *coreCli_module;
tpl_Thread *tcc_thread;

int onLoad() {
    // build coreApi_module
    coreCli_module = malloc(sizeof(tcore_Metadata));
    coreCli_module->name = COREAPI_MODULE_NAME;
    coreCli_module->version.major = COREAPI_MODULE_VERSION_MAJOR;
    coreCli_module->version.minor = COREAPI_MODULE_VERSION_MINOR;
    coreCli_module->dependencies = lll_newList();
    coreCli_module->interfaces = lll_newList();

    // dependencies
    // coreApi
    tcore_Dependency *dCoreApi = calloc(1, sizeof(tcore_Dependency));
    dCoreApi->moduleName = "coreApi";
    dCoreApi->versionMajor = 0;
    lll_add(coreCli_module->dependencies, dCoreApi);

    return SUCCESS;
}

tcore_Metadata* getMetadata(){
	return coreCli_module;
}

int onActivation(tcore_Interface* (*getInterface)(const char*, int, const char*)){
  tcore_Interface *shutdownI
      = getInterface("coreApi", 0, "shutdown");
  if(NULL == shutdownI || NULL == shutdownI->function){
      printf("--- [ FATAL ] --- Failed to load shutdown interface\n");
      return FATAL;
  }
  tcc_tca_shutdown = (void (*) (void)) shutdownI->function;

  tcore_Interface *logI
      = getInterface("coreApi", 0, "log");
  if(NULL == logI || NULL == logI->function){
      printf("--- [ FATAL ] --- Failed to load log interface\n");
      return FATAL;
  }
  tcc_tca_log = (int (*) (int, const char*, const char*, ...)) logI->function;

  tcc_thread = tpl_createThread(coreCli_main, NULL);
	return SUCCESS;
}

int onDeactivation(){
  tpl_cancelThread(tcc_thread);
  tpl_freeThread(tcc_thread);
	return SUCCESS;
}

int onUnload(){
  // free dependencies
  tcore_Dependency *dependency = NULL;
  int i;
  for(i = 0; i < lll_size(coreCli_module->dependencies); i++){
    lll_elementAtIndex(coreCli_module->dependencies, i, (void**)&dependency);
    lll_removeAtIndex(coreCli_module->dependencies, i);
    free(dependency);
  }
  lll_freeList(coreCli_module->dependencies);

  // free interfaces
  tcore_Interface *interface = NULL;
  for(i = 0; i < lll_size(coreCli_module->interfaces); i++){
    lll_elementAtIndex(coreCli_module->interfaces, i, (void**)&interface);
    lll_removeAtIndex(coreCli_module->interfaces, i);
    free(interface);
  }
  lll_freeList(coreCli_module->interfaces);

  free(coreCli_module);
  coreCli_module = NULL;

  return SUCCESS;
}
