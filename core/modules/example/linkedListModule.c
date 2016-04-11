#include "linkedListModule.h"
//#include "linkedListLib.h"

#define MODULE_NAME "LinkedList"
#define MODULE_VERSION_MAJOR 0
#define MODULE_VERSION_MINOR 0

#define ABORT 2
#define WARNING 1
#define SUCCESS 0

int (*fw_wirte)(char* msg);

int write(char*);


int onLoad(func *getFunction) {
	return SUCCESS;
}
getModule(tcore_Module *module){
	module.name = MODULE_NAME;
	module.version.major = MODULE_VERSION_MAJOR;
	module.version.minor = MOUDLE_VERSION_MINOR;
	module.dependencies = calloc(LinkedList, 1);
	module.methods = calloc(LinkedList, 1);

	// add
	tcore_Method add = calloc(1, sizeof(tcore_Method));
	add.name = "add";
	add.man = "int add (LinkedList ll, LinkedListEntry lle)"+
			"\n\tll\tThe linked list to add the entry."+
			"\n\tll\tThe entry to add to the linked list."
	add.function = lll_add;
	LinkedListEntry addEntry = malloc(1, sizeof(LinkedListEntry));
	addEntry.value = add;
	lll_add(module.methods, addEntry);

	// remove
	tcore_Method remove = calloc(1, sizeof(tcore_Method));
	remove.name = "remove";
	remove.man = "int remove (LinkedListEntry lle)"+
			"\n\tll\tThe entry to remove from the linked list."
	remove.function = lll_remove;
	LinkedListEntry removeEntry = malloc(1, sizeof(LinkedListEntry));
	removeEntry.value = remove;
	lll_add(module.methods, removeEntry);

	//
	tcore_Method add = calloc(1, sizeof(tcore_Method));
	add.name = "add";
	add.man = "int add (LinkedList ll, LinkedListEntry lle)"+
			"\n\tll\tThe linked list to add the entry."+
			"\n\tll\tThe entry added to the linked list."
	add.function = lll_add;
	LinkedListEntry addEntry = malloc(1, sizeof(LinkedListEntry));
	addEntry.value = add;
	lll_add(module.methods, addEntry);


	return SUCCESS;
}

onDestroy(){
	return SUCCESS;
}
