#include <stdio.h>
#include "cli.h"

tcore_Interface* (*getInterface)(const char*, int, const char*);


void setResolver(tcore_Interface* (*_getInterface)(const char*, int, const char*)){
    getInterface = _getInterface;
}

void* getMethod(const char* moduleName, int moduleVersion, const char* functionName){
    return getInterface(moduleName, moduleVersion, functionName)->function;
}

void readCommand(void);

void cli(void){
    //int(*addtion)(int,int) = (int(*)(int,int))getMethod("calculator", 0, "addition");
    //printf("%i\n", addition(5, 10));
    readCommand();
}


void readCommand(){
    //expected format: module.version.interface(params,...)
    char command[128];
    fgets(command, sizeof(command), stdin);
    fputs(command, stdout);
}


