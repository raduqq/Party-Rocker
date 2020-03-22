// Copyright 2020 Radu-Stefan Minea 314CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./LinkedList.h"
#include "./utils.h"

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
