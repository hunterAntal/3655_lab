#include <stdio.h>  // Include standard input/output header file

int main() {
    int nb, nf, i, j;  // Declare variables for number of blocks, number of files, and loop counters
    
    // Prompt the user to enter the number of memory blocks
    printf("Enter the number of memory blocks: ");
    scanf("%d", &nb);  // Read the number of memory blocks from user input
    
    int blockSize[nb], blockFlag[nb];  // Arrays to store block sizes and their allocation status
    
    // Initialize all blocks as free (blockFlag = 0)
    for(i = 0; i < nb; i++) {
        blockFlag[i] = 0;  // Set blockFlag[i] to 0 indicating block is free
    }
    
    // Prompt the user to enter the size of each memory block
    printf("Enter the size of each memory block:\n");
    for(i = 0; i < nb; i++) {
        printf("Size of block %d: ", i + 1);  // Display block number
        scanf("%d", &blockSize[i]);  // Read size of block i
    }
    
    // Prompt the user to enter the number of files/processes
    printf("Enter the number of files/processes: ");
    scanf("%d", &nf);  // Read the number of files from user input
    
    int fileSize[nf], allocation[nf];  // Arrays to store file sizes and allocation details
    
    // Initialize all files as unallocated (allocation = -1)
    for(i = 0; i < nf; i++) {
        allocation[i] = -1;  // Set allocation[i] to -1 indicating file is not allocated
    }
    
    // Prompt the user to enter the size of each file/process
    printf("Enter the size of each file/process:\n");
    for(i = 0; i < nf; i++) {
        printf("Size of file %d: ", i + 1);  // Display file number
        scanf("%d", &fileSize[i]);  // Read size of file i
    }
    
    // Implement the Best Fit algorithm for memory allocation
    for(i = 0; i < nf; i++) {  // Loop through each file
        int bestIdx = -1;  // Initialize bestIdx to -1 (no suitable block found yet)
        for(j = 0; j < nb; j++) {  // Loop through each memory block
            // Check if block is free and can accommodate the file
            if(blockFlag[j] == 0 && blockSize[j] >= fileSize[i]) {
                // If it's the first suitable block or a better fit is found
                if(bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;  // Update bestIdx to current block index
                }
            }
        }
        // If a suitable block was found
        if(bestIdx != -1) {
            allocation[i] = bestIdx;  // Allocate block to file
            blockFlag[bestIdx] = 1;  // Mark block as occupied
        }
    }
    
    // Display the allocation results
    printf("\nFile No.\tFile Size\tBlock No.\n");
    for(i = 0; i < nf; i++) {
        printf("%d\t\t%d\t\t", i + 1, fileSize[i]);  // Display file number and size
        if(allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);  // Display allocated block number (1-based index)
        } else {
            printf("Not Allocated\n");  // Indicate file was not allocated
        }
    }
    
    return 0;  // End of program
}
