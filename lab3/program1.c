#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"
int factorial(int n){
    int i=1;
    for(int j=1;j<=n;j++)
        i=i*j;
    return i;
}
int main(int argc,char * argv[]){
    MPI_Init(&argc,&argv);
    int rank,size;
    int root=0;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int arr[size];
    if(rank==0){
        printf("Enter %d numbers:\n",size);
        for(int i=0;i<size;i++)
            scanf("%d",&arr[i]);
    }
    int num;
    MPI_Scatter(arr,1,MPI_INT,&num,1,MPI_INT,root,MPI_COMM_WORLD);
    int fac=factorial(num);
    printf("Rank:%d Received:%d Factorial:%d\n",rank,num,fac);
    int final_result;
    MPI_Reduce(&fac,&final_result,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0)
        printf("The sum of factorial is %d\n",final_result);
    MPI_Finalize();
}