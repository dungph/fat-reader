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

//! Open an image file
//!
//! param:
//!     const char *filepath: path to the image
//! return:
//!     (int32_t)0 if success
//!     otherwise failed
//!
int32_t FAT_open_file(const char *filepath);

//! Close image file
//!
//! return:
//!     (int32_t)0 if success
//!     otherwise failed
//!
int32_t FAT_close_file(void);

//! Get fat fype in string
//!
//! return:
//!     NULL terminated string contains fat format
//!     NULL if failed
//!
const char *FAT_type(void);

//! Read all directory entry in the root
//! Equivalent FAT_list_fir(0)
//!
//! return:
//!     (linked list)struct entry* if success
//!     NULL if failed or none
//!
struct entry *FAT_list_root();

//! Read all directory entry in directory table
//!
//! param:
//!    int32_t cluster: begining cluster of the directory table
//!    root directory has cluster index of 0
//! return:
//!     (linked list)struct entry* if success
//!     NULL if failed or none
//!
struct entry *FAT_list_dir(int32_t cluster);

//! Read all cluster in single cluster chain
//!
//! param:
//!    int32_ti begin: begining cluster of the cluster chain
//! return:
//!     struct cluster* if success
//!     NULL if failed or none
//!
struct cluster *FAT_cluster_chain(int32_t cluster);

//! Read next cluster from this cluster in cluster chain
//!
//! param:
//!    int32_t cluster: input cluster
//! return:
//!    int32_t: next cluster from input cluster
//!
int32_t FAT_next_cluster(int32_t cluster);

//! Read single cluster from this cluster
//!
//! param:
//!    int32_t cluster: input cluster
//!    int32_t buf_size: actual size of the buf
//!    void *buf: pointer to the buffer
//! return:
//!    int32_t: number of read bytes
//!
int32_t FAT_read_cluster(int32_t cluster, int32_t buf_size, void *buf);

//! Read file content from begining cluster by following the cluster chain
//!
//! param:
//!    int32_t cluster: input cluster
//!    int32_t buf_size: actual size of the buffer
//!    void *buf: pointer to the buffer
//! return:
//!    int32_t: number of read bytes
//!
int32_t FAT_read_file(int32_t cluster, int32_t filesize, void *buf);

#endif
