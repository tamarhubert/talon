CC=gcc
CFLAGS=-I . -fPIC -g -Wall
CLIBS=-ldl -lpthread

LIB=../lib
OBJ=../obj
MDS=../modules

DEPS=core.o libraryHandler.o moduleHandler.o interfaceHandler.o

%.o: %.c
	$(CC) -c -o $(OBJ)/$@ $< $(CFLAGS)

make: $(DEPS) modules
	$(CC) -o $(OBJ)/talon.bin \
$(OBJ)/core.o $(OBJ)/libraryHandler.o $(OBJ)/moduleHandler.o $(OBJ)/interfaceHandler.o \
$(MDS)/coreApi/obj/coreApiModule.o \
$(MDS)/coreApi/obj/coreApi.o \
$(MDS)/coreApi/obj/logging.o \
$(LIB)/runtimeLinkingLibrary/obj/runtimeLinking.o \
$(LIB)/linkedListLibrary/obj/linkedList.o \
$(LIB)/threadingProcessingLibrary/obj/threadingProcessingLibrary.o \
$(CLIBS) $(CFLAGS)

modules:
	$(CC) -c -o $(MDS)/coreApi/obj/coreApiModule.o $(MDS)/coreApi/src/coreApiModule.c $(CFLAGS)
	$(CC) -c -o $(MDS)/coreApi/obj/coreApi.o $(MDS)/coreApi/src/coreApi.c $(CFLAGS)
	$(CC) -c -o $(MDS)/coreApi/obj/logging.o $(MDS)/coreApi/src/logging.c $(CFLAGS)
