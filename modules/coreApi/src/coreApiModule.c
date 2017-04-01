#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

#include "core.h"
#include "module.h"
#include "main.h"

#include "logging.h"
#include "coreApi.h"

static tmm_Module *tca_module;

int tca_onLoad(tmm_Module* module) {
  tmm_newModule(
    TCA_MODULE_NAME,
    TCA_MODULE_VERSION_MAJOR,
    TCA_MODULE_VERSION_MINOR,
    &tca_module
  );

  tmm_addFunction(
    tca_module,
    "shutdown",
    "void shutdown (void)",
    "void shutdown ()\n\
\tShuts talon down.\n",
    (void (*) ()) tca_shutdown
  );

  tmm_addFunction(
    tca_module,
    "getFunction",
    "int getFunction (const char*, int, const char*, tmf_Function*)",
    "int getFunction (const char* moduleName, int moduleVersion, const char* functionName, tmf_Function* result)\n\
\tis used to obtain references to another modules functions\n\
\tTODO: parameter description",
    (void (*) ()) tca_getFunction
  );

  // logging
  // log

  tmm_addFunction(
    tca_module,
    "log",
    "int log (int, const char*, const char*, ...)",
    "int log (int level, const char* module, const char* message, ...)\n\
\tLogs message to sink.\n\n\
\tlevel\tLog level, used to filter log messages\n\
\tmodule\tCalling modules name\n\
\tmessage\tMessage to be logged into sink\n\
\t...\tArgs similar to printf\n\n\
\treturns\tMessage passed (SUCCESS), message suppressed (WARNING)",
    (void (*) ()) tca_log
  );

  // set sink

  tmm_addFunction(
    tca_module,
    "setSink",
    "void setSink (int (*) (int, const char*, const char*))",
    "void setSink (int (*sink) (int, const char*, const char*))\n\
\tSets sink to be logged into.\n\n\
\tsink\tFunction pointer to function called by 'log'",
    (void (*) ()) tca_setSink
  );

  // set log level

  tmm_addFunction(
    tca_module,
    "setLogLevel",
    "void setLogLevel (int)",
    "void setLogLevel (int level)\n\
\tSets log level (default 'debug').\n\n\
\tlevel\tLog level, ...",
    (void (*) ()) tca_setLogLevel
  );

  *module = *tca_module;

  return SUCCESS;
}

int tca_onActivation(tc_ModulePool *pool){
  tca_setPool(pool);
  return SUCCESS;
}

int tca_onDeactivation(){
  return SUCCESS;
}

int tca_onUnload(){
  tmm_freeModule(tca_module);
  return SUCCESS;
}
