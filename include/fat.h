#ifndef FAT_H
#define FAT_H 1

#include <stdint.h>

struct entry {
  char filename[256];
  int8_t is_file;
  int8_t is_directory;
  int32_t filesize;
  int32_t cluster;
  struct entry *next;
};
struct cluster {
  int32_t cluster;
  struct cluster *next;
};

struct entry *FAT_list_root();
struct entry *FAT_list_dir(int32_t cluster);

struct cluster *FAT_cluster_chain(int32_t begin);

int32_t FAT_next_cluster(int32_t idx);

int32_t FAT_read_cluster(int32_t idx, int32_t buf_size, void *buf);
int32_t FAT_read_file(int32_t cluster, int32_t filesize, void *buf);

#endif
