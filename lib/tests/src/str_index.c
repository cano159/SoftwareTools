// ----------------------------------------------------------------------
// str_index.c: test str_index
// ----------------------------------------------------------------------

#include "str.h"

int main(int argc, char** argv) {
  STR s = "abcd";
  if (str_index(s, 'c') != 3)
    return 1;
  if (str_index(s, 'e') != 0)
    return 2;
  return 0;
}
