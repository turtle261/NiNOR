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
#include <stdio.h>
#include <stdlib.h>

static unsigned char is_first = 1;

/* Check if a VALUE_TYPE is in an array of VALUE_TYPE,
 * terminated by '\0' . Returns a boolean as unsigned char.*/
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
  (is_first) ? value = calloc(MAX_VALUES + 1, sizeof(value)) : 0;
  static VALUE_TYPE vallen = 1;
  (!value[0]) ? value[0] = root : 0;
  for (VALUE_TYPE i = 0, o = 0; !o; ++i) {
    if (root->next[i] == NULL) {
      o = 1;
    } else if (is_p_in_arr_of_p(root->next[i], value)) {
    } else {
      value[vallen] = root->next[i];
      ++vallen;
      unsigned char temp = is_first;
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
  (is_first) ? value = calloc(MAX_VALUES + 1, sizeof(value)) : 0;
  static VALUE_TYPE vallen = 1;
  (!value[0]) ? value[0] = root : 0;
  for (VALUE_TYPE i = 0, o = 0; !o; ++i) {
    if (root->next[i] == NULL) {
      o = 1;
    } else if (is_p_in_arr_of_p(root->next[i], value)) {
      ++max;
    } else {
      value[vallen] = root->next[i];
      ++vallen;
      unsigned char temp = is_first;
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

void print_graph_definitions(node *root, FILE *output) {
  while (root->next) {
    fprintf(output, GRAPH_DEFINE_FORMAT_STR, root->value, root->out);
    root++;
  }
}
void print_graph_definitions_with_pointers(node *root, FILE *output) {
  while (root->next) {
    fprintf(output, GRAPH_DEFINE_FORMAT_STR_WITH_POINTER, root->value,
            (void *)root, root->out);
    root++;
  }
}
void print_graph(node *root, FILE *output) {
  while (root->next) {
    for (VALUE_TYPE i = 0; root->next[i]; ++i) {
      fprintf(output, GRAPH_CONN_FORMAT_STR, root->value, root->next[i]->value);
    }
    root++;
  }
}
void print_graph_with_pointers(node *root, FILE *output) {
  while (root->next) {
    for (VALUE_TYPE i = 0; root->next[i]; ++i) {
      fprintf(output, GRAPH_CONN_FORMAT_STR_WITH_POINTER, root->value,
              (void *)root, root->next[i]->value, (void *)root->next[i]);
    }
    root++;
  }
}

/* Returns 1 if it added a connection to node, 0 otherwise */
int add_connection_to_node(node *base, node *next) {
  for (VALUE_TYPE i = 0; i < MAX_VALUES; ++i) {
    if (base->next[i] == NULL) {
      base->next[i] = next;
      i = MAX_VALUES;
      return 1; /* Worked */
    }
  }
  return 0;
}

VALUE_TYPE get_value_from_line(char *line, unsigned char lineidx,
                               unsigned char *finalidx) {
  char value_word[MAX_GRAPH_LINE_LEN - 8];
  for (unsigned char i = 0; i < (MAX_GRAPH_LINE_LEN - lineidx); ++i) {
    if (line[i + lineidx] == ' ' || line[i + lineidx] == '\n' ||
        line[i + lineidx] == '-') {
      value_word[i] = '\0';
      if (finalidx) { /* If finalidx is not a NULL pointer then set it to this
                         value */
        *finalidx = lineidx + (i - 1);
      }
      i = MAX_GRAPH_LINE_LEN; // leave the for loop
    } else {
      value_word[i] = line[i + lineidx];
    }
  }
  return (VALUE_TYPE)strtoull(value_word, NULL, VALUE_IS_BASE);
}

unsigned char idx_first_char_after_arrow(char *line) {
  unsigned char sum = 1;
  while (line) {
    if (*line == '>') {
      break;
    }
    ++sum;
    ++line;
  }
  return sum;
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
  VALUE_TYPE valnum = 0;
  VALUE_TYPE nodeidx = 0;
  node *nodes = calloc(MAX_VALUES + 1, sizeof(*nodes));
  while (fgets(line, MAX_GRAPH_LINE_LEN, file)) {
    if (line[0] == 'n' && line[1] == 'o' && line[2] == 'd' && line[3] == 'e' &&
        line[4] == ' ') { /* node declaration*/
      unsigned char lineidx = 5;
      values[valnum] = get_value_from_line(line, lineidx, &lineidx);
      nodes[nodeidx].next = calloc(MAX_VALUES + 1, sizeof(*nodes->next));
      nodes[nodeidx].value = values[valnum];
      ++valnum;
      /* Set the out/pending values */
      for (unsigned char i = 0; i < 4; ++i) {
        if (line[lineidx + i] == '\0') {
          i = 4;
        } else if (line[lineidx + i - 1] == ' ' &&
                   line[lineidx + i + 1] == '\n') {
          nodes[nodeidx].out = (line[lineidx + i] != '0') ? 1 : 0;
          nodes[nodeidx].pending = 0; /* Initialize to zero */
        }
      }
      ++nodeidx;
    } else if (nodeidx &&
               is_x_in_arr_of_x(get_value_from_line(line, 0, NULL), values) &&
               is_x_in_arr_of_x(
                   get_value_from_line(line, idx_first_char_after_arrow(line),
                                       NULL),
                   values)) {
      /* Direction definition */
      VALUE_TYPE x = 0, y = 0;
      for (VALUE_TYPE i = 0; i < nodeidx; ++i) {
        if (nodes[i].value == get_value_from_line(line, 0, NULL)) {
          x = i;
        }
        if (nodes[i].value ==
            get_value_from_line(line, idx_first_char_after_arrow(line), NULL)) {
          y = i;
        }
      }
      /*  Add Node connection */
      add_connection_to_node(&nodes[x], &nodes[y]);
    }
  }
  fclose(file);
  if (nodeidx) {
    return nodes;
  }
  if (nodes) {
    for (node *copy = nodes; copy->next; ++copy) {
      free(copy->next);
    }
    free(nodes);
  }
  return NULL;
}

/* Sets pending to out */
void set_graph_pending_to_out(node *root) {
  while (root->next) {
    for (VALUE_TYPE i = 0; root->next[i]; ++i) {
      if (root->out) {
        root->next[i]->pending = 1;
      }
    }
    root++;
  }
}

/* Sets out to zero  */
void set_graph_out_to_zero(node *root) {
  while (root->next) {
    for (VALUE_TYPE i = 0; root->next[i]; ++i) {
      root->next[i]->out = 0;
    }
    root->out = 0;
    root++;
  }
}

/* Sets out to !pending*/
void set_graph_out_to_pending(node *root) {
  while (root->next) {
    for (VALUE_TYPE i = 0; root->next[i]; ++i) {
      root->next[i]->out = !root->next[i]->pending;
    }
    root->out = !root->pending;
    root++;
  }
}

/* Sets graph pending to zero*/
void set_graph_pending_to_zero(node *root) {
  while (root->next) {
    for (VALUE_TYPE i = 0; root->next[i]; ++i) {
      root->next[i]->pending = 0;
    }
    root->pending = 0;
    root++;
  }
}

void step_graph(node *root) {
  /* Assume pending is already all zeroes */
  set_graph_pending_to_out(
      root); /* Now pending holds the values for the input + 1 tick */
  set_graph_out_to_zero(root); /* Remove the current ticks values so we can add
                                  the next tick values. */
  set_graph_out_to_pending(root); /*Add the next ticks values to out. Now out is
                                     the next ticks values*/
  set_graph_pending_to_zero(root); /* Make it so the pendings are zero so this
                                      function can be ran again */
}
