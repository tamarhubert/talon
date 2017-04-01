CC=gcc
ROOT=../..
IS= \
-Isrc \
-I$(ROOT)/src \
-I$(ROOT)/src/core \
-I$(ROOT)/src/module \
-I$(ROOT)/modules/coreApi/src \
-I$(ROOT)/lib/linkedListLibrary/src \
-I$(ROOT)/lib/threadingProcessingLibrary/src \
-I$(ROOT)/lib/runtimeLinkingLibrary/src
CFLAGS=$(IS) -fPIC -g -Wall

obj/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

make: obj/coreCli.o obj/coreCliModule.o
	$(CC) -shared -o bin/coreCli.so obj/coreCli.o obj/coreCliModule.o \
$(ROOT)/lib/linkedListLibrary/obj/linkedList.o \
$(ROOT)/lib/threadingProcessingLibrary/obj/threadingProcessingLibrary.o \
$(ROOT)/obj/dependency.o \
$(ROOT)/obj/function.o \
$(ROOT)/obj/module.o $(CFLAGS)
