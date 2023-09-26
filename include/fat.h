
#include <stdint.h>

struct normal_entry {
  int8_t filename[11];
  int8_t attributes;
  int8_t unused[8];
  uint16_t high_part_cluster;
  int8_t unused2[4];
  uint16_t low_part_cluster;
  int32_t file_size;
} __attribute__((packed));

union entry {
  struct normal_entry nentry;
  struct normal_entry nentry1;
};

union entry *FAT_root_dir();

uint8_t *FAT_get_content(int32_t start_cluster);

union entry *FAT_get_entry(union entry *directory, int32_t entry_index);
