#include <stdlib.h>
#include <stdio.h>

#include "libraryHandler.h"
#include "../lib/runtimeLinkingLibrary/src/runtimeLinking.h"

char *lh_error;
int id = 0;


tcore_Library* loadLibrary(const char* path){
    tcore_Library *library = malloc(sizeof(tcore_Library));

    library->handle = rll_open(path);
    if(!library->handle){
        free(library);
        lh_error = rll_error();
        return NULL;
    }

    tcore_Module *module = malloc(sizeof(tcore_Module));
    
    module->load = rll_get(library->handle, MH_LOAD);
    if((lh_error = rll_error()) != NULL){
        rll_close(library->handle);
	free(library);
        free(module);
        return NULL;
    }

    module->activate = rll_get(library->handle, MH_ACTIVATE);
    if((lh_error = rll_error()) != NULL){
        rll_close(library->handle);
        free(library);
        free(module);
        return NULL;
    }

    module->getMetadata = rll_get(library->handle, MH_METADATA);
    if((lh_error = rll_error()) != NULL){
        rll_close(library->handle);
        free(library);
        free(module);
        return NULL;
    }

    module->deactivate = rll_get(library->handle, MH_DEACTIVATE);
    if((lh_error = rll_error()) != NULL){
        rll_close(library->handle);
        free(library);
        free(module);
        return NULL;
    }

    module->unload = rll_get(library->handle, MH_UNLOAD);
    if((lh_error = rll_error()) != NULL){
        rll_close(library->handle);
        free(library);
        free(module);
        return NULL;
    }

    module->id = ++id;
    library->module = module;
    return library;
}

int unloadLibrary(tcore_Library* library){
    if(NULL == library){
        return WARNING;
    }

    if(NULL == library->module || NULL == library->handle){
        if(NULL != library->module){
            free(library->module);
        }
        if(NULL != library->handle){
            rll_close(library->handle);
        }
        free(library);
        return WARNING;
    }
    rll_close(library->handle);
    free(library->module);
    free(library);
    return SUCCESS;
}

char* lh_getError(void){
    return lh_error;
}
