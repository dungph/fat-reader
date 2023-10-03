#include "../include/hal.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#define ASSERT(detail, expr)                                                   \
  printf("%s\n", detail);                                                      \
  if (expr) {                                                                  \
    printf("\x1b[0;32mSuccess\x1b[0m %s \n", #expr);                           \
  } else {                                                                     \
    printf("\x1b[0;31mFailed\x1b[0m %s \n", #expr);                            \
  }

#define ASSERT_LIST_EQ(detail, list1, list2, size)                             \
  printf("%s\n", detail);                                                      \
  int f = 0;                                                                   \
  for (int i = 0; i < size; i++) {                                             \
    if (list1[i] == list2[i]) {                                                \
    } else {                                                                   \
      f = 1;                                                                   \
      printf("\x1b[0;31mFailed\x1b[0m assert failed at %d where %x != %x\n",   \
             i, list1[i], list2[i]);                                           \
    }                                                                          \
  }                                                                            \
  if (!f) {                                                                    \
    printf("\x1b[0;32mSuccess\x1b[0m %s==%s\n", #list1, #list2);               \
  }

int main() {
  uint8_t buf1[512 * 3];
  uint8_t buf2[512 * 3];

  char *filename = "./sample/floppy.img";
  HAL_open_file(filename);
  HAL_set_sector_size(512);

  ASSERT("check read return", 512 == HAL_read_sector(2, buf1));
  ASSERT("check read multi return",
         512 * 2 == HAL_read_multi_sector(3, 2, buf1 + 512));

  FILE *image = fopen(filename, "r");
  fseek(image, 2 * 512, SEEK_SET);
  assert(512 == fread(buf2, 1, 512, image));
  fseek(image, 3 * 512, SEEK_SET);
  assert(512 * 2 == fread(buf2 + 512, 1, 512 * 2, image));
  for (int i = 0; i < 512 * 3; i++) {
    assert(buf1[i] == buf2[i]);
  }
  buf1[0] = 2;
  ASSERT_LIST_EQ("check read bytes", buf1, buf2, 512 * 3)
}
