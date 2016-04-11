#include <stdlib.h>
#include <string.h>

int pattern_whereKey(LinkedList);

typedef struct _module _module;

struct _module {
	tcore_Module module;
	int (*getModule)( tcore_Module* );
	int (*onLoad)( getFunction );
	int (*onDestroy)( void );
	rll_Library lib;
};

LinkedList **rootModule;
char* core_key;
int core_abrot = 1;

int main(void) {
	rootModule = calloc(1, sizeof(LinkedList));
	while (abrot!=0){
		destroyAllModules();
	}
}

void abrot(){
	abrot = 0;
}

int loadModule(_module m, int level){
	int (*getModule) (tcore_Module*) = rll_getFunction(m.lib, "getModule");
	if(getModule == NULL){
		return LOAD_FAILED;
	}
	
	m.module = calloc(1, sizeof(tcore_Module));
	if (level < getModule(m.module)){
		return LOAD_FAILED;
	}
	if(validateModel(m.module) != MODEL_SUCCESS){
		return LOAD_FAILED;
	}
	if(checkDependencies(m.module) != DEPENDENCIES_SUCCESS){
		return LOAD_FAILED;
	}
	int (*onLoad) (getMothod*) = rll_getFunction(m.lib, "onLoad")
	if(onLoad == NULL){
		return LOAD_FAILED;
	}
	if (level < onLoad(getMethod)){
		return LOAD_FAILED;
	}
	lll_add(rootModule, m);
}

int destroyModule(_module m, int level){
	// FOR MODULE IN MODULES:
	//	FOR DEPENDENCY IN MODULE.DEPENDENCIES:
	//		IF DEPENDENCY.EQUALS(LIB.MODULE):
	//			RETURN TRUE
	// RETRUN FALSE

	int (*onDestroy) () = rll_getFunction(m.lib, "onDestroy");
	if(onDestroy == NULL){
		return DESTROY_FAILED;
	}
	if(level < onDestroy()){
		return DESTROY_FAILED;
	}
	rll_destroy(m.lib);
	lll_remove(rootModule, m) 
	return DESTROY_SUCCESS;
}

int hasDependencies(tcore_Module module){
	// FOR MODULE IN MODULES:
	//	FOR DEPENDENCY IN MODULE.DEPENDENCIES:
	//		IF DEPENDENCY.EQUALS(MODULE):
	//			RETURN TRUE
	// RETRUN FALSE
}

int checkDependencies(LinkedList dependencies){
	// FOR DEPENDENCY IN DEPENDENCIES:
	//	FOR MODULE IN MODULES:
	//		IF MODULE.NAME.EQUALES( DEPENDENCY.MODULE_NAME ):
	//			RETURN TRUE
	//	RETURN FLASE
}

tcore_Method getMethod(tcore_Module module, char* name){
	// FOR DEPENDENCY IN MODULE.DEPENDENCIES:
	//	MODULE = GET_MODULE(DEPENDENCY)
	//	FOR METHOD IN MODULE.METHODS:
	//		IF( METHOD.NAME.EQUALS(NAME) ):
	//			RETURN METHOD
	// RETURN NULL
}

int pattern_whereKey(LinkedList entry){
    if(strcmp(((CommandEntry*)entry.value)->key, core_key) == 0){
        return ENTRY_MATCH;
    }
    return ENTRY_DISMATCH;
}
