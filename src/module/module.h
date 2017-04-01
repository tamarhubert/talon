#ifndef TMOUDLE_MODULE_H_
#define TMOUDLE_MODULE_H_

#include "dependency.h"
#include "function.h"

typedef struct tmm_Module tmm_Module;
struct tmm_Module {
  char *name;
  int versionMajor;
  int versionMinor;
  tmd_DependencyList* dependencies;
  tmf_FunctionList* functions;
};

int tmm_newModule(
  const char *name,
  int vsersionMajor,
  int versionMinor,
  tmm_Module **module
);

int tmm_addFunction(
  tmm_Module *module,
  const char *name,
  const char *prototype,
  const char *man,
  void (* const function) ()
);

int tmm_addDependency(
  tmm_Module *module,
  const char *moduleName,
  const int versionMajor
);

int tmm_freeModule(tmm_Module *module);

#endif /* TMOUDLE_MODULE_H_ */
