CC=gcc
CFLAGS=-I . -g -fPIC -Wall

%.o: %.c
	$(CC) -c -fPIC -o ../obj/$@ $< $(CFLAGS)

make: calc.o calcModule.o
	$(CC) -shared -o ../obj/calc.so ../obj/calc.o ../obj/calcModule.o \
../../../lib/linkedListLibrary/obj/linkedList.o \
../../../lib/threadingProcessingLibrary/obj/threadingProcessingLibrary.o $(CFLAGS)
