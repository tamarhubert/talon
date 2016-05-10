#include <stdio.h>

#include "moduleHandler.h"
#include "interfaceHandler.h"

int main(void){
    ih_activate();
    mh_activate();

    int calcModuleId = loadModule("examples/calculator/calc.so");
    //int cliModuleId = loadModule("examples/cli/cli.so");
    
    printf("print all registered modules: \n");
    lll_print(*(lll_List*)getAllRegisterdModules());
    printf("printed all registered modules: \n");
    
    unloadModule(calcModuleId);
    //unloadModule(cliModuleId);
    
    ih_deactivate();
    mh_deactivate();
    
    return 0;    
}
