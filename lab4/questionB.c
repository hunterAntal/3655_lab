#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a linked list node
typedef struct node
{
    int val;            // Value stored in the node
    struct node *next;  // Pointer to the next node
} node_t;

// Function to print the entire linked list
void print_list(node_t *head)
{
    printf("\n");
    printf("Printing List:\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    node_t *current = head;

    while (current != NULL) // Traverse the list
    {
        printf("%d\n", current->val); // Print the value of each node
        current = current->next;     // Move to the next node
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

// Function to add a new node at the end of the list
void add(node_t *head, int val)
{
    if (head == NULL) // Check if head is NULL
    {
        perror("Head is NULL in add()");
        exit(EXIT_FAILURE);
    }

    node_t *current = head;
    // Traverse to the last node
    while (current->next != NULL)
    {
        current = current->next;
    }

    // Allocate memory for the new node
    current->next = (node_t *)malloc(sizeof(node_t));
    if (current->next == NULL) // Check for memory allocation failure
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize the new node
    current->next->val = val;
    current->next->next = NULL;
}

// Function to add a node at the beginning of the list
void push(node_t **head, int val)
{
    // Allocate memory for the new head node
    node_t *newHead = (node_t *)malloc(sizeof(node_t));
    if (newHead == NULL) // Check for memory allocation failure
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Set the new head's value and point it to the current head
    newHead->next = *head;
    newHead->val = val;

    *head = newHead; // Update the head pointer
}

// Function to remove the head of the list (LRU implementation)
int pop(node_t **head)
{
    if (*head == NULL) // Check if the list is empty
    {
        printf("List is empty, nothing to pop.\n");
        return -1; // Return error value
    }

    int val = (*head)->val; // Store the value of the head
    node_t *temp = *head;   // Temporarily hold the head
    *head = (*head)->next;  // Move the head pointer to the next node
    free(temp);             // Free the old head node

    return val; // Return the value of the removed node
}

// Function to search for a value in the linked list
int search(node_t *head, int val)
{
    node_t *current = head;

    while (current != NULL) // Traverse the list
    {
        if (current->val == val) // Check for a match
        {
            return 1; // Hit
        }
        current = current->next; // Move to the next node
    }

    return 0; // Page fault if not found
}

int main()
{
    int hits = 0;            // Count of hits
    int pageFaults = 0;      // Count of page faults
    int frameCount = 0;      // Current number of frames in use
    int pageReference = 0;   // Total number of page references
    float hitRatio = 0.0;    // Hit ratio

    // Prompt user for the number of frames
    printf("How many frames would you like to use?: ");
    int numberOfFrames = 0;
    scanf("%d", &numberOfFrames);

    // Prompt user for the page sequence
    printf("Enter page sequence separated by spaces (end with newline): ");
    char input[1000]; // Buffer for user input
    int *arr = NULL;  // Dynamic array to store the page sequence
    int n = 0;        // Number of elements in the page sequence

    getchar(); // Clear newline left by scanf
    if (fgets(input, sizeof(input), stdin) == NULL) // Read input as a line
    {
        perror("Failed to read input");
        exit(EXIT_FAILURE);
    }

    // Tokenize the input and convert to integers
    char *token = strtok(input, " ");
    while (token != NULL)
    {
        arr = realloc(arr, (n + 1) * sizeof(int)); // Dynamically resize the array
        if (arr == NULL) // Check for memory allocation failure
        {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        arr[n++] = atoi(token); // Convert token to integer
        token = strtok(NULL, " ");
    }

    // Initialize the linked list
    node_t *head = (node_t *)malloc(sizeof(node_t));
    if (head == NULL) // Check for memory allocation failure
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    head->val = -1;  // Dummy value for the head
    head->next = NULL;

    // Simulate the page replacement algorithm
    for (int i = 0; i < n; i++)
    {
        pageReference++; // Increment page reference count
        if (search(head, arr[i])) // Check if the page is already in memory
        {
            hits++; // Increment hits if found
        }
        else
        {
            pageFaults++; // Increment page faults if not found
            if (frameCount < numberOfFrames) // If frames are available
            {
                add(head, arr[i]); // Add the page to memory
                frameCount++;      // Increment the frame count
            }
            else // If no frames are available, remove LRU and add new page
            {
                pop(&head);
                add(head, arr[i]);
            }
        }
    }

    // Calculate and display the hit ratio
    hitRatio = (float)hits / pageReference;
    printf("Number of hits: %d\n", hits);
    printf("Number of page faults: %d\n", pageFaults);
    printf("Hit ratio: %.2f\n", hitRatio);

    free(arr); // Free the dynamic array
    return 0;
}
