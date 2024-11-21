// Created by: Hunter Antal
// Created on: 15/11/2024
// Student ID: 1181729
#include <stdio.h>
#include <stdlib.h>


#define MAX 10

void loadPages(int program[], int size, int storage[], int memory[]);

int main()
{
    // this is a simple program that simulates the memory management of a computer system
    // this is an idealized version of the memory management system of a computer where there are enough frames for each page

    // Secoundary storage each element represents a page in the main storage
    int storage[MAX] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // program 1 (word) uses 3 pages
    int program1[3] = {1, 2, 3};

    // program 2 (excel) uses 4 pages
    int program2[4] = {4, 5, 6, 7};

    // program 3 (power point) uses 3 pages
    int program3[3] = {8, 9, 10};

    // Main memory containing 10 frames
    int memory[MAX] = {0};

    // holds users choice of program
    int program = -1;
    while (program != 0)
    {
        // ask user which program to load
        printf("Programs available:\n");
        printf("0. Close\n");
        printf("1. Word\n");
        printf("2. Excel\n");
        printf("3. Power Point\n");
        printf("Enter program to load: ");
        scanf("%d", &program);

        // switch case to load program
        switch (program)
        {
        case 1:
            loadPages(program1, sizeof(program1) / sizeof(program1[0]), storage, memory);
            break;
        case 2:
            loadPages(program2, sizeof(program2) / sizeof(program2[0]), storage, memory);
            break;
        case 3:
            loadPages(program3, sizeof(program3) / sizeof(program3[0]), storage, memory);
            break;
        case 0:
            printf("\n");
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("Closing program\n");
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("\n");
            break;
        default:
            printf("\n");
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("Invalid Input: %d\n", program);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
            printf("\n");
            break;
        }
    }

    return 0;
}

// function to load a program into memory
void loadPages(int program[], int size, int storage[], int memory[])
{

    if (size > MAX)
    {
        printf("Program size is greater than main memory size\n");
        return;
    }
    else
    {
        // Load pages from storage into main memory
        for (int i = 0; i < size; i++)
        {
            memory[program[i] - 1] = storage[program[i] - 1];
        }
    }

    // print main memory
    printf("\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Main memory: ");
    printf("[");
    for (int i = 0; i < MAX; i++)
    {
        printf("%d", memory[i]);
        if (i != MAX - 1)
            printf(", ");
    }
    printf("]");
    printf("\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n");
}