CC=gcc
CFLAGS=-I . -fPIC -g -Wall
CLIBS=-ldl -lpthread

SRC=src/
LIB=lib/
OBJ=obj/
MDS=modules/
TCA=$(MDS)coreApi/

SRCS=$(TCASRC)$(SRC) $(SRC)

TC_DEPS=$(addprefix $(OBJ),core libraryHandler.o moduleHandler.o interfaceHandler.o)
TCA_DAPS=$(addprefix $(TCA)$(OBJ),coreApiModule.o coreApi.o logging.o)
LIB_DEPS=$(LIB)linkedListLibrary/obj/linkedList.o \
$(LIB)threadingProcessingLibrary/obj/threadingProcessingLibrary.o \

#
$(OBJ)%.o: %.c
	echo $@
	echo $<
	$(CC) -c -o $(OBJ)$@ $< $(CFLAGS)

%.o: %.c
	echo $@
	echo $<
	$(CC) -c -o $(OBJ)$@ $< $(CFLAGS)

%: %
	echo $@
	echo $<

make: $(TC_DEPS) $(TCA_DAPS)
	$(CC) -o $(OBJ)talon.bin $(TC_DEPS) $(TCA_DAPS) $(LIB_DEPS) $(CLIBS) $(CFLAGS)

# clean output directory
clean:
	rm $(OBJ)*

# make libs
libs:
	cd lib/linkedListLibrary/lib/threadingProcessingLibrary/src && $(MAKE)
	cd lib/linkedListLibrary/src && $(MAKE)
	cd lib/runtimeLinkingLibrary/src && $(MAKE)
	cd lib/threadingProcessingLibrary/src && $(MAKE)
