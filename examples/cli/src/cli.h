#ifndef _CALC_H_
#define _CALC_H_

#include "../../../src/module.h"

void cli();

void setResolver(tcore_Interface* (*)(const char*, int, const char*));

#endif /* _CALC_H_ */
