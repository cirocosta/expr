#include "expr/lexer.h"

#include <stdio.h>
#include <stdlib.h>

#define ASSERT(__cond, __msg, ...)                                             \
  do {                                                                         \
    if (!(__cond)) {                                                           \
      fprintf(stderr, "\n" __BASE_FILE__ " %2d\n", __LINE__);                  \
      fprintf(stderr, "Assertion `%s` failed\n", #__cond);                     \
      fprintf(stderr, "\t" __msg "\n", ##__VA_ARGS__);                         \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)

int test1()
{
  const char* str = "+";
  expr_Token token;
  expr_InBuffer* buffer = expr_new_buffer(str, 2);

  ASSERT(expr_lex(buffer, &token) != 0, "Tokenization must work");
  ASSERT(token.type == EXPR_T_PLUS, "Token type must match: +");

  expr_delete_buffer(buffer);
  return 0;
}

int main(int argc, char* argv[])
{
  printf("%s\n", "Test Lexer:");

  test1();

  printf("%s\n", "Test Lexer: OK!");

  return EXIT_SUCCESS;
}