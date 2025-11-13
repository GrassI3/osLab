#include <stdio.h>
#include <string.h> 

#define MAX 50 

struct Block {
    int size;         
    int isAllocated;  
    int processId;    
};

void worstFit(struct Block memoryBlocks[], int *numBlocks, int process[], int n);
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

    worstFit(memoryBlocks, &numBlocks, process, n);
    
    return 0;
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


void worstFit(struct Block memoryBlocks[], int *numBlocks, int process[], int n) {
    int allocation[MAX];
    memset(allocation, 0, sizeof(allocation)); 

    printf("\n\n--- Initial Memory State ---\n");
    printMemoryState(memoryBlocks, *numBlocks);

    for (int i = 0; i < n; i++) {
        int processSize = process[i];
        int processId = i + 1;
        int isAllocated = 0;
        
        int worstFitIndex = -1;
        int maxSizeFound = -1; // Start at -1 (or 0)

        // Worst-fit search loop
        for (int j = 0; j < *numBlocks; j++) {
            if (!memoryBlocks[j].isAllocated && memoryBlocks[j].size >= processSize) {
                // Find the largest block
                if (memoryBlocks[j].size > maxSizeFound) { 
                    maxSizeFound = memoryBlocks[j].size;
                    worstFitIndex = j;
                }
            }
        }

        // Allocation logic (if a fit was found)
        if (worstFitIndex != -1) {
            int originalBlockSize = memoryBlocks[worstFitIndex].size; 
            int remainingSize = originalBlockSize - processSize;

            memoryBlocks[worstFitIndex].isAllocated = 1;
            memoryBlocks[worstFitIndex].size = processSize;
            memoryBlocks[worstFitIndex].processId = processId;

            if (remainingSize > 0) {
                for (int k = *numBlocks; k > worstFitIndex + 1; k--) {
                    memoryBlocks[k] = memoryBlocks[k - 1];
                }

                memoryBlocks[worstFitIndex + 1].size = remainingSize;
                memoryBlocks[worstFitIndex + 1].isAllocated = 0;
                memoryBlocks[worstFitIndex + 1].processId = 0;

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