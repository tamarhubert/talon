CC=gcc
CFLAGS=-I .


make: core.c moduleHandler.c
	cd ../lib/rll && $(MAKE)
	cd ../lib/lll && $(MAKE)
	$(CC) -c libraryHandler.c $(CFLAGS)
	$(CC) -c moduleHandler.c $(CFLAGS)
	$(CC) -c interfaceHandler.c $(CFLAGS)
	$(CC) -c core.c $(CFLAGS)
	$(CC) -o ../talon.bin core.o libraryHandler.o moduleHandler.o interfaceHandler.o ../lib/rll/runtimeLinking.o ../lib/lll/LinkedList.o -ldl $(CFLAGS)

