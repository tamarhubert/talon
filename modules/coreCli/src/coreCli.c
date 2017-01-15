#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "coreCli.h"
#include "../../coreApi/src/logging.h"

void coreCli_logging(void);
void coreCli_setLogLevel(void);
void coreCli_log(void);
void coreCli_modules(void);

const char* coreCli_menu = "\n\
Main Menu\n\
1)\tlogging\n\
2)\tmodules\n\n\
0)\tshutdown\n\
>> ";

void* coreCli_main(void * na){
  int r = 0;
  do{
    printf("%s", coreCli_menu);
    scanf("%i", &r);

    tcc_tca_log(COREAPI_LL_INFO, "coreCli", "input: %i", r);
    switch (r) {
      case 1:
        coreCli_logging();
        break;
      case 2:
        coreCli_modules();
        break;
    }
  }while(r != 0);
  tcc_tca_shutdown();
  tcc_tca_log(COREAPI_LL_INFO, "coreCli", "shutting down");

  return NULL;
}

const char* coreCli_menu_logging = "\n\
Logging Menu\n\
1)\tset log level\n\
2)\tlog\n\n\
0)\tmain menu\n\
>> ";

void coreCli_logging(){
  int r = 0;
  do{
    printf("%s", coreCli_menu_logging);
    scanf("%i", &r);

    tcc_tca_log(COREAPI_LL_INFO, "coreCli", "input: %i", r);
    switch (r) {
      case 1:
        coreCli_setLogLevel();
        break;
      case 2:
        coreCli_log();
        break;
    }
  }while(r != 0);
}

void coreCli_setLogLevel(){
  int newLogLevel = 0;
  printf("new log level?\n>> ");
  scanf("%i", &newLogLevel);

  tcc_tca_setLogLevel(newLogLevel);
}

void coreCli_log(){
    int logLevel = 0;
    printf("log level?\n>> ");
    scanf("%i", &logLevel);
    getchar();

    char message[256];
    printf("log message? (max. 255)\n>> ");
    fgets(message, sizeof(message), stdin);

    tcc_tca_log(logLevel, "coreCli", message);
}

void coreCli_modules(){
  printf("soon...");
}
