#ifndef HAL_LAYER_H
#define HAL_LAYER_H

#include <stdint.h>
#include <stdio.h>

int32_t HAL_set_filepath(const char *path);
int32_t HAL_set_sector_size(int32_t size);

int32_t HAL_read_bytes(int offset, uint32_t num, uint8_t *buf);
int32_t HAL_read_sector(uint32_t idx, uint8_t *buf);
int32_t HAL_read_multi_sector(uint32_t idx, uint32_t num, uint8_t *buf);

uint8_t HAL_read_u8(int offset);

uint16_t HAL_read_uint16_le(int offset);

uint32_t HAL_read_uint32_le(int offset);

int32_t HAL_open_file(const char *path);
int32_t HAL_close_file();
#endif
