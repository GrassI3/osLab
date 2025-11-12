#include<stdio.h>
#define MAX 25
void firstFit(int memory[],int process[],int m,int n);
int main(){
    int memory[MAX],process[MAX],m,n,i;
    printf("\nEnter number of memory blocks: ");
    scanf("%d",&m);
    printf("\nEnter size of each memory block:\n");
    for(i=0;i<m;i++){
        printf("Block %d: ",i+1);
        scanf("%d",&memory[i]);
    }
    printf("\nEnter number of processes: ");
    scanf("%d",&n);
    printf("\nEnter size of each process:\n");
    for(i=0;i<n;i++){
        printf("Process %d: ",i+1);
        scanf("%d",&process[i]);
    }
    firstFit(memory,process,m,n);
}
void firstFit(int memory[],int process[],int m,int n){
    int allocation[MAX],temp[MAX],i,j;
    for(i=0;i<n;i++){allocation[i]=-1; }
    for(i=0;i<m;i++){temp[i]=memory[i]; }
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(memory[j]>=process[i]){
                allocation[i]=j;
                memory[j]-=process[i];
                break;
            }
        }
    }
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for(int i=0;i<n;i++){
        printf(" %d\t\t %d\t\t",i+1,process[i]);
        if(allocation[i]!=-1){
            printf("%d\n",allocation[i]+1);
        }
        else{
            printf("Not Allocated\n");
        }
    }
    for(i=0;i<n;i++){
        if(allocation[i]!=-1){
            printf("\nProcess %d of size %d is allocated to block %d of size %d",i+1,process[i],allocation[i]+1,temp[allocation[i]]);
        }
        else{
            printf("\nProcess %d of size %d is not allocated",i+1,process[i]);
        }
    }
    printf("\n");
}
