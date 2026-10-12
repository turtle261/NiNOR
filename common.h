#include <stdio.h>
#define TYPE size_t

// #define MAX_VALUES 255
// #define VALUE_TYPE unsigned char
#define VALUE_TYPE unsigned short
#define MAX_VALUES (VALUE_TYPE)(-1)
#define MAX_GRAPH_LINE_LEN 16
#define VALUE_IS_BASE 16
#define GRAPH_CONN_FORMAT_STR "%x->%x\n"
#define GRAPH_DEFINE_FORMAT_STR "node %x %u\n"
#define GRAPH_CONN_FORMAT_STR_WITH_POINTER "%x(%p)->%x(%p)\n"
#define GRAPH_DEFINE_FORMAT_STR_WITH_POINTER "node %x(%p) %u\n"
