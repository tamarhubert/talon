#include <stdlib.h>
#include <string.h>
#include "module.h"
#include "main.h"

int tmm_newModule(
  const char *name,
  int versionMajor,
  int versionMinor,
  tmm_Module **module
){
  (*module) = malloc(sizeof(tmm_Module));
  (*module)->name = malloc(strlen(name) + 1);
  strcpy((*module)->name, name);
  (*module)->versionMajor = versionMajor;
  (*module)->versionMinor = versionMinor;
  tmf_newFunctionList(&(*module)->functions);
  tmd_newDependencyList(&(*module)->dependencies);
  return SUCCESS;
}

int tmm_addFunction(
  tmm_Module *module,
  const char *name,
  const char *prototype,
  const char *man,
  void (* const function) ()
){
  return tmf_addFunction(
    module->functions,
    name,
    prototype,
    man,
    function
  );
}

int tmm_addDependency(
  tmm_Module *module,
  const char *moduleName,
  const int versionMajor
){
  return tmd_addDependency(
    module->dependencies,
    moduleName,
    versionMajor
  );
}

int tmm_freeModule(tmm_Module *module){
  free(module->name);
  tmf_freeFunctionList(module->functions);
  tmd_freeDependencyList(module->dependencies);
  free(module);
  return SUCCESS;
}
