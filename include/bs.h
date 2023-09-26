
#ifndef META_H
#define META_H

#include <stdint.h>

int32_t BS_sector_size();
int32_t BS_cluster_size();
int32_t BS_reserved_size();
int32_t BS_table_size();
int32_t BS_entry_size();
int32_t BS_table_count();
int32_t BS_maxfile_count();
int32_t BS_sector_count();
int32_t BS_is_fat12();
int32_t BS_is_fat16();
int32_t BS_is_fat32();

int32_t BS_root_offset();
int32_t BS_table_offset();
int32_t BS_data_offset();

#endif
