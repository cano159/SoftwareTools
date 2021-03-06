// ----------------------------------------------------------------------
// io.c: I/O implementation
// ----------------------------------------------------------------------

#include "io.h"
#include <sys/stat.h>

void io_putdec(const int n, const size_t w) {
  char chars[MAXCHARS];

  size_t nd = str_itoc(n, chars, MAXCHARS); 
  for (size_t i = nd + 1; i <= w; ++i)
    putchar(BLANK);
  for (size_t i = 1; i <= nd; ++i)
    putchar(ARR_AT(chars,i));
}

size_t io_getlin(STR const line, FILE *file, const size_t maxlen) {
  const STR const result = fgets(line, maxlen, file);
  if (result != NULL)
    return str_length(line); 
  return maxlen;
}

void io_cant(const STR const str) {
  fprintf(stderr, "can't open %s", str);
  exit(1);
}

void io_fcopy(FILE *const in, FILE *const out) {
  char buf[MAXLINE];
  
  while (io_getlin(buf, in, MAXLINE) < MAXLINE)
    io_putlin(buf, out);
}

size_t io_fsize(const STR const fname) {
  struct stat st;
  if (stat(fname, &st) != 0)
    return ERR;
  return st.st_size;
}

void io_fskip(FILE *fd, const size_t n) {
  fseek(fd, n, SEEK_CUR);  
}

FILE *io_open(const STR const name, MODE mode) {
  switch (mode) {
    case READ:
      return fopen(name, "r");
      break;
    case WRITE:
      return fopen(name, "w");
      break;
    case READWRITE:
      return fopen(name, "r+");
      break;
    default:
      return NULL;
      break;
  }
}

FILE *io_create(const STR const name, MODE mode) {
  switch (mode) {
    case WRITE:
      return fopen(name, "w");
      break;
    case READWRITE:
      return fopen(name, "w+");
      break;
    default:
      return NULL;
      break;
  }
}
