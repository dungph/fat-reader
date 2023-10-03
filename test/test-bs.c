#include "../include/bs.h"
#include "../include/hal.h"
#include "c-assert.h"

#include <string.h>

int main() {
  BS_set_cache(0);

  HAL_open_file("./sample/floppy.img");
  ASSERT("check floppy.img sector size", 512 == BS_sector_size());
  ASSERT("check floppy.img cluster size", 512 == BS_cluster_size());
  ASSERT("check floppy.img reserved size", 512 == BS_reserved_size());
  ASSERT("check floppy.img number of table", 2 == BS_table_count());
  ASSERT("check floppy.img max root entry", 224 == BS_root_entry_count());
  ASSERT("check floppy.img number of sector", 2880 == BS_sector_count());
  ASSERT("check floppy.img size of table", 9 * 512 == BS_table_size());
  HAL_close_file();

  HAL_open_file("./sample/floppy2.img");
  ASSERT("check floppy2.img sector size", 512 == BS_sector_size());
  ASSERT("check floppy2.img cluster size", 1024 == BS_cluster_size());
  ASSERT("check floppy2.img reserved size", 512 == BS_reserved_size());
  ASSERT("check floppy2.img number of table", 2 == BS_table_count());
  ASSERT("check floppy2.img max root entry", 224 == BS_root_entry_count());
  ASSERT("check floppy2.img number of sector", 2880 == BS_sector_count());
  printf("%d", BS_table_size());
  ASSERT("check floppy2.img size of table", 5 * 512 == BS_table_size());
  HAL_close_file();
}
