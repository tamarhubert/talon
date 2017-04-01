#include <stdlib.h>
#include <stdio.h>
#include "runtimeLinking.h"

#include "library.h"
#include "logging.h"

#include "main.h"

#define TCL_LOAD "onLoad"
#define TCL_ACTIVATE "onActivation"
#define TCL_METADATA "getMetadata"
#define TCL_DEACTIVATE "onDeactivation"
#define TCL_UNLOAD "onUnload"

#define TCL_LOG_NAME "tcore:library"

char *lh_error;

struct tcl_LibraryRegistry {
  lll_List *libraries;
  lll_List *indexes;
};

int tcl_newLibrarayRegistry(tcl_LibraryRegistry **result){
  *result = malloc(sizeof(tcl_LibraryRegistry));
  (*result)->libraries = lll_newList();
  (*result)->indexes = lll_newList();
  if(!*result || !(*result)->libraries || !(*result)->indexes){
    return ERROR;
  }
  return SUCCESS;§
}

int tcl_addLibrary(tcl_LibraryRegistry *registry, int _id, tc_Library *library){
  lll_add(registry->libraries, library);
  int *id = malloc(sizeof(int));
  *id = _id;
  lll_add(registry->indexes, id);
  return SUCCESS;
}

int tcl_popLibrary(tcl_LibraryRegistry *registry, int id, tc_Library **result){
  int index, *_id;
  for(index = 0; index < lll_size(registry->indexes); index++){
    lll_elementAtIndex(registry->indexes, index, (void**)&_id);
    if(*_id == id){
      break;
    }
  }
  lll_elementAtIndex(registry->libraries, index, (void**)result);
  lll_removeAtIndex(registry->libraries, index);
  lll_removeAtIndex(registry->indexes, index);
  return SUCCESS;
}

int tcl_freeLibraryRegistry(tcl_LibraryRegistry *registry){
  lll_freeList(registry->libraries);
  lll_freeList(registry->indexes);
  free(registry);
  return SUCCESS;
}

int tcl_loadLibrary(const char* path, tc_Library** result){
  tc_Library* library = malloc(sizeof(tc_Library));

  tca_log(TCA_LL_DEBUG, TCL_LOG_NAME, "loading library \"%s\"", path);
  library->handle = rll_open(path);
  if(!library->handle){
    lh_error = rll_error();
    tca_log(TCA_LL_ERROR, TCL_LOG_NAME, "failed to rll open \"%s\" (%s)", path, lh_error);
    return ERROR;
  }
  tca_log(TCA_LL_INFO, TCL_LOG_NAME, "rll opened \"%s\"", path);

  tca_log(TCA_LL_DEBUG, TCL_LOG_NAME, "factoring library...");
  library->load = rll_get(library->handle, TCL_LOAD);
  if(library->load == NULL){
    tca_log(TCA_LL_ERROR, TCL_LOG_NAME, "failed to rll get \"%s\"", TCL_LOAD);
    rll_close(library->handle);
    return ERROR;
  }
  tca_log(TCA_LL_INFO, TCL_LOG_NAME, "rll got %s", TCL_LOAD);

  library->activate = rll_get(library->handle, TCL_ACTIVATE);
  if(library->activate == NULL){
    tca_log(TCA_LL_ERROR, TCL_LOG_NAME, "failed to rll get \"%s\"", TCL_ACTIVATE);
    rll_close(library->handle);
    return ERROR;
  }
  tca_log(TCA_LL_INFO, TCL_LOG_NAME, "rll got %s", TCL_ACTIVATE);

  library->deactivate = rll_get(library->handle, TCL_DEACTIVATE);
  if(library->deactivate == NULL){
    tca_log(TCA_LL_ERROR, TCL_LOG_NAME, "failed to rll get \"%s\"", TCL_DEACTIVATE);
    rll_close(library->handle);
    return ERROR;
  }
  tca_log(TCA_LL_INFO, TCL_LOG_NAME, "rll got %s", TCL_DEACTIVATE);

  library->unload = rll_get(library->handle, TCL_UNLOAD);
  if(library->unload == NULL){
    tca_log(TCA_LL_ERROR, TCL_LOG_NAME, "failed to rll get \"%s\"", TCL_UNLOAD);
    rll_close(library->handle);
    return ERROR;
  }
  tca_log(TCA_LL_INFO, TCL_LOG_NAME, "rll got %s", TCL_UNLOAD);
  tca_log(TCA_LL_DEBUG, TCL_LOG_NAME, "created library.");

  *result = library;

  return SUCCESS;
}

int tcl_unloadLibrary(tc_Library* library){
  if(NULL == library){
    return WARNING;
  }

  if(NULL != library->handle){
    rll_close(library->handle);
  }

  free(library);

  return SUCCESS;
}

char* lh_getError(void){
  return lh_error;
}
