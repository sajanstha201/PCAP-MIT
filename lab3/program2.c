#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"
int main(int argc, char * argv[]){
    int rank,size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int m;
    int *arr;
    if(rank==0){
        printf("Enter a number:\n");
        scanf("%d",&m);
        arr=(int*)malloc(sizeof(int)*m*size);
        printf("Enter %d numbers: \n",m*size);
        for(int i=0;i<m*size;i++)
            scanf("%d",&arr[i]);
    }
    MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
    int r_arr[m];
    MPI_Scatter(arr,m,MPI_INT,r_arr,m,MPI_INT,0,MPI_COMM_WORLD);
    double sum=0;
    for(int i=0;i<m;i++)
        sum+=r_arr[i];
    sum=sum/m;
    printf("Rank: %d Average: %f\n",rank,sum);
    double final_result;
    MPI_Reduce(&sum,&final_result,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0){
        final_result=final_result/size;
        printf("The final result is %f\n",final_result);
    }
    MPI_Finalize();

}