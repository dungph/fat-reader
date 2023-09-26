#include "../include/fat.h"
#include "../include/bs.h"
#include "../include/hal.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static union entry *root_dir = NULL;

static void init() {
  if (root_dir == NULL) {
    root_dir = malloc(BS_maxfile_count() * BS_entry_size());
    HAL_read_bytes(BS_root_offset(), BS_maxfile_count() * BS_entry_size(),
                   (void *)root_dir);
  }
}

union entry *FAT_root_dir() {
  init();
  return root_dir;
}

union entry *FAT_dir_at(int32_t cluster) {
  uint8_t *buf = FAT_get_content(cluster);
  return (union entry *)buf;
}

uint16_t FAT_get_next_cluster(int32_t cluster) {
  init();
  cluster -= 2;
  assert(cluster >= 0);

  int32_t offset = cluster / 2 * 3;
  uint8_t pack[3];

  HAL_read_bytes(BS_table_offset() + offset, 3, pack);

  uint16_t ret;
  if (cluster % 2 == 0) {
    ret = ((pack[1] & 0x0f) << 8) | pack[0];
  } else {
    ret = (pack[2] << 4) | (pack[1] & 0xf0);
  }
  return ret;
}

uint8_t *FAT_get_content(int32_t start_cluster) {
  init();
  uint8_t *ret = malloc(sizeof(int8_t) * BS_cluster_size());
  uint8_t *ret_ptr = ret;
  int32_t next_cluster = start_cluster;
  int i = 0;
  do {
    i += 1;
    ret = realloc(ret, i * sizeof(int8_t) * BS_cluster_size());

    HAL_read_bytes(BS_data_offset() + next_cluster * BS_cluster_size() - 2,
                   BS_cluster_size(), ret_ptr);

    ret_ptr += BS_cluster_size();
    next_cluster = FAT_get_next_cluster(next_cluster);
//    printf("cluster %d\n", next_cluster);
  } while (next_cluster != 0xfff && next_cluster != 0);
  return ret;
}

union entry *FAT_get_entry(union entry *directory, int32_t entry_index) {
  init();
  union entry *cur = directory + entry_index;
  if (cur->nentry.filename[0] == 0) {
    return NULL;
  }
  union entry *ret = malloc(sizeof(union entry));
  memcpy(ret, directory + entry_index, sizeof(union entry));
  return ret;
}
