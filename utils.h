// Copyright 2020 Radu-Stefan Minea 314CA

#ifndef UTILS_H__
#define UTILS_H__

#include <stdio.h>

#define MAX_LINE 255
#define MAX_COMMANDS 13
#define COMMAND_LEN 20
#define ERROR_STATUS -1
#define METADATA_SIZE 97
#define SONG_DIR_NAME "songs"

#define TAG_LEN 3
#define TITLE_LEN 30
#define ARTIST_LEN 30
#define ALBUM_LEN 30
#define YEAR_LEN 4

struct metadata {
  char tag[TAG_LEN + 1];
  char title[TITLE_LEN + 1];
  char artist[ARTIST_LEN + 1];
  char album[ALBUM_LEN + 1];
  char year[YEAR_LEN + 1];
};

void opening_file_check(FILE *f, char *file_name);
void getMelodyName(char *p, char *melody_name, char **buffer);
void extractMelodyMetadata(struct metadata *melody, char *melody_name);

#endif  // UTILS_H_
