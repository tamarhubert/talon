#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../lib/linkedListLibrary/src/linkedList.h"

#include "interfaceHandler.h"

#include "../modules/coreApi/src/logging.h"

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
    tcore_log(COREAPI_LL_WARNING, "tcore", "No interface with id %i", id);
    return WARNING;
}

tcore_Interface* getInterface(const char* moduleName,
        int moduleVersion, const char* interfaceName){
    tcore_log(COREAPI_LL_INFO, "tcore", "getting interface for %s:%i:%s",
        moduleName, moduleVersion, interfaceName);
    int i;
    for(i = 0; i < lll_size(moduleDefs); i++){
        tcore_Metadata *metadata = NULL;
        lll_elementAtIndex(moduleDefs, i, (void**)&metadata);
        tcore_log(COREAPI_LL_INFO, "tcore", "is module %s:%i == %s:%i?",
          metadata->name, metadata->version.major, moduleName,moduleVersion);
        if(metadata->version.major == moduleVersion
                && strcmp(metadata->name, moduleName) == 0){
            int j; lll_List *interfaces = metadata->interfaces;
            for(j = 0; j < lll_size(interfaces); j++){
                tcore_Interface *intrface = NULL;
                lll_elementAtIndex(interfaces, j, (void**)&intrface);
                tcore_log(COREAPI_LL_INFO, "tcore", "is interface %s == %s?",
                  intrface->name, interfaceName);
                if(strcmp(intrface->name, interfaceName) == 0){
                    tcore_log(COREAPI_LL_INFO, "tcore", "interface %s:%i:%s found",
                      moduleName, moduleVersion, interfaceName);
                    return intrface;
                }
            }
        }
    }
    tcore_log(COREAPI_LL_ERROR, "tcore", "interface %s:%i:%s not found",
      moduleName, moduleVersion, interfaceName);
    return NULL;
}

int checkDependency(tcore_Dependency *dependency){
  int i;
  for(i = 0; i < lll_size(moduleDefs); i++){
    tcore_Metadata *metadata = NULL;
    lll_elementAtIndex(moduleDefs, i, (void**)&metadata);
    if(metadata->version.major == dependency->versionMajor
        && strcmp(metadata->name, dependency->moduleName) == 0){
      tcore_log(COREAPI_LL_INFO, "tcore", "dependency %s:%i satisfied",
        dependency->moduleName, dependency->versionMajor);
      return SUCCESS;
    }
  }
  tcore_log(COREAPI_LL_ERROR, "tcore", "dependency %s:%i not satisfied",
    dependency->moduleName, dependency->versionMajor);
  return FATAL;
}

int checkDependencies(lll_List *dependencies){
  int i;
  for(i = 0; i < lll_size(dependencies); i++){
    tcore_Dependency *dependency = NULL;
    lll_elementAtIndex(dependencies, i, (void**)&dependency);
    if(checkDependency(dependency) < WARNING){
      tcore_log(COREAPI_LL_ERROR, "tcore", "dependencies not satisfied");
      return FATAL;
    }
  }
  tcore_log(COREAPI_LL_INFO, "tcore", "dependencies satisfied");
  return SUCCESS;
}
