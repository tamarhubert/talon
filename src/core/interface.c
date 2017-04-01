#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "interface.h"
#include "logging.h"
#include "main.h"

// typedef lll_List tci_InterfaceRegistry; // fucking hacks

#define TCI_LOG_NAME "tcore:interface"

typedef struct tc_Interface tc_Interface;
struct tc_Interface {
  char* name;
  int versionMajor;
  int versionMinor;
  lll_List* functions;
  lll_List* parentDependencies;
  lll_List* childDependencies;
  short int isActivated;
};

typedef struct tc_Function tc_Function;
struct tc_Function {
  char *name;
  char *prototype;
  char *man;
  void (* pointer) ();
};

static int tci_getInterface(
  tci_InterfaceRegistry *list,
  const char* interfaceName,
  int interfaceVersionMajor,
  tc_Interface** queryResult);

int tci_newInterfaceRegistry(tci_InterfaceRegistry **registry){
  return (*registry = lll_newList()) ? SUCCESS : ERROR;
}

int tci_registerInterface(tci_InterfaceRegistry* registry, tmm_Module* module){
  tc_Interface *interface = malloc(sizeof(tc_Interface));
  interface->name = malloc(strlen(module->name) + 1);
  strcpy(interface->name, module->name);

  interface->versionMajor = module->versionMajor;
  interface->versionMinor = module->versionMinor;

  interface->functions = lll_newList();
  tmf_Function *module_function;
  int index;
  for(index = 0; index < lll_size(module->functions); index++){
    lll_elementAtIndex(module->functions, index, (void**)&module_function);

    tc_Function *core_function = malloc(sizeof(tc_Function));

    core_function->name = malloc(strlen(module_function->name) + 1);
    strcpy(core_function->name, module_function->name);

    core_function->prototype  = malloc(strlen(module_function->prototype) + 1);
    strcpy(core_function->prototype, module_function->prototype);

    core_function->man = malloc(strlen(module_function->man) + 1);
    strcpy(core_function->man, module_function->man);

    core_function->pointer = module_function->pointer;

    lll_add(interface->functions, core_function);
  }

  interface->parentDependencies = lll_newList();
  tmd_Dependency *module_dependency;
  tc_Interface *core_dependency;
  for(index = 0; index < lll_size(module->dependencies); index++){
    lll_elementAtIndex(module->dependencies, index, (void**)&module_dependency);
    if(tci_getInterface(
        registry,
        module_dependency->moduleName,
        module_dependency->versionMajor,
        &core_dependency) < WARNING){
      tca_log(TCA_LL_ERROR, TCI_LOG_NAME, "failed to resolve dependency (%s:%i)", module_dependency->moduleName, module_dependency->versionMajor);
      return ERROR;
    }
    lll_add(core_dependency->childDependencies, interface);
    lll_add(interface->parentDependencies, core_dependency);
  }

  interface->childDependencies = lll_newList();

  interface->isActivated = 0;

  return lll_add(registry, interface);
}

int tci_activateInterface(tci_InterfaceRegistry* registry, int id){
  tc_Interface *interface;
  lll_elementAtIndex(registry, id, (void**)&interface);
  interface->isActivated = 1;
  return SUCCESS;
}

static int tci_getInterface(
  tci_InterfaceRegistry *registry,
  const char* interfaceName,
  int interfaceVersionMajor,
  tc_Interface **queryResult){

  tc_Interface* interface;
  int index;
  for(index = 0; index < lll_size(registry); index++){
    lll_elementAtIndex(registry, index, (void**)&interface);
    if(interface->versionMajor == interfaceVersionMajor
      && strcmp(interface->name, interfaceName) == 0
    ){
      *queryResult = interface;
      return SUCCESS;
    }
  }
  return ERROR;
}

int tci_getFunction(
  tci_InterfaceRegistry* registry,
  const char* interfaceName,
  int interfaceVersionMajor,
  const char* functionName,
  tmf_Function* queryResult){

  tc_Interface *interface;
  tci_getInterface(registry, interfaceName, interfaceVersionMajor, &interface);
  tmf_Function* function;
  int index;
  for(index = 0; index < lll_size(interface->functions); index++){
    lll_elementAtIndex(interface->functions, index, (void**)&function);
    if(strcmp(function->name, functionName) == 0){
      *queryResult = *function;
      return SUCCESS;
    }
  }
  return ERROR;
}

int tci_deactivateInterface(tci_InterfaceRegistry* registry, int id){
  // find index of id
  int index = id;

  tc_Interface *interface;
  lll_elementAtIndex(registry, index, (void**)&interface);
  if(lll_size(interface->childDependencies) > 0){
    return ERROR;
  }
  interface->isActivated = 0;
  return SUCCESS;
}

int tci_deregisterInterface(tci_InterfaceRegistry* registry, int id){
  // find index of id
  int index = id;

  tc_Interface *interface;
  lll_elementAtIndex(registry, index, (void**)&interface);
  if(interface->isActivated == 0){
    return ERROR;
  }

  // remove parentDependencies (double dispatch)
  tc_Interface *dependency;
  while(lll_size(interface->parentDependencies) > 0){
    lll_elementAtIndex(interface->parentDependencies, 0, (void**)&dependency);
    int childIndex;
    tc_Interface *child;
    for(
      childIndex = 0;
      childIndex < lll_size(dependency->childDependencies);
      childIndex++)
    {
      lll_elementAtIndex(
        dependency->childDependencies,
        childIndex,
        (void**)&child);
      if(interface == child){
        lll_removeAtIndex(dependency->childDependencies, childIndex);
        break;
      }
    }
    lll_removeAtIndex(interface->parentDependencies, 0);
  }

  // remove from registry
  lll_removeAtIndex(registry, index);

  tc_Function *function;
  while (lll_size(interface->functions)) {
    lll_elementAtIndex(interface->functions, 0, (void**)&function);
    free(function->man);
    free(function->prototype);
    free(function->name);
    free(function);
    lll_removeAtIndex(interface->functions, 0);
  }
  lll_freeList(interface->functions);
  lll_freeList(interface->parentDependencies);
  lll_freeList(interface->childDependencies);
  free(interface->name);
  free(interface);

  return SUCCESS;
}

int tci_freeInterfaceRegistry(tci_InterfaceRegistry* registry){
  return lll_freeList(registry);
}
