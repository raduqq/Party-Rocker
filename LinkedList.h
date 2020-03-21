#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdio.h>

struct Node {
    struct metadata *data;
    struct Node *next, *prev;
};

struct LinkedList {
    struct Node *head;
    int size;
};

void init_list(struct LinkedList *list);

void add_first(struct LinkedList *list, struct Node *cursor, struct metadata *newData, FILE *out);

void del_song(struct LinkedList *list, struct Node *cursor, char *songName, FILE *out);

void show_first(struct LinkedList *list, FILE *out);

void show_last(struct LinkedList *list, FILE *out);

void show_curr(struct LinkedList *list, struct Node *cursor, FILE *out);

void show_playlist(struct LinkedList *list, FILE *out);

void move_prev(struct LinkedList *list, struct Node *cursor);

void move_next(struct LinkedList *list, struct Node *cursor);

void free_list(struct LinkedList **pp_list);

void print_int_linkedlist(struct LinkedList *list);

void print_string_linkedlist(struct LinkedList *list);

#endif
