#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cli.h"

void* cli_main(void * na){
    int r = 0;
    do{
        printf("first number: ");
        int p1 = 0;
        scanf("%i", &p1);
        printf("first number: %i\n", p1);

        printf("second number: ");
        int p2 = 0;
        scanf("%i", &p2);
        printf("second number: %i\n", p2);

        r = cli_clc_add(p1,p2);
        printf("result: %i\n", r);
    }while(r != 0);
    cli_tca_shutdown();
    return NULL;
}


void readCommand(){
    //expected format: module.version.interface(params,...)
    char command[128];
    fgets(command, sizeof(command), stdin);
    fputs(command, stdout);
}
