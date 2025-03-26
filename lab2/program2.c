#include<stdio.h>
#include"mpi.h"
int main(int argc, char *argv[]){
    MPI_Init(&argc,&argv);
    MPI_Status status;
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    if(rank==0){
        int n=5;
        for(int i=1;i<size;i++){
            MPI_Send(&n,1,MPI_INT,i,0,MPI_COMM_WORLD);
        }
    }
    else{
        int r;
        MPI_Recv(&r,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        printf("Rank: %d Value; %d\n",rank,r);
    }
    MPI_Finalize();
}