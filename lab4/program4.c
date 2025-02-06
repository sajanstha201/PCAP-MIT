#include<stdio.h>
#include<string.h>
#include "mpi.h"
void errorHandler(int err_code){
    if(err_code!=MPI_SUCCESS){
        int len,err_class;
        char err_str[256];
        MPI_Error_class(err_code,&err_class);
        MPI_Error_string(err_code,err_str,&len);
        printf("Error class: %d Error string: %s\n",len,err_str);
    }
}
int main(int argc, char *argv[]){
    MPI_Init(&argc,&argv);
    MPI_Comm_set_errhandler(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
    int rank,size;
    int err_code;
    err_code=MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    err_code=MPI_Comm_size(MPI_COMM_WORLD,&size);
    errorHandler(err_code);
    char str[100];
    int len;
    if(rank==0){
        printf("Enter the string: \n");
        fgets(str,100,stdin);
        len=strlen(str);
    }
    char c;
    MPI_Bcast(&len,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(str,1,MPI_CHAR,&c,1,MPI_CHAR,0,MPI_COMM_WORLD);
    char o_str[len];
    int i;
    for(i=0;i<len;i++)
        if(i<rank+1)
            o_str[i]=c;
        else
            o_str[i]='0';
    printf("rnak %d str %s\n",rank,o_str);
    char result[len*(size+1)];
    MPI_Gather(o_str,len,MPI_CHAR,result,len,MPI_CHAR,0,MPI_COMM_WORLD);
    if(rank==0){
        char final_result[len*(size+1)];
        int k=0;
        for(int i=0;i<len*(size+1);i++){
            if(result[i]!='0'){
                final_result[k]=result[i];
                k++;
            }

        }
        final_result[k]='\0';
        printf("The result is %s\n",final_result);
    }
    MPI_Finalize();
}
