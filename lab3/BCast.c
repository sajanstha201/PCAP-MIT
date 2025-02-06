#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mpi.h"
int main(int argc, char *argv[]){
    int rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int a;
    if(rank==0){
        printf("Enter a integer:\n");
        scanf("%d",&a);
    }
    MPI_Bcast(&a,1,MPI_INT,0,MPI_COMM_WORLD);
    printf("Process : %d value: %d\n",rank,a);
    MPI_Finalize();
}