#include "../include/bs.h"
#include "../include/fat.h"
#include "../include/hal.h"
#include <stdio.h>

int main() {
  HAL_open_file("./sample/floppy2.img");

  union entry *root = FAT_root_dir();
  for (int i = 0; i < BS_maxfile_count(); i++) {
    union entry *entry = FAT_get_entry(root, i);
    if (entry != NULL) {
      printf("%s", entry->nentry.filename);
      printf("\n");
    }
  }

  // printf("%s\n", entry->nentry->filename);
  // printf("%d\n", entry->nentry->file_size);
  // printf("%d\n", entry->nentry->cluster_idx);
  // printf("%s\n", FAT_get_content(entry->cluster_idx));
}
