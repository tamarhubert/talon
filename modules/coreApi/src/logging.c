#include <stdlib.h>
#include <string.h>

#include "module.h"

#include "logging.h"
#include "main.h"

int tca_defaultSink(int, const char*, const char*, va_list arg);
int tca_logLevel = TCA_LL_DEBUG;
int (*tca_sink) (int, const char*, const char*, va_list arg) = tca_defaultSink;

int tca_defaultSink(int level, const char* module, const char* message, va_list args){
  char* msg = malloc(strlen(message)+2);
  strcpy(msg, message);
  strcat(msg, "\n\0");
if(level >= TCA_LL_FATAL) {
    printf("[FATAL:%3i] %s: ", level, module);
    vprintf(msg, args);
  } else if(level >= TCA_LL_ERROR) {
    printf("[ERROR:%3i] %s: ", level, module);
    vprintf(msg, args);
  } else if(level >= TCA_LL_WARNING) {
    printf("[WARNING:%3i] %s: ", level, module);
    vprintf(msg, args);
  } else if(level >= TCA_LL_DEBUG) {
    printf("[DEBUG:%3i] %s: ", level, module);
    vprintf(msg, args);
  } else {
    printf("[INFO:%.3i] %s: ", level, module);
    vprintf(msg, args);
  }
  return SUCCESS;
}

void tca_setSink (int (*sink) (int, const char*, const char*, va_list)){
  tca_sink = sink ? sink : tca_defaultSink;
}

void tca_setLogLevel (int level){
  tca_logLevel = level;
}

int tca_log (int level, const char* module, const char* message, ...){
  if(level >= tca_logLevel){
    va_list args;
    va_start(args, message);
    int result = tca_sink(level, module, message, args);
    va_end(args);
    return result;
  }
  return WARNING;
}
