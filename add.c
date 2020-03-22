// Copyright 2020 Radu-Stefan Minea 314CA

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./LinkedList.h"
#include "./utils.h"

void add_first(struct LinkedList *list, struct metadata *value, FILE *out) {
  if (list == NULL) {
    return;
  }

  struct metadata *newData = malloc(sizeof(struct metadata));
  memcpy(newData, value, sizeof(struct metadata));

  // Delete already-existent song from playlist
  if (isInPlaylist(list, newData->title)) {
    del_song(list, newData->title, out);
  }

  // Adding the new song in playlist
  struct Node *newNode = malloc(sizeof(struct Node));

  newNode->prev = NULL;
  newNode->data = newData;

  if (list->size == 0) {
    // List previously empty => assigning cursor to the newly-added node
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

void add_last(struct LinkedList *list, struct metadata *value, FILE *out) {
  if (list == NULL) {
    return;
  }

  struct metadata *newData = malloc(sizeof(struct metadata));
  memcpy(newData, value, sizeof(struct metadata));

  // Delete already-existent song from playlist
  if (isInPlaylist(list, newData->title)) {
    del_song(list, newData->title, out);
  }

  struct Node *it = list->head;
  struct Node *newNode = malloc(sizeof(struct Node));

  newNode->next = NULL;
  newNode->data = newData;

  if (list->size == 0) {
    list->cursor = newNode;
    newNode->prev = NULL;
    list->head = newNode;
  } else {
    while (it->next != NULL) {
      it = it->next;
    }
    it->next = newNode;
    newNode->prev = it;
  }

  list->size++;
}

void add_after(struct LinkedList *list, struct metadata *value, FILE *out) {
  if (list == NULL || list->cursor == NULL) {
    return;
  }

  // If cursor's song == song we want to add
  if (strcmp(list->cursor->data->title, value->title) == 0) {
    return;
  }

  if (isInPlaylist(list, value->title)) {
    del_song(list, value->title, out);
  }

  if (list->cursor->next == NULL) {
    add_last(list, value, out);
    return;
  }

  struct metadata *newData = malloc(sizeof(struct metadata));
  memcpy(newData, value, sizeof(struct metadata));

  // At least 2 elements and the cursor is NOT on the last node
  // => adding in the middle of the list
  struct Node *it = list->cursor;
  struct Node *newNode = malloc(sizeof(struct Node));

  newNode->data = newData;

  newNode->next = it->next;
  it->next->prev = newNode;
  it->next = newNode;
  newNode->prev = it;

  list->size++;
}
