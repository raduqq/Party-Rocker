// Copyright 2020 Radu-Stefan Minea 314CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./utils.h"

void opening_file_check(FILE *f, char *file_name) {
  if (f == NULL) {
    fprintf(stderr, "Error opening %s\n", file_name);
    exit(ERROR_STATUS);
  }
}

void getMelodyName(char *p, char *melody_name, char **buffer) {
  p = strtok_r(*buffer, "\n", buffer);
  snprintf(melody_name, MAX_LINE, "%s", p);
}

void extractMelodyMetadata(struct metadata *melody, char *melody_name) {
  char file_path[MAX_LINE];
  memset(file_path, '\0', sizeof(file_path));

  snprintf(file_path, sizeof(file_path), "%s/%s", SONG_DIR_NAME, melody_name);

  FILE *f = fopen(file_path, "rb");
  opening_file_check(f, melody_name);
  fseek(f, -METADATA_SIZE, SEEK_END);

  fread(melody->tag, TAG_LEN, 1, f);
  fread(melody->title, TITLE_LEN, 1, f);
  fread(melody->artist, ARTIST_LEN, 1, f);
  fread(melody->album, ALBUM_LEN, 1, f);
  fread(melody->year, YEAR_LEN, 1, f);

  fclose(f);
}
