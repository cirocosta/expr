#include "expr/parser.h"

#if 0
struct lex_program {
  char la;
  const char* buf;
  const size_t bufsize;
};
#endif

void _EXPR(expr_InBuffer*, expr_Token*);
void _REST(expr_InBuffer*, expr_Token*);
void _TERM(expr_InBuffer*, expr_Token*);
void _match(char);

void parse_str(const char* str, size_t str_len)
{
  expr_InBuffer* buf = expr_new_buffer(str, str_len);
  expr_Token token;

  expr_lex(buf, &token);
  _EXPR(buf, &token);

  expr_delete_buffer(buf);
}

void _EXPR(expr_InBuffer* buf, expr_Token* token)
{
  /* _TERM(); */
  /* _REST(); */

  printf("%s\n", "Good Job!");
}
#if 0
void _REST(void)
{
  while (1) {
    if (la == '+') {
      _match(la);
      _TERM();
      printf("%s\n", "token +");
      continue;
    } else if (la == '-') {
      _match(la);
      _TERM();
      printf("%s\n", "token -");
      continue;
    } else {
      ; // epslon
    }

    break;
  }
}

void _TERM(void)
{
  char t = la;

  if (isdigit(la)) {
    _match(la);
    printf("term: %c\n", t);
  } else {
    fprintf(stderr, "%s\n", "syntax error");
  }
}

void _match(char t)
{
  if (la != t) {
    fprintf(stderr, "Error\nLA != EXPECTED: %c != %c\n", la, t);
    exit(EXIT_FAILURE);
  }

  expr_lex();
}
#endif
