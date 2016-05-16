CC=gcc
CFLAGS=-I .

make:
	$(CC) -c -fPIC cli.c $(CFLAGS)
	$(CC) -c -fPIC cliModule.c $(CFLAGS)
	$(CC) -shared -o cli.so cli.o cliModule.o ../../lib/lll/LinkedList.o $(CFLAGS)

