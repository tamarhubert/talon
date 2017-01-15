#ifndef _CORE_CLI_H_
#define _CORE_CLI_H_

int (*tcc_tca_log) (int, const char*, const char*, ...);

void* coreCli_main(void *);

void (*tcc_tca_shutdown)(void);


void (*tcc_tca_setLogLevel) (int);

#endif /* _CORE_CLI_H_ */
