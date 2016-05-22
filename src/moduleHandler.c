#include <stdlib.h>
#include <stdio.h>

#include "moduleHandler.h"
#include "libraryHandler.h"
#include "interfaceHandler.h"
#include "../lib/linkedListLibrary/src/linkedList.h"

void mh_print(void);

lll_List *modules;

int mh_activate(){
    modules = malloc(sizeof(lll_List));
    return 0;
}

int mh_deactivate(){
    int i;
    for(i = lll_size(*modules)-1; i >= 0; i--){
        lll_Element *element = lll_elementAtIndex(*modules, i);
        tcore_Module *module = (tcore_Module*)element->value;
        unloadModule(module->id);
    }
    free(modules);
    return 0;
}

int loadModule(const char* path){
    tcore_Module *module = loadLibrary(path);
    if(!module){
        return -1;
    }
    registerInterface(module->id, module->getMetadata());
    module->activate(getInterface);
    lll_Element *element = malloc(sizeof(lll_Element));
    element->value = module;
    lll_add(modules, element);      
    return module->id;
}

int unloadModule(int id){
    int i;
    for(i = 0; i < lll_size(*modules); i++){
        lll_Element *element = lll_elementAtIndex(*modules, i);
        tcore_Module *module = (tcore_Module*)element->value;
        if(module->id == id){
            deregisterInterface(id);
            module->deactivate();
            lll_removeAtIndex(modules, i);
            free(element);
            unloadLibrary(module);
            return 0;
        }
    }
    return -1;   
}
