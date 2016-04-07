/*
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
	LinkedList methods;
};
*/

int validateVersion(tcore_Version version){
	if(version == NULL){
		return VERSION_NULL_ERROR;	
	}
	return VERSION_SUCCESS;
}
int validateMethod(tcore_Method method){
	if(method == NULL){
		return METHOD_NULL_ERROR;	
	}
	if(method.name == NULL){
		return METHOD_NAME_ERROR;
	}
	if(method.man == NULL){
		return METHOD_MAN_ERROR;
	}
	if(method.function == NULL){
		return METHOD_FUNCTION_ERROR;
	}
	return METHOD_SUCCESS;
}

int validateDependency(tcore_Dependency dependency){
	if(dependency == NULL){
		return DEPENDENCY_NULL_ERROR;	
	}
	if(dependency.moduleName == NULL){
		return DEPENDENCY_NAME_ERROR;
	}
	if(validateDependency(dependency.version) != DEPENDENCY_SUCCESS){
		return DEPENDENCY_VERSION_ERROR;
	}
	return DEPENDENCY_SUCCESS;
}

int validateModule(tcore_Module module){
	if(module == NULL){
		return MODULE_NULL_ERROR;
	}
	if(module.name == NULL){
		return MODULE_NAME_ERROR;
	}
	if(valdiateVersion(module.version)){
		return MODULE_VERSION_ERROR;
	}
	if(module.dependenies == NULL){
		return MODULE_DEPENDENCIES_ERROR
	}
	// for dependency in module.dependency
		if(valdiateDependency(module.dependency)){
			return MODULE_DEPENDENCIES_ERROR;
		}
	// }
	// for method in module.methods:
		if(module.methods == NULL){
			return MODULE_METHODS_ERROR;
		}
	return MODULE_SUCCESS;
}
