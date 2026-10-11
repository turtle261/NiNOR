#include "dcg.h"
#include <stdio.h>
#include <stdlib.h>

static int is_first = 1;

/* Check if an unsigned char is in an unsigned string (array of unsigned chars,
 * terminated by '\0' */
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

/* Check if a pointer is in an array of pointers */
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
      printf("POINTER: %p->%p\n", (void *)root, (void *)root->next[i]);
    } else {
      value[vallen] = root->next[i];
      ++vallen;
      printf("%c->%c\n", root->value, root->next[i]->value);
      printf("POINTER: %p->%p\n", (void *)root, (void *)root->next[i]);
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
      printf("POINTER: %p->%p\n", (void *)root, (void *)root->next[i]);
      ++max;
    } else {
      value[vallen] = root->next[i];
      ++vallen;
      printf("%c->%c\n", root->value, root->next[i]->value);
      printf("POINTER: %p->%p\n", (void *)root, (void *)root->next[i]);
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
      printf("POINTER: %p->%p\n", (void *)root, (void *)root->next[i]);
    } else {
      value[vallen] = root->next[i]->value;
      ++vallen;
      printf("%c->%c\n", root->value, root->next[i]->value);
      printf("POINTER: %p->%p\n", (void *)root, (void *)root->next[i]);
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

/* Prints the graph following a root node, including identifying loops/cycles.
 * It does this by pointer, and thus DOES NOT assume nodes in the graph are
 * unique by value.*/
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
      printf("POINTER: %p->%p\n", (void *)root, (void *)root->next[i]);
    } else {
      value[vallen] = root->next[i];
      ++vallen;
      printf("%c->%c\n", root->value, root->next[i]->value);
      printf("POINTER: %p->%p\n", (void *)root, (void *)root->next[i]);
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
