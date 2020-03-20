#include <stdio.h>
#include <string.h>

#include "./utils.h"

void getMelodyName(char *p, char *melody_name) {
    p = strtok(NULL, "\n");
    strcpy(melody_name, p);   
}

// Extract metadata function
/*void extractMelodyMetadata(struct metadata *melody, char *melody_name) {
    file *f = fopen()
}*/