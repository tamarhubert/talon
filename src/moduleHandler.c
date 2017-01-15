#include <stdlib.h>
#include <stdio.h>
#include "../lib/linkedListLibrary/src/linkedList.h"

#include "moduleHandler.h"
#include "libraryHandler.h"
#include "interfaceHandler.h"

#include "../modules/coreApi/src/logging.h"

int loadModule(tcore_Module *module){
    if(!module){
        tcore_log(COREAPI_LL_ERROR, "tcore", "no module privided");
        return FATAL;
    }

    if(module->load() < WARNING){
        tcore_log(COREAPI_LL_ERROR, "tcore", "module loading failed");
        return FATAL;
    }

    tcore_Metadata *metadata = module->getMetadata();
    if(!metadata){
        tcore_log(COREAPI_LL_ERROR, "tcore",
          "module failed to provide metadata");
        return FATAL;
    }

    if(checkDependencies(metadata->dependencies) < WARNING){
      tcore_log(COREAPI_LL_ERROR, "tcore",
        "%s: dependency check failed", metadata->name);
      return FATAL;
    }

    if(registerInterface(module->id, metadata) < WARNING){
      tcore_log(COREAPI_LL_ERROR, "tcore",
        "%s: interface registration failed", metadata->name);
        return FATAL;
    }
    if(module->activate(getInterface) < WARNING){
      tcore_log(COREAPI_LL_ERROR, "tcore",
        "%s: activation failed", metadata->name);
        deregisterInterface(module->id);
        return FATAL;
    }
    tcore_log(COREAPI_LL_INFO, "tcore",
      "%s was successfully loaded and activated", metadata->name);
    return SUCCESS;
}

int unloadModule(tcore_Module *module){
    // TODO remove dependent modules

    deregisterInterface(module->id);
    module->deactivate();
    module->unload();
    return SUCCESS;
}
