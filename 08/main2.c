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
int navigateDesert(struct node *text, struct node *startCoords, int pattern[],
                   int patternLength);
node *lookForInitalLines(struct node *text);

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
  node *starts = lookForInitalLines(firstCoord);
  printList(starts);
  printf("Result: %d",
         navigateDesert(firstCoord, starts, pattern, patternLength));

  return 0;
}

void appendNode(struct node *list, char *text) {
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

void printList(struct node *list) {
  node *current = list;

  while (current != NULL) {
    printf("%s", current->text);
    current = current->next;
  }
  // printf("\n");
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
  char leftMem[4] = "000\0";
  char rightMem[4] = "000\0";
  char *left = &leftMem[0];
  char *right = &rightMem[0];
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

char *lookForLine(struct node *text, char *coord) {
  node *current = text;
  char lineStartMem[4] = "000\0";
  char *lineStart = &lineStartMem[0];

  while (current != NULL) {
    strncpy(lineStart, current->text, 3);
    lineStart[3] = '\0';
    if (!strcmp(coord, lineStart)) {
      return current->text;
    }
    current = current->next;
  }
}

node *lookForInitalLines(struct node *text) {
  node *current = text;
  node *head = NULL;
  head = (node *)malloc(sizeof(node));
  head->next = NULL;
  head->text = "Head\n";

  char *lineStart = (char *)malloc(4 * sizeof(char));

  while (current != NULL) {
    strncpy(lineStart, current->text, 3);
    lineStart[3] = '\0';
    char *thirdChar = &lineStart[2];
    char *compareChar = "A";
    if (!strcmp(thirdChar, compareChar)) {
      appendNode(head, current->text);
    }
    current = current->next;
  }
  free(lineStart);
  head = head->next;
  return head;
}

int navigateDesert(struct node *text, struct node *startCoords, int pattern[],
                   int patternLength) {
  long long steps = 0;

  char nextCoordVar[4];
  char line[128];
  int leftRight = 0;
  int startCoordsLength = 0;
  long cycles[6] = {0, 0, 0, 0, 0, 0};
  int zCounter = 0;
  char *zChar = "Z";
  node *current = startCoords;
  int currentIndex = 0;
  int offset = 0;

  while (current != NULL) {
    startCoordsLength += 1;
    current = current->next;
  }
  current = startCoords;

  while (steps < 10000000000000) {
    leftRight = pattern[steps % patternLength];
    // Loops: 19637 12643 14257 15871 11567 19099
    while (current != NULL) {
      strcpy(nextCoordVar, nextCoord(current->text, leftRight));
      // printf("Step: %d, LeftRight: %d, Line: %s   Next Coord: %s\n", steps,
      //        leftRight, current->text, nextCoordVar);
      if (!strcmp(&nextCoordVar[2], zChar)) {
        if (cycles[currentIndex] == 0) {
          cycles[currentIndex] = steps + 1;
        } else if (cycles[currentIndex] > steps - cycles[currentIndex]) {
          cycles[currentIndex] = steps - cycles[currentIndex] + 1;
        }
        if (offset == 0) {
          offset = steps;
        } else if (offset > steps - offset + 1) {
          offset = steps - offset + 1;
        }
        zCounter++;
      }
      strcpy(current->text, lookForLine(text, nextCoordVar));
      current = current->next;
      currentIndex++;
    }
    current = startCoords;
    currentIndex = 0;
    if (zCounter > 1) {
      printList(current);
      printf("zCounter:%d\n", zCounter);
      printf("Offset:%d\n", offset);
      printf("Steps:%d\n", steps);
      printf("Cycles: %d %d %d %d %d %d\n", cycles[0], cycles[1], cycles[2],
             cycles[3], cycles[4], cycles[5]);
    }
    steps++;
    if (zCounter == startCoordsLength) {
      break;
    } else {
      zCounter = 0;
    }
  }
  // Loops: 19637 12643 14257 15871 11567 19099 = LCM: 8811050362409
  return steps;
}
