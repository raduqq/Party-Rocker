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

void moveRemovedCursor(struct LinkedList *list, FILE *out) {
  if (list->cursor->next != NULL) {
    // If there's a node to the right, we move the cursor there.
    move_next(list, out);
  } else {
    // Else, we move left
    move_prev(list, out);
  }
}

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
  fprintf(out, "Title: %s\nArtist: %s\nAlbum: %s\nYear: %s\n",
          insideData->title, insideData->artist, insideData->album,
          insideData->year);
}

void show_last(struct LinkedList *list, FILE *out) {
  if (list == NULL) {
    return;
  }

  if (list->size == 0) {
    fprintf(out, "Error: show empty playlist\n");
    return;
  }

  struct Node *it = list->head;
  while (it->next != NULL) {
    it = it->next;
  }

  struct metadata *insideData = it->data;
  fprintf(out, "Title: %s\nArtist: %s\nAlbum: %s\nYear: %s\n",
          insideData->title, insideData->artist, insideData->album,
          insideData->year);
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
  fprintf(out, "Title: %s\nArtist: %s\nAlbum: %s\nYear: %s\n",
          insideData->title, insideData->artist, insideData->album,
          insideData->year);
}

void show_playlist(struct LinkedList *list, FILE *out) {
  if (list == NULL) {
    return;
  }

  struct Node *it = list->head;

  fprintf(out, "[");
  while (it != NULL) {
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

  if (list->cursor == NULL) {
    fprintf(out, "Error: no track playing\n");
    return;
  }

  if (list->cursor->prev == NULL) {
    return;
  }

  list->cursor = list->cursor->prev;
}

void move_next(struct LinkedList *list, FILE *out) {
  if (list == NULL) {
    return;
  }

  if (list->cursor == NULL) {
    fprintf(out, "Error: no track playing\n");
    return;
  }

  if (list->cursor->next == NULL) {
    return;
  }

  list->cursor = list->cursor->next;
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
