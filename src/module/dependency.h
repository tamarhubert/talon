#ifndef TMODULE_DEPENDENCY_H_
#define TMODULE_DEPENDENCY_H_

#include "linkedList.h"

typedef struct lll_List tmd_DependencyList;
typedef struct tmd_Dependency tmd_Dependency;
struct tmd_Dependency {
  char *moduleName;
  int versionMajor;
};

int tmd_newDependencyList(tmd_DependencyList**);

int tmd_addDependency(
  tmd_DependencyList* list,
  const char *moduleName,
  const int versionMajor
);

int tmd_removeDependency(tmd_DependencyList*, int index);

int tmd_freeDependencyList(tmd_DependencyList*);

#endif /* TMODULE_DEPENDENCY_H_ */
