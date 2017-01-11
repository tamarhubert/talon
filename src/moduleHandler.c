#include <stdlib.h>
#include <stdio.h>

#include "moduleHandler.h"
#include "libraryHandler.h"
#include "interfaceHandler.h"
#include "../lib/linkedListLibrary/src/linkedList.h"

int loadModule(tcore_Module *module){
    if(!module){
        return FATAL;
    }

    if(module->load() < WARNING){
        return FATAL;
    }

    tcore_Metadata *metadata = module->getMetadata();

    if(checkDependencies(metadata->dependencies) < WARNING){
      return FATAL;
    }

    if(registerInterface(module->id, metadata) < WARNING){
        return FATAL;
    }
    if(module->activate(getInterface) < WARNING){
        deregisterInterface(module->id);
        return FATAL;
    }

    return SUCCESS;
}

int unloadModule(tcore_Module *module){
    // TODO remove dependent modules

    deregisterInterface(module->id);
    module->deactivate();
    module->unload();
    return SUCCESS;
}
