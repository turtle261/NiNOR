#include "dcg.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
  if (argc > 1) {
    node *new = load_graph(argv[1]);
    print_nodes_definition_by_pointer(new, stdout);
    print_nodes_by_value(new, stdout);
    free(new->next);
    free(new);
  } else {
    printf("Size of:\n");
    printf("\tNode: %u\n", (unsigned)sizeof(node));
  }
  return 0;
}
