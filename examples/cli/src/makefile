CC=gcc
CFLAGS=-I . -g

OBJ=../obj
LIB=../../../lib

%.o: %.c
	$(CC) -c -fPIC -o $(OBJ)/$@ $< $(CFLAGS)

make: cli.o cliModule.o
	$(CC) -shared -o $(OBJ)/cli.so $(OBJ)/cli.o $(OBJ)/cliModule.o $(LIB)/linkedListLibrary/obj/linkedList.o $(CFLAGS)

