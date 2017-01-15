#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "../../../src/module.h"

#include "logging.h"

int tcore_defaultSink(int, const char*, const char*, va_list arg);
int tcore_logLevel = COREAPI_LL_DEBUG;
int (*tcore_sink) (int, const char*, const char*, va_list arg) = tcore_defaultSink;

int tcore_defaultSink(int level, const char* module, const char* message, va_list args){
  char* msg = malloc(sizeof(message)+2);
  strcpy(msg, message);
  strcat(msg, "\n");
  switch (level) {
    case COREAPI_LL_INFO:
      printf("[INFO:%.3i] %s: ", level, module);
      vprintf(msg, args);
      break;
    case COREAPI_LL_DEBUG:
      printf("[DEBUG:%3i] %s: ", level, module);
      vprintf(msg, args);
      break;
    case COREAPI_LL_WARNING:
      printf("[WARNING:%3i] %s: ", level, module);
      vprintf(msg, args);
      break;
    case COREAPI_LL_ERROR:
      printf("[ERROR:%3i] %s: ", level, module);
      vprintf(msg, args);
      break;
    case COREAPI_LL_FATAL:
      printf("[FATAL:%3i] %s: ", level, module);
      vprintf(msg, args);
      break;
    default:
      printf("[UNKNOWN:%.3i] %s: ", level, module);
      vprintf(msg, args);
  }
  va_end(args);
  return SUCCESS;
}

void tcore_setSink (int (*sink) (int, const char*, const char*, va_list)){
  tcore_sink = sink ? sink : tcore_defaultSink;
}

void tcore_setLogLevel (int level){
  tcore_logLevel = level;
}

int tcore_log (int level, const char* module, const char* message, ...){
  if(level >= tcore_logLevel){
    va_list args;
    va_start(args, message);
    int result = tcore_sink(level, module, message, args);
    va_end(args);
    return result;
  }
  return WARNING;
}
