CC=gcc
CFLAGS=-I . -g


make: core.c moduleHandler.c
	cd ../lib/runtimeLinkingLibrary && $(MAKE)
	cd ../lib/linkedListLibrary && $(MAKE)
	$(CC) -c libraryHandler.c $(CFLAGS)
	$(CC) -c moduleHandler.c $(CFLAGS)
	$(CC) -c interfaceHandler.c $(CFLAGS)
	$(CC) -c core.c $(CFLAGS)
	$(CC) -o ../talon.bin core.o libraryHandler.o moduleHandler.o interfaceHandler.o ../lib/runtimeLinkingLibrary/runtimeLinking.o ../lib/linkedListLibrary/LinkedList.o -ldl $(CFLAGS)

