#include "../include/bs.h"
#include "../include/fat.h"
#include "../include/hal.h"
#include <assert.h>
#include <stdio.h>

int main() {
  FAT_open_file("./sample/floppy.img");

  // union entry *root = FAT_root_dir();

  // union entry *entry = FAT_get_entry(root, 6);

  // if (entry != NULL) {
  //   uint8_t *ret = FAT_get_content(entry->nentry.low_part_cluster);
  //   printf("%s\n\n\n", ret);
  // }

  // printf("%s\n", entry->nentry->filename);
  // printf("%d\n", entry->nentry->file_size);
  // printf("%d\n", entry->nentry->cluster_idx);
  // printf("%s\n", FAT_get_content(entry->cluster_idx));
}
