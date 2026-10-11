CC ?= gcc
CFLAGS ?= -Wall -pedantic -std=c99 -O3 -march=native  -flto=auto

all:
	$(CC) $(CFLAGS) ninor.c -o ninor

clean:
	rm -f a.out ninor dcg

clang:
	clang $(CFLAGS) ninor.c -o ninor

tcc:
	tcc $(CFLAGS) ninor.c -o ninor

dcg-clang:
	 clang  $(CFLAGS) dcg.c main.c -o dcg

dcg-gcc:
	 gcc $(CFLAGS) dcg.c main.c -o dcg

dcg-tcc:
	tcc $(CFLAGS) dcg.c main.c -o dcg 
