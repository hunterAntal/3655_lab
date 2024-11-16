#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
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
    while (current->next != NULL)
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

// search will return 1 if hit and 0 if page fault
int search(node_t *head, int val)
{
    node_t *current = (node_t *)malloc(sizeof(node_t));

    current = head;

    while (current->next != NULL)
    {
        // if there is a hit return 1
        if (current->val == val)
        {
            return 1;
        }
        // move to next node
        current = current->next;

        // if there is a hit return 1
        if (current->val == val)
        {
            return 1;
        }
    }
    // page fault return 0
    return 0;
}


int main()
{

    int hits = 0;
    int pageFaults = 0;
    int frameCount = 0;
    int pageReference = 0;
    float hitRatio = 0.0;

    //int numberOfFrames = 3;
    //int pageSeq[MAX] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3};

    node_t *head = NULL;
    head = (node_t *)malloc(sizeof(node_t));
    head->val = -1;
    head->next = NULL;

    // Take user input for number of frames and page sequence
    printf("How many frames would you like to use?:");
    int numberOfFrames = 0;
    scanf("%d", &numberOfFrames);
    char input[1000]; // Buffer for user input
    int *arr = NULL;   // Dynamic array to store numbers
    int n = 0;         // Number of elements

    printf("Enter numbers separated by spaces: ");
    fgets(input, sizeof(input), stdin); // Read entire line of input

    // Tokenize the string and convert to integers
    char *token = strtok(input, " ");
    while (token != NULL)
    {
        arr = realloc(arr, (n + 1) * sizeof(int)); // Resize array
        if (arr == NULL)
        {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        arr[n++] = atoi(token); // Convert string to integer
        token = strtok(NULL, " ");
    }

    printf("You entered: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Convert dynamic array to static array
    int pageSeq[n];
    for (int i = 0; i < n; i++)
    {
        pageSeq[i] = arr[i];
    }

    // Loop through the page sequence
    for (int i = 0; i < (sizeof(pageSeq) / sizeof(pageSeq[0])); i++)
    {
        // if page hit then increment hits
        pageReference++;
        if (search(head, pageSeq[i]) == 1)
        {
            hits++;
        }
        else
        {
            // page fault so we must check to see if there us a spare frame
            pageFaults++;
            if (frameCount < numberOfFrames)
            {
                add(head, pageSeq[i]);
                frameCount++;
            }
            else // if there is no free frames remove LRU frame then use it
            {
                pop(&head);
                add(head, pageSeq[i]);
            }
        }
    }

    hitRatio = (float)hits / pageReference;
    printf("Number of hits: %d\n", hits);
    printf("Number of page faults: %d\n", pageFaults);
    printf("Hit ratio: %.2f\n", hitRatio);
}