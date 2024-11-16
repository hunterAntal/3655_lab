#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
} node_t;

void print_list(node_t *head)
{
    printf("\n");
    printf("Printing List:\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    node_t *current = head;

    while (current != NULL)
    {
        printf("%d\n", current->val);
        current = current->next;
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

// add to the end of the list
void add(node_t *head, int val)
{
    node_t *current = head;
    while (current != NULL)
    {
        current = current->next;
    }
    current->next = (node_t *)malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

// push to the beggining of the list
void push(node_t **head, int val)
{
    node_t *newHead = (node_t *)malloc(sizeof(node_t));
    newHead->next = *head;
    newHead->val = val;

    *head = newHead;
}

// pop the head of the list aka LRU
int pop(node_t **head)
{
    int newVal;
    node_t *newHead = (node_t *)malloc(sizeof(node_t));
    if ((*head)->next == NULL)
        return -1;

    newHead = (*head)->next;
    newVal = (*head)->val;
    free(*head);
    *head = newHead;

    return newVal;
}

int main()
{
}