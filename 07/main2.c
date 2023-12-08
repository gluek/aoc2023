#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  char *text;
  struct node *next;
} node;

void appendNode(node *list, char *text);
int compareHandPower(char *handOne, char *handTwo);
void printList(node *list);
int getIndex(int c);
int getPower(int counter[13]);
int bubbleSort(struct node **head, int count);
int calculateResult(node *list);
struct node *swap(struct node *ptr1, struct node *ptr2);
void useJoker(int counter[]);

enum power { card, pair, twopair, three, fullhouse, four, five };

int main() {
  FILE *fh;
  fh = fopen("puzzle.txt", "r");

  node *head = NULL;
  head = (node *)malloc(sizeof(node));
  head->next = NULL;
  head->text = "Head\n";

  char line[128];
  int lineCount = 0;
  while (fgets(line, sizeof(line), fh)) {
    appendNode(head, line);
    lineCount++;
  }
  head = head->next;  // remove empty head

  printf("\n");

  printList(head);
  printf("----------\n");
  bubbleSort(&head, lineCount);
  printList(head);
  int result = calculateResult(head);
  printf("Result: %d", result);
  fclose(fh);

  return 0;
}

void appendNode(node *list, char *text) {
  // printf("Append: %s", text);
  char *newText = (char *)malloc(sizeof(*text));
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

int compareHandPower(char *handOne, char *handTwo) {
  int counterOne[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int counterTwo[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  char one[15] = "";
  char two[15] = "";
  strcpy(one, handOne);
  strcpy(two, handTwo);
  for (size_t i = 0; i < 5; i++) {
    counterOne[getIndex(one[i])] += 1;
    counterTwo[getIndex(two[i])] += 1;
  }
  useJoker(counterOne);
  useJoker(counterTwo);

  int powerOne = getPower(counterOne);
  int powerTwo = getPower(counterTwo);

  if (powerOne == powerTwo) {
    for (size_t i = 0; i < 5; i++) {
      // printf("%c, %c\n", one[i], two[i]);
      if (one[i] != two[i]) {
        if (getIndex(one[i]) > getIndex(two[i])) {
          powerOne += 1;
        } else {
          powerTwo += 1;
        }
        break;
      }
    }
  }
  // printf("Power One: %d, Power Two: %d\n", powerOne, powerTwo);
  if (powerOne > powerTwo) {
    return 1;
  } else {
    return 0;
  }
}

void printList(node *list) {
  node *current = list;

  while (current != NULL) {
    printf("%s", current->text);
    current = current->next;
  }
  printf("\n");
}

int getIndex(int c) {
  switch (c) {
    case 'A':
      return 12;
    case 'K':
      return 11;
    case 'Q':
      return 10;
    case 'T':
      return 9;
    case '9':
      return 8;
    case '8':
      return 7;
    case '7':
      return 6;
    case '6':
      return 5;
    case '5':
      return 4;
    case '4':
      return 3;
    case '3':
      return 2;
    case '2':
      return 1;
    case 'J':
      return 0;
    default:
      printf("This should not happen! Char: %c\n", c);
      return -1;
  }
}

int getPower(int counter[13]) {
  enum power pow;
  pow = card;
  int pairs = 0;
  int threes = 0;
  for (size_t i = 0; i < 13; i++) {
    if (counter[i] == 5) {
      pow = five;
      break;
    } else if (counter[i] == 4) {
      pow = four;
      break;
    } else if (counter[i] == 3) {
      pow = three;
      threes++;
    } else if (counter[i] == 2) {
      pairs++;
    }
  }
  if (threes == 1 && pairs == 1) {
    pow = fullhouse;
  }
  if (threes != 1 && pairs == 1) pow = pair;
  if (pairs == 2) pow = twopair;
  return pow;
}

/*Function to swap the nodes */
struct node *swap(struct node *ptr1, struct node *ptr2) {
  struct node *tmp = ptr2->next;
  ptr2->next = ptr1;
  ptr1->next = tmp;
  return ptr2;
}

/* Function to sort the list */
int bubbleSort(struct node **head, int count) {
  struct node **h;
  int i, j, swapped;

  for (i = 0; i <= count; i++) {
    h = head;
    swapped = 0;

    for (j = 0; j < count - i - 1; j++) {
      struct node *p1 = *h;
      struct node *p2 = p1->next;

      if (compareHandPower(p1->text, p2->text)) {
        /* update the link after swapping */
        *h = swap(p1, p2);
        swapped = 1;
      }

      h = &(*h)->next;
    }

    /* break if the loop ended without any swap */
    if (swapped == 0) break;
  }
}

int calculateResult(node *list) {
  node *current = list;
  long rank = 1;
  long long result = 0;
  while (current != NULL) {
    char *value = (char *)(current->text + 6);
    long intValue = atoi(value);
    // printf("Rank: %d, Result: %d, IntValue: %d, Line:%s", rank, result,
    //        intValue, current->text);
    result += rank * intValue;
    current = current->next;
    rank++;
  }
  printf("\n");

  return result;
}

void useJoker(int counter[]) {
  int jokers = counter[0];
  int counterLength = 13;
  int currentMax = 0;
  int indexMax = 0;
  for (size_t i = 1; i < counterLength; i++) {
    if (counter[i] > currentMax) {
      currentMax = counter[i];
      indexMax = i;
    }
  }
  if (jokers != 5) {
    counter[indexMax] += jokers;
    counter[0] = 0;
  }
}