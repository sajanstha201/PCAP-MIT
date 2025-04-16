#include<stdio.h>
#include<string.h>
#include<cuda_runtime.h>
__global__ void operation(int *arr,int m,int n){
    int id=threadIdx.x+blockDim.x*blockIdx.x;
    if(id<m*n){
      if(id%n!=0 and (id+1)%n!=0 and id>n and id<n*(m-1))
        arr[id]=~arr[id];
    }
}
int main(){
  printf("Enter number of row and col: ");
  int m,n;
  scanf("%d%d",&m,&n);
  int h_arr[m*n];
  printf("Enter the array element: ");
  for(int i=0;i<m*n;i++)
    scanf("%d",&h_arr[i]);
  int *d_arr;
  cudaMalloc(&d_arr,m*n*sizeof(int));
  cudaMemcpy(d_arr,h_arr,m*n*sizeof(int),cudaMemcpyHostToDevice);
  operation<<<m,n>>>(d_arr,m,n);
  cudaMemcpy(h_arr,d_arr,m*n*sizeof(int),cudaMemcpyDeviceToHost);
  printf("Result:\n ");
  for(int i=0;i<m;i++){
    for(int j=0;j<n;j++)
      printf("%d ",h_arr[i*n+j]);
    printf("\n");
  }
}