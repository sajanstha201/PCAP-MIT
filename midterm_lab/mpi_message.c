#include<stdio.h>
#include"mpi.h"
int main(int argc, char *argv[]){
    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Status status;
    int result;
    if(rank==0){
        printf("Enter a value:\n");
        int num;
        scanf("%d",&num);
        char buffer[100];
        int bsize=MPI_BSEND_OVERHEAD+100;
        MPI_Buffer_attach(buffer,bsize);
        MPI_Bsend(&num,1,MPI_INT,1,0,MPI_COMM_WORLD);
        MPI_Ssend(&num,1,MPI_INT,2,1,MPI_COMM_WORLD);
        MPI_Send(&num,1,MPI_INT,3,2,MPI_COMM_WORLD);
        MPI_Buffer_detach(buffer,&bsize);
    }
    else if(rank==1){
        MPI_Recv(&result,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        printf("Rank: %d Value: %d\n",rank,result);
    }
    else if(rank==2){
        MPI_Recv(&result,1,MPI_INT,0,1,MPI_COMM_WORLD,&status);
        printf("Rank: %d Value: %d\n",rank,result);
    }
    else if(rank==3){
        MPI_Recv(&result,1,MPI_INT,0,2,MPI_COMM_WORLD,&status);
        printf("Rank: %d Value: %d\n",rank,result);
    }
    MPI_Finalize();
}
