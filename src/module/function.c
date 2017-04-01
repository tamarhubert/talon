#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

#include "function.h"
#include "main.h"

int tmf_newFunctionList(tmf_FunctionList** result){
	lll_List* list = lll_newList();
	if(!list){
		return ERROR;
	}
	*result = (tmf_FunctionList*)list;
	return SUCCESS;
}

int tmf_addFunction(
  tmf_FunctionList* list,
  const char *name,
  const char *prototype,
  const char *man,
  void (* const pointer) ()
){
  tmf_Function *function = malloc(sizeof(tmf_Function));
  function->name = malloc(strlen(name) + 1);
  strcpy(function->name, name);
  function->prototype  = malloc(strlen(prototype) + 1);
  strcpy(function->prototype, prototype);
  function->man = malloc(strlen(man) + 1);
  strcpy(function->man, man);
  function->pointer = pointer;

  return lll_add((lll_List*)list, (void*)function);
}

int tmf_removeFunction(tmf_FunctionList* list, int index){
  return lll_removeAtIndex((lll_List*) list, index);
}

int tmf_freeFunctionList(tmf_FunctionList* list){
  return lll_freeList((lll_List*) list);
}
