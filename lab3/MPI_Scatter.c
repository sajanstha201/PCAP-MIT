#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mpi.h"
int main(int argc, char * argv[]){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int arr[4]={0,1,2,3};
    int recv;
    MPI_Scatter(arr,1,MPI_INT,&recv,1,MPI_INT,0,MPI_COMM_WORLD);
    printf("rank %d value : %d\n",rank,recv);
    MPI_Finalize();
}