#ifndef HAL_LAYER_H
#define HAL_LAYER_H

#include <stdint.h>

int32_t HAL_open_ro_image(char *path);
int32_t HAL_close_image();
int32_t HAL_sector_size();
int32_t HAL_cluster_size();

int32_t HAL_read_sector(uint32_t idx, uint8_t *buf);
int32_t HAL_read_multi_sector(uint32_t idx, uint32_t num, uint8_t *buf);

#endif
