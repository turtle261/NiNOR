#include <stdio.h>
#include <stdlib.h>
typedef unsigned long long TYPE;

#define MAX_VALUES 255
#define VALUE_TYPE unsigned char

/* Notes:
 * 1. A root node is a node with no incoming connection
 * 2. Use array of node--and find/identify roots.
 *
 *
 */
typedef struct node {
  VALUE_TYPE value;   /* The nodes value */
  struct node **next; /* Array of pointers to the nodes this one points to*/
} node;

unsigned char is_x_in_arr_of_x(VALUE_TYPE in, VALUE_TYPE *check) {
  VALUE_TYPE iter = 0;
  while (check[iter] != '\0') {
    if (check[iter] == in) {
      return 1;
    }
    ++iter;
  }
  return 0;
}

unsigned char is_p_in_arr_of_p(void *in, void **check) {
  VALUE_TYPE iter = 0;
  while (check[iter] != NULL) {
    if (check[iter] == in) {
      return 1;
    }
    ++iter;
  }
  return 0;
}

static int is_first = 1;

// TYPE node_number_of_connections(node *root) {
//   TYPE max = 0;
//   VALUE_TYPE *value = calloc(MAX_VALUES, sizeof(*value));
//   VALUE_TYPE vallen = 1;
//   value[0] = root->value;
//   for (unsigned i = 0, o = 0; !o; i++) {
//     if (root->next[i] == NULL) {
//       o = 1;
//     } else if (is_x_in_arr_of_x(root->next[i]->value, value)) {
//       continue;
//     } else {
//       value[vallen] = root->next[i]->value;
//       ++vallen;
//       max += node_number_of_connections(root->next[i]);
//       ++max;
//     }
//   }
//   free(value);
//   return max;
// }

/* Gets the number of connections derived from a given root node by pointer(thus
 * it DOES NOT assume unique values for each node in the graph). I.e. number of
 * nodes it connects to + those of which those connect to and so forth, NOT
 * counting loops. */
TYPE node_number_of_connections(node *root) {
  static void **value;
  TYPE max = 0;
  (is_first) ? value = calloc(MAX_VALUES, sizeof(value)) : 0;
  static VALUE_TYPE vallen = 1;
  (!value[0]) ? value[0] = root : 0;
  for (unsigned i = 0, o = 0; !o; i++) {
    if (root->next[i] == NULL) {
      o = 1;
    } else if (is_p_in_arr_of_p(root->next[i], value)) {
      printf("%c->%c\n", root->value, root->next[i]->value);
      printf("POINTER: %p->%p\n", root, root->next[i]);
    } else {
      value[vallen] = root->next[i];
      ++vallen;
      printf("%c->%c\n", root->value, root->next[i]->value);
      printf("POINTER: %p->%p\n", root, root->next[i]);
      int temp = is_first;
      (temp) ? is_first = 0 : 0;
      max += node_number_of_connections(root->next[i]);
      ++max;
      (temp) ? is_first = 1 : 0;
    }
  }
  if (is_first) {
    free(value);
    vallen = 1;
  }

  return max;
}

/* Gets the number of connections derived from a given root node by pointer
 * (thus it DOES NOT assume unique values for each node in the graph). I.e.
 * number of nodes it connects to + those of which those connect to and so
 * forth, INCLUDING LOOPS/CYCLES. */
TYPE node_number_of_connections_incl_loop(node *root) {
  static void **value;
  TYPE max = 0;
  (is_first) ? value = calloc(MAX_VALUES, sizeof(value)) : 0;
  static VALUE_TYPE vallen = 1;
  (!value[0]) ? value[0] = root : 0;
  for (unsigned i = 0, o = 0; !o; i++) {
    if (root->next[i] == NULL) {
      o = 1;
    } else if (is_p_in_arr_of_p(root->next[i], value)) {
      printf("%c->%c\n", root->value, root->next[i]->value);
      printf("POINTER: %p->%p\n", root, root->next[i]);
      ++max;
    } else {
      value[vallen] = root->next[i];
      ++vallen;
      printf("%c->%c\n", root->value, root->next[i]->value);
      printf("POINTER: %p->%p\n", root, root->next[i]);
      int temp = is_first;
      (temp) ? is_first = 0 : 0;
      max += node_number_of_connections_incl_loop(root->next[i]);
      ++max;
      (temp) ? is_first = 1 : 0;
    }
  }
  if (is_first) {
    free(value);
    vallen = 1;
  }
  return max;
}

