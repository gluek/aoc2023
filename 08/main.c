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
  fh = fopen("puzzle.txt", "r");

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
  node *firstCoord = head->next->next;

  //   printList(head);
  //   printf("Next: %s", nextCoord(firstCoord->text, 0));
  //   printf("Line: %s", lookForLine(firstCoord, "DDD"));

  int patternLength = 0;
  int *pattern = parseLR(head->text, &patternLength);
  printf("Result: %d", navigateDesert(firstCoord, pattern, patternLength));

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

int *parseLR(char *line, int *length) {
  int linelength = strlen(line) - 1;
  *length = linelength;
  int *pattern = (int *)malloc(linelength * sizeof(int));
  for (size_t i = 0; i < linelength; i++) {
    if (line[i] == 'L') {
      pattern[i] = 0;
    } else {
      pattern[i] = 1;
    }
  }

  return pattern;
}

char *nextCoord(char *line, int leftRight) {
  char *left = (char *)malloc(4 * sizeof(char));
  char *right = (char *)malloc(4 * sizeof(char));
  strncpy(left, line + 7, 3);
  strncpy(right, line + 12, 3);
  left[3] = '\0';
  right[3] = '\0';
  if (leftRight) {
    return right;
  } else {
    return left;
  }
}

char *lookForLine(node *text, char *coord) {
  node *current = text;
  char *lineStart = (char *)malloc(4 * sizeof(char));

  while (current != NULL) {
    strncpy(lineStart, current->text, 3);
    lineStart[3] = '\0';
    if (!strcmp(coord, lineStart)) {
      return current->text;
    }
    current = current->next;
  }
  free(lineStart);
}

int navigateDesert(node *text, int pattern[], int patternLength) {
  long long steps = 0;

  char nextCoordVar[4];
  char line[128];
  int leftRight = 0;
  strcpy(line, lookForLine(text, "AAA"));
  nextCoordVar[3] = '\0';

  while (steps < 100000000000) {
    leftRight = pattern[steps % patternLength];
    strcpy(nextCoordVar, nextCoord(line, leftRight));
    // printf("Step: %d, LeftRight: %d, Line: %s   Next Coord: %s\n", steps,
    // leftRight, line, nextCoordVar);
    if (!strcmp(nextCoordVar, "ZZZ")) {
      steps++;
      break;
    }
    strcpy(line, lookForLine(text, nextCoordVar));
    steps++;
  }
  return steps;
}