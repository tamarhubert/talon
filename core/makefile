CC=gcc
CFLAGS=-I .


make: core.c moduleHandler.c
	cd ../lib/rll && $(MAKE)
	$(CC) -c moduleHandler.c $(CFLAGS)
	$(CC) -c core.c $(CFLAGS)
	$(CC) -o ../talon.bin core.o moduleHandler.o ../lib/rll/runtimeLinking.o ../lib/lll/LinkedList.o -ldl $(CFLAGS)

