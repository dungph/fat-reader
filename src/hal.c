#include "../include/hal.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE *image = NULL;

uint8_t HAL_read_u8(int offset) {
  uint8_t ret;
  HAL_read_bytes(offset, 1, &ret);
  return ret;
}

uint16_t HAL_read_uint16_le(int offset) {
  uint8_t buf[2];
  HAL_read_bytes(offset, 2, buf);
  return ((uint16_t)buf[0] | ((uint16_t)buf[1]) << 8);
}

uint32_t HAL_read_uint24_le(int offset) {
  uint8_t buf[3];
  HAL_read_bytes(offset, 3, buf);
  return ((uint32_t)buf[0] | ((uint32_t)buf[1]) << 8 |
          ((uint32_t)buf[2]) << 16);
}

uint32_t HAL_read_uint32_le(int offset) {
  uint8_t buf[4];
  HAL_read_bytes(offset, 4, buf);
  return ((uint32_t)buf[0] | ((uint32_t)buf[1]) << 8 |
          ((uint32_t)buf[2]) << 16 | ((uint32_t)buf[3]) << 24);
}

int32_t HAL_sector_size() {
  ;
  return HAL_read_uint16_le(11);
}

int32_t HAL_open_file(const char *path) {
  image = fopen(path, "r");
  if (!image) {
    printf("open failed! abort");
    return -1;
  }
  return 0;
}

int32_t HAL_close_file(void) {
  int ret = fclose(image);
  image = NULL;
  return ret;
}

int32_t HAL_read_bytes(uint32_t offset, uint32_t num, void *buf) {
  if (fseeko(image, offset, SEEK_SET)) {
    printf("seek failed! retry");
    if (fseeko(image, offset, SEEK_SET)) {
      printf("seek failed! abort");
      return 1;
    }
  }
  return fread(buf, 1, num, image);
}

int32_t HAL_read_sector(uint32_t idx, uint8_t *buf) {
  return HAL_read_bytes(idx * HAL_sector_size(), HAL_sector_size(), buf);
}

int32_t HAL_read_multi_sector(uint32_t idx, uint32_t num, uint8_t *buf) {
  return HAL_read_bytes(idx * HAL_sector_size(), HAL_sector_size() * num, buf);
}
