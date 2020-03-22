// Copyright 2020 Radu-Stefan Minea 314CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./LinkedList.h"
#include "./utils.h"

// Deletes the node of a single-node list
void del_lonely_element(struct LinkedList *list) {
  struct Node *rmvdNode;
  rmvdNode = list->head;
  list->head = NULL;
  list->cursor = NULL;

  free(rmvdNode->data);
  free(rmvdNode);
  list->size--;
}

// Deletes a node from "inside" the list
void del_mid(struct LinkedList *list, struct Node *it, FILE *out) {
  struct Node *rmvdNode = it;
  it->next->prev = it->prev;
  it->prev->next = it->next;

  if (list->cursor == rmvdNode) {
    moveRemovedCursor(list, out);
  }

  free(rmvdNode->data);
  free(rmvdNode);
  list->size--;
}

void del_first(struct LinkedList *list, FILE *out) {
  if (list == NULL) {
    return;
  }

  struct Node *it = list->head;

  if (it == NULL) {
    fprintf(out, "Error: no song found to delete\n");
    return;
  }

  struct Node *rmvdNode;

  // One element in list => the one we want to delete
  if (list->size == 1) {
    del_lonely_element(list);
    return;
  }

  // At least 2 songs in playlist
  rmvdNode = list->head;
  list->head = list->head->next;
  list->head->prev = NULL;

  if (list->cursor == rmvdNode) {
    moveRemovedCursor(list, out);
  }

  free(rmvdNode->data);
  free(rmvdNode);
  list->size--;
  return;
}

void del_last(struct LinkedList *list, FILE *out) {
  if (list == NULL) {
    return;
  }

  struct Node *it = list->head;

  if (it == NULL) {
    fprintf(out, "Error: no song found to delete\n");
    return;
  }

  struct Node *rmvdNode;

  if (list->size == 1) {
    del_lonely_element(list);
    return;
  }

  while (it->next != NULL) {
    it = it->next;
  }

  rmvdNode = it;
  it->prev->next = NULL;

  if (list->cursor == rmvdNode) {
    moveRemovedCursor(list, out);
  }

  free(rmvdNode->data);
  free(rmvdNode);
  list->size--;
  return;
}

void del_curr(struct LinkedList *list, FILE *out) {
  if (list == NULL) {
    return;
  }

  if (list->cursor == NULL) {
    fprintf(out, "Error: no track playing\n");
    return;
  }

  if (list->cursor == list->head) {
    del_first(list, out);
    return;
  }

  if (list->cursor->next == NULL) {
    del_last(list, out);
    return;
  }

  del_mid(list, list->cursor, out);
}

void del_song(struct LinkedList *list, char *songName, FILE *out) {
  if (list == NULL) {
    return;
  }

  // Getting the iterator to the song we want to delete
  struct Node *it = list->head;

  while (it != NULL && strcmp(songName, it->data->title)) {
    it = it->next;
  }

  // SONG NOT FOUND => ignore command
  if (it == NULL) {
    fprintf(out, "Error: no song found to delete\n");
    return;
  }

  // SONG FOUND
  if (it == list->head) {
    del_first(list, out);
    return;
  }

  if (it->next == NULL) {
    del_last(list, out);
    return;
  }

  del_mid(list, it, out);
}
