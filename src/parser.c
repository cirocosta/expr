#include "expr/parser.h"

void _EXPR(expr_InBuffer*);
void _REST(expr_InBuffer*);
void _TERM(expr_InBuffer*);
void _match(char);

void parse_str(const char* str, size_t str_len)
{
  expr_InBuffer* buf = expr_new_buffer(str, str_len);

  expr_lex(buf);
  _EXPR(buf);

  expr_delete_buffer(buf);
}

void _EXPR(expr_InBuffer* buf)
{
  _TERM(buf);
  _REST(buf);

  DLOG("%s\n", "Good Job!");
}

void _TERM(expr_InBuffer* buf)
{
  ASSERT(buf->token->type == EXPR_T_NUM, "");
  DLOG("term: %lu\n", buf->token->value.big_integral);
  expr_lex(buf);
}

void _REST(expr_InBuffer* buf)
{
  while (1) {
    if (buf->token->type == EXPR_T_PLUS) {
      expr_lex(buf);
      DLOG("%s\n", "token +");
      _TERM(buf);
      continue;
    } else if (buf->token->type == EXPR_T_MINUS) {
      expr_lex(buf);
      DLOG("%s\n", "token -");
      _TERM(buf);
      continue;
    } else {
      ; // epslon
    }

    break;
  }
}
