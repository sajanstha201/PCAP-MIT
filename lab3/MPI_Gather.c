#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"
int main(int argc, char * argv[]){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int arr[4];
    MPI_Gather(&rank,1,MPI_INT,arr,1,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0){
        int i;
        printf("The value in the array are: ");
        for(i=0;i<4;i++){
            printf("%d ",arr[i]);
        }
    }
    MPI_Finalize();
}