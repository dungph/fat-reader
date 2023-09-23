#include "../include/hal-layer.h"
#include "../include/utils.h"

#include <stdint.h>
#include <stdio.h>

static FILE *image;
static uint32_t sector_size;
static uint32_t cluster_size;

int32_t HAL_open_ro_image(char *path) {
  image = fopen(path, "r");
  sector_size = read_byte_per_sector(image);
  cluster_size = read_sector_per_cluster(image) * sector_size;

  if (image != NULL) {
    return 0;
  } else {
    return -1;
  }
}

int32_t HAL_sector_size() { return sector_size; }

int32_t HAL_cluster_size() { return cluster_size; }

int32_t HAL_read_sector(uint32_t idx, uint8_t *buf) {
  fseek(image, idx * sector_size, SEEK_SET);
  return fread(buf, 1, sector_size, image);
}

int32_t HAL_read_multi_sector(uint32_t idx, uint32_t num, uint8_t *buf) {
  fseek(image, idx * sector_size, SEEK_SET);
  return fread(buf, 1, sector_size * num, image);
}

int32_t HAL_close_image() {
  return fclose(image);
}
