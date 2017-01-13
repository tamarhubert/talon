CC=gcc
CFLAGS=-I . -fPIC -g -Wall

%.o: %.c
	$(CC) -c -o ../obj/$@ $< $(CFLAGS)

make: coreCli.o coreCliModule.o
	$(CC) -shared -o ../obj/coreCli.so ../obj/coreCli.o ../obj/coreCliModule.o \
../../../lib/linkedListLibrary/obj/linkedList.o \
../../../lib/threadingProcessingLibrary/obj/threadingProcessingLibrary.o $(CFLAGS)
