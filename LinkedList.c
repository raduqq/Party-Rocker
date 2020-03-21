#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./utils.h"
#include "./LinkedList.h"

void init_list(struct LinkedList *list) {
    list->head = NULL;
    list->size = 0;
}

bool isInPlaylist(struct LinkedList *list, char* songName) {
    if (list == NULL) {
        return 0;
    }

    struct Node *it = list->head;
    struct metadata *insideData;

    while (it != NULL) {
        insideData = it->data;
        if(strcmp(songName, insideData->title) == 0) {
            return 1;
        }
    }

    return 0;
}

/*
void add_first(struct LinkedList *list, struct Node *cursor, struct metadata *newData) {

// !!!!!!!!!!!! SI PREVURILE UNDE SUNT BAMBI??

    if(list == NULL) {
        return;
    }

    // Song already in playlist => deleted first
    if(isInPlaylist(list, newData->title)) {
        //del_song ... plm song-ul asta
    }

    // New song in playlist
    struct Node *it = list->head;
    struct Node *newNode = malloc(sizeof(struct Node));

    newNode->data = newData;
    list->head = newNode;

    if(list->size == 0) {
         // List previously empty => assign cursor to the now-added node
        cursor = newNode;
        newNode->next = NULL;
    } else {
         // If the list had at least one element
        newNode->next = it;   
    }

    list->size++;
}

// add_last

// add_after

// del_first

// del_last

// del_curr

void del_song(struct LinkedList *list, char *songName) {
    if (list == NULL || list->size == 0) {
        return;
    }

    // Finding song-to-delete by songname
    struct Node *it = list->head;
    struct metadata *insideData = it->data;

    while(it != NULL && strcmp(songName, insideData->title)) {
        it = it->next;
        insideData = it->data;
    }

    // SONG NOT FOUND => EXIT
    if (it == NULL) {
        return;
    }

    // SONG FOUND
    struct Node *rmvdNode;

/////////////////////////////////////// DEL_FIRST

    // One element in list => its the one we want to remove
    if (list->size == 1) {
        rmvdNode = list->head;
        list->head = NULL;
        
        list->size --;
        return;
    }

    // Requested song = first in list
    if (it == list->head) {
        rmvdNode = list->head;
        list->head = list->head->next;
        
        list->size --;
        return;
    }

/////////////////////////////////// END_DEL_FIRST

//////////////////////////////////// DEL_LAST

    if(it->next == NULL) {
        it = it->prev; // going back a little
    }


}
*/

void free_list(struct LinkedList **pp_list) {
    if(pp_list == NULL) {
        return;
    }

    struct Node *it;
    it = (*pp_list)->head; // From pointer to list to list.

    // Solution: Mananci din lista ca la Pacman

    // Eliberez fix ce nu e NULL
    while((*pp_list)->head != NULL) {
        it = (*pp_list)->head;
        (*pp_list)->head = ((*pp_list)->head)->next;
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