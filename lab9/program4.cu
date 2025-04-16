#include<stdio.h>
#include<stdlib.h>
#include<cuda_runtime.h>
__global__ void op(int *a,int *b,int row, int col){
  int idx=threadIdx.x+blockIdx.x*blockDim.x;
  if(idx<row*col){
      int i=(int)(idx/col);
      int j=(int)(idx%col);
      int sum=0;
      for(int k=0;k<col;k++){
        sum=sum+a[i*col+k];
      }
      for(int k=0;k<row;k++){
        sum=sum+a[k*col+j];
      }
      b[idx]=sum;

  }
}

void printArray(int row,int col, int *arr){
  for(int i=0;i<row;i++){
    for(int j=0;j<col;j++){
      printf("%d ",arr[i*col+j]);
    }
    printf("\n");
  }
}
int main(){
  int m,n;
  printf("Enter the matrix size: ");
  scanf("%d",&m);
  scanf("%d",&n);
  int h_a[m*n],h_b[m*n];
  printf("Enter the matrix A element:");
  for(int i=0;i<m*n;i++)
    scanf("%d",&h_a[i]);
  int *d_a,*d_b;
  cudaMalloc(&d_a,sizeof(int)*m*n);
  cudaMalloc(&d_b,sizeof(int)*m*n);
  cudaMemcpy(d_a,h_a,sizeof(int)*m*n,cudaMemcpyHostToDevice);
  op<<<m,n>>>(d_a,d_b,m,n);
  cudaMemcpy(h_b,d_b,sizeof(int)*m*n,cudaMemcpyDeviceToHost);
  printf("Result: \n");
  printArray(m,n,h_b);
}