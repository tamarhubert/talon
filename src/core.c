#include <stdio.h>

#include "module.h"
#include "moduleHandler.h"
#include "interfaceHandler.h"

int main(void){
    ih_activate();
    mh_activate();

    int calcModuleId =  loadModule("examples/calculator/obj/calc.so");
    if(calcModuleId < WARNING){
        printf("-- [ FATAL ] -- failed to load calc module");
        return FATAL;
    }
    int cliModuleId =   loadModule("examples/cli/obj/cli.so");
    if(cliModuleId < WARNING){
        printf("-- [ FATAL ] -- failed to load cli module");
        unloadModule(calcModuleId);
        return FATAL;
    }
    
    tcore_Interface *cliInterface = getInterface("cli", 0, "cli");
    if(!cliInterface){
        printf("cli::cli interface not found\n");
    }
    else {
        void(*cli)(void) = (void(*)(void))cliInterface->function;
        cli();
    }
    
    unloadModule(calcModuleId);
    unloadModule(cliModuleId);
    
    ih_deactivate();
    mh_deactivate();
    
    return 0;    
}
