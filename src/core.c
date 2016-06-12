#include <stdio.h>

#include "libraryHandler.h"
#include "module.h"
#include "moduleHandler.h"
#include "interfaceHandler.h"

int tcore_isActive = 1;

void tcore_deactivate(void) {
    tcore_isActive = 0;
}

int isActive(void){
    return tcore_isActive;
}

int main(void){
    ih_activate();

    tcore_Library *calcLib = loadLibrary("examples/calculator/obj/calc.so");
    if(NULL == calcLib){
        printf("-- [ FATAL ] -- failed to compute calc library\n");
        return FATAL;
    }
    if(loadModule(calcLib->module) < WARNING){
        printf("-- [ FATAL ] -- failed to load calc module\n");
        return FATAL;
    }

    tcore_Library *cliLib = loadLibrary("examples/cli/obj/cli.so");
    if(NULL == cliLib){
        printf("-- [ FATAL ] -- failed to compute cli library\n");
        return FATAL;
    }
    if(loadModule(cliLib->module) < WARNING){
        printf("-- [ FATAL ] -- failed to load cli module\n");
        return FATAL;
    }
    
    while(isActive()){}

    unloadModule(calcLib->module);
    unloadLibrary(calcLib);

    unloadModule(cliLib->module);
    unloadLibrary(cliLib);
    
    ih_deactivate();

    return 0;
}
