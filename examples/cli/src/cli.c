#include <stdio.h>
#include "cli.h"

void* cli(void * na){
    char cmd = ' ';
    while(cmd != 'q'){
        cmd = getchar();
        printf("\n%c\n",cmd);
    }
    shotdown();
    printf(" -- [ DEBUG ] -- exitig cli\n");   
    return NULL;
}


void readCommand(){
    //expected format: module.version.interface(params,...)
    char command[128];
    fgets(command, sizeof(command), stdin);
    fputs(command, stdout);
}
