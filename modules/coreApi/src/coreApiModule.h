#ifndef _COREAPI_H_
#define _COREAPI_H_


int coreApi_onLoad(void);
tcore_Metadata* coreApi_getMetadata(void);
int coreApi_onActivation(
    tcore_Interface* (*getInterface)(const char*, int, const char*));
int coreApi_onDeactivation(void);
int coreApi_onUnload(void);


#endif /* _COREAPI_H_ */
