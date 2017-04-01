#include <stdlib.h>
#include "interface.h"
#include "library.h"

#include "main.h"
#include "core.h"
#include "function.h"
#include "module.h"
#include "logging.h"

#define TC_LOG_NAME "tcore:core"

typedef struct tc_ModulePool tc_ModulePool;
struct tc_ModulePool{
  int coreApiId;
  tci_InterfaceRegistry* interfaces;
  tcl_LibraryRegistry* libraries;
};

int tc_newModulePool(tmm_Module* coreApi, tc_ModulePool** result){
  tc_ModulePool *pool = malloc(sizeof(tc_ModulePool));
  tci_newInterfaceRegistry(&pool->interfaces);
  tcl_newLibrarayRegistry(&pool->libraries);

  int id = tci_registerInterface(pool->interfaces, coreApi);
  if(id < WARNING){
    tca_log(TCA_LL_ERROR - id / 10, TC_LOG_NAME, "failed to register pool interface \"%s\"", coreApi->name);
    return ERROR;
  }
  tca_log(TCA_LL_INFO, TC_LOG_NAME, "successfully registered pool interface \"%s\"", coreApi->name);

  int res;
  if((res = tci_activateInterface(pool->interfaces, id)) < WARNING){
    tca_log(TCA_LL_ERROR - res / 10, TC_LOG_NAME, "failed to activate pool interface \"%s\"", coreApi->name);
    return ERROR;
  }
  tca_log(TCA_LL_INFO, TC_LOG_NAME, "successfully activated pool interface \"%s\"", coreApi->name);
  pool->coreApiId = id;

  *result = pool;
  return SUCCESS;
}

int tc_integrateModule(
  tc_ModulePool* pool,
  tmf_Function activationFunction,
  const char* path
){
  tc_Library* library;
  int result = tcl_loadLibrary(path, &library);
  if(result < WARNING){
    tca_log(TCA_LL_ERROR - result / 10, TC_LOG_NAME, "faild to load library at \"%s\"", path);
    return ERROR;
  }
  tca_log(TCA_LL_INFO - result / 10, TC_LOG_NAME, "successfully loaded library from \"%s\"", path);

  tmm_Module* module = malloc(sizeof(tmm_Module));
  if((result = library->load(module)) < WARNING){
    tca_log(TCA_LL_ERROR - result / 10, TC_LOG_NAME, "failed to load module from \"%s\"", path);
    return ERROR;
  }
  tca_log(TCA_LL_INFO, TC_LOG_NAME, "successfully loaded module \"%s\"", module->name);

  int id = tci_registerInterface(pool->interfaces, module);
  if(id < WARNING){
    tca_log(TCA_LL_ERROR - id / 10, TC_LOG_NAME, "failed to register interface \"%s\"", module->name);
    return ERROR;
  }
  tca_log(TCA_LL_INFO, TC_LOG_NAME, "successfully registered interface \"%s\"", module->name);

  if((result = library->activate(activationFunction)) < WARNING){
    tca_log(TCA_LL_ERROR - result / 10, TC_LOG_NAME, "failed to activate module \"%s\"", module->name);
    return ERROR;
  }
  tca_log(TCA_LL_INFO, TC_LOG_NAME, "successfully activated module \"%s\"", module->name);

  if((result = tci_activateInterface(pool->interfaces, id)) < WARNING){
    tca_log(TCA_LL_ERROR - result / 10, TC_LOG_NAME, "failed to activate interface \"%s\"", module->name);
    return ERROR;
  }
  tca_log(TCA_LL_INFO, TC_LOG_NAME, "successfully activated interface \"%s\"", module->name);

  tcl_addLibrary(pool->libraries, id, library);
  return id;
}

int tc_getFunction(
  tc_ModulePool* pool,
  const char* interfaceName,
  int interfaceVersionMajor,
  const char* functionName,
  tmf_Function *queryResult
){
  return tci_getFunction(
    pool->interfaces,
    interfaceName,
    interfaceVersionMajor,
    functionName,
    queryResult);
}

int tc_disintegrateModule(tc_ModulePool* pool, int id){
  tci_deactivateInterface(pool->interfaces, id);
  tc_Library *library;
  tcl_popLibrary(pool->libraries, id, &library);
  library->deactivate();
  tci_deregisterInterface(pool->interfaces, id);
  library->unload();
  tcl_unloadLibrary(library);
  return SUCCESS;
}

int tc_freeModulePool(tc_ModulePool* pool){
  tci_deactivateInterface(pool->interfaces, pool->coreApiId);
  tci_deregisterInterface(pool->interfaces, pool->coreApiId);
  tci_freeInterfaceRegistry(pool->interfaces);
  tcl_freeLibraryRegistry(pool->libraries);
  free(pool);
  return SUCCESS;
}
