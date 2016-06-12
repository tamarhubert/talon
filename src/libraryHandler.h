#include "module.h"

#ifndef _LIBRARY_HANDLER_H_
#define _LIBRARY_HANDLER_H_

typedef struct tcore_Library tcore_Library;

struct tcore_Library {
    void* handle;
    tcore_Module *module;
};


tcore_Library* loadLibrary(const char*);
int unloadLibrary(tcore_Library*);

#endif /* _LIBRARY_HANDLER_H_ */
