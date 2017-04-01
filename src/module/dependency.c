#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

#include "main.h"
#include "dependency.h"

int tmd_newDependencyList(tmd_DependencyList** list){
	*list = (tmd_DependencyList*)lll_newList();
	if(!*list){
		return ERROR;
	}
	return SUCCESS;
}

int tmd_addDependency(
  tmd_DependencyList* list,
  const char *moduleName,
  int versionMajor
){
  tmd_Dependency *dependency = malloc(sizeof(tmd_Dependency));
  dependency->moduleName = malloc(strlen(moduleName) + 1);
  strcpy(dependency->moduleName, moduleName);
  dependency->versionMajor = versionMajor;

  return lll_add((lll_List*)list, (void*)dependency);
}

int tmd_removeDependency(tmd_DependencyList* list, int index){
  return lll_removeAtIndex((lll_List*) list, index);
}

int tmd_freeDependencyList(tmd_DependencyList* list){
  return lll_freeList((lll_List*) list);
}
