#ifndef META_H
#define META_H

#include <stdint.h>

//! Read sector size
//!
//! return:
//!      int32_t: sector size
//!
int32_t BS_sector_size();

//! Read cluster size (in bytes)
//!
//! return:
//!      int32_t: cluster size (in bytes)
//!
int32_t BS_cluster_size();

//! Read reserved size (in bytes)
//!
//! return:
//!      int32_t: reserved size (in bytes)
//!
int32_t BS_reserved_size();

//! Read table size (in bytes)
//!
//! return:
//!      int32_t: table size (in bytes)
//!
int32_t BS_table_size();

//! Read entry size (in bytes)
//!
//! return:
//!      int32_t: entry size (in bytes)
//!
int32_t BS_entry_size();

//! Read number of fat table
//!
//! return:
//!      int32_t: number of fat table
//!
int32_t BS_table_count();

//! Read root directory entry count
//!
//! return:
//!      int32_t: root directory entry count
//!
int32_t BS_root_entry_count();

//! Read number of sector
//!
//! return:
//!      int32_t: number of sector
//!
int32_t BS_sector_count();

//! Read position of root directory
//!
//! return:
//!      int32_t: position of root directory
//!
int32_t BS_root_offset();

//! Read position of fat table
//!
//! return:
//!      int32_t: position of fat table
//!
int32_t BS_table_offset();

//! Read position of data region
//!
//! return:
//!      int32_t: position of data region
//!
int32_t BS_data_offset();

//! Check if this is in fat12 format
//!
//! return:
//!     (int32_t)1 if is fat12
//!     (int32_t)0 otherwise
//!
int32_t BS_is_fat12();

//! Check if this is in fat16 format
//!
//! return:
//!     (int32_t)1 if is fat16
//!     (int32_t)0 otherwise
//!
int32_t BS_is_fat16();

//! Check if this is in fat32 format
//!
//! return:
//!     (int32_t)1 if is fat32
//!     (int32_t)0 otherwise
//!
int32_t BS_is_fat32();

//! Read begin cluster of fat32 root directory
//!
//! return:
//!      int32_t: begin cluster of fat 32 root directory
//!
int32_t BS_root_cluster();

//! Set cache on or off (for debugging and testing)
//! Default: 1(on)
//!
//! param:
//!      int32_t cache: boolean val for the setting
//!
void BS_set_cache(int32_t cache);

#endif
