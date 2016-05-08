#include "../lib/lll/LinkedList.h"

#ifndef TCORE_MODULE_H_
#define TCORE_MODULE_H_

typedef struct tcore_Version tcore_Version;

typedef struct tcore_Dependency tcore_Dependency;

typedef struct tcore_Interface tcore_Interface;

typedef struct tcore_ModuleDefinition tcore_ModuleDefinition;

struct tcore_Version {
	int major;
	int minor;
};

struct tcore_Dependency {
	char *moduleName;
	tcore_Version version;
};

struct tcore_Interface {
	char *name;
	char *man;
	void (*function) ();
};

struct tcore_ModuleDefinition {
	char *name;
	tcore_Version version;
	lll_List *dependencies;
	lll_List *interfaces;
};


#endif /* TCORE_MODULE_H_ */
