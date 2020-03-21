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

    buffer = calloc(MAX_LINE, sizeof(char));
    char *cp_buffer = buffer;

    struct Node *currNode;
    struct Node *cursor = NULL;
    struct LinkedList *playlist;

    playlist = malloc(sizeof(struct LinkedList));
    init_list(playlist);

    // Queries
    for (int i = 0; i < no_queries; i++) {
        command_no = -1;
        fgets(buffer, MAX_LINE, in);
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
            //add_first
            break;
        case 1:
            getMelodyName(p, melody_name, &buffer);
            extractMelodyMetadata(&melody, melody_name);
            //add_last
            break;
        case 2:
            getMelodyName(p, melody_name, &buffer);
            extractMelodyMetadata(&melody, melody_name);
            // add after
            break;
        case 3:
            // del song:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            getMelodyName(p, melody_name, &buffer);
            extractMelodyMetadata(&melody, melody_name);
            //del song
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
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