#include "utils.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

uint8_t read_uint8(FILE *file, int offset) {
  fseek(file, offset, SEEK_SET);
  uint8_t ret;
  fread(&ret, 1, 1, file);
  return ret;
}

uint16_t read_uint16_le(FILE *file, int offset) {
  fseek(file, offset, SEEK_SET);
  uint8_t buf[2];
  fread(buf, 1, 2, file);
  uint16_t ret;
  ret = ((uint16_t)buf[0] | ((uint16_t)buf[1]) << 8);
  return ret;
}

uint16_t read_uint32_le(FILE *file, int offset) {
  fseek(file, offset, SEEK_SET);
  int8_t buf[4];
  fread(buf, 1, 4, file);
  uint16_t ret;
  ret = ((uint32_t)buf[0] | ((uint32_t)buf[1]) << 8 | ((uint32_t)buf[2]) << 16 |
         ((uint32_t)buf[3]) << 24);
  return ret;
}

uint16_t read_byte_per_sector(FILE *file) { return read_uint16_le(file, 11); }
uint16_t read_sector_per_reserved(FILE *file) {
  return read_uint16_le(file, 14);
}
uint8_t read_sector_per_cluster(FILE *file) { return read_uint8(file, 13); }
uint16_t read_sector_per_fat(FILE *file) { return read_uint16_le(file, 22); }
uint8_t read_nof_fat(FILE *file) { return read_uint8(file, 16); }
uint16_t read_max_file_in_root(FILE *file) { return read_uint16_le(file, 17); }
uint16_t read_nof_sector(FILE *file) {
  uint16_t n2 = read_uint16_le(file, 19);
  if (n2 == 0) {
    return read_uint32_le(file, 32);
  } else {
    return n2;
  }
}
