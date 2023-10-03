#include "../include/fat.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *separator = "----------------------------------------------";

int main(int argc, char *argv[]) {
  // file open in argv[1]
  printf("opening %s\n", argv[1]);
  if (FAT_open_file(argv[1])) {
    printf("open failed!");
    return 1;
  }
  printf("Image type: %s\n", FAT_type());

  // init with all directories and files entry in root
  struct entry *directory = FAT_list_root();

  printf("%s\n", separator);
  int select;
  do {
    // print all files and directories in current directory
    printf("%s\n", separator);
    printf("List files and directories\n");
    printf("%s\n", separator);
    printf("%3s|%20s|%8s|%8s|%8s\n", "ID", "NAME", "SIZE", "TYPE", "CLUSTER");

    struct entry *entry = directory;
    int id = 1;
    while (entry != 0) {
      // printf("%3d|%20.20s|%8d|%8x|%8x\n", id, entry->filename,
      // entry->filesize,
      //        (entry->is_file), entry->cluster);
      printf("%3d|%20.20s|%8d|%8s|%8x\n", id, entry->filename, entry->filesize,
             (entry->is_file) ? "file" : "dir", entry->cluster);
      entry = entry->next;
      id += 1;
    }
    printf("%s\n", separator);

    // wait for selection
    printf("Select file or directory ID (0 for terminate): ");
    if (scanf("%d", &select)) {
    } else {
      return -1;
    }

    // clear screen
    printf("\x1b[2J\x1b[H");

    // if valid id
    if (0 < select && select < id) {

      entry = directory;
      for (int i = 1; i < select; i++) {
        entry = entry->next;
      }

      if (entry->is_directory) {
        // if select directory, read new directory
        // table and change current directory
        while (directory != NULL) {
          struct entry *next = directory->next;
          free(directory);
          directory = next;
        }
        directory = FAT_list_dir(entry->cluster);
      } else if (entry->is_file) {
        // if is file, read the content
        printf("%s\n", separator);
        char *buf = malloc(entry->filesize + 1);
        buf[entry->filesize] = 0;
        FAT_read_file(entry->cluster, entry->filesize, (uint8_t *)buf);
        // check if file is binary. binary usually
        // has invalid text char such as \0
        int32_t is_binary = 0;
        for (int i = 0; i < entry->filesize; i++) {
          if (buf[i] == 0) {
            is_binary = 1;
          }
        }
        int prev = 0;
        if (is_binary) {
          for (int i = 0; i < entry->filesize; i++) {
            printf("%02X ", buf[i] & 0xff);
            if (i % 16 == 0 || i + 1 == entry->filesize) {
              for (int j = prev; j < i; j++) {
                printf("%c", (31 < buf[j] && buf[j] < 127) ? buf[j] : '.');
              }
              prev = i;
              printf("\n");
            }
          }
        } else {
          printf("%s\n", buf);
        }
        printf("%s\n", separator);
      }
    }
  } while (select != 0);

  return 0;
}
