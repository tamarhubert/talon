#include <stdio.h>
#include <stdlib.h>

#include "../../../src/core.h"
#include "../../../src/module.h"
#include "../../../lib/linkedListLibrary/src/linkedList.h"

#define COREAPI_MODULE_NAME "coreApi"
#define COREAPI_MODULE_VERSION_MAJOR 0
#define COREAPI_MODULE_VERSION_MINOR 0

tcore_Metadata *coreApi_module;

int coreApi_onLoad() {
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

tcore_Metadata* coreApi_getMetadata(){
	return coreApi_module;
}

int coreApi_onActivation(tcore_Interface* (*getInterface)(const char*, int, const char*)){
	return SUCCESS;
}

int coreApi_onDeactivation(){
	return SUCCESS;
}

int coreApi_onUnload(){
    lll_freeList(coreApi_module->dependencies);
    tcore_Interface *shotdownInterface = NULL;
    lll_elementAtIndex(coreApi_module->interfaces, 0, (void**)&shotdownInterface);
    lll_removeAtIndex(coreApi_module->interfaces,0);
    free(shotdownInterface);
    lll_freeList(coreApi_module->interfaces);
    free(coreApi_module);
    coreApi_module = NULL;
    return SUCCESS;
}


