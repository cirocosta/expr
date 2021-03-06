#ifndef EXPR__DEBUG_H
#define EXPR__DEBUG_H

#include "expr/common.h"

#ifndef NDEBUG
#define DASSERT(__cond, __msg, ...) ASSERT(__cond, __msg, #__VA_ARGS__)
#define DLOG(__msg, ...) LOG(__msg, ##__VA_ARGS__)
#define DLOGERR(__msg, ...) LOGERR(__msg, ##__VA_ARGS__)
#define DPERROR(__msg)                                                         \
  do {                                                                         \
    perror(__msg)                                                              \
  } while (0)
#else
#define DASSERT(__cond, __msg, ...)
#define DLOG(__msg, ...)
#define DLOGERR(__msg, ...)
#define DPERROR(__msg)
#endif // ! NDEBUG

#endif // ! EXPR__DEBUG_H
