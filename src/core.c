#include <stdio.h>

#include "libraryHandler.h"
#include "module.h"
#include "moduleHandler.h"
#include "interfaceHandler.h"
#include "../modules/coreApi/src/coreApiModule.h"
#include "../modules/coreApi/src/coreApi.h"

int tcore_isActive = 1;

void tcore_shutdown(void) {
    tcore_isActive = 0;
}

int isActive(void){
    return tcore_isActive;
}

int main(void){
    ih_activate();

    tcore_Module coreApi = {
        0,
        coreApi_onLoad,
        coreApi_onActivation,
        coreApi_getMetadata,
        coreApi_onDeactivation,
        coreApi_onUnload
    };
    tcore_setLogLevel(COREAPI_LL_INFO);
    // loading coreApi
    if(loadModule(&coreApi) < WARNING){
        tcore_log(COREAPI_LL_FATAL, "tcore", "failed to load core api module");
        return FATAL;
    }
    tcore_log(COREAPI_LL_INFO, "tcore", "loaded core api module");


    // manually loading core cli module
    tcore_Library *coreCliLib = loadLibrary("modules/coreCli/obj/coreCli.so");
    if(NULL == coreCliLib){
        tcore_log(COREAPI_LL_FATAL, "tcore", "failed to compute core cli library");
        return FATAL;
    }
    tcore_log(COREAPI_LL_INFO, "tcore", "computed core cli module");

    if(loadModule(coreCliLib->module) < WARNING){
        tcore_log(COREAPI_LL_FATAL, "tcore", "failed to load core cli module");
        return FATAL;
    }
    tcore_log(COREAPI_LL_INFO, "tcore", "loaded core cli module");

    while(isActive()){
#ifdef _WIN32
#include <windows.h>
        Sleep(100);
#elif __linux__
#include <unistd.h>
        usleep(100*1000);
#else
        #error "Unknown compiler"
#endif
    }

    tcore_log(COREAPI_LL_DEBUG, "tcore", "shutting down...");

    unloadModule(coreCliLib->module);
    unloadLibrary(coreCliLib);

    unloadModule(&coreApi);

    ih_deactivate();

    tcore_log(COREAPI_LL_DEBUG, "tcore", "bye.");

    return 0;
}
