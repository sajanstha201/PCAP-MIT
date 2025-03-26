#include<stdio.h>
#include<mpi.h>
#include<string.h>
int main(int argc, char * argv[]){
    MPI_Status status;
    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    if(rank==0){
        char str[]={"Sajan"};
        MPI_Ssend(str,strlen(str),MPI_CHAR,1,0,MPI_COMM_WORLD);
        MPI_Recv(str,strlen(str),MPI_CHAR,1,0,MPI_COMM_WORLD,&status);
        printf("The toggle value is  %s\n",str);
    }
    if(rank==1){
        char str[100];
        MPI_Recv(str,100,MPI_CHAR,0,0,MPI_COMM_WORLD,&status);
        for(int i=0;i<strlen(str);i++){
            if('a'<=str[i]&&str[i]<='z'){
                str[i]=str[i]-('a'-'A');
            }
            else{
                str[i]=str[i]+('a'-'A');
            }
        }
        MPI_Ssend(str,strlen(str),MPI_CHAR,0,0,MPI_COMM_WORLD);
    }
    MPI_Finalize();
}