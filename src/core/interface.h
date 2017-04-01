#ifndef TCORE_INTERFACE_H_
#define TCORE_INTERFACE_H_

#include "linkedList.h"
#include "function.h"
#include "module.h"

// fucking hacks
// typedef struct tci_InterfaceRegistry tci_InterfaceRegistry;
typedef lll_List tci_InterfaceRegistry;

int tci_newInterfaceRegistry(tci_InterfaceRegistry** registry);

int tci_registerInterface(tci_InterfaceRegistry* registry, tmm_Module* module);
int tci_activateInterface(tci_InterfaceRegistry* registry, int id);

int tci_getFunction(
  tci_InterfaceRegistry* registry,
  const char* interfaceName,
  int interfaceVersionMajor,
  const char* functionName,
  tmf_Function *queryResult);

int tci_deactivateInterface(tci_InterfaceRegistry* registry, int id);
int tci_deregisterInterface(tci_InterfaceRegistry* registry, int id);

int tci_freeInterfaceRegistry(tci_InterfaceRegistry* registry);

#endif /* TCORE_INTERFACE_H_ */
