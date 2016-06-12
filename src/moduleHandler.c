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

    // TODO resolve dependencies

    if(registerInterface(module->id, module->getMetadata()) < WARNING){
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
