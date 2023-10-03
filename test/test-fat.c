#include "../include/fat.h"
#include "c-assert.h"
#include <stdlib.h>

int main() {
  FAT_open_file("./sample/floppy.img");

  ASSERT_LIST_EQ("Check image type", "FAT12", FAT_type(), 5)

  struct entry *entry = FAT_list_root();
  ASSERT_LIST_EQ("Check first entry name", "Sample1.txt", entry->filename, 11)
  ASSERT("Check first entry cluster", 3 == entry->cluster)
  ASSERT("Check first entry next cluster",
         0xff0 <= FAT_next_cluster(entry->cluster));
  char *buf = malloc(entry->filesize);
  FAT_read_file(entry->cluster, entry->filesize, buf);
  ASSERT_LIST_EQ("Check first entry content",
                 "Day la file mau cho chuong trinh doc FAT - Sample1.", buf,
                 entry->filesize)
  // TODO: test other directory
}