// TYPE node_number_of_connections_incl_loop(node *root) {
//   int foundloop = 0; /* So we can print then set this to 1 to never print
//   again,
//                         so the loop is shown but not followed indefinitely.
//                         */
//   TYPE max = 0;
//   VALUE_TYPE *value = calloc(MAX_VALUES, sizeof(*value));
//   VALUE_TYPE vallen = 1;
//   value[0] = root->value;
//   for (unsigned i = 0, o = 0; !o; i++) {
//     if (root->next[i] == NULL) {
//       o = 1;
//     } else if (is_x_in_arr_of_x(root->next[i]->value, value) && !foundloop) {
//       ++max;
//       foundloop = 1; /* Don't keep following the loop forever */
//       continue;
//     } else {
//       value[vallen] = root->next[i]->value;
//       ++vallen;
//       max += node_number_of_connections_incl_loop(root->next[i]);
//       ++max;
//     }
//   }
//   free(value);
//   return max;
// }

/* Prints the graph following a root node, including identifying loops/cycles.
 * It does this by value, and thus assumes nodes in the graph are unique by
 * value.*/
void print_nodes_by_value(node *root) {
  static VALUE_TYPE *value;
  (is_first) ? value = calloc(MAX_VALUES, sizeof(*value)) : 0;
  static VALUE_TYPE vallen = 1;
  (!value[0]) ? value[0] = root->value : 0;
  for (unsigned i = 0, o = 0; !o; i++) {
    if (root->next[i] == NULL) {
      o = 1;
    } else if (is_x_in_arr_of_x(root->next[i]->value, value)) {
      printf("%c->%c\n", root->value, root->next[i]->value);
      printf("POINTER: %p->%p\n", root, root->next[i]);
    } else {
      value[vallen] = root->next[i]->value;
      ++vallen;
      printf("%c->%c\n", root->value, root->next[i]->value);
      printf("POINTER: %p->%p\n", root, root->next[i]);
      int temp = is_first;
      (temp) ? is_first = 0 : 0;
      print_nodes_by_value(root->next[i]);
      (temp) ? is_first = 1 : 0;
    }
  }
  if (is_first) {
    free(value);
    vallen = 1;
  }
}

void print_nodes_by_pointer(node *root) {
  static void **value;
  (is_first) ? value = calloc(MAX_VALUES, sizeof(value)) : 0;
  static VALUE_TYPE vallen = 1;
  (!value[0]) ? value[0] = root : 0;
  for (unsigned i = 0, o = 0; !o; i++) {
    if (root->next[i] == NULL) {
      o = 1;
    } else if (is_p_in_arr_of_p(root->next[i], value)) {
      printf("%c->%c\n", root->value, root->next[i]->value);
      printf("POINTER: %p->%p\n", root, root->next[i]);
    } else {
      value[vallen] = root->next[i];
      ++vallen;
      printf("%c->%c\n", root->value, root->next[i]->value);
      printf("POINTER: %p->%p\n", root, root->next[i]);
      int temp = is_first;
      (temp) ? is_first = 0 : 0;
      print_nodes_by_pointer(root->next[i]);
      (temp) ? is_first = 1 : 0;
    }
  }
  if (is_first) {
    free(value);
    vallen = 1;
  }
}

// node *add_node_at_index(short idx, struct node **next) {}

int main(int argc, char *argv[]) {
  node *one = malloc(sizeof(*one));
  node *two = malloc(sizeof(*two));
  node *three = malloc(sizeof(*three));
  one->value = 'a';
  two->value = 'b';
  two->next = malloc(sizeof(*two->next));
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
  /* Here through to return 0, if commented, removes the segfault issue */
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
  // print_nodes_by_pointer(six);
  print_nodes_by_value(six);
  free(one);
  free(two);
  free(three);
  free(four);
  free(five);
  free(six);
  return 0;
}
