#include "../include/bs.h"
#include "../include/fat.h"
#include "../include/hal.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  HAL_open_file("./sample/floppy2.img");
  struct entry *entry = FAT_list_root();

  while (entry != NULL) {
    printf("%14s - %8d - %8x - %8x\n", (entry)->filename, (entry)->filesize,
           (entry)->attributes, entry->cluster);
    // struct chain *chain = FAT_cluster_chain(entry->cluster);
    // while (chain != NULL) {
    //   printf("%x->", chain->cluster);
    //   chain = chain->next;
    // }
    // printf("x\n");
    entry = entry->next;
  }

  printf("[start content]\n");
  printf("%x\n", FAT_next_cluster(0x26b));
  // uint8_t buf[512];
  // FAT_read_cluster(0x26b, buf);
  // printf("%c", buf[0]);
  // for (int i = 0; i < 512; i++) {
  //   printf("%c", buf[i]);
  // }
  //  FAT_read_cluster(0x26a, buf);
  //  for (int i = 0; i < 512; i++) {
  //    printf("%c", buf[i]);
  //  }
  // struct clus_chain *chain = FAT_revered_cluster_chain(0x5);
  // while (chain != NULL) {
  //  char buf[512];
  //  FAT_read_cluster(chain->cluster, buf);
  //  for (int i = 0; i < 512; i++) {
  //    printf("%c", buf[i]);
  //  }
  //  chain = chain->next;
  //}
  //    char buf[1000];
  //    FAT_read_cluster(0xff0, buf);
  //    for (int i = 0; i < 100; i++) {
  //      printf("%c", buf[i]);
  //    }
  //     printf("%s\n", buf);
  //       entry = FAT_list(0xa2c);

  // while (entry != NULL) {
  //   printf("%14s - %8x - %8d - %8x\n", (entry)->filename, (entry)->cluster,
  //          (entry)->filesize, (entry)->attributes);
  //   entry = entry->next;
  // }
  //  do {
  //    printf(
  //        //"%s - %x - %d - %x\n",
  //        " %x - %d - %x\n",
  //        //(entry)->filename,
  //        (entry)->cluster, (entry)->filesize, (entry)->attributes);
  //    entry = entry->next;
  //  } while (entry != NULL);
  //     union entry *root = FAT_root_dir();

  // union entry *entry = FAT_get_entry(root, 5);

  // int clus = entry->nentry.low_part_cluster;
  // printf("%s\n", entry->nentry.filename);
  // char *con = FAT_get_content(clus);
  // printf("%s", con);
  //  uint8_t *ret = malloc(BS_cluster_size());
  //  while (clus > 0 && clus < 0xfff) {
  //    FAT_read_cluster(clus, ret);
  //    printf("%s", ret);
  //    clus = FAT_next_cluster(clus);
  //  }
}

// int main() {
//   HAL_open_file("./sample/floppy.img");
//
//   union entry *root = FAT_root_dir();
//
//   for (int i = 0; i < BS_maxfile_count(); i++) {
//     int clus = root[i].nentry.low_part_cluster;
//     root[i].nentry.filename;
//   }
//   union entry *entry = FAT_get_entry(root, 2);
//
//   int clus = entry->nentry.low_part_cluster;
//   printf("%s\n", entry->nentry.filename);
//
//   uint8_t *ret = malloc(BS_cluster_size());
//   while (clus > 0 && clus < 0xfff) {
//     FAT_read_cluster(clus, ret);
//     printf("%s", ret);
//     clus = FAT_next_cluster(clus);
//   }
// }
