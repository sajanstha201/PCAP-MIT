#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mpi.h"
int main(int argc, char *argv[]){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    char str1[100],str2[100];
    int len;
    if(rank==0){
        printf("Enter two string of length divisible by %d\n",size);
        scanf("%s",str1);
        scanf("%s",str2);
        len=strlen(str1);
    }
    MPI_Bcast(&len,1,MPI_INT,0,MPI_COMM_WORLD);
    int block_len=len/size;
    char r_str1[block_len],r_str2[block_len];
    
    MPI_Scatter(str1,block_len,MPI_CHAR,r_str1,block_len,MPI_CHAR,0,MPI_COMM_WORLD);
    MPI_Scatter(str2,block_len,MPI_CHAR,r_str2,block_len,MPI_CHAR,0,MPI_COMM_WORLD);
    char result[2*len];
    char combine[2*block_len];
    int i;
    for(i=0;i<block_len;i++){
        combine[i]=r_str1[i];
        combine[i+block_len]=r_str2[i];
    }
    combine[i+block_len]='\0';
    MPI_Gather(combine,2*block_len,MPI_CHAR,result,2*block_len,MPI_CHAR,0,MPI_COMM_WORLD);
    if(rank==0){
        result[2*len]='\0';
        printf("The result value is %s\n",result);
    }
    MPI_Finalize();
}