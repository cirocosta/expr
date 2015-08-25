#ifndef parser_h
#define parser_h 

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "expr/lexer.h"

void parse_buf(const char* buf, size_t bufsize);

#endif
