#ifndef _CALC_H_
#define _CALC_H_

#include "../../../src/module.h"

void* cli_main(void*);
int (*cli_clc_add)(int,int);
void (*cli_tca_shutdown)(void);

#endif /* _CALC_H_ */
