#include "dcg.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  node *one = malloc(sizeof(*one));
  node *two = malloc(sizeof(*two));
  node *three = malloc(sizeof(*three));
  one->value = 'a';
  two->value = 'b';
  two->next = malloc(2 * sizeof(*two->next));
  three->next = malloc(sizeof(*three->next));
  two->next[0] = NULL;
  three->next[0] = NULL;
  three->value = 'c';
  node *four = malloc(sizeof(*four));
  four->value = 'd';
  four->next = malloc(2 * sizeof(*four->next));
  four->next[0] = four;
  four->next[1] = NULL;

  one->next = malloc(5 * sizeof(*one->next));
  one->next[0] = two;
  one->next[1] = three;
  one->next[2] = one;
  one->next[3] = four;
  one->next[4] = NULL;
  printf("%u\n", (unsigned)node_number_of_connections(one));
  printf("%u\n", (unsigned)node_number_of_connections(two));
  printf("%u\n", (unsigned)node_number_of_connections(three));
  printf("%u\n", (unsigned)node_number_of_connections(four));
  print_nodes_by_value(one);
  printf("%u\n", (unsigned)node_number_of_connections_incl_loop(one));
  print_nodes_by_pointer(one);
  one->next[0] = two;
  one->next[1] = three;
  one->next[2] = NULL;
  two->next[0] = four;
  three->next[0] = four;
  two->next[1] = NULL;
  three->next[1] = NULL;
  four->next[0] = four;
  four->next[1] = NULL;
  printf("\n\n\n\n");
  print_nodes_by_pointer(one);
  node *five = malloc(sizeof(*five));
  node *six = malloc(sizeof(*six));
  five->next = malloc(2 * sizeof(five->next));
  six->next = malloc(2 * sizeof(six->next));
  five->value = 'z';
  six->value = 'y';
  five->next[0] = six;
  six->next[0] = five;
  five->next[1] = NULL;
  six->next[1] = NULL;
  printf("\n\n\n\n");
  print_nodes_by_pointer(five);
  printf("\n\n\n\n");
  print_nodes_by_value(six);

  free(one->next);
  free(two->next);
  free(three->next);
  free(four->next);
  free(five->next);
  free(six->next);
  free(one);
  free(two);
  free(three);
  free(four);
  free(five);
  free(six);
  return 0;
}
