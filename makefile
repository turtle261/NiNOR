CC ?= gcc
CFLAGS ?= -Wall -pedantic -std=c99 -O2 -march=native  -flto=auto

all:
	$(CC) $(CFLAGS) dcg.c tests.c -o dcg
	$(CC) $(CFLAGS) dcg.c dcg_print_graph_from_file.c -o dcg_print

clean:
	rm -f a.out ninor dcg dcg_print

clang:
	clang  $(CFLAGS) dcg.c tests.c -o dcg
	clang $(CFLAGS) dcg.c dcg_print_graph_from_file.c -o dcg_print

gcc:
	gcc $(CFLAGS) dcg.c tests.c -o dcg
	gcc $(CFLAGS) dcg.c dcg_print_graph_from_file.c -o dcg_print

tcc:
	tcc $(CFLAGS) dcg.c tests.c -o dcg 
	tcc $(CFLAGS) dcg.c dcg_print_graph_from_file.c -o dcg_print

file-roundtrip-test: tcc
	./scripts/test1.sh
