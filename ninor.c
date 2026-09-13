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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* The below is equal to the number of NOR answers one will recieve, and is half
 * of how many input bits will be processed. It should be no more than half of
 * UINT_MAX  N_WIDTH * 2 must be an even number, otherwise N_WIDTH is set to an
 * invalid value(keep it a whole number).*/
#define N_WIDTH 6

/* Super simple NOR on uint */
unsigned int nor(unsigned short a, unsigned short b) {
  if (a == 0 && b == 0) {
    return 1;
  } else
    return 0;
}
/* Does the n-input NOR calculation on the n_inputs string, processing 2xN_WIDTH
 * bits, and writing N_WIDTH answers to ans. Prepare any input to be valid
 * first before sending it here.*/
void ninor(char *n_inputs, unsigned int *ans) {
  char curr[2] = {0};
  for (unsigned int i = 0; i < (2 * N_WIDTH); i += 2) {
    curr[0] = n_inputs[i];
    unsigned short a = strtoul(curr, NULL, 10);
    curr[0] = n_inputs[i + 1];
    unsigned short b = strtoul(curr, NULL, 10);
    ans[i / 2] = nor(a, b);
  };
}

void printarray(unsigned int *ans) {
  for (unsigned int i = 0; i < N_WIDTH; i++) {
    printf("%u", ans[i]);
  }
  printf("\n");
}

/* Validates that input bitstring is even, and truncates
 * it to 2*N_WIDTH if necessary. return true if n_inputs is valid(after
 * processing it), otherwise false.*/
unsigned int process_bitstring(char *n_inputs) {
  unsigned long n = strlen(n_inputs);
  if (n == 2 * N_WIDTH) {
    /* Len is the correct length already and hence even, return true */
    return 1;
  } else if (n > (2 * N_WIDTH)) {
    /* Too large anyways so truncate and its fine */
    n_inputs[(2 * N_WIDTH)] = '\0';
    return 1;
  } else {
    /* The data is bad */
    return 0;
  }
}

int main(void) {

  char bitstring[] = "0000100011001100110011";
  int good = process_bitstring(bitstring);
  if (!good) {
    fprintf(stderr, "You did not give a valid bitstring and we could not "
                    "truncate it to one either.\n");
    return 1;
  }
  unsigned int ans[N_WIDTH];
  ninor(bitstring, ans);
  printarray(ans);
  return 0;
}
