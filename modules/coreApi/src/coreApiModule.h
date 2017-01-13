#ifndef _CORE_API_MODULE_H_
#define _CORE_API_MODULE_H_


int coreApi_onLoad(void);
tcore_Metadata* coreApi_getMetadata(void);
int coreApi_onActivation(
    tcore_Interface* (*getInterface)(const char*, int, const char*));
int coreApi_onDeactivation(void);
int coreApi_onUnload(void);


#endif /* _CORE_API_H_ */
