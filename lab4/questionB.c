#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void add(node_t *head, int val)
{
    if (head == NULL)
    {
        perror("Head is NULL in add()");
        exit(EXIT_FAILURE);
    }

    node_t *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = (node_t *)malloc(sizeof(node_t));
    if (current->next == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    current->next->val = val;
    current->next->next = NULL;
}

void push(node_t **head, int val)
{
    node_t *newHead = (node_t *)malloc(sizeof(node_t));
    if (newHead == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    newHead->next = *head;
    newHead->val = val;

    *head = newHead;
}

int pop(node_t **head)
{
    if (*head == NULL)
    {
        printf("List is empty, nothing to pop.\n");
        return -1;
    }

    int val = (*head)->val;
    node_t *temp = *head;
    *head = (*head)->next;
    free(temp);

    return val;
}

int search(node_t *head, int val)
{
    node_t *current = head;

    while (current != NULL)
    {
        if (current->val == val)
        {
            return 1; // Hit
        }
        current = current->next;
    }

    return 0; // Page fault
}

int main()
{
    int hits = 0;
    int pageFaults = 0;
    int frameCount = 0;
    int pageReference = 0;
    float hitRatio = 0.0;

    printf("How many frames would you like to use?: ");
    int numberOfFrames = 0;
    scanf("%d", &numberOfFrames);

    printf("Enter page sequence separated by spaces (end with newline): ");
    char input[1000];
    int *arr = NULL;
    int n = 0;

    getchar(); // Clear newline left by scanf
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        perror("Failed to read input");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(input, " ");
    while (token != NULL)
    {
        arr = realloc(arr, (n + 1) * sizeof(int));
        if (arr == NULL)
        {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        arr[n++] = atoi(token);
        token = strtok(NULL, " ");
    }

    // Initialize the linked list
    node_t *head = (node_t *)malloc(sizeof(node_t));
    if (head == NULL)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    head->val = -1;
    head->next = NULL;

    // Simulate page replacement
    for (int i = 0; i < n; i++)
    {
        pageReference++;
        if (search(head, arr[i]))
        {
            hits++;
        }
        else
        {
            pageFaults++;
            if (frameCount < numberOfFrames)
            {
                add(head, arr[i]);
                frameCount++;
            }
            else
            {
                pop(&head);
                add(head, arr[i]);
            }
        }
    }

    hitRatio = (float)hits / pageReference;
    printf("Number of hits: %d\n", hits);
    printf("Number of page faults: %d\n", pageFaults);
    printf("Hit ratio: %.2f\n", hitRatio);

    free(arr);

    return 0;
}
