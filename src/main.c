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
    line[strcspn(line, "\r\n")] = '\0'; // Search the line with the strcspn function. Search for the newline and last line characters. On their place in the array, replace it with a null-termination instead.
    
    // Her skal du bruge funktionen 'strcspn'. Det er en funktion der leder efter de karakterer som du definerer. Hvis den finder karakteren, så fortæller dig dig på hvilken placering den er fundet. 
    // Hvorfor skal vi vide hvor karakteren er? Jo, hvis vi ved hvor den er, så kan vi erstatte den. I vores tilfælde vil vi gerne erstatte den med en null-termination, \0. 
    // Så målet er at finde placering af newline og lastline i vores array "line", og erstatte den med null termination.

  // MY CODE END

  return line;
}

/// Reads lines from `filename`, creates a node for each line and inserts
/// nodes to `list`.
Node **load_file(const char *filename, Node **list) {
  // Open the file and assign to stream `f`
  // MY CODE START

    FILE *f = fopen(filename,"r"); // We assign it to the parsed filename. We open it in read mode, since we don't want to edit the original file. 
    // Brug funktionen fopen til at tildele den fil der skal loades, ind i pointeren f.
    // Bemærk han ikke har defineret at der skal være en pointer der hedder f, at pointertypen FILE. Så det skal du også gøre. 

  // MY CODE END

  if (!f) {
    perror(filename);
    exit(EXIT_FAILURE);
  }
  char line[TRACK_TITLE_SIZE];

  while (
      // Read one line from the stream
        fgets(line, TRACK_TITLE_SIZE, f) // fgets is a function that reads one line at a time from a document, and saves it to the buffer 'line'.
        // Brug funktionen fgets til at læse en linje fra 'f' ind i 'line'
  ) {
    remove_newline_if_exists(line); // Here we run the function to remove unwanted characters.

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

    memcpy((char *)data, line, strlen(line) + 1); // We copy the memory into a buffer called data

    new_node->data = data; // We load the data from the memcpy function into a new nodes data slot. 

    if (!(*list)) { // We check if the list is empty. If is is, then we load the data
      *list = new_node; // into the start of the list. 
    } else { // If it isn't
      Node *current = *list; // We start at the start of the list
      // And checks if it is the end of the list we have reached
      while (current->next) { // As long as the current node, points to a new node, we are not at the end
        current = current->next; // Iterate to the next node in line.
      } // We exit this while loop, when the current node no longer points to a new node, but a NULL pointer. 
      current->next = new_node;  // We set the new node into the current nodes pointer, so we have appended the data to the end of the list
    }

    /*
     Den her del er meget svær. Der er i denne kodeblok du skal lægge din data ind i listen.

     Først skal du kopiere din data. Lige nu ligger den i 'line', men vi skal have den ind i liste-format. Det skal du gøre med memcpy funtionen. 
     Vi bruger den, fordi vi kan tildele ekstra plads i den variable vi laver med den. Og vi skal bruge den ekstra plads til at holde på noget adresse data.
     Så din kode kommer til at være memcpy(NAVN PÅ BUFFER, DEN DATA DU VIL KOPIERE, LÆNGDEN SOM BUFFEREN) hvor at længden skal være data-længden + 1.

     Derned skal du lave en node, med den data du skal lægge ind i listen. Det gør du med pointeren 'new_node' hvor du peger på datablokken i new_node og sætter den lig bufferen fra memcpy.

     Vi skal tjekke om listen er tom. Det kan man gøre med en if statement, hvor man enten tjekker for om der er noget, eller om det ikke er noget.
     Hvis den er tom, så kan vi bare lægge vores new_node ind i toppen af listen. 

     Hvis ikke den er tom, så skal vi lave et loop der løber gennem listen, for at finde bunden af den. Her skal du nok bruge et while loop. 
    */
  }
  fclose(f);
  return list;
}

/// Saves `list` contents to the file at `filename`.
void save_file(const char *filename, Node *list) {
  // Open file

  FILE *f = fopen(filename,"w"); // Open up file, also create it at the same time. 

  // Move through the list and save the tracks to the file
  // Note: You have to cast the data to print the track to the file as follows:
  // (char *)current->data
  // Because current->data is a pointer to everything (void*).
  Node *current = list;

    while(current){ // As long as there is some data in current (meaning no terminating character)
        fprintf(f, "%s", (char *)current->data); // Print the data in current to the output file 'f'
        
        if (current->next) { // If there is data in the next node
            fprintf(f,"%s", "\n"); // Print a new line
        }

        current = current->next; // Go to the next node
    }

    /*
    Her skal vi lægge dataen ind i vores dokument. Det gør vi med en fprintf. 
    Vi skal også huske, at der skal være en newline-karakter. Ellers bliver al teksten bare en lang linje. 
    Det er nok smartest at tjekke, om der faktisk er brug for en new-line, ved hjælp af en if statement, hvor man ser om der er data i den næste node.
    Alternativt kan man være lidt doven, og bare sætte newline i hver linje.
    Når det er ordnet, så skal man gå til den næste node i listen, og indsætte den data i dokumentet. 
    Det vigtigt at du finder en måde at stoppe processen på. Det klart, at når der ikke er mere data i listen, så skal vi stoppe med at indsætte data. 
    Det er nemmest at lave det som et while loop, der tjekker for om der er data i noden man står i. 
    */

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
  Node node = {.data = "Tarkan – Şımarık", .next = NULL};
  insert_at(&playlist, 3, &node);

  save_file(PLAYLIST_OUT_PATH, playlist);
}