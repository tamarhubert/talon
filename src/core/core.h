#ifndef TCORE_CORE_H_
#define TCORE_CORE_H_

#include "module.h"
#include "function.h"

typedef struct tc_ModulePool tc_ModulePool;

int tc_newModulePool(tmm_Module* coreApi, tc_ModulePool** pool);
int tc_integrateModule(
  tc_ModulePool* pool,
  tmf_Function activationFunction,
  const char* path);
int tc_getFunction(
  tc_ModulePool* pool,
  const char* interfaceName,
  int interfaceVersionMajor,
  const char* functionName,
  tmf_Function *queryResult);
int tc_disintegrateModule(tc_ModulePool* pool, int id);
int tc_freeModulePool(tc_ModulePool* pool);

#endif /* TCORE_CORE_H_ */
