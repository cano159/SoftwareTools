// ---------------------------------------------------------------------- 
// translit: map characters 
// ---------------------------------------------------------------------- 

#include "st.h"

#define MAXARR 1024
#define MAXSET 1024

static const STR const digits = "0123456789";
static const STR const lowalf = "abcdefghijklmnopqrstuvwxyz";
static const STR const upalf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// ---------------------------------------------------------------------- 
// dodash: expand array[*i-1]--array[*i+1] into set[*j]... from valid
// ---------------------------------------------------------------------- 
static void dodash(const STR const valid, const STR const array,
    size_t *const i, STR const set, size_t *const j, 
    const size_t maxset) {
  ++*i;
  --*j;

  size_t limit = str_index(valid, str_esc(array, i));
  for (size_t k = str_index(valid, ARR_AT(set, *j)); k <= limit; ++k)
      str_addset(ARR_AT(valid, k), set, j, maxset);
}

// ---------------------------------------------------------------------- 
// filset: expand set at array[*i] into set[*j], stop at delim
// ---------------------------------------------------------------------- 
static void filset(const char delim, const STR const array, size_t *const i,
    STR const set, size_t *const j, const size_t maxset) {
  for ( ; ARR_AT(array, *i) != delim && ARR_AT(array, *i) != EOS; ++*i)
   if (ARR_AT(array, *i) == ESCAPE)
     str_addset(str_esc(array, i), set, j, maxset);
   else if (ARR_AT(array, *i) != DASH)
     str_addset(ARR_AT(array, *i), set, j, maxset);
   else if (*j <= 1 || ARR_AT(array, (*i)+1) == EOS)
     // literal DASH
     str_addset(DASH, set, j, maxset);
   else if (str_index(digits, ARR_AT(set, (*j)-1)) > 0)
     dodash(digits, array, i, set, j, maxset);
   else if (str_index(lowalf, ARR_AT(set, (*j)-1)) > 0)
     dodash(lowalf, array, i, set, j, maxset);
   else if (str_index(upalf, ARR_AT(set, (*j)-1)) > 0)
     dodash(upalf, array, i, set, j, maxset);
   else
     str_addset(DASH, set, j, maxset); 
}

// ---------------------------------------------------------------------- 
// makset: make set from array[k] in set
// ---------------------------------------------------------------------- 
bool_t makset(const STR const array, const size_t k, STR const set,
    const size_t size) {
  size_t i = k;
  size_t j = 1;
  filset(EOS, array, &i, set, &j, size);
  return str_addset(EOS, set, &j, size);
}

// ---------------------------------------------------------------------- 
// xindex: invert condition returned by index
// ---------------------------------------------------------------------- 
size_t str_xindex(const STR const array, const char c,
    const bool_t allbut, const size_t lastto) {
  if (c == EOF)
    return 0;
  else if (allbut == NO)
    return str_index(array, c);
  else if (str_index(array, c) > 0)
    return 0;
  else
    return lastto + 1;
}

static char arg[MAXARR];
static char from[MAXSET];
static char to[MAXSET];

MAIN ( 
  char c;
  size_t lastto;
  bool_t allbut;
  bool_t collap;

  if (args_getarg(1, arg, MAXARR) >= MAXARR)
    error("usage: translit from to");
  else if (ARR_AT(arg, 1) == NOT) {
    allbut = YES; 
    if (makset(arg, 2, from, MAXSET) == NO)
      error("from: to large.");
  }
  else {
    allbut = NO;
    if (makset(arg, 1, from, MAXSET) == NO)
      error("from: too large.");
  }
  if (args_getarg(2, arg, MAXARR) >= MAXARR)
    ARR_AT(to, 1) = EOS;
  else if (makset(arg, 1, to, MAXSET) == NO)
    error("to: too large.");

  lastto = str_length(to);
  if (str_length(from) > lastto || allbut == YES)
    collap = YES;
  else
    collap = NO;
  REPEAT {
    size_t i = str_xindex(from, GETC(c), allbut, lastto);
    if (collap == YES && i >= lastto && lastto > 0) {
      // collapse
      PUTC(ARR_AT(to, lastto));
      do
        i = str_xindex(from, GETC(c), allbut, lastto);
      UNTIL (i < lastto);
    }
    if (c == EOF)
      break;
    if (i > 0 && lastto > 0)
      // translate
      PUTC(ARR_AT(to, i));
    else if (i == 0)
      // copy
      PUTC(c);
  }
  return 0;
)

