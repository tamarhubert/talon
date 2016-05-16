#include <stdio.h>
#include "cli.h"

tcore_Interface* (*getInterface)(const char*, int, const char*);

void* getMethod(const char* moduleName, int moduleVersion, const char* functionName){
    return getInterface(moduleName, moduleVersion, functionName)->function;
}

void setResolver(tcore_Interface* (*_getInterface)(const char*, int, const char*)){
    getInterface = _getInterface;
}

void cli(void){
    int(*addtion)(int,int) = (int(*)(int,int))getMethod("calculator", 0, "addition");
    printf("%i\n", addition(5, 10));
}
