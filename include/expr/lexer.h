#ifndef expr__lexer_h
#define expr__lexer_h

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define isnewline(__c) (__c == '\n')

typedef enum token_type {
  EXPR_T_NUM = 1,
  EXPR_T_PLUS,
  EXPR_T_MINUS,
  EXPR_T_SPACE
} expr_TokenType;

typedef struct in_buffer {
  char const** la;
  unsigned lines;
  unsigned loc;

  const char* buf;
  int buf_pos;
  size_t buf_size;
} expr_InBuffer;

typedef union token_value {
  char* str;
  int integral;
  unsigned long big_integral;
} expr_TokenValue;

typedef struct token {
  expr_TokenType type;
  expr_TokenValue value;
} expr_Token;

expr_InBuffer* expr_new_buffer(const char* str, size_t buf_len);
void expr_delete_buffer(expr_InBuffer* buf);

expr_Token* expr_new_token(expr_TokenType type, expr_TokenValue value);
void expr_delete_token(expr_Token* token);

int expr_lex_plus(expr_InBuffer* buf, expr_Token* token);
int expr_lex_minus(expr_InBuffer* buf, expr_Token* token);
int expr_lex_number(expr_InBuffer* buf, expr_Token* token);
int expr_lex_spaces(expr_InBuffer* buf, expr_Token* token);
int expr_lex(expr_InBuffer* buf, expr_Token* token);

char expr_read_in(expr_InBuffer* buf);

#endif
