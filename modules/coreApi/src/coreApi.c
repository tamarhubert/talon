#include <stdlib.h>
#include "library.h"

#include "coreApi.h"
#include "logging.h"
#include "main.h"

static volatile int tca_isActive = 1;
static tc_ModulePool *tca_pool;

void tca_setPool(tc_ModulePool *pool){
  tca_pool = pool;
}

int tca_getIsActive(void){
  return tca_isActive;
}

void tca_shutdown(void) {
    tca_isActive = 0;
}

int tca_getFunction(
  const char* moduleName,
  int moduleVersion,
  const char*functionName,
  tmf_Function* result)
{
  return tc_getFunction(
    tca_pool,
    moduleName,
    moduleVersion,
    functionName,
    result);
};

int tca_loadModule(const char* path){
  tmf_Function activationFunction;
  tca_getFunction(
    TCA_MODULE_NAME,
    TCA_MODULE_VERSION_MAJOR,
    "getFunction",
    &activationFunction);
  return tc_integrateModule(tca_pool, activationFunction, path);
}

int tca_unloadModule(int id){
  return tc_disintegrateModule(tca_pool, id);
}
