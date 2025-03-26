#include<stdio.h>
#include<mpi.h>
int main(int argc, char * argv[]){
    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    char str[]={"sajan"};
    if('a'<=str[rank]&&str[rank]<='z'){
        str[rank]=str[rank]-('a'-'A');
    }
    else
        str[rank]=str[rank]+('a'-'A');
    printf("rank %d value : %s\n",rank,str);
    MPI_Finalize();
}