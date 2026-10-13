#include "dcg.h"
#include <stdio.h>
#include <stdlib.h>
#define PRINT                                                                  \
  print_graph_definitions(new, stdout);                                        \
  print_graph(new, stdout);

#define PPRINT                                                                 \
  print_graph_definitions_with_pointers(new, stdout);                          \
  print_graph_with_pointers(new, stdout);

int main(int argc, char *argv[]) {
  char *should_print_pointers = getenv("PRINT_POINTERS");
  if (argc == 2) {
    node *new = load_graph(argv[1]);
    if (should_print_pointers) {
      PPRINT
    } else {
      PRINT
    }
    for (node *copy = new; copy->next; ++copy) {
      free(copy->next);
    }
    free(new);
  } else if (argc == 3) {
    node *new = load_graph(argv[1]);
    char *end;

    for (TYPE i = 0; i < (strtoull(argv[2], &end, 10)); ++i) {
      // printf("Stepping...\n");
      step_graph(new);
    }
    if (should_print_pointers) {
      PPRINT
    } else {
      PRINT
    }

    for (node *copy = new; copy->next; ++copy) {
      free(copy->next);
    }
    free(new);
  } else {
    printf("Size of:\n");
    printf("\tNode: %u\n", (unsigned)sizeof(node));
    printf("MAX VALUE_TYPE = %zu\n", (size_t)(MAX_VALUES));
  }
  return 0;
}
