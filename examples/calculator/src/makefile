CC=gcc
CFLAGS=-I . -g

%.o: %.c
	$(CC) -c -fPIC -o ../obj/$@ $< $(CFLAGS)

make: calc.o calcModule.o
	$(CC) -shared -o ../obj/calc.so ../obj/calc.o ../obj/calcModule.o ../../../lib/linkedListLibrary/obj/linkedList.o $(CFLAGS)

