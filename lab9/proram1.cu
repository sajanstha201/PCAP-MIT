
#include<stdio.h>
#include<string.h>
#include<cuda_runtime.h>
__global__ void mul(int *value,int *arr,int *col_arr, int *row,int *result,int m,int n,int col){
    int id=threadIdx.x+blockDim.x*blockIdx.x;
    if(id<m){
      int sum=0;
      for(int i=row[id];i<row[id+1];i++){
          sum=sum+value[i]*arr[col_arr[i]];
      }
      result[id]=sum;
    }
}
int main(){
  printf("Enter number of row and col: ");
  int row,col;
  scanf("%d%d",&row,&col);
  int h_arr[col];
  printf("Enter the scalr vecotr of length %d: ",col);
  for(int i=0;i<col;i++)
    scanf("%d",&h_arr[i]);
  printf("Enter the number of non zero element: ");
  int n,m;
  scanf("%d",&n);
  printf("Enter the element in row array: ");
  scanf("%d",&m);
  int h_value[n],h_col[n],h_row[m];
  printf("Enter the value array:");
  for(int i=0;i<n;i++)
    scanf("%d",&h_value[i]);
  printf("Enter the col array: ");
  for(int i=0;i<n;i++)
    scanf("%d",&h_col[i]);
  printf("Enter the row array: ");
  for(int i=0;i<m;i++)
    scanf("%d",&h_row[i]);
  int *d_col,*d_value,*d_row,*d_result,*d_arr;
  cudaMalloc(&d_col,n*sizeof(int));
  cudaMalloc(&d_value,n*sizeof(int));
  cudaMalloc(&d_result,n*sizeof(int));
  cudaMalloc(&d_row,m*sizeof(int));
  cudaMalloc(&d_arr,col*sizeof(int));
  cudaMemcpy(d_value,h_value,n*sizeof(int),cudaMemcpyHostToDevice);
  cudaMemcpy(d_col,h_col,n*sizeof(int),cudaMemcpyHostToDevice);
  cudaMemcpy(d_row,h_row,m*sizeof(int),cudaMemcpyHostToDevice);
  cudaMemcpy(d_arr,h_arr,col*sizeof(int),cudaMemcpyHostToDevice);
  mul<<<1,n>>>(d_value,d_arr,d_col,d_row,d_result,m,n,col);
  int result[col];
  cudaMemcpy(result,d_result,col*sizeof(int),cudaMemcpyDeviceToHost);
  printf("Result: ");
  for(int i=0;i<col;i++)
    printf("%d ",result[i]);
}