#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mpi.h"
int main(int argc,char * argv[]){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_rank(MPI_COMM_WORLD,&size);
    int result=0;
    MPI_Reduce(&rank,&result,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0){
        printf("The result is %d\n",result);
    }
    MPI_Finalize();
}