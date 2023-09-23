#include "../include/hal-layer.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

int main() {
  uint8_t buf1[512 * 3];
  uint8_t buf2[512 * 3];

  char *filename = "./sample/floppy.img";
  HAL_open_ro_image(filename);
  assert(512 == HAL_read_sector(2, buf1));
  assert(512 * 2 == HAL_read_multi_sector(3, 2, buf1 + 512));
  HAL_close_image();

  FILE *image = fopen(filename, "r");
  fseek(image, 2 * 512, SEEK_SET);
  assert(512 == fread(buf2, 1, 512, image));
  fseek(image, 3 * 512, SEEK_SET);
  assert(512 * 2 == fread(buf2 + 512, 1, 512 * 2, image));
  for (int i = 0; i < 512 * 3; i++) {
    assert(buf1[i] == buf2[i]);
  }
}
