#ifndef TALON_VALIDATOR_H_
#define TALON_VALIDATOR_H_

// MODULE
#define MODULE_SUCCESS 0
#define MODULE_NAME_ERROR 1
#define MODULE_VERSION_ERROR 2
#define MODULE_DEPENDENCIES_ERROR 3
#define MODULE_METHODS_ERROR 4

// METHOD
#define METHOD_SUCCESS 0
#define METHOD_NAME_ERROR 1
#define METHOD_MAN_ERROR 2
#define METHOD_FUNCTION_ERROR 3

// DEPENDENCY
#define DEPENDENCY_SUCCESS 0
#define DEPENDENCY_NAME_ERROR 1
#define DEPENDENCY_VERSION_ERROR 2

// VERSION
#define VERSION_SUCCESS 0

int validateVersion(tcore_Version version);
int validateMethod(tcore_Dependency dependency);
int validateMethod(tcore_Method method);
int validateModule(tcore_Module module);

#endif /* TALON_VALIDATOR_H_ */
