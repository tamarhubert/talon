CC=gcc
CFLAGS=-I . -fPIC -g -Wall

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

TC_DEPS := $(addprefix $(OBJ),core.o libraryHandler.o moduleHandler.o interfaceHandler.o)
TCA_DAPS := $(addprefix $(TCA)$(OBJ),coreApiModule.o coreApi.o logging.o)
LIB_DEPS := \
$(LIB)linkedListLibrary/obj/linkedList.o \
$(LIB)threadingProcessingLibrary/obj/threadingProcessingLibrary.o \
$(LIB)runtimeLinkingLibrary/obj/runtimeLinking.o

# compileing
%.o:
	$(CC) -c -o $@ $(subst .o,.c, $(subst obj,src,$@)) $(CFLAGS)

# linking
make: $(TC_DEPS) $(TCA_DAPS)
	$(CC) -o $(BIN)talon.bin $(TC_DEPS) $(TCA_DAPS) $(LIB_DEPS) $(CLIBS) $(CFLAGS)
