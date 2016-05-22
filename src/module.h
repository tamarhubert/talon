#include "../lib/linkedListLibrary/src/linkedList.h"

#ifndef TCORE_MODULE_H_
#define TCORE_MODULE_H_

#define MH_LOAD "onLoad"
#define MH_ACTIVATE "onActivation"
#define MH_METADATA "getMetadata"
#define MH_DEACTIVATE "onDeactivation"
#define MH_UNLOAD "onUnload"

typedef struct tcore_Version tcore_Version;
struct tcore_Version {
	int major;
	int minor;
};

typedef struct tcore_Dependency tcore_Dependency;
struct tcore_Dependency {
	char *moduleName;
	tcore_Version version;
};

typedef struct tcore_Interface tcore_Interface;
struct tcore_Interface {
	char *name;
	char *prototype;
	char *man;
	void (*function) ();
};

typedef struct tcore_Metadata tcore_Metadata;
struct tcore_Metadata {
    int id;
	char *name;
	tcore_Version version;
	lll_List *dependencies;
	lll_List *interfaces;
};

typedef struct tcore_Module tcore_Module;
struct tcore_Module {
    int id;
    void* handle;
	int (*activate) (tcore_Interface* (*getInterface)(const char*, int, const char*));
	tcore_Metadata* (*getMetadata) (void);
	int (*deactivate) (void);
};


#endif /* TCORE_MODULE_H_ */
