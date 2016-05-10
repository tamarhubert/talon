#include "module.h"

#ifndef _LIBRARY_HANDLER_H_
#define _LIBRARY_HANDLER_H_

tcore_Module* loadLibrary(const char*);
int unloadLibrary(tcore_Module*);

#endif /* _LIBRARY_HANDLER_H_ */
