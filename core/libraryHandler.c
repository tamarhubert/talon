#include <stdlib.h>
#include <stdio.h>

#include "libraryHandler.h"
#include "../lib/rll/runtimeLinking.h"

int id = 0;

tcore_Module* loadLibrary(const char* path){
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
    module->activate = rll_get(module->handle, MH_ACTIVATE);
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
    module->deactivate = rll_get(module->handle, MH_DEACTIVATE);
    if((error = rll_error()) != NULL){
        rll_close(module->handle);
        free(module);
        return NULL;
    }

    onLoad();
    
    module->id = id;
    id++;
    return module;
}
int unloadLibrary(tcore_Module* module){
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
