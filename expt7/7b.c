#include <stdio.h>
#include <string.h>
#include <limits.h> // For INT_MAX

#define MAX 50

struct Block {
    int size;
    int isAllocated;
    int processId;
};

void bestFit(struct Block memoryBlocks[], int *numBlocks, int process[], int n);
void printMemoryState(struct Block memoryBlocks[], int numBlocks);

int main() {
    struct Block memoryBlocks[MAX];
    int process[MAX], m, n, i;

    int numBlocks;

    printf("\nEnter number of initial memory blocks (holes): ");
    scanf("%d", &m);
    numBlocks = m;

    printf("\nEnter size of each initial memory block:\n");
    for (i = 0; i < numBlocks; i++) {
        scanf("%d", &memoryBlocks[i].size);
        memoryBlocks[i].isAllocated = 0;
        memoryBlocks[i].processId = 0;
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &n);
    printf("\nEnter size of each process:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &process[i]);
    }

    bestFit(memoryBlocks, &numBlocks, process, n);
}

void printMemoryState(struct Block memoryBlocks[], int numBlocks) {
    for (int i = 0; i < numBlocks; i++) {
        printf("+------------------------------------------+\n"); 
        char content[50]; 

        if (memoryBlocks[i].isAllocated) {
            sprintf(content, "P%d (Allocated: %dK)", 
                   memoryBlocks[i].processId, 
                   memoryBlocks[i].size);
        } else {
            sprintf(content, "Free (Size: %dK)", 
                   memoryBlocks[i].size);
        }
        printf("[ %-40s ]\n", content); 
    }
    printf("+------------------------------------------+\n\n");
}


void bestFit(struct Block memoryBlocks[], int *numBlocks, int process[], int n) {
    int allocation[MAX];
    memset(allocation, 0, sizeof(allocation)); 

    printf("\n\n--- Initial Memory State ---\n");
    printMemoryState(memoryBlocks, *numBlocks);

    for (int i = 0; i < n; i++) {
        int processSize = process[i];
        int processId = i + 1;
        int isAllocated = 0;
        
        int bestFitIndex = -1;
        int minSizeFound = INT_MAX;

        // Best-fit search loop
        for (int j = 0; j < *numBlocks; j++) {
            if (!memoryBlocks[j].isAllocated && memoryBlocks[j].size >= processSize) {
                if (memoryBlocks[j].size < minSizeFound) {
                    minSizeFound = memoryBlocks[j].size;
                    bestFitIndex = j;
                }
            }
        }

        // Allocation logic (if a fit was found)
        if (bestFitIndex != -1) {
            int originalBlockSize = memoryBlocks[bestFitIndex].size; 
            int remainingSize = originalBlockSize - processSize;

            memoryBlocks[bestFitIndex].isAllocated = 1;
            memoryBlocks[bestFitIndex].size = processSize;
            memoryBlocks[bestFitIndex].processId = processId;

            if (remainingSize > 0) {
                for (int k = *numBlocks; k > bestFitIndex + 1; k--) {
                    memoryBlocks[k] = memoryBlocks[k - 1];
                }

                memoryBlocks[bestFitIndex + 1].size = remainingSize;
                memoryBlocks[bestFitIndex + 1].isAllocated = 0;
                memoryBlocks[bestFitIndex + 1].processId = 0;

                (*numBlocks)++;
            }
            
            allocation[i] = 1; 
            isAllocated = 1;

            printf("\n--- P%d (Size: %dK) allocated to block of size %dK ---\n", 
                   processId, processSize, originalBlockSize);
            printMemoryState(memoryBlocks, *numBlocks);

        }
        
        if (!isAllocated) {
            printf("\n--- Attempt failed for P%d (Size: %dK) ---\n", processId, processSize);
            printf("!!! P%d (Size: %dK) could NOT be allocated.\n", processId, processSize);
            printMemoryState(memoryBlocks, *numBlocks);
        }
    }

    printf("\n--- Final Allocation Report ---\n");
    int totalExternalFrag = 0;
    int largestHole = 0;
    
    for (int i = 0; i < *numBlocks; i++) {
        if (!memoryBlocks[i].isAllocated) {
            totalExternalFrag += memoryBlocks[i].size;
            if (memoryBlocks[i].size > largestHole) {
                largestHole = memoryBlocks[i].size;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (allocation[i] == 1) {
            printf("Process %d (Size: %dK) was allocated.\n", i + 1, process[i]);
        } else {
            printf("Process %d (Size: %dK) was NOT allocated.\n", i + 1, process[i]);
            if (process[i] <= totalExternalFrag && process[i] > largestHole) {
                printf("  -> This process failed due to External Fragmentation.\n");
            }
        }
    }
    
    printf("\nTotal External Fragmentation (sum of all holes): %dK\n", totalExternalFrag);
    printf("Largest Hole: %dK\n", largestHole);
}
