CC=gcc
CFLAGS=-I . -g

make:
	$(CC) -c -fPIC cli.c $(CFLAGS)
	$(CC) -c -fPIC cliModule.c $(CFLAGS)
	$(CC) -shared -o cli.so cli.o cliModule.o ../../lib/linkedListLibrary/LinkedList.o $(CFLAGS)

