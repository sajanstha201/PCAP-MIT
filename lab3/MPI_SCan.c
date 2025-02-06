#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"
void error_handler(int error_code){
    MPI_Error_class(error_code,&error_class);
    char string[100];
    int len;
    MPI_Error_string(error_code,string,&len);
    printf("%d %s %d\n",error_class,string,len);
}

int main(int argc,char *argv[]){
    int rank;
    MPI_Init(&argc,&argv);
    int c=3;
    int error_code=MPI_Comm_rank(c,&rank); 
        int error_class;
    error_handler(error_class);
    int result;
    MPI_Scan(&rank,&result,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    printf("Rank: %d valeu: %d\n",rank,result);
    MPI_Finalize();

}