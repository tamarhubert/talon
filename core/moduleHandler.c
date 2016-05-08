#include <stdlib.h>
#include <stdio.h>

#include "moduleHandler.h"
#include "../lib/rll/runtimeLinking.h"

tcore_Module* loadModule(const char* path){
    tcore_Module *module = malloc(sizeof(module));
    char* error;

    module->handle = rll_open(path);
    if(!module->handle){
        return NULL;
        free(module);
    }

    int (*onLoad) ();

    onLoad = rll_get(module->handle, MH_ON_LOAD);
    if((error = rll_error()) != NULL){
        rll_close(module->handle);
        free(module);
        return NULL;
    }
    module->init = rll_get(module->handle, MH_INIT);
    if((error = rll_error()) != NULL){
        rll_close(module->handle);
        free(module);
        return NULL;
    }
    module->getDefinition = rll_get(module->handle, MH_DEFINITION);
    if((error = rll_error()) != NULL){
        rll_close(module->handle);
        free(module);
        return NULL;
    }
    module->deinit = rll_get(module->handle, MH_DEINIT);
    if((error = rll_error()) != NULL){
        rll_close(module->handle);
        free(module);
        return NULL;
    }

    onLoad();

    return module;
}
int unloadModule(tcore_Module* module){
    char * error;
    int (*onUnload) () = rll_get(module->handle, MH_ON_UNLOAD);
    if((error = rll_error()) != NULL){
        free(module);
        rll_close(module->handle);
        return -1;
    }
    onUnload();
    
    free(module);
    rll_close(module->handle);
    return 0;   
}
