// Copyright 2020 Radu-Stefan Minea 314CA

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./LinkedList.h"
#include "./utils.h"

int main(int argc, char **argv) {
    // Input interpretation:
    if (argc < 3) {
        fprintf(stderr, "Please enter the name of both .in and .out files\n");
        exit(ERROR_STATUS);
    }

    // Opening in/out files
    int in_len = strlen(argv[1]);
    int out_len = strlen(argv[2]);
    char *in_name = strndup(argv[1], in_len);
    char *out_name = strndup(argv[2], out_len);

    FILE *in = fopen(in_name, "r");
    FILE *out = fopen(out_name, "w");
    opening_file_check(in, in_name);
    opening_file_check(out, out_name);

    // Declaring variables
    struct metadata melody;
    char commands[MAX_COMMANDS][COMMAND_LEN] = {"ADD_FIRST", "ADD_LAST", "ADD_AFTER", "DEL_FIRST", "DEL_LAST", "DEL_CURR", "DEL_SONG", "MOVE_NEXT", "MOVE_PREV", "SHOW_FIRST", "SHOW_LAST", "SHOW_CURR", "SHOW_PLAYLIST"};
    int no_queries, command_no;
    char *buffer, melody_name[MAX_LINE], *p, query[COMMAND_LEN];
    fscanf(in, "%d\n", &no_queries);

    buffer = malloc(MAX_LINE * sizeof(char));
    char *cp_buffer = buffer;

    struct LinkedList *playlist;

    playlist = malloc(sizeof(struct LinkedList));
    init_list(playlist);

    // Queries
    for (int i = 0; i < no_queries; i++) {
        command_no = -1;

        buffer = cp_buffer;
        memset(buffer, '\0', MAX_LINE * sizeof(char));
        
        fgets(buffer, MAX_LINE * sizeof(char), in);
        p = strtok_r(buffer, " \n", &buffer);

        for (int j = 0; j < MAX_COMMANDS; j++) {
            if(strcmp(p, commands[j]) == 0) {
                snprintf(query, sizeof(query), "%s", p);
                command_no = j;
                break;
            }
        }
        
        memset(melody_name, '\0', sizeof(melody_name));
        memset(&melody, '\0', sizeof(melody));
        
        switch (command_no) {
        case 0:
            getMelodyName(p, melody_name, &buffer);
            extractMelodyMetadata(&melody, melody_name);
            add_first(playlist, &melody, out);
            break;
        case 1:
            getMelodyName(p, melody_name, &buffer);
            extractMelodyMetadata(&melody, melody_name);
            // add_last
            break;
        case 2:
            getMelodyName(p, melody_name, &buffer);
            extractMelodyMetadata(&melody, melody_name);
            // add after
            break;
        case 3:
            del_first(playlist, out);
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            getMelodyName(p, melody_name, &buffer);
            extractMelodyMetadata(&melody, melody_name);
            del_song(playlist, melody.title, out);
            break;
        case 7:
            move_next(playlist, out);
            break;
        case 8:
            move_prev(playlist, out);
            break;
        case 9:
            show_first(playlist, out);
            break;
        case 10:
            show_last(playlist, out);
            break;
        case 11:
            show_curr(playlist, out);
            break;
        case 12:
            show_playlist(playlist, out);
            break;
        default:
            fprintf(stderr, "Wrong command! Please try again.\n");
            i--;
            break;
        }
    }

    fclose(in);
    fclose(out);

    free(in_name);
    free(out_name);

    buffer = cp_buffer;
    free(buffer);

    free_list(&playlist);

    return 0;
}