#include "../include/hal.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE *image = NULL;

uint8_t HAL_read_u8(int offset) {
  assert(image != NULL);

  fseek(image, offset, SEEK_SET);
  uint8_t ret;
  fread(&ret, 1, 1, image);
  return ret;
}

uint16_t HAL_read_uint16_le(int offset) {
  assert(image != NULL);

  fseek(image, offset, SEEK_SET);
  uint8_t buf[2];
  fread(buf, 1, 2, image);
  uint16_t ret;
  ret = ((uint16_t)buf[0] | ((uint16_t)buf[1]) << 8);
  return ret;
}

uint32_t HAL_read_uint32_le(int offset) {
  assert(image != NULL);

  fseek(image, offset, SEEK_SET);
  int8_t buf[4];
  fread(buf, 1, 4, image);
  uint16_t ret;
  ret = ((uint32_t)buf[0] | ((uint32_t)buf[1]) << 8 | ((uint32_t)buf[2]) << 16 |
         ((uint32_t)buf[3]) << 24);
  return ret;
}

int32_t HAL_sector_size() {
  ;
  return HAL_read_uint16_le(11);
}

int32_t HAL_open_file(const char *path) {
  image = fopen(path, "r");
  return 0;
}
int32_t HAL_close_file() {
  fclose(image);
  image = NULL;
  return 0;
}
int32_t HAL_read_bytes(int offset, uint32_t num, uint8_t *buf) {
  fseeko(image, offset, SEEK_SET);
  int ret = fread(buf, 1, num, image);
  return ret;
}

int32_t HAL_read_sector(uint32_t idx, uint8_t *buf) {
  return HAL_read_bytes(idx * HAL_sector_size(), HAL_sector_size(), buf);
}

int32_t HAL_read_multi_sector(uint32_t idx, uint32_t num, uint8_t *buf) {
  return HAL_read_bytes(idx * HAL_sector_size(), HAL_sector_size() * num, buf);
}
