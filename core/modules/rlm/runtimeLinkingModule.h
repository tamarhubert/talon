#include "../module.h"
#include "../../lib/runtimeLinkingLib.h"

#ifndef RUNTIME_LINKING_MODULE_H_
#define RUNTIME_LINKING_MODULE_H_

int rlm_getModule(tcore_module*);
int rlm_onLoad(getFuntion);
int rlm_onDestroy();

#endif /* RUNTIME_LINKING_MODULE_H_ */
