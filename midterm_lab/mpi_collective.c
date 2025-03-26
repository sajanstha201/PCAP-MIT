#include<stdio.h>
#include"mpi.h"
int main(int argc, char *argv[]){
    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int num;
    if(rank==0){
        printf("Enter a value: \n");
        scanf("%d",&num);
    }
    MPI_Bcast(&num,1,MPI_INT,0,MPI_COMM_WORLD);
    printf("Rank: %d BValue: %d\n",rank,num);
    int reduce_sum;
    int scan_sum;
    MPI_Reduce(&num,&reduce_sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    MPI_Scan(&num,&scan_sum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    if(rank==0){
        printf("Rank: %d The Reduce sum is %d Scan sum is : %d\n",rank,reduce_sum,scan_sum);
    }
    if(rank==3){
        printf("rank 3: The scan sum is %d\n",scan_sum);
    }
    int arr[4];
    MPI_Gather(&rank,1,MPI_INT,arr,1,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0){
        printf("Rank %d THe Gather value: ",rank);
        for(int i=0;i<4;i++){
            printf("%d ",arr[i]);
        }
        printf("\n");
    }
    int scatter_value;
    MPI_Scatter(arr,1,MPI_INT,&scatter_value,1,MPI_INT,0,MPI_COMM_WORLD);
    printf("Rank %d Scatter Value: %d\n",rank,scatter_value);
    for(int i=0;i<4;i++)
        arr[i]=rank;
    int all_arr[4];
    MPI_Alltoall(arr,1,MPI_INT,all_arr,1,MPI_INT,MPI_COMM_WORLD);
    if(rank==0){
        printf("rank: 0 the all to all resutl is : ");
    for(int i=0;i<4;i++){
        printf(" %d ",all_arr[i]);
    }
        printf("\n");
    }
    MPI_Finalize();
}