#ifndef _CORE_API_H_
#define _CORE_API_H_

#define COREAPI_LL_INFO 100
#define COREAPI_LL_DEBUG 200
#define COREAPI_LL_WARNING 300
#define COREAPI_LL_ERROR 400
#define COREAPI_LL_FATAL 500

void tcore_setSink (int (*) (int, const char*, const char*, va_list));
void tcore_setLogLevel (int);
int tcore_log(int, const char*, const char*, ...);

#endif /* _CORE_API_H_ */
