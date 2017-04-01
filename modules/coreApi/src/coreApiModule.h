#ifndef _CORE_API_MODULE_H_
#define _CORE_API_MODULE_H_


int tca_onLoad(tmm_Module*);
int tca_onActivation(
    tc_ModulePool* pool);
int tca_onDeactivation(void);
int tca_onUnload(void);


#endif /* _CORE_API_H_ */
