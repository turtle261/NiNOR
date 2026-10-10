typedef unsigned long long TYPE;

#define MAX_VALUES 255
#define VALUE_TYPE unsigned char

/* Notes:
 * 1. A root node is a node with no incoming connection
 * 2. Use array of node--and find/identify roots.
 */
typedef struct node {
  VALUE_TYPE value;   /* The nodes value */
  struct node **next; /* Array of pointers to the nodes this one points to*/
} node;

static int is_first = 1;
