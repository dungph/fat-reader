#ifndef C_ASSERT_H
#define C_ASSERT_H

#include "stdio.h"

#define ASSERT(detail, expr)                                                   \
  printf("%s\n", detail);                                                      \
  if (expr) {                                                                  \
    printf("\x1b[0;32mSuccess\x1b[0m %s \n", #expr);                           \
  } else {                                                                     \
    printf("\x1b[0;31mFailed\x1b[0m %s \n", #expr);                            \
  }

#define ASSERT_LIST_EQ(detail, list1, list2, size)                             \
  {                                                                            \
    printf("%s\n", detail);                                                    \
    int f = 0;                                                                 \
    for (int i = 0; i < size; i++) {                                           \
      if (list1[i] == list2[i]) {                                              \
      } else {                                                                 \
        f = 1;                                                                 \
        printf("\x1b[0;31mFailed\x1b[0m assert failed at %d where %x != %x\n", \
               i, list1[i], list2[i]);                                         \
      }                                                                        \
    }                                                                          \
    if (!f) {                                                                  \
      printf("\x1b[0;32mSuccess\x1b[0m %s==%s\n", #list1, #list2);             \
    }                                                                          \
  }

#endif
