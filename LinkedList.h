#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

struct Node {
    void *data; /* Pentru ca datele stocate sa poata avea orice tip, folosim un pointer la void. */
    struct Node *next, *prev;
};

struct LinkedList {
    struct Node *head;
    int size;
};

void init_list(struct LinkedList *list);

/*
 * Acestea sunt functiile pe care trebuie sa le implementam.
 * Implementarea acestora se va face in LinkedList.c .
 */

/*
void add_first(struct LinkedList *list);

void add_last(struct LinkedList *list);
*/

void free_list(struct LinkedList **pp_list);

void print_int_linkedlist(struct LinkedList *list);

void print_string_linkedlist(struct LinkedList *list);

#endif /* __LINKEDLIST_H__ */
