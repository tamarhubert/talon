#include "talonExtensionService.h"
#include "extension.h"

LinkedList **rootExtension;

int registerNewExtension();
int getNewExtensions(**LinkedList);
int getExtensions();
int getReqisteredExtension();
int pattern_registerExtension(LinkedList);

int registerNewExtensions(){
    /*
    FOR EXTENSION IN GET_NEW_EXTENSION_DLLS():
        REGISTER_NEW_EXTENSION( EXTENSION )
    */
    int result = NOT_IMPLEMENTED;

    LinkedList **extensions;
    if ((result = getNewExtensions(extensions)) BAD){
        return result;
    }

    if ((result = ll_foreach(extensions, pattern_registerExtension)) BAD) {
        return result;
    }
}

int registerNewExtension(Extension extension){
    /*
    EXTENSIONS.ADD( EXTENSION_ENTRY(EXTENSION) )

    FOR COMMAND IN EXTENSION.COMMANDS:
        REGISTER_COMMAND(COMMAND)
    */
}

int getNewExtensionDLLs(){
    /*
    FOR EXTENSION IN GET_EXTENSION():
        IF NOT IN EXTENSIONS
    */
}

int getExtensionDLLs(LinkedList extensions){
    /*
    FOR FILE IN GET_FILES_OF_FOLDER(FOLDER, FILES):
        IF FILE IS EXTNESION:
            EXTENSIONS.ADD( FILE )
    */
}

int getFilesOfFolder(char* folder, LinkedList files){
    /*
    FOR FILE IN FOLDER:
        FILES.ADD(FILE)
    */
}

int pattern_registerExtension(LinkedList entry){
    registerNewExtension(*(Extension*)entry.value);
    return ENTRY_MATCH;
}
