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

    // manually loading modules calc and cli
    // calc
    tcore_Library *calcLib = loadLibrary("examples/calculator/obj/calc.so");
    if(NULL == calcLib){
        tcore_log(COREAPI_LL_FATAL, "tcore", "failed to compute calc library");
        return FATAL;
    }
    tcore_log(COREAPI_LL_INFO, "tcore", "computed calculator module");

    if(loadModule(calcLib->module) < WARNING){
        tcore_log(COREAPI_LL_FATAL, "tcore", "failed to load calc module");
        return FATAL;
    }
    tcore_log(COREAPI_LL_INFO, "tcore", "loaded calculator module");

    // cli
    tcore_Library *cliLib = loadLibrary("examples/cli/obj/cli.so");
    if(NULL == cliLib){
        tcore_log(COREAPI_LL_INFO, "tcore", "failed to compute cli library");
        return FATAL;
    }
    tcore_log(COREAPI_LL_INFO, "tcore", "computed cli module");
    if(loadModule(cliLib->module) < WARNING){
        tcore_log(COREAPI_LL_INFO, "tcore", "failed to load cli module");
        return FATAL;
    }
    tcore_log(COREAPI_LL_INFO, "tcore", "loaded cli module");

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

    unloadModule(calcLib->module);
    unloadLibrary(calcLib);

    unloadModule(cliLib->module);
    unloadLibrary(cliLib);

    unloadModule(&coreApi);

    ih_deactivate();

    return 0;
}
