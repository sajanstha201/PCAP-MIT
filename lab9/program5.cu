#include<stdio.h>
#include<stdlib.h>
#include<cuda_runtime.h>
__global__ void op(int *a,char *b,char *str,int row, int col){
  int idx=threadIdx.x+blockIdx.x*blockDim.x;
  if(idx<row*col){
    int i=0;
    for(int k=0;k<idx;k++)
      i=i+a[k];
    for(int j=i;j<i+a[idx];j++)
      str[j]=b[idx];

  }
}
int main(){
  int m,n;
  printf("Enter the matrix size: ");
  scanf("%d",&m);
  scanf("%d",&n);
  int h_a[m*n];
  char h_b[m*n];
  printf("Enter the matrix int A element:");
  for(int i=0;i<m*n;i++)
    scanf("%d",&h_a[i]);
  printf("Enter the matrix char B element:");
  for(int i=0;i<m*n;i++)
    scanf(" %c",&h_b[i]);
  int *d_a;
  char *d_b;
  char *str;
  int size=0;
  for(int i=0;i<m*n;i++)
    size=size+h_a[i];
  size=size*sizeof(char);
  cudaMalloc(&str,size);
  cudaMalloc(&d_a,sizeof(int)*m*n);
  cudaMalloc(&d_b,sizeof(char)*m*n);
  cudaMemcpy(d_a,h_a,sizeof(int)*m*n,cudaMemcpyHostToDevice);
  cudaMemcpy(d_b,h_b,sizeof(char)*m*n,cudaMemcpyHostToDevice);
  op<<<m,n>>>(d_a,d_b,str,m,n);
  char h_str[size];
  cudaMemcpy(h_str,str,size,cudaMemcpyDeviceToHost);
  h_str[size]='\0';
  printf("Result is %s\n",h_str);
}