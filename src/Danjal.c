#include "singly_linked_list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRACK_TITLE_SIZE 60

#define PLAYLIST_IN_PATH "playlist.txt"
#define PLAYLIST_OUT_PATH "playlist-out.txt"
// To avoid unnecessary complexity, we fix the filenames instead of getting them
// through runtime parameters.

typedef char Data[TRACK_TITLE_SIZE];
Node *playlist;

/// Removes trailing newline from the line, if it exists.
/// Note: Some lines may not have a newline, e.g., last line in a file,
/// therefore we have to check for presence.
char *remove_newline_if_exists(char *line) {
  // MY CODE START

  // NULL-terminate the line and truncate it after the first occurrence of
  // either '\r' or '\n'
  line[strcspn(line, "\r\n")] = '\0';

  // MY CODE END

  return line;
}

/// Reads lines from `filename`, creates a node for each line and inserts
/// nodes to `list`.
Node **load_file(const char *filename, Node **list) {
  // Open the file and assign to stream `f`
  // MY CODE START

  // Open `filename` in read mode
  FILE *f = fopen(filename, "r");

  // MY CODE END

  if (!f) {
    perror(filename);
    exit(EXIT_FAILURE);
  }
  char line[TRACK_TITLE_SIZE];

  while (
      // Read one line from the stream
      // MY CODE START

      fgets(line, TRACK_TITLE_SIZE, f)

      // MY CODE END
  ) {
    remove_newline_if_exists(line);

    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) {
      perror("malloc");
      continue;
    }
    Data *data = (Data *)malloc(sizeof(Data));
    if (!data) {
      perror("malloc");
      continue;
    }
    new_node->next = NULL;
    new_node->data = data;

    // Copy line to `new_node` and append `new_node` to `list`
    // MY CODE START

    // Copy the data from `line` into `new_node`'s data
    // Here I'm copying strlen(line) + 1 bytes to include the NULL-terminator
    memcpy((char *)data, line, strlen(line) + 1);
    new_node->data = data;

    // If the list is empty, set the head to `new_node`
    if (!(*list)) {
      *list = new_node;
      // If the list isn't empty, append new_node to its tail
    } else {
      Node *current = *list;
      // Keep traversing the list until `current`'s next node is NULL
      while (current->next) {
        current = current->next;
      }
      // Append `new_node` to the list by setting
      // `current`'s next node to `new_node`
      current->next = new_node;
    }

    // MY CODE END
  }
  fclose(f);
  return list;
}

/// Saves `list` contents to the file at `filename`.
void save_file(const char *filename, Node *list) {
  // Open file
  // MY CODE START

  // Open `filename` in write mode
  FILE *f = fopen(filename, "w");

  // If opening the file fails, exit the program
  if (!f) {
    perror(filename);
    exit(EXIT_FAILURE);
  }

  // MY CODE END

  // Move through the list and save the tracks to the file
  // Note: You have to cast the data to print the track to the file as follows:
  // (char *)current->data
  // Because current->data is a pointer to everything (void*).
  Node *current = playlist;
  // MY CODE START¨

  // Keep looping through the list and printing to the output file
  while (current) {
    fprintf(f, "%s", (char *)current->data);
    // Only print at newline if the `current` has a `next` node
    if (current->next) {
      fprintf(f, "%s", "\n");
    }
    // Iterate to the next node
    current = current->next;
  }

  // MY CODE END

  fclose(f);
  //// END SOLUTION
}

void print_tracks(const Node *const playlist) {
  const Node *current = playlist;
  for (size_t i = 1; current; i++, current = current->next)
    printf("%2zu: %s\n", i, (char *)current->data);
}

int main() {
  load_file(PLAYLIST_IN_PATH, &playlist);
  print_tracks(playlist);

  // Deletion
  size_t node_index_to_del = 4;
  free(delete_at(&playlist, node_index_to_del));

  // Insertion
  Node node = {.data = "Tarkan – Şımarık 💋", .next = NULL};
  insert_at(&playlist, 3, &node);

  save_file(PLAYLIST_OUT_PATH, playlist);
}