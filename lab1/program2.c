#include<stdio.h>
#include<mpi.h>
int main(int argc, char *argv[]){
    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank%2==0){
        printf("Rank : %d Hello\n",rank);
    }
    else 
        printf("Rank: %d World\n",size);
    MPI_Finalize();
}