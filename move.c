// Copyright 2020 Radu-Stefan Minea 314CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./LinkedList.h"
#include "./utils.h"

void moveRemovedCursor(struct LinkedList *list, FILE *out) {
  if (list->cursor->next != NULL) {
    // If there's a node to the right, we move the cursor there.
    move_next(list, out);
  } else {
    // Else, we move left
    move_prev(list, out);
  }
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
