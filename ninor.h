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

/*
1 , 2   3 , 4   5   6   7   8   9   10
T	T	F	F	T	T	F	F	F	T
T	F	F	T	F	T	T	F	T	F
F	T	T	F	F	T	T	F	T	F
F	F	T	T	F	F	T	T	F	T
1,2: Name(function)
3,4: NOT(negation)
5: AND(conjunction)
6: OR(disjunction)
7: NAND(non-conjunction)
8: NOR(non-disjunction)
9: XOR(non-equivalence)
10: XNOR(equivalence)
*/

#include "common.h"
#include <stdio.h>
/* This macro sets the type, which restricts the maximum length of inputs to a
 * NiNOR gate. */

/* Performs N-input NOR (NiNOR) on n(len) bool inputs (n_input) and returns
 * result */
unsigned char ninor(unsigned char n_inputs[], VALUE_TYPE len) {
  for (VALUE_TYPE i = 0; i < len; i++) {
    if (n_inputs[i]) {
      return 0;
    }
  }
  return 1;
}

/* Writes unsigned chars up to len and offsets them so they print as numbers
 * right. */
void putchars(unsigned char n_inputs[], TYPE len, FILE *stream) {
  for (TYPE i = 0; i < len; i++) {
    putc(n_inputs[i] + '0', stream);
  }
  putc('\n', stream);
}
