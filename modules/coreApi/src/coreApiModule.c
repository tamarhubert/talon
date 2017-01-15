#include <stdio.h>
#include <stdlib.h>
#include "../../../lib/linkedListLibrary/src/linkedList.h"

#include "../../../src/core.h"
#include "../../../src/module.h"

#include "coreApi.h"
#include "logging.h"

#define COREAPI_MODULE_NAME "coreApi"
#define COREAPI_MODULE_VERSION_MAJOR 0
#define COREAPI_MODULE_VERSION_MINOR 0

tcore_Metadata *coreApi_module;

int coreApi_onLoad() {
    // build coreApi_module
    coreApi_module = malloc(sizeof(tcore_Metadata));
    coreApi_module->name = COREAPI_MODULE_NAME;
    coreApi_module->version.major = COREAPI_MODULE_VERSION_MAJOR;
    coreApi_module->version.minor = COREAPI_MODULE_VERSION_MINOR;
    coreApi_module->dependencies = lll_newList();
    coreApi_module->interfaces = lll_newList();

    // shutdown
    tcore_Interface *shutdownInterface = malloc(sizeof(tcore_Interface));
    shutdownInterface->name = "shutdown";
    shutdownInterface->prototype = "void shutdown (void)";
    shutdownInterface->man = "void shutdown ()\n\
\tShuts talon down.\n";
    shutdownInterface->function = (void (*) ()) tcore_shutdown;
    lll_add(coreApi_module->interfaces, shutdownInterface);

    // logging
    // log
    tcore_Interface *logInterface = malloc(sizeof(tcore_Interface));
    logInterface->name = "log";
    logInterface->prototype = "int log (int, const char*, const char*, ...)";
    logInterface->man = "int log (int level, const char* module, const char* message, ...)\n\
\tLogs message to sink.\n\n\
\tlevel\tLog level, used to filter log messages\n\
\tmodule\tCalling modules name\n\
\tmessage\tMessage to be logged into sink\n\
\t...\tArgs similar to printf\n\n\
\treturns\tMessage passed (SUCCESS), message suppressed (WARNING)";
    logInterface->function = (void (*) ()) tcore_log;
    lll_add(coreApi_module->interfaces, logInterface);

    // set sink
    tcore_Interface *setSinkInterface = malloc(sizeof(tcore_Interface));
    setSinkInterface->name = "setSink";
    setSinkInterface->prototype = "void setSink (int (*) (int, const char*, const char*))";
    setSinkInterface->man = "void setSink (int (*sink) (int, const char*, const char*))\n\
\tSets sink to be logged into.\n\n\
\tsink\tFunction pointer to function called by 'log'";
    setSinkInterface->function = (void (*) ()) tcore_setSink;
    lll_add(coreApi_module->interfaces, setSinkInterface);

    // set log level
    tcore_Interface *setLogLevelInterface = malloc(sizeof(tcore_Interface));
    setLogLevelInterface->name = "setLogLevel";
    setLogLevelInterface->prototype = "void setLogLevel (int)";
    setLogLevelInterface->man = "void setLogLevel (int level)\n\
\tSets log level (default 'debug').\n\n\
\tlevel\tLog level, ...";
    setLogLevelInterface->function = (void (*) ()) tcore_setLogLevel;
    lll_add(coreApi_module->interfaces, setLogLevelInterface);

    return SUCCESS;
}

tcore_Metadata* coreApi_getMetadata(){
	return coreApi_module;
}

int coreApi_onActivation(tcore_Interface* (*getInterface)(const char*, int, const char*)){
  tcore_init();
	return SUCCESS;
}

int coreApi_onDeactivation(){
  tcore_deinit();
  return SUCCESS;
}

int coreApi_onUnload(){
  // free dependencies
  int i;
  tcore_Dependency *dependency = NULL;
  for(i = 0; i < lll_size(coreApi_module->dependencies); i++){
    lll_elementAtIndex(coreApi_module->dependencies, i, (void**)&dependency);
    lll_removeAtIndex(coreApi_module->dependencies, i);
    free(dependency);
  }
  lll_freeList(coreApi_module->dependencies);

  // free interfaces
  tcore_Interface *interface = NULL;
  for(i = 0; i < lll_size(coreApi_module->interfaces); i++){
    lll_elementAtIndex(coreApi_module->interfaces, i, (void**)&interface);
    lll_removeAtIndex(coreApi_module->interfaces, i);
    free(interface);
  }
  lll_freeList(coreApi_module->interfaces);

  free(coreApi_module);
  coreApi_module = NULL;

  return SUCCESS;
}
