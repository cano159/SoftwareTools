// ----------------------------------------------------------------------
// str.h: operations on strings
// ----------------------------------------------------------------------
#ifndef STR_H
#define STR_H

#include "str_type.h"
#include "bool_type.h"
#include "arr.h"

#define STR_HEAP(s,n) ARR_HEAP(s,char,n+1)
#define STR_BUF(name, size) char name[size+1]

#define MAXCHARS 255

#define BLANK ' '
#define EOS 0
#define ESCAPE '@'
#define DASH '-'
#define LETN 'n'
#define LETT 't'
#define MINUS '-'
#define NEWLINE '\n'
#define NOT '~'
#define TAB '\t'

// ---------------------------------------------------------------------- 
// index: find character c in string str
// ---------------------------------------------------------------------- 
size_t str_index(const STR const str, const char c);

// ---------------------------------------------------------------------- 
// length: compute length of string 
// ---------------------------------------------------------------------- 
size_t str_length(const STR str);

// ---------------------------------------------------------------------- 
// itoc: convert integer in to string in str 
// ---------------------------------------------------------------------- 
size_t str_itoc(const int in, STR str, const size_t size);

// ---------------------------------------------------------------------- 
// ctoi: convert string at in[*ip] to integer, increment *ip
// ---------------------------------------------------------------------- 
int str_ctoi(const STR in, size_t *ip);

// ---------------------------------------------------------------------- 
// esc: map array[i] into escaped character if appropriate 
// ---------------------------------------------------------------------- 
char str_esc(const STR const array, size_t *const ip); 

// ---------------------------------------------------------------------- 
// addset: put c in set[*jp] if it fits, increment *jp
// ---------------------------------------------------------------------- 
bool_t str_addset(char c, STR const set, size_t *const jp, 
    const size_t maxsiz);

// ---------------------------------------------------------------------- 
// equal: compare str1 to str2; return YES if equal, NO if not
// ---------------------------------------------------------------------- 
bool_t str_equal(const STR const str1, const STR const str2);

// ---------------------------------------------------------------------- 
// scopy: copy string at from(i) to to(j)
// ---------------------------------------------------------------------- 
void str_scopy(const STR const from, const int i, STR const to,
    const int j);

// ---------------------------------------------------------------------- 
// getwrd: get non-blank word from in[*i] into out; increment *i
// ---------------------------------------------------------------------- 
size_t str_getwrd(const STR const in, size_t *i, STR const out);

#endif
