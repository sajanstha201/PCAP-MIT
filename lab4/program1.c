#include<stdio.h>
#include "mpi.h"
int fac(int n){
    int f=1;
    for(int i=1;i<=n;i++)
        f=f*i;
    return f;
}
void errHandler(int error){
    int err_string[256];
    int err_class,err_length;
    if(error!=MPI_SUCCESS){
        MPI_Error_class(error,&err_class);
        MPI_Error_string(error,err_string,&err_length);
        printf("Error Class: %d Error String: %s\n",err_class,err_string);
    }
}
int main(int argc, char * argv[]){
    int rank,size;
    MPI_Init(&argc,&argv);
    int err;
    MPI_Comm_set_errhandler(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
    err=MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    err=MPI_Comm_size(MPI_COMM_WORLD,&size);
    errHandler(err);
    int factorial=fac(rank+1);
    int result;
    MPI_Reduce(&factorial,&result,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    printf("Rank: %d Factorial: %d\n",rank,factorial);
    if(rank==0){
        printf("The sum of factorial: %d\n",result);
    }

    MPI_Finalize();
}