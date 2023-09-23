#include <stdint.h>
#include <stdio.h>

#ifndef UTILS_H
#define UTILS_H

uint8_t read_uint8(FILE *file, int offset);
uint16_t read_uint16_le(FILE *file, int offset);
uint16_t read_uint32_le(FILE *file, int offset);
uint16_t read_byte_per_sector(FILE *file);
uint16_t read_sector_per_reserved(FILE *file);
uint8_t read_sector_per_cluster(FILE *file);
uint16_t read_sector_per_fat(FILE *file);
uint8_t read_nof_fat(FILE *file);
uint16_t read_max_file_in_root(FILE *file);
uint16_t read_nof_sector(FILE *file);

#else
#endif
