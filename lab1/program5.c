#include<stdio.h>
#include<mpi.h>
int fac(int n){
    int r=1;
    for(int i=1;i<=n;i++)
        r=r*i;
    return r;
}
int fib(int n){
    if(n==0)
        return 0;
    else if(n==1)
        return 1;
    return fib(n-1)+fib(n-2);
}
int main(int argc, char *argv[]){
    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank%2==0){
        printf("Rank %d fac: %d\n",rank,fac(rank));
    }
    else 
        printf("Rank :%d Fib: %d\n",rank,fib(rank));
    MPI_Finalize();
}