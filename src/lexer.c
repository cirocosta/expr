#include "expr/lexer.h"

expr_InBuffer* expr_new_buffer(const char* str, size_t len)
{
  expr_InBuffer* buf = malloc(sizeof(*buf));
  expr_Token* token = malloc(sizeof(*token));

  if (!buf) {
    perror("expr_new_buffer mem allocation:");
    exit(EXIT_FAILURE);
  }

  buf->token = token;
  buf->buf = str;
  buf->la = &buf->buf;
  buf->buf_pos = 0;
  buf->buf_size = len;

  return buf;
}

void expr_delete_buffer(expr_InBuffer* buf)
{
  free(buf->token);
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

int expr_lex_plus(expr_InBuffer* buf)
{
  char peek = *(buf->buf + buf->buf_pos);

  if (peek != '+')
    return 0;

  buf->token->type = EXPR_T_PLUS;
  buf->buf_pos++;

  return 1;
}

int expr_lex_minus(expr_InBuffer* buf)
{
  char peek = *(buf->buf + buf->buf_pos);

  if (peek != '-')
    return 0;

  buf->token->type = EXPR_T_MINUS;
  buf->buf_pos++;

  return 1;
}

int expr_lex_number(expr_InBuffer* buf)
{
  unsigned pos = buf->buf_pos;
  char peek = *(buf->buf + pos);
  char* end = NULL;

  if (!(isdigit(peek)))
    return 0;

  buf->token->type = EXPR_T_NUM;
  buf->token->value.big_integral = strtol(buf->buf + buf->buf_pos, &end, 10);
  // TODO debug this
  pos += (end - (buf->buf + pos));

  buf->buf_pos = pos;

  return 1;
}

int expr_lex_spaces(expr_InBuffer* buf)
{
  unsigned loc = buf->loc;
  unsigned lines = buf->lines;
  unsigned pos = buf->buf_pos;
  char peek = *(buf->buf + pos);

  while (pos < buf->buf_size) {
    if (isblank(peek))
      loc++;
    else
      break;

    peek = *(buf->buf + pos++);
  }

  // read at least one space
  if ((pos - buf->buf_pos) < 2)
    return 0;

  // we readed-ahead
  pos--;
  buf->loc = loc;
  buf->lines = lines;
  buf->buf_pos = pos;

  buf->token->type = EXPR_T_SPACE;

  return 1;
}

int expr_lex(expr_InBuffer* buf)
{
  // disconsidering spaces
  expr_lex_spaces(buf);

  return expr_lex_plus(buf) || expr_lex_minus(buf) || expr_lex_number(buf);
}
