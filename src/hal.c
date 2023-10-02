#include "../include/hal.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE *image = NULL;
static uint32_t sector_size = 0;

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
  if (fseek(image, offset, SEEK_SET)) {
    printf("seek failed! retry\n");
    if (fseek(image, offset, SEEK_SET)) {
      printf("seek failed! abort\n");
      return 1;
    }
  }
  return fread(buf, 1, num, image);
}

int32_t HAL_read_sector(uint32_t idx, uint8_t *buf) {
  if (sector_size == 0) {
    printf("invalid sector size");
    exit(-1);
  }
  return HAL_read_bytes(idx * sector_size, sector_size, buf);
}

int32_t HAL_read_multi_sector(uint32_t idx, uint32_t num, uint8_t *buf) {
  if (sector_size == 0) {
    printf("invalid sector size");
    exit(-1);
  }
  return HAL_read_bytes(idx * sector_size, sector_size * num, buf);
}

void HAL_set_sector_size(uint32_t size) {
  sector_size = size;
  return;
}
