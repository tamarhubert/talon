#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "interfaceHandler.h"
#include "../lib/linkedListLibrary/LinkedList.h"

lll_List *moduleDefs;
int id_count = 0;

int ih_activate(){
    moduleDefs = malloc(sizeof(lll_List));
    return 0;
}
int ih_deactivate(){
    int i;
    for(i = lll_size(*moduleDefs)-1; i >= 0; i--){
        lll_Element *element = lll_elementAtIndex(*moduleDefs, i);
        tcore_ModuleDefinition *moduleDef = (tcore_ModuleDefinition*)element->value;
        deregisterInterface(moduleDef->id);
    }
    free(moduleDefs);
    return 0;
}

int registerInterface(tcore_ModuleDefinition *moduleDef){
    printf("%s\n",moduleDef->name);
    lll_Element *element = malloc(sizeof(lll_Element));
    element->value = moduleDef;
    lll_add(moduleDefs, element);
    
    moduleDef->id = id_count;
    id_count++;
    
    return moduleDef->id;
}
int deregisterInterface(int id){
    int i;
    printf("DEBUG: deregister interface with id %i\n", id);
    for(i = 0; i < lll_size(*moduleDefs); i++){
        lll_Element *element = lll_elementAtIndex(*moduleDefs, i);
        tcore_ModuleDefinition *moduleDef = (tcore_ModuleDefinition*)element->value;
        if(moduleDef->id == id){
            lll_removeAtIndex(moduleDefs, i);
            free(element);
            return 0;
        }
    }
    return -1;
}

tcore_Interface* getInterface(const char* moduleName, int moduleVersion, const char* interfaceName){
    int i;
    for(i = 0; i < lll_size(*moduleDefs); i++){
        lll_Element *mdElement = lll_elementAtIndex(*moduleDefs, i);
        tcore_ModuleDefinition *moduleDef = (tcore_ModuleDefinition*)mdElement->value;
        if(moduleDef->version.major == moduleVersion
                && strcmp(moduleDef->name, moduleName) == 0){
            int j; lll_List *interfaces = moduleDef->interfaces;
            for(j = 0; j < lll_size(*interfaces); j++){
                lll_Element *iElement = lll_elementAtIndex(*interfaces, i);
                tcore_Interface *interface = (tcore_Interface*)iElement->value;
                if(strcmp(interface->name, interfaceName) == 0){
                    return interface;
                }
            }
        }
    }
    return NULL;
}

lll_List* getAllRegisterdModules(){
    return moduleDefs;
}
