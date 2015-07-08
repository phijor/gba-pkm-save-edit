#ifndef  SAVE_CHAR_ENCODING
#define  SAVE_CHAR_ENCODING

#include <stddef.h>

unsigned char save_char_table[256];

size_t save_string_decode(char dest[], unsigned char source[]);
#endif
