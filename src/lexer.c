#include "expr/lexer.h"

#define isnewline(__c) (__c == '\n')

typedef enum token_type { T_NUM = 1, T_ID, T_SPACE } expr_TokenType;

typedef struct buffer {
  char const** la;
  unsigned lines;
  unsigned loc;

  const char* buf;
  int buf_pos;
  size_t buf_size;
  // FIXME
  // conside something like
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

char expr_read_in(expr_InBuffer* buf);

expr_InBuffer* expr_new_buffer(const char* str)
{
  expr_InBuffer* buf = malloc(sizeof(*buf));

  if (!buf) {
    perror("expr_new_buffer mem allocation:");
    exit(EXIT_FAILURE);
  }

  buf->buf = str;
  buf->la = &buf->buf;
  buf->buf_pos = 0;
  buf->buf_size = strlen(str);

  return buf;
}

void expr_delete_buffer(expr_InBuffer* buf)
{
  free(buf);
  buf = NULL;
}

expr_Token* expr_new_token(expr_TokenType type, expr_TokenValue value)
{
  expr_Token* tok = malloc(sizeof(*tok));

  if (!tok) {
    perror("expr_new_token mem allocation:");
    exit(EXIT_FAILURE);
  }

  tok->type = type;
  tok->value = value;

  return tok;
}

int expr_lex_plus(expr_InBuffer* buf, expr_Token* token) {}

int expr_lex_minus(expr_InBuffer* buf, expr_Token* token) {}

int expr_lex_number(expr_InBuffer* buf, expr_Token* token)
{
  unsigned pos = buf->buf_pos;
  char peek = *(buf->buf + pos++);
  char* end = NULL;

  if (!(isdigit(peek)))
    return 0;

  token->type = T_NUM;
  token->value.big_integral = strtol(buf->buf + buf->buf_pos, &end, 10);
  buf_current = &end;

  return 1;
}

int expr_lex_spaces(expr_InBuffer* buf, expr_Token* token)
{
  unsigned loc = buf->loc;
  unsigned lines = buf->lines;
  unsigned pos = buf->buf_pos;
  char peek = *(buf->buf + pos++);

  // FIXME expr_read_in actually consumes the buffer.
  //       we don't want this behavior.
  for (; peek != EOF && pos < buf->buf_size; peek = *(buf->buf + pos++)) {
    if (isblank(peek))
      loc++;
    else if (isnewline(peek)) {
      lines++;
      loc = 0;
    } else {
      break;
    }
  }

  if (!(loc && lines)) // FIXME
    return 0;

  buf->loc = loc;
  buf->lines = lines;
  buf->buf_pos = pos;

  token->type = T_SPACE;

  return 1;
}

int expr_lex(expr_InBuffer* buf, expr_Token* token)
{
  expr_lex_spaces(buf, token);

  return expr_lex_plus(buf, token) || expr_lex_minus(buf, token) ||
         expr_lex_number(buf, token);
}

void expr_InBuffer_print(const expr_InBuffer* buf)
{
  printf("InBuffer: la=%c, pos=%d, max=%lu\n", buf->la, buf->buf_pos,
         buf->buf_size);
}

char expr_read_in(expr_InBuffer* buf)
{
  char la;

  la = *(buf->buf + buf->buf_pos);

#ifndef NDEBUG
  expr_InBuffer_print(buf);
#endif

  return ++buf->buf_pos < buf->buf_size ? la : EOF;
}
