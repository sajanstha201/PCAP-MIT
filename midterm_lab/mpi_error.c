#include<stdio.h>
#include"mpi.h"
void errorHandler(int error_code){
    int error_class,error_len;
    char error_string[100];
    if(error_code!=MPI_SUCCESS){
        MPI_Error_string(error_code,error_string,&error_len);
        MPI_Error_class(error_code,&error_class);
        printf("The error class is %d error stingi is %s\n",error_class,error_string);
    }
}
int main(int argc, char *argv[]){
    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Comm_set_errhandler(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
    int err;
    err=MPI_Comm_rank(4,&rank);
    errorHandler(err);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Finalize();
}