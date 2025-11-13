#include <stdio.h>
#include <stdlib.h>
#define MAX 50

int main() {
    int n, i, totalHeadMovement = 0, requests[MAX], head;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("Enter Request Queue: ");
    for (i = 0; i < n; i++)
        scanf("%d", &requests[i]);
    printf("Enter Current Head Position: ");
    scanf("%d", &head);
    
    printf("\n--- FCFS Disk Scheduling Algorithm ---\n");
    printf("--------------------------------------------------\n");
    printf("From\t\tTo\t\tDistance\n");
    printf("--------------------------------------------------\n");
    int currentHead = head;
    for (i = 0; i < n; i++) {
        int distance = abs(currentHead - requests[i]);
        printf("%d\t\t%d\t\t%d\n", currentHead, requests[i], distance);
        totalHeadMovement += distance;
        currentHead = requests[i];
    }
    printf("--------------------------------------------------\n");
    printf("\nSeek Sequence: %d", head);
    for (i = 0; i < n; i++)
        printf(" -> %d", requests[i]);
    printf("\nTotal Number of Head Movements: %d\n", totalHeadMovement);
    return 0;
}