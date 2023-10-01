#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include <stdio.h>

//! Set sector size for `FAT_read_sector` and `FAT_read_multi_sector`
//! sector size must be in greater than 0.
//!
//! params:
//!     uint32_t sector_size: new sector size for hal
//!
void HAL_set_sector_size(uint32_t sector_size);

//! Read multiple bytes from the HAL
//!
//! params:
//!     uint32_t offset: start position from the begining of file or disk
//!     uint32_t num: number of bytes to read
//!     void *buf: buffer for the read data
//! returning:
//!     number of read bytes
//!
int32_t HAL_read_bytes(uint32_t offset, uint32_t num, void *buf);

//! Read a sector from the HAL. Sector size is 512 bytes by default if
//! not be set by `HAL_set_sector_size`. Use `HAL_read_bytes` if not care about
//! sector size.
//!
//! param:
//!     uint32_t idx: index of the sector
//!     void *buf: buffer for the read data
//! returning:
//!     number of read bytes
//!
int32_t HAL_read_sector(uint32_t idx, uint8_t *buf);

//! Read multiple sector from the HAL. Sector size is 512 bytes by default ! if
//! not be set by `HAL_set_sector_size`. Use `HAL_read_bytes` if not care about
//! sector size.
//!
//! param:
//!     uint32_t idx: index of the sector
//!     uint32_t num: number of sector to read
//!     void *buf: buffer for the read data
//! returning:
//!     number of read bytes
//!
int32_t HAL_read_multi_sector(uint32_t idx, uint32_t num, uint8_t *buf);

//! Read a uint8_t from the HAL
//!
//! param:
//!     uint32_t offset: start position from the begining of file or disk
//! returning:
//!     the uint8_t value
//!
uint8_t HAL_read_u8(int offset);

//! Read a uint16_t in little endian from the HAL
//!
//! param:
//!     uint32_t offset: start position from the begining of file or disk
//! returning:
//!     the uint16_t value
//!
uint16_t HAL_read_uint16_le(int offset);

//! Read a uint24_t in little endian from the HAL (stored in uint32_t)
//!
//! param:
//!     uint32_t offset: start position from the begining of file or disk
//! returning:
//!     the uint24_t value
//!
uint32_t HAL_read_uint24_le(int offset);

//! Read a uint32_t in little endian from the HAL
//!
//! param:
//!     uint32_t offset: start position from the begining of file or disk
//! returning:
//!     the uint32_t value
//!
uint32_t HAL_read_uint32_le(int offset);

//! Set up hal using image file
//!
//! param:
//!     const char *path: path for the input image file
//! returning:
//!     (int32_t)0 if success
//!     other if failed
//!
int32_t HAL_open_file(const char *path);

//! Close image file
//!
//! returning:
//!     (int32_t)0 if success
//!     other if failed
//!
int32_t HAL_close_file(void);

#endif
