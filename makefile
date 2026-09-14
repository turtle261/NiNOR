CC ?= gcc
CFLAGS ?= -Wall -pedantic -std=c99 -O3 -march=native  -flto=auto

all:
	$(CC) $(CFLAGS) ninor.c -o ninor

clean:
	rm -f a.out ninor

clang:
	clang $(CFLAGS) ninor.c -o ninor
