#include "../include/bs.h"
#include "../include/hal.h"
#include <assert.h>
#include <string.h>

int main() {
  char *filename = "./sample/floppy2.img";
  HAL_open_file(filename);

  assert(512 == BS_sector_size());
  assert(512 == BS_cluster_size());
  assert(512 == BS_reserved_size());
  assert(2 == BS_table_count());
  assert(224 == BS_maxfile_count());
  assert(2880 == BS_sector_count());
  assert(9 * 512 == BS_table_size());

  for (int i = 0; i < BS_maxfile_count(); i++) {
    uint8_t entry[BS_entry_size()];
    HAL_read_bytes(BS_root_offset() + i * BS_entry_size(), BS_entry_size(),
                   entry);

    if (entry[0] != 0) {
      // printf("%d\n", root_offset + i * HAL_entry_size());
      uint8_t file_name[9];
      memcpy(file_name, entry, 8);
      file_name[8] = 0;
      for (int i = 8; i >= 0; i--) {
        if (file_name[i] == 0x20 || file_name[i] == 0x00) {
          file_name[i] = 0x00;
        }
      }
      uint8_t file_ext[4];
      memcpy(file_ext, entry + 8, 3);
      file_ext[3] = 0;
      for (int i = 3; i >= 0; i--) {
        if (file_ext[i] == 0x20 || file_ext[i] == 0x00) {
          file_ext[i] = 0x00;
        }
      }
      if (file_ext[0] == 0x00) {
        printf("%s\n", file_name);
      } else {
        printf("%s.%s\n", file_name, file_ext);
      }
    }
  }
}
