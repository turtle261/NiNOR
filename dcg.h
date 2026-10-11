typedef unsigned long long TYPE;

#define MAX_VALUES 255
#define VALUE_TYPE unsigned char

/* Notes:
 * 1. A root node is a node with no incoming connection
 * 2. Use array of node--and find/identify roots.
 */

/* The node itself which can point to several other nodes and hold a value */
typedef struct node {
  VALUE_TYPE value;   /* The nodes value */
  struct node **next; /* Array of pointers to the nodes this one points to*/
} node;

/* Function declarations */

/* Prints the graph following a root node, including identifying loops/cycles.
 * It does this by pointer, and thus DOES NOT assume nodes in the graph are
 * unique by value.*/
void print_nodes_by_pointer(node *root);

/* Prints the graph following a root node, including identifying loops/cycles.
 * It does this by value, and thus assumes nodes in the graph are unique by
 * value.*/
void print_nodes_by_value(node *root);

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
