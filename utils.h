#ifndef __UTILS_H__
#define __UTILS_H__

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

void getMelodyName(char *p, char *melody_name);

#endif