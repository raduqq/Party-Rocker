// Copyright 2020 Radu-Stefan Minea 314CA

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./LinkedList.h"
#include "./utils.h"

void init_list(struct LinkedList *list) {
  list->head = NULL;
  list->cursor = NULL;
  list->size = 0;
}

bool isInPlaylist(struct LinkedList *list, char *songName) {
  if (list == NULL) {
    return 0;
  }

  struct Node *it = list->head;

  // Parses the list until it finds the song we're after
  while (it != NULL) {
    if (strcmp(songName, it->data->title) == 0) {
      return 1;
    }
    it = it->next;
  }

  return 0;
}

void free_list(struct LinkedList **pp_list) {
  if (pp_list == NULL) {
    return;
  }

  struct Node *it;

  while ((*pp_list)->head != NULL) {
    it = (*pp_list)->head;
    (*pp_list)->head = ((*pp_list)->head)->next;
    free(it->data);
    free(it);
  }

  free((*pp_list)->head);
  free(*pp_list);
}
