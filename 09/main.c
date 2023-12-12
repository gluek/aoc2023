#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  char *text;
  struct node *next;
} node;

void appendNode(node *list, char *text);
void printList(node *list);
int *parseLR(char *line, int *length);
char *nextCoord(char *line, int leftRight);
char *lookForLine(node *text, char *coord);
int navigateDesert(node *text, int pattern[], int patternLength);

int main() {
  FILE *fh;
  fh = fopen("input.txt", "r");

  node *head = NULL;
  head = (node *)malloc(sizeof(node));
  head->next = NULL;
  head->text = "Head\n";

  char line[512];
  int lineCount = 0;
  while (fgets(line, sizeof(line), fh)) {
    appendNode(head, line);
    lineCount++;
  }
  head = head->next;  // remove empty head

  printList(head);

  return 0;
}

void appendNode(node *list, char *text) {
  // printf("Append: %s", text);
  int len = strlen(text);
  char *newText = (char *)malloc(len * sizeof(char));
  strcpy(newText, text);
  node *current = list;
  while (current->next != NULL) {
    current = current->next;
  }

  /* now we can add a new variable */
  current->next = (node *)malloc(sizeof(node));
  current->next->text = newText;
  current->next->next = NULL;
}

void printList(node *list) {
  node *current = list;

  while (current != NULL) {
    printf("%s", current->text);
    current = current->next;
  }
  printf("\n");
}