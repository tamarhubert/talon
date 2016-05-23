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
    int i, status = 0;
    for(i = lll_size(*modules)-1; i >= 0; i--){
        lll_Element *element = lll_elementAtIndex(*modules, i);
        tcore_Module *module = (tcore_Module*)element->value;
        int state = unloadModule(module->id);
        if(state < status){
            status = state;
        }
    }
    free(modules);
    return status;
}

int loadModule(const char* path){
    tcore_Module *module = loadLibrary(path);
    if(!module){
        return FATAL;
    }
    if(registerInterface(module->id, module->getMetadata()) < WARNING){
        unloadLibrary(module);
        return FATAL;
    }
    if(module->activate(getInterface) < WARNING){
        deregisterInterface(module->id);
        unloadLibrary(module);
        return FATAL;
    }
    
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
            return SUCCESS;
        }
    }
    return WARNING;   
}
