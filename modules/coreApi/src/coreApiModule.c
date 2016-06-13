#include <stdio.h>
#include <stdlib.h>

#include "../../../src/core.h"
#include "../../../src/module.h"
#include "../../../lib/linkedListLibrary/src/linkedList.h"

#define COREAPI_MODULE_NAME "coreApi"
#define COREAPI_MODULE_VERSION_MAJOR 0
#define COREAPI_MODULE_VERSION_MINOR 0

tcore_Metadata *coreApi_module;

int onLoad() {
    // build coreApi_module
    coreApi_module = malloc(sizeof(tcore_Metadata));
    coreApi_module->name = COREAPI_MODULE_NAME;
    coreApi_module->version.major = COREAPI_MODULE_VERSION_MAJOR;
    coreApi_module->version.minor = COREAPI_MODULE_VERSION_MINOR;
    coreApi_module->dependencies = lll_newList();
    coreApi_module->interfaces = lll_newList();

    // shotdown
    tcore_Interface *shotdownInterface = calloc(1, sizeof(tcore_Interface));
    shotdownInterface->name = "shotdown";
    shotdownInterface->prototype = "void shotdown (void)";
    shotdownInterface->man = "void shotdown ()\n\
\t\tShotsdown talon.\n";
    shotdownInterface->function = (void (*) ()) tcore_shotdown;
    lll_add(coreApi_module->interfaces, shotdownInterface);

    return SUCCESS;
}

tcore_Metadata* getMetadata(){
	return coreApi_module;
}

int onActivation(tcore_Interface* (*getInterface)(const char*, int, const char*)){
	return SUCCESS;
}

int onDeactivation(){
	return SUCCESS;
}

int onUnload(){
    lll_freeList(coreApi_module->dependencies);
    void *shotdownInterface = lll_elementAtIndex(*coreApi_module->interfaces, 0);
    free(shotdownInterface);
    lll_freeList(coreApi_module->interfaces);
    free(coreApi_module);
    coreApi_module = NULL;
    return SUCCESS;
}


