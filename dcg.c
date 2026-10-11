/*
Copyright (c) 2026 Noah Cashin <noahcashin@disroot.org>

Permission to use, copy, modify, and distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include "dcg.h"
#include "ninor.h"
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
    } else {
      value[vallen] = root->next[i];
      ++vallen;
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
      ++max;
    } else {
      value[vallen] = root->next[i];
      ++vallen;
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
void print_nodes_by_value(node *root, FILE *output) {
  static VALUE_TYPE *value;
  (is_first) ? value = calloc(MAX_VALUES, sizeof(*value)) : 0;
  static VALUE_TYPE vallen = 1;
  (!value[0]) ? value[0] = root->value : 0;
  for (unsigned i = 0, o = 0; !o; i++) {
    if (root->next[i] == NULL) {
      o = 1;
    } else if (is_x_in_arr_of_x(root->next[i]->value, value)) {
      fprintf(output, "%c->%c\n", root->value, root->next[i]->value);
#ifdef ALWAYS_PRINT_GRAPH_POINTERS
      fprintf(output, "%p->%p\n", (void *)root, (void *)root->next[i]);
#endif
    } else {
      value[vallen] = root->next[i]->value;
      ++vallen;
      fprintf(output, "%c->%c\n", root->value, root->next[i]->value);
#ifdef ALWAYS_PRINT_GRAPH_POINTERS
      fprintf(output, "%p->%p\n", (void *)root, (void *)root->next[i]);
#endif
      int temp = is_first;
      (temp) ? is_first = 0 : 0;
      print_nodes_by_value(root->next[i], output);
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
void print_nodes_by_pointer(node *root, FILE *output) {
  static void **value;
  (is_first) ? value = calloc(MAX_VALUES, sizeof(value)) : 0;
  static VALUE_TYPE vallen = 1;
  (!value[0]) ? value[0] = root : 0;
  for (unsigned i = 0, o = 0; !o; i++) {
    if (root->next[i] == NULL) {
      o = 1;
    } else if (is_p_in_arr_of_p(root->next[i], value)) {

#ifdef ALWAYS_PRINT_GRAPH_VALUES
      fprintf(output, "%c->%c\n", root->value, root->next[i]->value);
#endif
      fprintf(output, "POINTER: %p->%p\n", (void *)root, (void *)root->next[i]);
    } else {
      value[vallen] = root->next[i];
      ++vallen;
#ifdef ALWAYS_PRINT_GRAPH_VALUES
      fprintf(output, "%c->%c\n", root->value, root->next[i]->value);
#endif
      fprintf(output, "POINTER: %p->%p\n", (void *)root, (void *)root->next[i]);
      int temp = is_first;
      (temp) ? is_first = 0 : 0;
      print_nodes_by_pointer(root->next[i], output);
      (temp) ? is_first = 1 : 0;
    }
  }
  if (is_first) {
    free(value);
    vallen = 1;
  }
}

/* Prints the node definitions of a graph following a root node. It does this by
 * pointer, and thus DOES NOT assume nodes in the graph are unique by value. It
 * will write to the output (FILE *) parameter.*/
void print_nodes_definition_by_pointer(node *root, FILE *output) {
  static node **val;
  (is_first) ? val = calloc(MAX_VALUES, sizeof(val)) : 0;
  static VALUE_TYPE vallen = 1;
  (!val[0]) ? val[0] = root : 0;
  for (unsigned i = 0, o = 0; !o; i++) {
    if (root->next[i] == NULL) {
      o = 1;
    } else if (is_p_in_arr_of_p(root->next[i], (void *)val)) {

    } else {
      val[vallen] = root->next[i];
      ++vallen;
      int temp = is_first;
      (temp) ? is_first = 0 : 0;
      print_nodes_definition_by_pointer(root->next[i], output);
      (temp) ? is_first = 1 : 0;
    }
  }
  if (is_first) {
    for (VALUE_TYPE i = 0; i < vallen; i++) {
      fprintf(output, "node %c\n", val[i]->value);
    }
    free(val);
    vallen = 1;
  }
}

