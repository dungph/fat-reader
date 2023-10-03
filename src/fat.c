#include "../include/fat.h"
#include "../include/bs.h"
#include "../include/hal.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a < b) ? (a) : (b))

static struct entry *__list_directory(int32_t d_offset, int32_t n) {
  struct entry *ret = NULL;
  struct entry *cur = NULL;

  char *lfn = NULL;

  for (int i = 0; i < n; i++) {
    int32_t offset = d_offset + i * 32;
    uint8_t first_char = HAL_read_u8(offset);
    if (first_char == 0) {
      break;
    } else if (first_char == 0xe5) {
    } else if (HAL_read_u8(offset + 11) == 0xf) {
      // LFN
      uint8_t is_last = first_char & 0x40;
      uint8_t lfn_idx = first_char & 0x1F;
      if (is_last) {
        lfn = calloc(1, 13 * lfn_idx + 1);
      }

      char *lfn_ptr = lfn + 13 * (lfn_idx - 1);

      for (int j = 0; j < 5; j++) {
        uint16_t uchar = HAL_read_uint16_le(offset + 1 + j * 2);
        if (uchar < 127) {
          *lfn_ptr = uchar;
          lfn_ptr += 1;
        }
      }
      for (int j = 0; j < 6; j++) {
        uint16_t uchar = HAL_read_uint16_le(offset + 14 + j * 2);
        if (uchar < 127) {
          *lfn_ptr = uchar;
          lfn_ptr += 1;
        }
      }
      for (int j = 0; j < 2; j++) {
        uint16_t uchar = HAL_read_uint16_le(offset + 28 + j * 2);
        if (uchar < 127) {
          *lfn_ptr = uchar;
          lfn_ptr += 1;
        }
      }

    } else {
      struct entry *en = malloc(sizeof(struct entry));
      en->next = NULL;
      en->is_directory = HAL_read_u8(offset + 11) & 0x10;
      en->is_file = !en->is_directory;
      // en->is_file = HAL_read_u8(offset + 11);
      //  en->is_file = HAL_read_u8(offset + 11) & 0x20;
      en->filesize = HAL_read_uint32_le(offset + 28);
      en->cluster = HAL_read_uint16_le(offset + 20) << 16 |
                    HAL_read_uint16_le(offset + 26);
      if (lfn) {
        strcpy(en->filename, lfn);

        // TODO: if free, read floppy.img will fail
        lfn = NULL;
        // free(lfn);
      } else {
        HAL_read_bytes(offset, 11, en->filename);
        en->filename[11] = 0;

        // clean trailing spaces
        for (int i = 11; i >= 0; i--) {
          if (en->filename[i] == 0 || en->filename[i] == ' ') {
            en->filename[i] = 0;
          }
        }
      }

      // add to list
      if (ret == NULL) {
        ret = en;
        cur = ret;
      } else {
        cur->next = en;
        cur = cur->next;
      }
    }
  }
  return ret;
}

struct entry *FAT_list_root() {
  if (BS_is_fat32()) {
    return FAT_list_dir(BS_root_cluster());
  } else {
    return (__list_directory(BS_root_offset(), BS_root_entry_count()));
  }
}

struct entry *FAT_list_dir(int32_t cluster) {
  if (cluster == 0) {
    return FAT_list_root();
  }
  struct entry *ret = NULL;
  struct entry *last = NULL;

  struct cluster *clus = FAT_cluster_chain(cluster);
  while (clus != NULL) {
    int32_t offset = BS_data_offset() + (cluster - 2) * BS_cluster_size();
    struct entry *list = __list_directory(offset, BS_cluster_size() / 32);
    if (list == NULL) {
      break;
    }
    if (ret == NULL) {
      ret = list;
      last = ret;
    } else {
      last = list;
    }
    while (last->next != NULL) {
      last = last->next;
    }
    clus = clus->next;
  }
  return ret;
}

int32_t FAT_next_cluster(int32_t cluster) {
  if (BS_is_fat12()) {
    int32_t offset = BS_table_offset() + cluster / 2 * 3;
    uint32_t pack = HAL_read_uint24_le(offset);

    if (cluster % 2 == 0) {
      return (pack & 0x00000fff);
    } else {
      return ((pack & 0x00fff000) >> 12);
    }
  } else if (BS_is_fat16()) {
    int32_t offset = BS_table_offset() + cluster * 2;
    return HAL_read_uint16_le(offset);
  } else if (BS_is_fat32()) {
    int32_t offset = BS_table_offset() + cluster * 4;
    return HAL_read_uint32_le(offset);
  } else {
    printf("File system not detected!");
    exit(-1);
  }
}
struct cluster *FAT_cluster_chain(int32_t begin) {
  struct cluster *ret = NULL;
  struct cluster *cur = NULL;
  int32_t clus = begin;
  while (0x2 <= clus && clus < 0xFF0) {
    struct cluster *next = malloc(sizeof(struct cluster));
    next->cluster = clus;
    next->next = NULL;
    if (ret == NULL) {
      ret = next;
      cur = next;
    } else {
      cur->next = next;
      cur = cur->next;
    }
    clus = FAT_next_cluster(clus);
  }
  return ret;
}

int32_t FAT_read_cluster(int32_t idx, int32_t buf_size, void *buf) {
  int offset = BS_data_offset() + (idx - 2) * BS_cluster_size();
  return HAL_read_bytes(offset, MIN(BS_cluster_size(), buf_size), buf);
}

int32_t FAT_read_file(int32_t cluster, int32_t filesize, void *buf) {
  uint8_t *u8buf = buf;
  struct cluster *clus = FAT_cluster_chain(cluster);
  int32_t read = 0;
  while (clus != NULL) {
    int len = FAT_read_cluster(clus->cluster, filesize - read, u8buf);
    read += len;
    u8buf += len;
    clus = clus->next;
  }
  return read;
}

int32_t FAT_open_file(const char *filepath) {
  ;
  return HAL_open_file(filepath);
}
int32_t FAT_close_file(void) {
  ;
  return HAL_close_file();
}
const char *FAT_type(void) {
  if (BS_is_fat12()) {
    return "FAT12";
  }
  if (BS_is_fat16()) {
    return "FAT16";
  }
  if (BS_is_fat32()) {
    return "FAT32";
  }
  return "Unknown";
}
