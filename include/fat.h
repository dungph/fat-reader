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

/// Read all directory entry in the root
/// Equivalent FAT_list_fir(0)
///
/// output:
///     (linked list)struct entry* if success
///     NULL* if failed or none
///
struct entry *FAT_list_root();

/// Read all directory entry in directory table
///
/// input:
///    int32_t cluster: begining cluster of the directory table
///    root directory has cluster index of 0
/// output:
///     (linked list)struct entry* if success
///     NULL* if failed or none
///
struct entry *FAT_list_dir(int32_t cluster);

/// Read all cluster in single cluster chain
///
/// input:
///    int32_ti begin: begining cluster of the cluster chain
/// output:
///     struct entry* if success
///     NULL* if failed or none
///
struct cluster *FAT_cluster_chain(int32_t cluster);

/// Read next cluster from this cluster in cluster chain
///
/// input:
///    int32_t cluster: input cluster
/// output:
///    int32_t: next cluster from input cluster
///
int32_t FAT_next_cluster(int32_t cluster);

/// Read single cluster from this cluster
///
/// input:
///    int32_t cluster: input cluster
///    int32_t buf_size: actual size of the buf
///    void *buf: pointer to the buffer
/// output:
///    int32_t: number of read file
///
int32_t FAT_read_cluster(int32_t cluster, int32_t buf_size, void *buf);

/// Read file content from begining cluster by following the cluster chain
///
/// input:
///    int32_t cluster: input cluster
///    int32_t buf_size: actual size of the buffer
///    void *buf: pointer to the buffer
/// output:
///    int32_t: number of read file
///
int32_t FAT_read_file(int32_t cluster, int32_t filesize, void *buf);

#endif
