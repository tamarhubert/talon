#ifndef _CORE_API_LOGGING_H_
#define _CORE_API_LOGGING_H_

#include <stdarg.h>

#define TCA_LL_INFO 100
#define TCA_LL_DEBUG 200
#define TCA_LL_WARNING 300
#define TCA_LL_ERROR 400
#define TCA_LL_FATAL 500

void tca_setSink (int (*) (int, const char*, const char*, va_list));
void tca_setLogLevel (int);
int tca_log(int, const char*, const char*, ...);

#endif /* _CORE_API_LOGGING_H_ */
