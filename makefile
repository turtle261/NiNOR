CC ?= gcc
CFLAGS ?= -Wall -pedantic -std=c99 -O3 -march=native  -flto=auto

all:
	$(CC) $(CFLAGS) ninor.c -o ninor

clean:
	rm -f a.out ninor dcg dcg_print

clang:
	clang $(CFLAGS) ninor.c -o ninor

tcc:
	tcc $(CFLAGS) ninor.c -o ninor

dcg-clang:
	clang  $(CFLAGS) dcg.c tests.c -o dcg
	clang $(CFLAGS) dcg.c dcg_print_graph_from_file.c -o dcg_print

dcg-gcc:
	gcc $(CFLAGS) dcg.c tests.c -o dcg
	gcc $(CFLAGS) dcg.c dcg_print_graph_from_file.c -o dcg_print

dcg-tcc:
	tcc $(CFLAGS) dcg.c tests.c -o dcg 
	tcc $(CFLAGS) dcg.c dcg_print_graph_from_file.c -o dcg_print

file-roundtrip-test:
	./scripts/test1.sh
