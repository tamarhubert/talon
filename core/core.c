#include <stdio.h>

#include "../lib/lll/LinkedList.h"
#include "moduleHandler.h"

int main(void){
    tcore_Module* calcModule = loadModule("examples/calculator/calc.so");
    if(!calcModule){
        return -1;
    }
    tcore_ModuleDefinition *calc= calcModule->getDefinition();
    tcore_Interface *additionInterface = (tcore_Interface*)lll_elementAtIndex(*calc->interfaces, 0)->value;
    int (*addition) (int, int) = (int (*) (int, int))additionInterface->function;


    printf("addition interface man:\n%s\n", additionInterface->man);
    printf("%i = addition(10, 5)\n", addition(10, 5));

    return unloadModule(calcModule);
}
