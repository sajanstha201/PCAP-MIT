#include<stdio.h>
#include<mpi.h>
int main(int argc, char * argv[]){
    MPI_Init(&argc,&argv);
    MPI_Status status;
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    char buffer[100];
    int bsize=MPI_BSEND_OVERHEAD+100;
    MPI_Buffer_attach(buffer,bsize);
    if(rank==0){
        int arr[size-1];
        printf("Enter the vlaue %d\n",size-1);
        for(int i=0;i<size-1;i++)
            scanf("%d",&arr[i]);
        for(int i=1;i<size;i++){
            MPI_Bsend(arr+i-1,1,MPI_INT,i,0,MPI_COMM_WORLD);
        }
        MPI_Buffer_detach(buffer,&bsize);
    }
    else{
        int r;
        MPI_Recv(&r,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        if(rank%2==0){
            printf("Rank : %d Squared: %d\n",rank,r*r);
        }
        else 
            printf("Rank: %d cube: %d\n",rank,r*r*r);
    }
    MPI_Finalize();
}