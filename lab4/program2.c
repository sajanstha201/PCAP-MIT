#include<stdio.h>
#include "mpi.h"
void errorHandler(int error_code){
    int len,error_class;
    char error_string[256];
    if(error_class!=MPI_SUCCESS){
        MPI_Error_class(error_code,&error_class);
        MPI_Error_string(error_code,error_string,&len);
    }
}
int main(int argc, char *argv[]){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_set_errhandler(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
    int error_code;
    error_code=(MPI_COMM_WORLD,&rank);
    error_code=(MPI_COMM_WORLD,&size);

}