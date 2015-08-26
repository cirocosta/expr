#include "expr/lexer.h"

void expr_InBuffer_print(const expr_InBuffer* buf)
{
  printf("InBuffer: *(buf+pos)=%c, pos=%d, max=%lu, \n",
         *(buf->buf + buf->buf_pos), buf->buf_pos, buf->buf_size);
}

expr_InBuffer* expr_new_buffer(const char* str, size_t len)
{
  expr_InBuffer* buf = malloc(sizeof(*buf));

  if (!buf) {
    perror("expr_new_buffer mem allocation:");
    exit(EXIT_FAILURE);
  }

  buf->buf = str;
  buf->la = &buf->buf;
  buf->buf_pos = 0;
  buf->buf_size = len;

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

void expr_delete_token(expr_Token* token)
{
  switch (token->type) {
    case EXPR_T_NUM:
    case EXPR_T_SPACE:
    case EXPR_T_MINUS:
    case EXPR_T_PLUS:
      break; //  these simply doesn't allocate.
    default:
      fprintf(stderr, "%s\n", "Unknown token type to free.");
      exit(EXIT_FAILURE);
  }
}

int expr_lex_plus(expr_InBuffer* buf, expr_Token* token)
{
  char peek = *(buf->buf);

  expr_InBuffer_print(buf);

  if (peek != '+')
    return 0;

  token->type = EXPR_T_PLUS;
  buf->buf_pos++;

  return 1;
}

int expr_lex_minus(expr_InBuffer* buf, expr_Token* token)
{
  char peek = *(buf->buf + 1);

  if (peek != '-')
    return 0;

  token->type = EXPR_T_MINUS;
  buf->buf_pos++;

  return 0;
}

int expr_lex_number(expr_InBuffer* buf, expr_Token* token)
{
  unsigned pos = buf->buf_pos;
  char peek = *(buf->buf + pos++);
  char* end = NULL;

  if (!(isdigit(peek)))
    return 0;

  token->type = EXPR_T_NUM;
  token->value.big_integral = strtol(buf->buf + buf->buf_pos, &end, 10);
  // TODO debug this
  pos += (end - (buf->buf + pos));

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

  token->type = EXPR_T_SPACE;

  return 1;
}

int expr_lex(expr_InBuffer* buf, expr_Token* token)
{
  /* expr_lex_spaces(buf, token); */

  printf("%s\n", "hue");

  return expr_lex_plus(buf, token);
}

