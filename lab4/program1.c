#include<stdio.h>
#include "mpi.h"
int fac(int n){
    int f=1;
    for(int i=1;i<=n;i++)
        f=f*i;
    return f;
}
int main(int argc, char * argv[]){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int factorial=fac(rank+1);
    int result;
    MPI_Reduce(&fac,&result,1,MPI_INT,MPI_SUM,0,rank,MPI_COMM_WORLD);
    if(rank==0){
        printf("The sum of factorial: %d\n",result);
    }


}