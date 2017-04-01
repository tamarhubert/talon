#ifndef TMOUDLE_FUNCTION_H_
#define TMOUDLE_FUNCTION_H_

#include "linkedList.h"

typedef struct tmf_Function tmf_Function;
struct tmf_Function {
  char *name;
  char *prototype;
  char *man;
  void (* pointer) ();
};

typedef struct lll_List tmf_FunctionList;

int tmf_newFunctionList(tmf_FunctionList**);

int tmf_addFunction(
  tmf_FunctionList* list,
  const char *name,
  const char *prototype,
  const char *man,
  void (* const function) ()
);

int tmf_removeFunction(tmf_FunctionList*, int index);

int tmf_freeFunctionList(tmf_FunctionList*);

#endif /* TMOUDLE_FUNCTION_H_ */
