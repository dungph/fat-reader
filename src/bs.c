#include "../include/bs.h"
#include "../include/hal.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// To read boot sector region, we can read whole 512 bytes and
/// cast them to a struct. that method only work in little endian
/// machine. Here I will read directly from the hal to get each
/// BS value (can easily generate automatically with macro and
/// cached with local static variable)
///

#define BS_FIELD(func_name, init)                                              \
  int32_t BS_##func_name() {                                                   \
    static uint32_t val = 0;                                                   \
    if (val == 0) {                                                            \
      val = init;                                                              \
    }                                                                          \
    return val;                                                                \
  }

// offset ref: https://wiki.osdev.org/FAT
BS_FIELD(sector_size, HAL_read_uint16_le(11))
BS_FIELD(cluster_size, HAL_read_u8(13) * BS_sector_size())
BS_FIELD(reserved_size, HAL_read_uint16_le(14) * BS_sector_size())
BS_FIELD(table_size, BS_is_fat32() ? HAL_read_uint16_le(22) * BS_sector_size()
                                   : HAL_read_uint16_le(22) * BS_sector_size())
BS_FIELD(table_count, HAL_read_u8(16))
BS_FIELD(maxfile_count, BS_is_fat32() ? 0 : HAL_read_uint16_le(17))
BS_FIELD(sector_count, HAL_read_uint16_le(19) ? HAL_read_uint16_le(19)
                                              : HAL_read_uint32_le(32))
BS_FIELD(entry_size, 32)
BS_FIELD(is_fat12, 1)
BS_FIELD(is_fat16, 0)
BS_FIELD(is_fat32, 0)
BS_FIELD(table_offset, BS_reserved_size())
BS_FIELD(data_offset,
         BS_is_fat32() ? BS_reserved_size() + BS_table_size() * BS_table_count()
                       : BS_root_offset() + BS_maxfile_count() * 32)
BS_FIELD(root_offset, BS_is_fat32() ? 0
                                    : BS_reserved_size() +
                                          BS_table_size() * BS_table_count())
