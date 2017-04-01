#ifndef _CORE_CLI_H_
#define _CORE_CLI_H_

#define TCC_LOG_NAME "tcc:module"

void* coreCli_main(void *);

void (*tcc_tca_setLogLevel) (int);
int (*tcc_tca_log) (int, const char*, const char*, ...);
void (*tcc_tca_shutdown)(void);

#endif /* _CORE_CLI_H_ */
