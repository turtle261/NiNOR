#include "dcg.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
  if (argc == 2) {
    node *new = load_graph(argv[1]);
    // print_nodes_definition_by_pointer(new, stdout);
    // print_nodes_by_value(new, stdout);
    print_definitions_raw(new, stdout);
    print_raw(new, stdout);
    free(new->next);
    free(new);
  } else if (argc == 3) {
    node *new = load_graph(argv[1]);
    char *end;
    for (TYPE i = 0; i < (strtol(argv[2], &end, 10)); ++i) {
      // printf("Stepping...\n");
      step_graph(new);
    }
    //    print_nodes_definition_by_pointer(new, stdout);
    //    print_nodes_by_value(new, stdout);
    print_definitions_raw(new, stdout);
    print_raw(new, stdout);

    free(new->next);
    free(new);

  } else {
    printf("Size of:\n");
    printf("\tNode: %u\n", (unsigned)sizeof(node));
  }
  return 0;
}
