#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>

int main() {

  FILE *image = fopen("./sample/floppy.img", "r");

  assert(512 == read_byte_per_sector(image));
  assert(1 == read_sector_per_cluster(image));
  assert(1 == read_sector_per_reserved(image));
  assert(2 == read_nof_fat(image));
  assert(224 == read_max_file_in_root(image));
  assert(2880 == read_nof_sector(image));
  assert(9 == read_sector_per_fat(image));

  return 0;
}
