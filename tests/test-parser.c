#include <stdio.h>
#include <string.h>
#include "expr/parser.h"
#include "expr/common.h"

void test1()
{
  const char* str = "1+2+3";

  parse_str(str, strlen(str));
}

int main(int argc, char* argv[])
{
  printf("%s\n", "Test Parser: RUNNING");

  test1();

  printf("%s\n", "Test Parser: OK OK OK");

  return 0;
}
