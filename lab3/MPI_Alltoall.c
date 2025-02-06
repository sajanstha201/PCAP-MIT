#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"
int main(int argc, char * argv[]){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    int arr[4]={rank,rank,rank,rank};
    int recv[4];
    MPI_Alltoall(arr,1,MPI_INT,recv,1,MPI_INT,MPI_COMM_WORLD);
    printf("Rank : %d\n",rank);
    for(int i=0;i<4;i++){
        printf("%d ",recv[i]);
    }   
    printf("\n");
    MPI_Finalize();
}