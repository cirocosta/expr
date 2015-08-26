#include "expr/lexer.h"
#include "expr/common.h"

#include <stdio.h>
#include <stdlib.h>

// "+"
int test1()
{
  const char* str = "+";
  expr_InBuffer* buffer = expr_new_buffer(str, strlen(str));

  ASSERT(expr_lex(buffer) != 0, "Tokenization must work");
  ASSERT(buffer->token->type == EXPR_T_PLUS, "Token type must match: +");

  expr_delete_buffer(buffer);
  return 0;
}

// {SPACE}+"+"
int test2()
{
  const char* str = "           \t\t      +-";
  expr_InBuffer* buffer = expr_new_buffer(str, strlen(str));

  ASSERT(expr_lex(buffer) != 0, "Tokenization must work");
  ASSERT(buffer->token->type == EXPR_T_PLUS, "Token type must match: +");

  ASSERT(expr_lex(buffer) != 0, "Tokenization must work");
  ASSERT(buffer->token->type == EXPR_T_MINUS, "Token type must match: -");

  expr_delete_buffer(buffer);
  return 0;
}

// {NUMBER}{SPACE}+{NUMBER}
int test3()
{
  const char* str = "123+321";
  expr_InBuffer* buffer = expr_new_buffer(str, strlen(str));

  ASSERT(expr_lex(buffer) != 0, "Tokenization must work");
  ASSERT(buffer->token->type == EXPR_T_NUM, "Token type must match: NUMBER");
  ASSERT(buffer->token->value.big_integral == 123, "number must match");

  ASSERT(expr_lex(buffer) != 0, "Tokenization must work");
  ASSERT(buffer->token->type == EXPR_T_PLUS, "Token type must match: +");

  ASSERT(expr_lex(buffer) != 0, "Tokenization must work");
  ASSERT(buffer->token->type == EXPR_T_NUM, "Token type must match: NUMBER");
  ASSERT(buffer->token->value.big_integral == 321, "number must match");

  expr_delete_buffer(buffer);
  return 0;
}

int main(int argc, char* argv[])
{
  printf("%s\n", "Test Lexer:");

  test1();
  test2();
  test3();

  printf("%s\n", "Test Lexer: OK!");

  return EXIT_SUCCESS;
}
