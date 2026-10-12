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

#include "common.h"
/* #define ALWAYS_PRINT_GRAPH_POINTERS */
/* #define ALWAYS_PRINT_GRAPH_VALUES */

/* The node itself which can point to several other nodes and hold a value */
typedef struct node {
  struct node **next; /* Array of pointers to the nodes this one points to*/
  VALUE_TYPE value; /* The nodes value -- can use as label, a value or ignore */
  unsigned char out : 1; /* What things this node points to will get now */
  unsigned char pending : 1;
} node;

/* Function declarations */

/* Prints the graph following a root node, including identifying loops/cycles.
 * It does this by pointer, and thus DOES NOT assume nodes in the graph are
 * unique by value. It * will write to the output (FILE *) parameter.*/
void print_nodes_by_pointer(node *root, FILE *output);

/* Prints the graph following a root node, including identifying loops/cycles.
 * It does this by value, and thus assumes nodes in the graph are unique by
 * value. It * will write to the output (FILE *) parameter.*/
void print_nodes_by_value(node *root, FILE *output);

/* Gets the number of connections derived from a given root node by pointer
 * (thus it DOES NOT assume unique values for each node in the graph). I.e.
 * number of nodes it connects to + those of which those connect to and so
 * forth, INCLUDING LOOPS/CYCLES. */
TYPE node_number_of_connections_incl_loop(node *root);

/* Gets the number of connections derived from a given root node by pointer(thus
 * it DOES NOT assume unique values for each node in the graph). I.e. number of
 * nodes it connects to + those of which those connect to and so forth, NOT
 * counting loops. */
TYPE node_number_of_connections(node *root);

/* Check if a pointer is in an array of pointers */
unsigned char is_p_in_arr_of_p(void *in, void **check);

/* Check if an unsigned char is in an unsigned string (array of unsigned chars,
 * terminated by '\0' */
unsigned char is_x_in_arr_of_x(VALUE_TYPE in, VALUE_TYPE *check);

/* Parses input files in the super simple format... Will try to return NULL on
wrong files or inputs. Avoid bad inputs.*/
node *load_graph(char *filepath);

/* Returns 1 if it added a connection to node, 0 otherwise */
int add_connection_to_node(node *base, node *next);

/* Prints the node definitions of a graph following a root node. It does this by
 * value, and thus assumes nodes in the graph are unique by value. It will write
 * to the output (FILE *) parameter.*/
void print_nodes_definition_by_value(node *root, FILE *output);

/* Prints the node definitions of a graph following a root node. It does this by
 * pointer, and thus DOES NOT assume nodes in the graph are unique by value. It
 * will write to the output (FILE *) parameter.*/
void print_nodes_definition_by_pointer(node *root, FILE *output);

/* Iterates the graph a tick */
void step_graph(node *root);
void print_raw(node *root, FILE *output);
void print_definitions_raw(node *root, FILE *output);
