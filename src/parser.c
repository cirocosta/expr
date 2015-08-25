#include "expr/parser.h"

char read_in();


#if 0
struct lex_program {
  char la;
  const char* buf;
  const size_t bufsize;
};
#endif

char la = 0;
const char* in_buf = NULL;
int pos = 0;
size_t in_bufsize = 0;

void _EXPR(void);
void _REST(void);
void _TERM(void);
void _match(char);

void parse_buf(const char* buf, size_t bufsize)
{
  in_buf = buf;
  in_bufsize = bufsize;

  read_in();
  _EXPR();
}

void _EXPR(void)
{
  _TERM();
  _REST();

  printf("%s\n", "Good Job!");
}

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

  read_in();
}
