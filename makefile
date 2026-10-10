CC ?= gcc
CFLAGS ?= -Wall -pedantic -std=c99 -O3 -march=native  -flto=auto

all:
	$(CC) $(CFLAGS) ninor.c -o ninor
	$(CC) $(CFLAGS) dcg.c -o dcg

clean:
	rm -f a.out ninor dcg

clang:
	clang $(CFLAGS) ninor.c -o ninor
	clang $(CFLAGS) dcg.c -o dcg 

tcc:
	tcc $(CFLAGS) ninor.c -o ninor
	tcc $(CFLAGS) dcg.c -o dcg

dcg-clang:
	 clang -Wall -pedantic -std=c99 -O3 -march=native -flto=auto dcg.c 

dcg-gcc:
	 gcc -Wall -pedantic -std=c99 -O3 -march=native -flto=auto dcg.c
