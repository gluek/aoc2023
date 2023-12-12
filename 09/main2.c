#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  char *text;
  struct node *next;
} node;

typedef struct nodeInt {
  long long value;
  struct nodeInt *next;
} nodeInt;

void appendNode(node *list, char *text);
void printList(node *list);

nodeInt *splitLine(char *line);
void printListInt(nodeInt *list);
int listLength(struct nodeInt *list);
long long *calculateDiff(long long *history, int length,
                         struct nodeInt *firstNumbers);
long long parseLine(char *line);
int checkForValues(long long *array, int length);
void appendNodeInt(struct nodeInt *list, long long value);

int main() {
  FILE *fh;
  fh = fopen("puzzle.txt", "r");

  node *head = NULL;
  head = malloc(sizeof(node));
  head->next = NULL;
  head->text = "Head\n";

  char line[512];
  int lineCount = 0;
  while (fgets(line, sizeof(line), fh)) {
    appendNode(head, line);
    lineCount++;
  }

  head = head->next;  // remove empty head
  node *current = head;
  // printList(head);
  long long result = 0;
  while (current->next != NULL) {
    result += parseLine(current->text);
    current = current->next;
  }
  result += parseLine(current->text);
  printf("Result: %ld", result);
  return 0;
}

void appendNode(node *list, char *text) {
  // printf("Append: %s", text);
  int len = strlen(text);
  char *newText = malloc(len * sizeof(char));
  strcpy(newText, text);
  node *current = list;
  while (current->next != NULL) {
    current = current->next;
  }

  /* now we can add a new variable */
  current->next = malloc(sizeof(node));
  current->next->text = newText;
  current->next->next = NULL;
}

void appendNodeInt(struct nodeInt *list, long long value) {
  // printf("Append: %d\n", value);
  struct nodeInt *current = list;
  while (current->next != NULL) {
    current = current->next;
  }

  /* now we can add a new variable */
  current->next = malloc(sizeof(struct nodeInt));
  current->next->value = value;
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

void printListInt(nodeInt *list) {
  nodeInt *current = list;

  while (current != NULL) {
    printf("%d ", current->value);
    current = current->next;
  }
  printf("\n");
}

long long parseLine(char *line) {
  nodeInt *lineAsNumbers = splitLine(line);
  nodeInt *current = lineAsNumbers;
  int length = listLength(lineAsNumbers);
  long long *lineArray = malloc(sizeof(long long) * length);

  long long finalResult = current->value;
  int i = 0;
  while (current->next != NULL) {
    lineArray[i] = current->value;
    i++;
    current = current->next;
  }
  lineArray[i] = current->value;

  nodeInt *firstNumbers = malloc(sizeof(nodeInt));
  firstNumbers->next = NULL;
  firstNumbers->value = 0;
  long long *result = calculateDiff(lineArray, length, firstNumbers);
  int j = 1;
  while (checkForValues(result, length - j)) {
    result = calculateDiff(result, length - j, firstNumbers);
    j++;
  }
  firstNumbers = firstNumbers->next;
  int lengthNumbers = listLength(firstNumbers);
  nodeInt *currentNew = firstNumbers;
  i = 1;
  while (currentNew->next != NULL) {
    finalResult += currentNew->value * (1 - 2 * (i % 2));
    currentNew = currentNew->next;
    i++;
  }
  // printListInt(firstNumbers);
  printf("Line Result: %d\n", finalResult);
  return finalResult;
}

long long *calculateDiff(long long *history, int length,
                         struct nodeInt *firstNumbers) {
  long long *result = malloc((length - 1) * sizeof(long long));
  for (size_t i = 0; i < length - 1; i++) {
    result[i] = history[i + 1] - history[i];
  }
  appendNodeInt(firstNumbers, result[0]);
  return result;
}

int checkForValues(long long *array, int length) {
  for (size_t i = 0; i < length; i++) {
    if (array[i] != 0) {
      return 1;
    }
  }
  return 0;
}

nodeInt *splitLine(char *line) {
  int length = strlen(line);
  char space = 32;
  char newline = 10;
  nodeInt *list = (nodeInt *)malloc(sizeof(nodeInt));
  list->next = NULL;
  list->value = 0;
  int j = 0;
  for (size_t i = 0; i < length; i++) {
    char curChar = line[i];
    if (curChar == space || curChar == newline) {
      char *tempStr = (char *)malloc((i - j) * sizeof(char));
      strncpy(tempStr, line + j, i - j);
      tempStr[i - j] = '\0';
      appendNodeInt(list, atol(tempStr));
      j = i + 1;
    }
  }
  list = list->next;
  return list;
}

int listLength(struct nodeInt *list) {
  int length = 0;
  nodeInt *current = list;
  while (current->next != NULL) {
    length++;
    current = current->next;
  }
  length++;
  return length;
}