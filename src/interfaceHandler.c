#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "interfaceHandler.h"
#include "../lib/linkedListLibrary/src/linkedList.h"

lll_List *moduleDefs;

int ih_activate(){
    moduleDefs = lll_newList();
    return 0;
}
int ih_deactivate(){
    int i;
    for(i = lll_size(moduleDefs)-1; i >= 0; i--){
        tcore_Metadata *moduleDef = NULL;
        lll_elementAtIndex(moduleDefs, i, (void**)&moduleDef);
        deregisterInterface(moduleDef->id);
    }
    lll_freeList(moduleDefs);
    return SUCCESS;
}

int registerInterface(int id, tcore_Metadata *metadata){
    metadata->id = id;
    lll_add(moduleDefs, metadata);

    return metadata->id;
}
int deregisterInterface(int id){
    int i;
    for(i = 0; i < lll_size(moduleDefs); i++){
        tcore_Metadata *metadata = NULL;
        lll_elementAtIndex(moduleDefs, i, (void**)&metadata);
        if(metadata->id == id){
            lll_removeAtIndex(moduleDefs, i);
            return SUCCESS;
        }
    }
    return WARNING;
}

tcore_Interface* getInterface(const char* moduleName, int moduleVersion, const char* interfaceName){
    int i;
    for(i = 0; i < lll_size(moduleDefs); i++){
        tcore_Metadata *metadata = NULL;
        lll_elementAtIndex(moduleDefs, i, (void**)&metadata);
        if(metadata->version.major == moduleVersion
                && strcmp(metadata->name, moduleName) == 0){
            int j; lll_List *interfaces = metadata->interfaces;
            for(j = 0; j < lll_size(interfaces); j++){
                tcore_Interface *interface = NULL;
                lll_elementAtIndex(interfaces, i, (void**)&interface);
                if(strcmp(interface->name, interfaceName) == 0){
                    return interface;
                }
            }
        }
    }
    return NULL;
}

int checkDependency(tcore_Dependency *dependency){
  int i;
  for(i = 0; i < lll_size(moduleDefs); i++){
    tcore_Metadata *metadata = NULL;
    lll_elementAtIndex(moduleDefs, i, (void**)&metadata);
    if(metadata->version.major == dependency->versionMajor
      && strcmp(metadata->name, dependency->moduleName) == 0){
        return SUCCESS;
      }
    }
    return FATAL;
  }

int checkDependencies(lll_List *dependencies){
  int i;
  for(i = 0; i < lll_size(dependencies); i++){
    tcore_Dependency *dependency = NULL;
    lll_elementAtIndex(dependencies, i, (void**)&dependency);
    if(checkDependency(dependency) < WARNING){
      return FATAL;
    }
  }
  return SUCCESS;
}
