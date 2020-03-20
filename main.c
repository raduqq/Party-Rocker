#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./LinkedList.h"
#include "./utils.h"

#define MAX_LINE 255
#define MAX_COMMANDS 13
#define COMMAND_LEN 20
#define ERROR_STATUS -1

void opening_file_check(FILE *f, char *file_name) {
    if(f == NULL) {
        fprintf(stderr, "Error opening %s\n", file_name);
        exit(ERROR_STATUS);
    }
}

int main(int argc, char **argv) {
    // 1) Input interpretation:
    // 1.1) Command-line parameters
    if (argc < 3) {
        fprintf(stderr, "Please enter the name of both .in and .out files\n");
        exit(ERROR_STATUS);
    }

    // Supposing both files have the correct extension
    char *in_name = strdup(argv[1]);
    char *out_name = strdup(argv[2]);

    FILE *in = fopen(in_name, "r");
    FILE *out = fopen(out_name, "w");
    opening_file_check(in, in_name);
    opening_file_check(out, out_name);

    char commands[MAX_COMMANDS][COMMAND_LEN] = {"ADD_FIRST", "ADD_LAST", "ADD_AFTER", "DEL_FIRST", "DEL_LAST", "DEL_CURR", "DEL_SONG", "MOVE_NEXT", "MOVE_PREV", "SHOW_FIRST", "SHOW_LAST", "SHOW_CURR", "SHOW_PLAYLIST"};
    int no_queries, command_no;
    int melody_len = ARTIST_LEN + strlen(" - ") + TITLE_LEN + strlen(".mp3");
    char buffer[MAX_LINE], melody_name[melody_len], *p, query[COMMAND_LEN];
    fscanf(in, "%d\n", &no_queries);

    // 1.2) Queries
    for (int i = 0; i < no_queries; i++) {
        command_no = -1;
        fgets(buffer, sizeof(buffer), in);
        p = strtok(buffer, " \n");        
        for (int j = 0; j < MAX_COMMANDS; j++) {
            if(strcmp(p, commands[j]) == 0) {
                strcpy(query, p);
                command_no = j;
                break;
            }
        }
            switch (command_no) {
            case 0:
                getMelodyName(p, melody_name);
                // Extract file metadata on all
                break;
            case 1:
                getMelodyName(p, melody_name);
                break;
            case 2:
                getMelodyName(p, melody_name);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                getMelodyName(p, melody_name);
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

    return 0;
}
