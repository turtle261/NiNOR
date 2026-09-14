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

#include <stdbool.h>
#include <stdio.h>

/* This macro sets the type, which restricts the maximum length of inputs to a
 * NiNOR gate. */
#define TYPE unsigned long long

/* Performs N-input NOR (NiNOR) on n(len) bool inputs (n_input) and returns
 * result */
bool ninor(bool n_inputs[], TYPE len) {
  for (TYPE i = 0; i < len; i++) {
    if (n_inputs[i]) {
      return 0;
    }
  }
  return 1;
}

/* Writes bools to stream cast to unsigned char */
void putbools(bool n_inputs[], TYPE len, FILE *stream) {
  for (TYPE i = 0; i < len; i++) {
    putc(n_inputs[i] + '0', stream);
  }
  putc('\n', stream);
}

int main(void) {
  /* bool mylist[] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
                   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
                   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
*/
  bool mylist[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  TYPE len = sizeof mylist / sizeof(bool);
  putbools(mylist, len, stdout);
  return ninor(mylist, len);
}
