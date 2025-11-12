#include<stdio.h>
#define MAX 25
void worstFit(int memory[],int process[],int m,int n);
int main(){
    int memory[MAX],process[MAX],m,n,i;
    printf("\nEnter number of memory blocks: ");
    scanf("%d",&m);
    printf("\nEnter size of each memory block:\n");
    for(i=0;i<m;i++){
        printf("Block %d: ",i+1);
        scanf("%d",&memory[i]);
    }printf("\nEnter number of processes: ");
    scanf("%d",&n);
    printf("\nEnter size of each process:\n");
    for(i=0;i<n;i++){ printf("Process %d: ",i+1);
        scanf("%d",&process[i]);
    }
    worstFit(memory,process,m,n);
}
void worstFit(int memory[],int process[],int m,int n){
    int allocation[MAX],temp[MAX],i,j,idx;
    for(i=0;i<n;i++){allocation[i]=-1; }
    for(i=0;i<m;i++) temp[i]=memory[i];
    for(i=0;i<n;i++){
        idx=-1;
        for(j=0;j<m;j++){
            if(memory[j]>=process[i]){ if(idx==-1 || memory[j]>memory[idx]) idx=j;}
        }
        if(idx!=-1){
            allocation[i]=idx;
            memory[idx]-=process[i];
        }
    }
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for(int i=0;i<n;i++){
        printf(" %d\t\t %d\t\t",i+1,process[i]);
        if(allocation[i]!=-1){ printf("%d\n",allocation[i]+1); }
        else{printf("Not Allocated\n");}
    }
    for(i=0;i<n;i++){
        if(allocation[i]!=-1){
            printf("\nProcess %d of size %d is allocated to block %d of size %d",i+1,process[i],allocation[i]+1,temp[allocation[i]]);
        }
        else{
            printf("\nProcess %d of size %d is not allocated",i+1,process[i]);
        }
    }printf("\n");
}
