#ifndef META_H
#define META_H

#include <stdint.h>

/// Read sector size
///
/// output:
///      int32_t: sector size
///
int32_t BS_sector_size();

/// Read cluster size (in bytes)
///
/// output:
///      int32_t: cluster size (in bytes)
///
int32_t BS_cluster_size();

/// Read reserved size (in bytes)
///
/// output:
///      int32_t: reserved size (in bytes)
///
int32_t BS_reserved_size();

/// Read table size (in bytes)
///
/// output:
///      int32_t: table size (in bytes)
///
int32_t BS_table_size();

/// Read entry size (in bytes)
///
/// output:
///      int32_t: entry size (in bytes)
///
int32_t BS_entry_size();

/// Read number of fat table
///
/// output:
///      int32_t: number of fat table
///
int32_t BS_table_count();

/// Read root directory entry count
///
/// output:
///      int32_t: root directory entry count
///
int32_t BS_maxfile_count();

/// Read number of sector
///
/// output:
///      int32_t: number of sector
///
int32_t BS_sector_count();

/// Check if this is in fat12 format
///
/// output:
///     1 if is fat12
///     0 otherwise
///
int32_t BS_is_fat12();

/// Check if this is in fat16 format
///
/// output:
///     1 if is fat16
///     0 otherwise
///
int32_t BS_is_fat16();

/// Check if this is in fat32 format
///
/// output:
///     1 if is fat32
///     0 otherwise
///
int32_t BS_is_fat32();

/// Read position of root directory
///
/// output:
///      int32_t: position of root directory
///
int32_t BS_root_offset();

/// Read position of fat table
///
/// output:
///      int32_t: position of fat table
///
int32_t BS_table_offset();

/// Read position of data region
///
/// output:
///      int32_t: position of data region
///
int32_t BS_data_offset();

#endif
