#include <stdio.h>
#include <stdlib.h>

#include "core.h"
#include "module.h"

#include "coreApiModule.h"
#include "logging.h"
#include "coreApi.h"

#define TC_LOG_NAME "tca:core"

tca_setLogLevel(TCA_LL_INFO);
int main(void){

  tmm_Module *coreApi = malloc(sizeof(tmm_Module));
  tca_onLoad(coreApi);

  tc_ModulePool *pool;
  tc_newModulePool(coreApi, &pool);

  tca_onActivation(pool);


  int coreCliId = tca_loadModule("modules/coreCli/bin/coreCli.so");

  while(tca_getIsActive()){
#ifdef _WIN32
#include <windows.h>
    Sleep(100);
#elif __linux__
#include <unistd.h>
    usleep(100*1000);
#else
    #error "Unknown compiler"
#endif
  }

  tca_log(TCA_LL_DEBUG, TC_LOG_NAME, "shutting down...");

  tca_unloadModule(coreCliId);

  tca_onDeactivation();
  tca_onUnload();
  tc_freeModulePool(pool);

  tca_log(TCA_LL_DEBUG, TC_LOG_NAME, "bye.");

  return 0;
}