/* Prints the node definitions of a graph following a root node. It does this by
 * value, and thus assumes nodes in the graph are unique by value. It will write
 * to the output (FILE *) parameter.*/
void print_nodes_definition_by_value(node *root, FILE *output) {
  static VALUE_TYPE *value;
  (is_first) ? value = calloc(MAX_VALUES, sizeof(*value)) : 0;
  static VALUE_TYPE vallen = 1;
  (!value[0]) ? value[0] = root->value : 0;
  for (unsigned i = 0, o = 0; !o; i++) {
    if (root->next[i] == NULL) {
      o = 1;
    } else if (is_x_in_arr_of_x(root->next[i]->value, value)) {
    } else {
      value[vallen] = root->next[i]->value;
      ++vallen;
      int temp = is_first;
      (temp) ? is_first = 0 : 0;
      print_nodes_definition_by_value(root->next[i], output);
      (temp) ? is_first = 1 : 0;
    }
  }
  if (is_first) {
    for (VALUE_TYPE i = 0; i < vallen; i++) {
      fprintf(output, "node %c\n", value[i]);
    }
    free(value);
    vallen = 1;
  }
}

/* Returns 1 if it added a connection to node, 0 otherwise */
int add_connection_to_node(node *base, node *next) {
  for (VALUE_TYPE i = 0; i < MAX_VALUES; i++) {
    if (base->next[i] == NULL) {
      base->next[i] = next;
      i = MAX_VALUES;
      return 1; /* Worked */
    }
  }
  return 0;
}

/* Parses input files in the super simple format... Will try to return NULL on
wrong files or inputs. Avoid bad inputs.*/
node *load_graph(char *filepath) {
  FILE *file = fopen(filepath, "r");
  if (!file) { /* If null */
    fprintf(stderr, "Failed to open file %s\n", filepath);
    return NULL;
  }
  char line[MAX_GRAPH_LINE_LEN];
  VALUE_TYPE values[MAX_VALUES] = {0};
  int valnum = 0;
  unsigned short nodeidx = 0;
  node *nodes = calloc(MAX_VALUES, sizeof(*nodes));
  while (fgets(line, MAX_GRAPH_LINE_LEN, file)) {
    /*    if (!has_root && line[0] == 'r' && line[1] == 'o' && line[2] == 'o' &&
            line[3] == 't' && line[4] == ' ' && line[5] == 'n' && line[6] == 'o'
       && line[7] == 'd' && line[8] == 'e' && line[9] == ' ') { values[valnum] =
       line[10];
          ++valnum;
          roots[has_root].next = calloc(MAX_VALUES, sizeof(*roots));
          roots[has_root].value = line[10];
          ++has_root;
        } else*/
    if (line[0] == 'n' && line[1] == 'o' && line[2] == 'd' && line[3] == 'e' &&
        line[4] == ' ' && line[6] == '\n') { /* node definition */
      values[valnum] = line[5];
      valnum++;
      nodes[nodeidx].next = calloc(MAX_VALUES, sizeof(*nodes->next));
      nodes[nodeidx].value = line[5];
      ++nodeidx;
    } else if (nodeidx && is_x_in_arr_of_x(line[0], values) && line[1] == '-' &&
               line[2] == '>' && is_x_in_arr_of_x(line[3], values)) {
      if (nodeidx) {
        unsigned x = 0, y = 0;
        for (unsigned i = 0; i < nodeidx; i++) {
          if (nodes[i].value == line[0]) {
            x = i;
          }
          if (nodes[i].value == line[3]) {
            y = i;
          }
        }
        /*  Add Node connection */
        add_connection_to_node(&nodes[x], &nodes[y]);
      }
    }
  }
  fclose(file);
  if (nodeidx) {
    return nodes;
  }
  return NULL;
}
