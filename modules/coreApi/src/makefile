CC=gcc
CFLAGS=-I . -g -Wall

LIB=../lib
OBJ=../obj
MDS=../modules

DEPS=coreApiModule.o

%.o: %.c
	$(CC) -c -o $(OBJ)/$@ $< $(CFLAGS)

make: $(DEPS)
