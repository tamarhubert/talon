#include "../../../src/libraryHandler.h"
#include "../../../src/moduleHandler.h"
#include "../../../src/module.h"

#include "coreApi.h"
#include "logging.h"

lll_List *tcore_modules;

int tcore_init(){
  tcore_modules = lll_newList();
  return SUCCESS;
}

int tcore_deinit(){
  int i;
  for(i = 0; i < lll_size(tcore_modules); i++){
    tcore_Library *library = NULL;
    lll_elementAtIndex(tcore_modules, i, (void**)&library);
    tcore_Metadata *metadata = library->module->getMetadata();
    tcore_log(COREAPI_LL_INFO, "tcore", "unloading module %s v%i.%i",
      metadata->name, metadata->version.major, metadata->version.minor);
    unloadModule(library->module);
    unloadLibrary(library);
    lll_removeAtIndex(tcore_modules, i);
    tcore_log(COREAPI_LL_INFO, "tcore", "unloaded module");
  }
  return SUCCESS;
}

int tcore_loadModule(const char* path){
  tcore_Library *library = loadLibrary(path);
  if(NULL == library){
    tcore_log(COREAPI_LL_ERROR, "tcore", "failed to load library at %s", path);
    return FATAL;
  }
  tcore_log(COREAPI_LL_INFO, "tcore", "loaded library at %s", path);

  if(loadModule(library->module) < WARNING){
    tcore_log(COREAPI_LL_ERROR, "tcore", "failed to load moudle at %s", path);
    return FATAL;
  }
  tcore_Metadata *metadata = library->module->getMetadata();
  tcore_log(COREAPI_LL_INFO, "tcore", "loaded module %s v%i.%i",
    metadata->name, metadata->version.major, metadata->version.minor);

  lll_add(tcore_modules, (void*)library);
  return library->module->id;
}

int tcore_unloadModule(int id){
  int i;
  for(i = 0; i < lll_size(tcore_modules); i++){
    tcore_Library *library = NULL;
    lll_elementAtIndex(tcore_modules, i, (void**)&library);
    if(library->module->id == id){
      tcore_Metadata *metadata = library->module->getMetadata();
      tcore_log(COREAPI_LL_INFO, "tcore", "unloading module %s v%i.%i",
        metadata->name, metadata->version.major, metadata->version.minor);
      unloadModule(library->module);
      unloadLibrary(library);
      lll_removeAtIndex(tcore_modules, i);
      tcore_log(COREAPI_LL_INFO, "tcore", "unloaded module");
      return SUCCESS;
    }
  }
  tcore_log(COREAPI_LL_WARNING, "tcore", "No module loaded with id %i", id);
  return WARNING;
}

int tcore_getModules(lll_List** modules){
  return FATAL;
}
