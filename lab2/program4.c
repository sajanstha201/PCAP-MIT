#include<stdio.h>
#include<mpi.h>
int main(int argc, char * argv[]){
    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int num;
    MPI_Status status;
    if(rank==0){
        printf("Enter a value: \n");
        scanf("%d",&num);
        printf("Rank %d, value: %d\n",rank,num);
        num++;
        MPI_Send(&num,1,MPI_INT,1,0,MPI_COMM_WORLD);

        MPI_Recv(&num,1,MPI_INT,size-1,0,MPI_COMM_WORLD,&status);
    }
    else if(rank==size-1){
        MPI_Recv(&num,1,MPI_INT,size-2,0,MPI_COMM_WORLD,&status);
        printf("Rank %d, value: %d\n",rank,num);
        num++;
        MPI_Send(&num,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }
    else{
        MPI_Recv(&num,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
        printf("Rank %d, value: %d\n",rank,num);
        num++;
        MPI_Send(&num,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
    }
    MPI_Finalize();
}