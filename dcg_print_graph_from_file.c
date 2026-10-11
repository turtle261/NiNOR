#include "dcg.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
  if (argc > 1) {
    node *new = load_graph(argv[1]);
    print_nodes_by_value(new);
    free(new->next);
    free(new);
  }
  return 0;
}
