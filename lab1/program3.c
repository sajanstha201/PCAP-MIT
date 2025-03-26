#include<stdio.h>
#include<mpi.h>
int main(int argc, char * argv[]){
    MPI_Init(&argc, &argv);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int a=5,b=9;
    if(rank==0){
        printf("%d + %d = %d\n",a,b,a+b);
    }
    if(rank==1){
        printf("%d - %d = %d\n",a,b,a-b);
    }
    if(rank==2){
        printf("%d * %d = %d\n",a,b,a*b);
    }
    if(rank==3){
        printf("%d / %d = %d\n",a,b,a/b);
    }
    MPI_Finalize();
}