#include "../include/bs.h"
#include "../include/fat.h"
#include "../include/hal.h"
#include <stdio.h>

int main() {
  HAL_open_file("./sample/floppy2.img");

  union entry *root = FAT_root_dir();

  union entry *entry = FAT_get_entry(root, 6);

  uint8_t *ret = FAT_get_content(entry->nentry.low_part_cluster);
  printf("%s\n\n\n", ret);
}
