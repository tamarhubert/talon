CC=gcc
IS=\
-Isrc \
-Isrc/core \
-Isrc/module \
-Imodules/coreApi/src \
-Ilib/linkedListLibrary/src \
-Ilib/threadingProcessingLibrary/src \
-Ilib/runtimeLinkingLibrary/src
CFLAGS=$(IS) -fPIC -g -Wall

# windows:
#CLIBS=
# linux:
CLIBS=-ldl -lpthread

SRC=src/
LIB=lib/
OBJ=obj/
BIN=bin/
MDS=modules/
TCA=$(MDS)coreApi/

TC_DEPS := $(addprefix $(OBJ), \
core.o \
library.o \
interface.o \
dependency.o \
function.o \
module.o)

TCA_DEPS := $(addprefix $(TCA)$(OBJ), \
coreApiModule.o \
coreApi.o \
logging.o)

LIB_DEPS := $(addprefix $(LIB), \
linkedListLibrary/obj/linkedList.o \
threadingProcessingLibrary/obj/threadingProcessingLibrary.o \
runtimeLinkingLibrary/obj/runtimeLinking.o)


# linking
make: main core module library interface dependency function coreApi
	$(CC) -o $(BIN)talon.bin obj/main.o $(TC_DEPS) $(TCA_DEPS) $(LIB_DEPS) $(CLIBS) $(CFLAGS)

# compileing
main: src/main.c
	$(CC) -c -o obj/main.o src/main.c $(CFLAGS)

core: src/core/core.c
	$(CC) -c -o obj/core.o src/core/core.c $(CFLAGS)

library: src/core/library.c
	$(CC) -c -o obj/library.o src/core/library.c $(CFLAGS)

interface: src/core/interface.c
	$(CC) -c -o obj/interface.o src/core/interface.c $(CFLAGS)

dependency: src/module/dependency.c
	$(CC) -c -o obj/dependency.o src/module/dependency.c $(CFLAGS)

function: src/module/function.c
	$(CC) -c -o obj/function.o src/module/function.c $(CFLAGS)

module: src/module/module.c
	$(CC) -c -o obj/module.o src/module/module.c $(CFLAGS)

coreApi: modules/coreApi/src/coreApi.c modules/coreApi/src/coreApiModule.c modules/coreApi/src/logging.c
	$(CC) -c -o modules/coreApi/obj/coreApi.o modules/coreApi/src/coreApi.c $(CFLAGS)
	$(CC) -c -o modules/coreApi/obj/coreApiModule.o modules/coreApi/src/coreApiModule.c $(CFLAGS)
	$(CC) -c -o modules/coreApi/obj/logging.o modules/coreApi/src/logging.c $(CFLAGS)
