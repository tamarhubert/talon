#include <stdlib.h>
#include <stdio.h>
#include "../lib/runtimeLinkingLibrary/src/runtimeLinking.h"

#include "libraryHandler.h"

#include "../modules/coreApi/src/logging.h"

char *lh_error;
int id = 0;


tcore_Library* loadLibrary(const char* path){
    tcore_Library *library = malloc(sizeof(tcore_Library));

    tcore_log(COREAPI_LL_INFO, "tcore", "load library \"%s\"", path);

    library->handle = rll_open(path);
    if(!library->handle){
        tcore_log(COREAPI_LL_ERROR, "tcore", "failed to rll open \"%s\"", path);
        free(library);
        lh_error = rll_error();
        return NULL;
    }
    tcore_log(COREAPI_LL_INFO, "tcore", "rll opened \"%s\"", path);

    tcore_Module *module = malloc(sizeof(tcore_Module));

    module->load = rll_get(library->handle, MH_LOAD);
    if(module->load == NULL){
        rll_close(library->handle);
        free(library);
        free(module);
        return NULL;
    }
    tcore_log(COREAPI_LL_INFO, "tcore", "rll got %s", MH_LOAD);

    module->activate = rll_get(library->handle, MH_ACTIVATE);
    if(module->activate == NULL){
        rll_close(library->handle);
        free(library);
        free(module);
        return NULL;
    }
    tcore_log(COREAPI_LL_INFO, "tcore", "rll got %s", MH_ACTIVATE);

    module->getMetadata = rll_get(library->handle, MH_METADATA);
    if(module->getMetadata == NULL){
        rll_close(library->handle);
        free(library);
        free(module);
        return NULL;
    }
    tcore_log(COREAPI_LL_INFO, "tcore", "rll got %s", MH_METADATA);

    module->deactivate = rll_get(library->handle, MH_DEACTIVATE);
    if(module->deactivate == NULL){
        rll_close(library->handle);
        free(library);
        free(module);
        return NULL;
    }
    tcore_log(COREAPI_LL_INFO, "tcore", "rll got %s", MH_DEACTIVATE);

    module->unload = rll_get(library->handle, MH_UNLOAD);
    if(module->unload == NULL){
        rll_close(library->handle);
        free(library);
        free(module);
        return NULL;
    }
    tcore_log(COREAPI_LL_INFO, "tcore", "rll got %s", MH_UNLOAD);

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
