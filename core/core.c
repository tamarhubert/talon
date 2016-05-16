#include <stdio.h>

#include "module.h"
#include "moduleHandler.h"
#include "interfaceHandler.h"

int main(void){
    ih_activate();
    mh_activate();

    int calcModuleId =  loadModule("examples/calculator/calc.so");
    int cliModuleId =   loadModule("examples/cli/cli.so");
    printf("%i\n",calcModuleId);
    printf("%i\n",cliModuleId);
    
    printf("registerd prototypes:\n\n");
    lll_List *modules = getAllRegisterdModules();
    int i;
    for(i = lll_size(*modules)-1; i >= 0; i--){
        int j;
        tcore_ModuleDefinition *moduleDef = ((tcore_ModuleDefinition*)lll_elementAtIndex(*modules, i)->value);
        lll_List *interfaces = moduleDef->interfaces;
        printf("%s: m-id:%i c:%i\n",moduleDef->name, moduleDef->id, lll_size(*interfaces));
        for(j = lll_size(*interfaces)-1; j >= 0; j--){
            printf("%s\n", ((tcore_Interface*)lll_elementAtIndex(*interfaces, j)->value)->man);
        }
    }
    
    //mh_print();
    
    tcore_Interface *cliInterface = getInterface("cli", 0, "cli");
    if(!cliInterface){
        printf("cli::cli interface not found\n");
    }
    else {
        void(*cli)(void) = (void(*)(void))cliInterface->function;
        printf("calling cli::cli\n");
        cli();
    }
    
    printf("unload calc module (%i)\n",calcModuleId);
    printf("\t returned %i",unloadModule(calcModuleId));
    /**
    printf("registerd prototypes:\n\n");
    for(i = lll_size(*modules)-1; i >= 0; i--){
        int j;
        tcore_ModuleDefinition *moduleDef = ((tcore_ModuleDefinition*)lll_elementAtIndex(*modules, i)->value);
        lll_List *interfaces = moduleDef->interfaces;
        printf("%s: %i\n",moduleDef->name, lll_size(*interfaces));
        for(j = lll_size(*interfaces)-1; j >= 0; j--){
            printf("%s\n", ((tcore_Interface*)lll_elementAtIndex(*interfaces, j)->value)->man);
        }
    }
    **/
    printf("unload calc module (%i)\n",cliModuleId);
    printf("\t returned %i",unloadModule(cliModuleId));
    
    
    ih_deactivate();
    mh_deactivate();
    
    return 0;    
}
