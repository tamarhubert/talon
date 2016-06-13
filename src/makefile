CC=gcc
CFLAGS=-I . -g
CLIBS=-ldl -lpthread

LIB=../lib
OBJ=../obj

DEPS=core.o libraryHandler.o moduleHandler.o interfaceHandler.o

%.o: %.c
	$(CC) -c -o $(OBJ)/$@ $< $(CFLAGS)

make: $(DEPS)
	$(CC) -o $(OBJ)/talon.bin $(OBJ)/core.o $(OBJ)/libraryHandler.o $(OBJ)/moduleHandler.o $(OBJ)/interfaceHandler.o \
$(LIB)/runtimeLinkingLibrary/obj/runtimeLinking.o \
$(LIB)/linkedListLibrary/obj/linkedList.o \
$(LIB)/threadingProcessingLibrary/obj/threadingProcessingLibrary.o \
$(CLIBS) $(CFLAGS)

