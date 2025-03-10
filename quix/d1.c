#include <mpi.h>

#include <stdio.h>

int main(int argc, char *argv[]) {

    int rank, size, value, sum;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    value = rank;

    MPI_Reduce(&value, &sum, 1, MPI_INT, MPI_SUM, 0,     MPI_COMM_WORLD);

    if (rank == 0) {

        printf("Sum of ranks: %d\n", sum);

    }

    MPI_Finalize();

    return 0;

}