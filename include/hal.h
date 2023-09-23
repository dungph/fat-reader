#ifndef HAL_LAYER_H
#define HAL_LAYER_H

#include <stdint.h>
#include <stdio.h>

int32_t HAL_open_ro_image(char *path);
int32_t HAL_close_image();

uint8_t HAL_read_uint8(int offset);
uint16_t HAL_read_uint16_le(int offset);
uint16_t HAL_read_uint32_le(int offset);

int32_t HAL_sector_size();
int32_t HAL_cluster_size();
int32_t HAL_reserved_size();
int32_t HAL_fat_size();
int32_t HAL_fat_count();
int32_t HAL_maxfile_count();
int32_t HAL_sector_count();

int32_t HAL_read_sector(uint32_t idx, uint8_t *buf);
int32_t HAL_read_multi_sector(uint32_t idx, uint32_t num, uint8_t *buf);

#endif
