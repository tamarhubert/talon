#include <stdio.h>

#include "module.h"
#include "moduleHandler.h"
#include "interfaceHandler.h"

int tcore_isActive = 0;

void tcore_deactivate(void) {
    tcore_isActive = 1;
}

int isActive(void){
    return tcore_isActive;
}


int main(void){
    ih_activate();
    mh_activate();

    int calcModuleId =  loadModule("examples/calculator/obj/calc.so");
    if(calcModuleId < WARNING){
        printf("-- [ FATAL ] -- failed to load calc module\n");
        return FATAL;
    }
    int cliModuleId =   loadModule("examples/cli/obj/cli.so");
    if(cliModuleId < WARNING){
        printf("-- [ FATAL ] -- failed to load cli module\n");
        unloadModule(calcModuleId);
        return FATAL;
    }
    
    while(isActive()){}
    
    unloadModule(calcModuleId);
    unloadModule(cliModuleId);
    
    ih_deactivate();
    mh_deactivate();
    
    return 0;
}
