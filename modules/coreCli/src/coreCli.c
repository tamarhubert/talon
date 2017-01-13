#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "coreCli.h"
#include "../../coreApi/src/coreApi.h"

void printMenu(void);

const char* coreCli_menu = "\
0)\tshut down\n\
";

void* coreCli_main(void * na){
    int r = 0;
    do{
        printMenu();
        scanf("%i", &r);
        tcc_tca_log(COREAPI_LL_INFO, "coreCli", "input: %i", r);
    }while(r != 0);
    tcc_tca_shutdown();
    tcc_tca_log(COREAPI_LL_INFO, "coreCli", "shutting down");

    return NULL;
}

void printMenu(){
  printf("%s\n", coreCli_menu);
}
