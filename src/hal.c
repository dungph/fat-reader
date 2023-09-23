#include "../include/hal.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

static FILE *image = NULL;

static uint32_t sector_size;
static uint32_t cluster_size;
static uint32_t reserved_size;
static uint32_t fat_size;
static uint32_t fat_count;
static uint32_t maxfile_count;
static uint32_t sector_count;

uint8_t HAL_read_byte(int offset) {
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

uint16_t HAL_read_uint32_le(int offset) {
  assert(image != NULL);
  fseek(image, offset, SEEK_SET);
  int8_t buf[4];
  fread(buf, 1, 4, image);
  uint16_t ret;
  ret = ((uint32_t)buf[0] | ((uint32_t)buf[1]) << 8 | ((uint32_t)buf[2]) << 16 |
         ((uint32_t)buf[3]) << 24);
  return ret;
}

int32_t HAL_open_ro_image(char *path) {
  image = fopen(path, "r");
  sector_size = HAL_read_uint16_le(11);
  cluster_size = HAL_read_byte(13) * sector_size;
  reserved_size = HAL_read_uint16_le(14) * sector_size;
  fat_size = HAL_read_uint16_le(22) * sector_size;
  fat_count = HAL_read_byte(16);
  maxfile_count = HAL_read_uint16_le(17);
  sector_count = HAL_read_uint16_le(19);
  if (sector_count == 0) {
    sector_count = HAL_read_uint32_le(32);
  }

  if (image != NULL) {
    return 0;
  } else {
    return -1;
  }
}

int32_t HAL_sector_size() {
  assert(image != NULL);
  return sector_size;
}

int32_t HAL_cluster_size() {
  assert(image != NULL);
  return cluster_size;
}

int32_t HAL_reserved_size() {
  assert(image != NULL);
  return reserved_size;
}
int32_t HAL_fat_size() {

  assert(image != NULL);
  return fat_size;
}
int32_t HAL_fat_count() {

  assert(image != NULL);
  return fat_count;
}
int32_t HAL_maxfile_count() {
  assert(image != NULL);
  return maxfile_count;
}
int32_t HAL_sector_count() {
  assert(image != NULL);
  return sector_count;
}

int32_t HAL_read_sector(uint32_t idx, uint8_t *buf) {
  assert(image != NULL);
  fseek(image, idx * sector_size, SEEK_SET);
  return fread(buf, 1, sector_size, image);
}

int32_t HAL_read_multi_sector(uint32_t idx, uint32_t num, uint8_t *buf) {
  assert(image != NULL);
  fseek(image, idx * sector_size, SEEK_SET);
  return fread(buf, 1, sector_size * num, image);
}

int32_t HAL_close_image() {
  int32_t ret = fclose(image);
  image = NULL;
  return ret;
}
