#ifndef _TCORE_LIBRARY_H_
#define _TCORE_LIBRARY_H_

#include "module.h"
#include "function.h"
typedef struct tc_Library tc_Library;


typedef struct tcl_LibraryRegistry tcl_LibraryRegistry;
int tcl_newLibrarayRegistry(tcl_LibraryRegistry **result);
int tcl_addLibrary(tcl_LibraryRegistry *registry, int _id, tc_Library *library);
int tcl_popLibrary(tcl_LibraryRegistry *registry, int id, tc_Library **result);
int tcl_freeLibraryRegistry(tcl_LibraryRegistry *registry);

struct tc_Library {
  void* handle;
  int (* load) (tmm_Module*);
  int (* activate) (tmf_Function);
  int (* deactivate) (void);
  int (* unload) (void);
};
int tcl_loadLibrary(const char* path, tc_Library** result);
int tcl_unloadLibrary(tc_Library*);

#endif /* _TCORE_LIBRARY_H_ */
