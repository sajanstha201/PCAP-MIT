#include <mpi.h>
#include <stdio.h>
int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, value = 1;
     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
          MPI_Scan(&value, &value, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    printf("Rank %d, Value: %d\n", rank, value);
     MPI_Finalize();
     return 0;
}