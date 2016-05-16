CC=gcc
CFLAGS=-I .

make:
	$(CC) -c -fPIC calc.c $(CFLAGS)
	$(CC) -c -fPIC calcModule.c $(CFLAGS)
	$(CC) -shared -o calc.so calc.o calcModule.o ../../lib/lll/LinkedList.o $(CFLAGS)

