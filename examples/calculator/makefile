CC=gcc
CFLAGS=-I .
DEPS = calc.h,../../core/module.h,../../lib/lll/LinkedList.h,../../lib/lll/LinkedList.h

%.o: %.c $(DEPS)
	$(CC) -c -fPIC %.c $(CFLAGS)

calc.so: calc.o calcModule.o ../../lib/lll/LinkedList.o
	$(CC) -shared -o calc.so calc.o calcModule.o ../../lib/lll/LinkedList.o $(CFLAGS)

make: calc.so
