CC ?= gcc
CFLAGS ?= -Wall -pedantic -std=c99 -O2 -march=native  -flto=auto

all:
	$(CC) $(CFLAGS) dcg.c main.c -o dcg

clean:
	rm -f a.out dcg 

clang:
	clang $(CFLAGS) dcg.c main.c -o dcg

gcc:
	gcc $(CFLAGS) dcg.c main.c -o dcg

tcc:
	tcc $(CFLAGS) dcg.c main.c -o dcg

file-roundtrip-test: tcc
	./scripts/test1.sh
