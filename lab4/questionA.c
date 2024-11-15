#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
    // this is a simple program that simulates the memory management of a computer system
    // this is an idealized version of the memory management system of a computer where there are enough frames for each page

    // Secoundary storage each element represents a page in the main storage
    int storage[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // program 1 (word) uses 3 pages
    int program1[3] = {1, 2, 3};

    // program 2 (excel) uses 4 pages
    int program2[4] = {4, 5, 6, 7};

    // program 3 (power point) uses 3 pages
    int program3[3] = {8, 9, 10};

    // Main memory containing 10 frames
    int memory[10] = {0};


    


    return 0;
}

// function to load a program into memory
void loadPages(int program[], int storage[], int memory[]){
    // calculate size of program in pages
}