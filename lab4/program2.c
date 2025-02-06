#include<stdio.h>
#include "mpi.h"
void errorHandler(int error_code){
    int len,error_class;
    char error_string[256];
    if(error_code!=MPI_SUCCESS){
        MPI_Error_class(error_code,&error_class);
        MPI_Error_string(error_code,error_string,&len);
        printf("Error Class: %d Error String: %s\n",error_class,error_string);
    }
}
int main(int argc, char *argv[]){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_set_errhandler(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
    int error_code;
    error_code=MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    error_code=MPI_Comm_size(MPI_COMM_WORLD,&size);
    errorHandler(error_code);
    if(size!=3){
        printf("Need 3 process \n");
        MPI_Finalize();
        return 0;
    }
    int arr[9];
    int element;
    if(rank==0){
        printf("Enter the element of arr:\n");
        for(int i=0;i<9;i++)
            scanf("%d",&arr[i]);
        printf("Enter the element to search:\n ");
        scanf("%d",&element);
    }
    int got_arr[3];
    MPI_Bcast(&element,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(arr,3,MPI_INT,got_arr,3,MPI_INT,0,MPI_COMM_WORLD);
    int count=0;
    for(int i=0;i<3;i++){
        if(element==got_arr[i])
            count++;
    }
    int result;
    MPI_Reduce(&count,&result,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0){
        printf("The number of element is %d\n",result);
    }
    MPI_Finalize();
}