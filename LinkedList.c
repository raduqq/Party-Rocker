#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./utils.h"
#include "./LinkedList.h"

void init_list(struct LinkedList *list) {
    list->head = NULL;
    list->cursor = NULL;
    list->size = 0;
}

bool isInPlaylist(struct LinkedList *list, char* songName) {
    if (list == NULL) {
        return 0;
    }

    struct Node *it = list->head;

    while (it != NULL) {
        if(strcmp(songName, it->data->title) == 0) {
            return 1;
        }
        it = it->next;
    }

    return 0;
}

void add_first(struct LinkedList *list, struct metadata *value, FILE *out) {
    if(list == NULL) {
        return;
    }

    struct metadata *newData = malloc(sizeof(struct metadata));
    memcpy(newData, value, sizeof(struct metadata));

    // Delete already-existent song from playlist
    if(isInPlaylist(list, newData->title)) {
        del_song(list, newData->title, out);
    }

    // Adding the new song in playlist
    struct Node *newNode = malloc(sizeof(struct Node));

    newNode->prev = NULL;
    newNode->data = newData;

    if(list->size == 0) {
         // List previously empty => assign list->cursor to the now-added node
        list->cursor = newNode;
        newNode->next = NULL;
    } else {
         // If the list had at least one element
        newNode->next = list->head;
        list->head->prev = newNode; 
    }
    list->head = newNode;
    list->size++;
}

void del_song(struct LinkedList *list, char *songName, FILE *out) {
    if (list == NULL) {
        return;
    }

    // Getting the iterator to the song we want to delete
    struct Node *it = list->head;
    
    while(it != NULL && strcmp(songName, it->data->title)) {
        it = it->next;
    }

    // SONG NOT FOUND => ignore command
    if (it == NULL) {
        fprintf(out, "Error: no song found to delete\n");
        return;
    }

    // SONG FOUND
    struct Node *rmvdNode;

// DEL_FIRST

    // One element in list => the one we want => USABLE IN ALL
    if (list->size == 1) {
        rmvdNode = list->head;
        list->head = NULL;
        list->cursor = NULL;

        free(rmvdNode->data);
        free(rmvdNode);
        list->size --;
        return;
    }

    // At least 2 songs in playlist
    // Requested song = first in list
    if (it == list->head) {

        rmvdNode = list->head;
        list->head = list->head->next;
        list->head->prev = NULL;
        
        if (list->cursor == rmvdNode) {
            if (list->cursor->next != NULL) {
                move_next(list, out);
            } else if (list->cursor->prev != NULL) {
                move_prev(list, out);
            } else {
                list->cursor = NULL;
            }
        }

        free(rmvdNode->data);
        free(rmvdNode);
        list->size--;
        return;
    }

// DEL_LAST: with more than one element
    if(it->next == NULL) {
        rmvdNode = it;
        it->prev->next = NULL; // going back a little

        if (list->cursor == rmvdNode) {
            if (list->cursor->next != NULL) {
                move_next(list, out);
            } else if (list->cursor->prev != NULL) {
                move_prev(list, out);
            } else {
                list->cursor = NULL;
            }
        }

        free(rmvdNode->data);
        free(rmvdNode);
        list->size--;
        return;
    }
    
// DEL_MIDDLE: normal case: at least 3: not first, not last
    rmvdNode = it;
    it->next->prev = it->prev;
    it->prev->next = it->next;

    free(rmvdNode->data);
    free(rmvdNode);
    list->size--;
    return;
}

void show_first(struct LinkedList *list, FILE *out) {
    if (list == NULL) {
        return;
    }


    if (list->size == 0) {
         fprintf(out, "Error: show empty playlist\n");
         return;
    }

    struct Node *it = list->head;
    struct metadata *insideData = it->data;
    fprintf(out, "Title: %s\nArtist: %s\nAlbum: %s\nYear: %s\n", insideData->title, insideData->artist, insideData->album, insideData->year);

}

void show_last(struct LinkedList *list, FILE *out) {
    if (list == NULL) {
        return;
    }


    if(list->size == 0) {
        fprintf(out, "Error: show empty playlist\n");
        return;
    }

    struct Node *it = list->head;
    while (it->next != NULL) {
        it = it->next;
    }

    struct metadata *insideData = it->data;
    fprintf(out, "Title: %s\nArtist: %s\nAlbum: %s\nYear: %s\n", insideData->title, insideData->artist, insideData->album, insideData->year);


}

void show_curr(struct LinkedList *list, FILE *out) {
    if (list == NULL) {
        return;
    }

    if (list->size == 0) {
        fprintf(out, "Error: show empty playlist\n");
        return;
    }

    struct metadata *insideData = list->cursor->data;
    fprintf(out, "Title: %s\nArtist: %s\nAlbum: %s\nYear: %s\n", insideData->title, insideData->artist, insideData->album, insideData->year);
   

}

void show_playlist(struct LinkedList *list, FILE *out) {
    if (list == NULL) {
        return;
    }

    struct Node *it = list->head;

    if(it == NULL) {
         fprintf(out, "Error: show empty playlist\n");
         return;
    }

    fprintf(out, "[");    
    while(it != NULL){
        if (it->next == NULL) {
            fprintf(out, "%s", it->data->title);
        } else {
            fprintf(out, "%s; ", it->data->title);
        }
        it = it->next;
    }
    fprintf(out, "]\n");
}

void move_prev(struct LinkedList *list, FILE *out) {
    if (list == NULL) {
        return;
    }

    if(list->cursor == NULL) {
        fprintf(out, "Error: no track playing\n");
        return;
    }

    if(list->cursor->prev == NULL) {
        return;
    }

    list->cursor = list->cursor->prev;
}

void move_next(struct LinkedList *list, FILE *out) {
    if (list == NULL) {
        return;
    }

    if(list->cursor == NULL) {
        fprintf(out, "Error: no track playing\n");
        return;
    }

    if(list->cursor->next == NULL) {
        return;
    }

    list->cursor = list->cursor->next;
}

void free_list(struct LinkedList **pp_list) {
    if(pp_list == NULL) {
        return;
    }

    struct Node *it;
    // Solution: Mananci din lista ca la Pacman

    // Eliberez fix ce nu e NULL
    while((*pp_list)->head != NULL) {
        it = (*pp_list)->head;
        (*pp_list)->head = ((*pp_list)->head)->next;
        free(it->data);
        free(it);
    }

    free((*pp_list)->head);
    free(*pp_list);
}

void print_int_linkedlist(struct LinkedList *list) {
    if (list == NULL || list->size == 0) {
        return;
    }

    struct Node *it = list->head;

    while (it != NULL) {
        printf("%d ", *((int *)it->data));
        it = it->next;
    } 

    printf("\n");
}

void print_string_linkedlist(struct LinkedList *list) {
    if (list == NULL || list->size == 0) {
        return;
    }

    struct Node *it = list->head;    

    while (it != NULL) {
        printf("%s ", (char *)it->data);
        it = it->next;
    }
    printf("\n");
}