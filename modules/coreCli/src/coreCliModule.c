#include <stdio.h>
#include <stdlib.h>

#include "coreCli.h"
#include "core.h"
#include "main.h"
#include "module.h"
#include "linkedList.h"
#include "logging.h"

#define TCC_MODULE_NAME "coreCli"
#define TCC_MODULE_VERSION_MAJOR 0
#define TCC_MODULE_VERSION_MINOR 0

static tmm_Module *tcc_module;
static tpl_Thread *tcc_thread;

int onLoad(tmm_Module *module) {
  tmm_newModule(
    TCC_MODULE_NAME,
    TCC_MODULE_VERSION_MAJOR,
    TCC_MODULE_VERSION_MINOR,
    &tcc_module
  );

  tmm_addDependency(tcc_module, "coreApi", 0);

  *module = *tcc_module;

  return SUCCESS;
}

int onActivation(tmf_Function activationFunction){
  int (*getFunction)(const char*, int, const char*, tmf_Function*)
    = (int (*)(const char*, int, const char*, tmf_Function*))
      activationFunction.pointer;

  tmf_Function function;
  int result;
  if((result = getFunction("coreApi", 0, "log", &function)) < WARNING){
    printf("--- [ FATAL ] --- failed to load log interface\n");
    return ERROR;
  }
  tcc_tca_log = (int (*) (int, const char*, const char*, ...)) function.pointer;
  tcc_tca_log(TCA_LL_INFO, TCC_LOG_NAME, "loaded log interface");

  if((result = getFunction("coreApi", 0, "setLogLevel", &function)) < WARNING){
    tcc_tca_log(TCA_LL_ERROR, TCC_LOG_NAME, "failed to load shutdown interface");
    return ERROR;
  }
  tcc_tca_setLogLevel = (void (*) (int)) function.pointer;
  tcc_tca_log(TCA_LL_INFO, TCC_LOG_NAME, "loaded setLogLevel interface");

  if((result = getFunction("coreApi", 0, "shutdown", &function)) < WARNING){
    tcc_tca_log(TCA_LL_ERROR, TCC_LOG_NAME, "failed to load shutdown interface");
    return ERROR;
  }
  tcc_tca_shutdown = (void (*) (void)) function.pointer;
  tcc_tca_log(TCA_LL_INFO, TCC_LOG_NAME, "loaded shutdown interface");

  tcc_thread = tpl_createThread(coreCli_main, NULL);

	return SUCCESS;
}

int onDeactivation(){
  tpl_cancelThread(tcc_thread);
  tpl_freeThread(tcc_thread);
  return SUCCESS;
}

int onUnload(){
  tmm_freeModule(tcc_module);
  return SUCCESS;
}
