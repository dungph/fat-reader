#include "../include/bs.h"
#include "../include/hal.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int32_t BS_sector_size() {
  ;
  return HAL_read_uint16_le(11);
}
int32_t BS_cluster_size() { return HAL_read_u8(13) * BS_sector_size(); }

int32_t BS_reserved_size() { return HAL_read_uint16_le(14) * BS_sector_size(); }
int32_t BS_table_size() {

  if (BS_is_fat32()) {
    // unimplemented
    assert(0 == 1);
  } else {
    return HAL_read_uint16_le(22) * BS_sector_size();
  }
}
int32_t BS_entry_size() {
  ;
  return 32;
}
int32_t BS_table_count() {
  ;
  return HAL_read_u8(16);
}
int32_t BS_maxfile_count() {
  if (BS_is_fat32()) {
    // unimplemented
    assert(0 == 1);
  } else {
    return HAL_read_uint16_le(17);
  }
}
int32_t BS_sector_count() {
  uint32_t size = HAL_read_uint16_le(19);
  if (size > 0) {
    return size;
  } else {
    return HAL_read_uint32_le(32);
  }
}
int32_t BS_is_fat12() { return 1; }

int32_t BS_is_fat16() { return 0; }

int32_t BS_is_fat32() { return 0; }

int32_t BS_table_offset() { return BS_reserved_size(); }

int32_t BS_data_offset() {
  if (BS_is_fat32()) {
    assert(0 == 1);
  } else {
    return BS_root_offset() + BS_maxfile_count() * BS_entry_size();
  }
}

int32_t BS_root_offset() {
  if (BS_is_fat32()) {
    assert(0 == 1);
  } else {
    return BS_reserved_size() + BS_table_size() * BS_table_count();
  }
}
