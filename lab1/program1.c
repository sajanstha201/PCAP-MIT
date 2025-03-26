#include<stdio.h>
#include<mpi.h>
#include<math.h>
int main(int argc, char *argv[]){
    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    printf("Rank : %d Valeu: %f\n",rank, pow(2,rank));
    MPI_Finalize();
}