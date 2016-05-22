#include <stdlib.h>
#include <stdio.h>

#include "libraryHandler.h"
#include "../lib/runtimeLinkingLibrary/src/runtimeLinking.h"

char *lh_error;
int id = 0;


tcore_Module* loadLibrary(const char* path){
    tcore_Module *module = malloc(sizeof(tcore_Module));

    module->handle = rll_open(path);
    if(!module->handle){
        free(module);
        lh_error = rll_error();
        return NULL;
    }

    int (*onLoad) ();

    onLoad = rll_get(module->handle, MH_LOAD);
    if((lh_error = rll_error()) != NULL){
        rll_close(module->handle);
        free(module);
        return NULL;
    }
    module->activate = rll_get(module->handle, MH_ACTIVATE);
    if((lh_error = rll_error()) != NULL){
        rll_close(module->handle);
        free(module);
        return NULL;
    }
    module->getDefinition = rll_get(module->handle, MH_DEFINITION);
    if((lh_error = rll_error()) != NULL){
        rll_close(module->handle);
        free(module);
        return NULL;
    }
    module->deactivate = rll_get(module->handle, MH_DEACTIVATE);
    if((lh_error = rll_error()) != NULL){
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
    int (*onUnload) (void) = rll_get(module->handle, MH_UNLOAD);
    if((lh_error = rll_error()) != NULL){
        free(module);
        rll_close(module->handle);
        return -1;
    }
    onUnload();   
    free(module);
    rll_close(module->handle);
    return 0;   
}
