#include <stdio.h>
#include <string.h> 

#define MAX 25

struct Allocation {
    int processId;
    int processSize;
};

struct Block {
    int originalSize;
    int freeSpace;
    struct Allocation allocatedProcs[MAX]; 
    int numProcsAllocated;                 
};

void worstFit(struct Block memoryBlocks[], int process[], int m, int n);
void printMemoryState(struct Block memoryBlocks[], int m);

int main() {
    struct Block memoryBlocks[MAX];
    int process[MAX], m, n, i;

    printf("\nEnter number of memory blocks: ");
    scanf("%d", &m);

    printf("\nEnter size of each memory block:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &memoryBlocks[i].originalSize);
        memoryBlocks[i].freeSpace = memoryBlocks[i].originalSize;
        memoryBlocks[i].numProcsAllocated = 0;
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter size of each process:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &process[i]);
    }

    worstFit(memoryBlocks, process, m, n);
    return 0;
}

void printMemoryState(struct Block memoryBlocks[], int m) {
    for (int i = 0; i < m; i++) {
        printf("+------------------------------------------+\n");
        printf("[ Total Size: %-28d ]\n", memoryBlocks[i].originalSize);

        char content[256] = "";
        char temp[50];
        for (int j = 0; j < memoryBlocks[i].numProcsAllocated; j++) {
            sprintf(temp, "P%d(%dK) | ",
                    memoryBlocks[i].allocatedProcs[j].processId,
                    memoryBlocks[i].allocatedProcs[j].processSize);
            strcat(content, temp);
        }
        sprintf(temp, "Free: %dK", memoryBlocks[i].freeSpace);
        strcat(content, temp);
        printf("[ %-40s ]\n", content);
    }
    printf("+------------------------------------------+\n\n");
}

void worstFit(struct Block memoryBlocks[], int process[], int m, int n) {
    int allocation[MAX];
    int i, j;

    for (i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    printf("\n\n--- Initial Memory State ---\n");
    printMemoryState(memoryBlocks, m);

    for (i = 0; i < n; i++) { 
        
        int worstFitIndex = -1;
        for (j = 0; j < m; j++) {
            if (memoryBlocks[j].freeSpace >= process[i]) {
                if (worstFitIndex == -1) {
                    worstFitIndex = j;
                } else if (memoryBlocks[j].freeSpace > memoryBlocks[worstFitIndex].freeSpace) {
                    worstFitIndex = j;
                }
            }
        }

        if (worstFitIndex != -1) {
            allocation[i] = worstFitIndex;

            int procIndex = memoryBlocks[worstFitIndex].numProcsAllocated;
            memoryBlocks[worstFitIndex].allocatedProcs[procIndex].processId = i + 1;
            memoryBlocks[worstFitIndex].allocatedProcs[procIndex].processSize = process[i];
            memoryBlocks[worstFitIndex].numProcsAllocated++;

            memoryBlocks[worstFitIndex].freeSpace -= process[i];
        }
        printf("\n--- Memory State after attempting to allocate P%d (Size: %d) ---\n", i + 1, process[i]);
        printMemoryState(memoryBlocks, m);
    }
    printf("\n--- Detailed Allocation Report ---\n");
    for (i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d of size %d is allocated to block %d of size %d\n",
                   i + 1, process[i], allocation[i] + 1, memoryBlocks[allocation[i]].originalSize);
        } else {
            printf("Process %d of size %d is not allocated\n", i + 1, process[i]);
        }
    }
    printf("\n");
}