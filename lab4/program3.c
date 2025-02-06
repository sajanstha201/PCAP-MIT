#include<stdio.h>
#include "mpi.h"
void errorHandler(int error_code){
    if(error_code!=MPI_SUCCESS){
        int len,error_class;
        char error_str[256];
        MPI_Error_class(error_class,&error_class);
        MPI_Error_string(error_class,error_str,&len);
        printf("Error class: %d Error string: %s\n",error_class,error_str);
    }
}
int main(int argc, char * argv[]){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_set_errhandler(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
    int error_code;
    error_code=MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    error_code=MPI_Comm_size(MPI_COMM_WORLD,&size);
    errorHandler(error_code);
    int arr[4][4];
    if(size!=4){
        printf("4 process need\n");
        MPI_Finalize();
        return 0;
    }
    if(rank==0){
        printf("Enter the element: \n");
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                scanf("%d",&arr[i][j]);
    }
    int got_arr[4];
    MPI_Scatter(arr[rank],4,MPI_INT,got_arr,4,MPI_INT,0,MPI_COMM_WORLD);
    int result[4][4];
    int int_result[4];
    for(int i=0;i<4;i++){
        MPI_Scan(&got_arr[i],&int_result[i],1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    }
    MPI_Gather(int_result,4,MPI_INT,result,4,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0){
    printf("The result array is \n");
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
            printf("%d ",result[i][j]);
        printf("\n");
    }
    }
    MPI_Finalize();
}