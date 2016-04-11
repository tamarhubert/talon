#ifndef TCORE_MODULE_H_
#define TCORE_MODULE_H_

typedef struct tcore_Version tcore_Version;

typedef struct tcore_Dependency tcore_Dependency;

typedef struct tcore_Method tcore_Method;

typedef struct tcore_Module tcore_Module;

struct tcore_Version {
	int major;
	int minor;
};

struct tcore_Dependency {
	char *moduleName;
	tcore_Version version;
};

struct tcore_Method {
	char *name;
	char *man;
	() (*function) ();
};

struct tcore_Module {
	char *name;
	tcore_Version version;
	LinkedList dependencies;
	LinkedList methodes;
};


#endif /* TCORE_MODULE_H_ */
