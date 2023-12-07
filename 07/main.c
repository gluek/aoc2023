#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node
{
    char *text;
    struct node *next;
} node;

void appendNode(node *list, char *text);
int compareHandPower(char *handOne, char *handTwo);
void printList(node *list);
int getIndex(int c);
int getPower(int counter[13]);

enum power
{
    card,
    pair,
    twopair,
    three,
    fullhouse,
    four,
    five
};

int main()
{
    printf("Hello World!\n");

    FILE *fh;
    fh = fopen("input.txt", "r");

    node *head = NULL;
    head = (node *)malloc(sizeof(node));
    head->next = NULL;
    head->text = "Head\n";

    char line[128];
    while (fgets(line, sizeof(line), fh))
    {
        appendNode(head, line);
    }
    printf("\n");

    compareHandPower("AAAAA", "AAAAK");

    printList(head);

    fclose(fh);

    return 0;
}

void appendNode(node *list, char *text)
{
    printf("Append: %s", text);
    char *newText = (char *)malloc(sizeof(*text));
    strcpy(newText, text);
    node *current = list;
    while (current->next != NULL)
    {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = (node *)malloc(sizeof(node));
    current->next->text = newText;
    current->next->next = NULL;
}

int compareHandPower(char *handOne, char *handTwo)
{
    int counterOne[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int counterTwo[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    char one[6];
    char two[6];
    strcpy(one, handOne);
    strcpy(two, handTwo);
    for (size_t i = 0; i < 5; i++)
    {
        counterOne[getIndex(one[i])] += 1;
        counterTwo[getIndex(two[i])] += 1;
    }
    int powerOne = getPower(counterOne);
    int powerTwo = getPower(counterTwo);

    return 1;
}

void printList(node *list)
{
    node *current = list;
    current = current->next;

    while (current != NULL)
    {
        printf("%s", current->text);
        current = current->next;
    }
}

int getIndex(int c)
{
    switch (c)
    {
    case 'A':
        return 12;
    case 'K':
        return 11;
    case 'Q':
        return 10;
    case 'J':
        return 9;
    case 'T':
        return 8;
    case '9':
        return 7;
    case '8':
        return 6;
    case '7':
        return 5;
    case '6':
        return 4;
    case '5':
        return 3;
    case '4':
        return 2;
    case '3':
        return 1;
    case '2':
        return 0;
    default:
        return 13;
    }
}

int getPower(int counter[13])
{
    enum power pow;
    pow = card;
    int pairs = 0;
    for (size_t i = 0; i < 13; i++)
    {
        if (counter[i] == 5)
        {
            pow = five;
            break;
        }
        else if (counter[i] == 4)
        {
            pow = four;
            break;
        }
        else if (counter[i] == 3)
        {
            pow = three;
            break;
        }
        else if (counter[i] == 2)
        {
            pairs++;
        }
    }
    if (pairs == 1)
        pow = pair;
    if (pairs == 2)
        pow = twopair;
    return pow;
}