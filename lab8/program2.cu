
#include<stdio.h>
#include<stdlib.h>
#include<cuda_runtime.h>
__global__ void mulRow(int *a,int *b,int *c,int row, int col){
  int idx=threadIdx.x+blockIdx.x*blockDim.x;
  if(idx<row){
    for (int i=0;i<col;i++){
      int sum=0;
      for(int k=0;k<row;k++){
          sum=sum+a[idx*col+k]*b[k*col+i];
      }
      c[idx*col+i]=sum;
    }
  }
}
__global__ void mulCol(int *a,int *b,int *c,int row, int col){
  int idx=threadIdx.x+blockIdx.x*blockDim.x;
  if(idx<col){
    for (int i=0;i<row;i++){
        int sum=0;
        for(int k=0;k<col;k++){
            sum=sum+a[k+i*col]*b[k*col+idx];
        }
        c[idx+col*i]=sum;
    }
  }
}
__global__ void mulEach(int *a,int *b,int *c,int row, int col){
  int idx=threadIdx.x+blockIdx.x*blockDim.x;
  if(idx<row*col){
    int sum=0;
    for(int k=0;k<col;k++){
      sum=sum+a[(int)(idx/col)*col+k]*b[k*col+(int)(idx%col)];
    }
    c[idx]=sum;
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
  int h_a[m*n],h_b[m*n],h_c[m*n];
  printf("Enter the matrix A element:");
  for(int i=0;i<m*n;i++)
    scanf("%d",&h_a[i]);
  printf("Enter the matrix B element: ");
  for(int i=0;i<m*n;i++)
    scanf("%d",&h_b[i]);
  int *d_a,*d_b,*d_c;
  cudaMalloc(&d_a,sizeof(int)*m*n);
  cudaMalloc(&d_b,sizeof(int)*m*n);
  cudaMalloc(&d_c,sizeof(int)*m*n);
  cudaMemcpy(d_a,h_a,sizeof(int)*m*n,cudaMemcpyHostToDevice);
  cudaMemcpy(d_b,h_b,sizeof(int)*m*n,cudaMemcpyHostToDevice);
  mulRow<<<1,m>>>(d_a,d_b,d_c,m,n);
  cudaMemcpy(h_c,d_c,sizeof(int)*m*n,cudaMemcpyDeviceToHost);
  printf("Row Wise mulition: \n");
  printArray(m,n,h_c);
  mulCol<<<1,n>>>(d_a,d_b,d_c,m,n);
  cudaMemcpy(h_c,d_c,sizeof(int)*m*n,cudaMemcpyDeviceToHost);
  printf("Col Wise mulition: \n");
  printArray(m,n,h_c);
  mulEach<<<m,n>>>(d_a,d_b,d_c,m,n);
  cudaMemcpy(h_c,d_c,sizeof(int)*m*n,cudaMemcpyDeviceToHost);
  printf("Each mulition: \n");
  printArray(m,n,h_c);
}