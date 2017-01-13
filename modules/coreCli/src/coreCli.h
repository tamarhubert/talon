#ifndef _CORE_CLI_H_
#define _CORE_CLI_H_

void* coreCli_main(void *);
void (*tcc_tca_shutdown)(void);
int (*tcc_tca_log) (int, const char*, const char*, ...);

#endif /* _CORE_CLI_H_ */
