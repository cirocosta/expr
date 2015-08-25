#include <stdio.h>
#include <string.h>
#include "expr/parser.h"

int main(int argc, char* argv[])
{
  const char* buf = "1+2";
  size_t bufsize = strlen(buf);

  parse_buf(buf, bufsize);

  return 0;
}
