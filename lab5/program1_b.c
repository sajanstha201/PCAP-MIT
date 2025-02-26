#include <stdio.h>
#include <cuda_runtime.h>
__global__ void add(int *a,int *b,int *c){
  int idx=blockDim.x*blockIdx.x+threadIdx.x;
  c[idx]=a[idx]+b[idx];
  printf("a: %d b: %d index: %d\n",a[idx],b[idx],idx);
}
int main(){
  int n;
  printf("Enter the number of element: ");
  scanf("%d",&n);
  int h_a[n],h_b[n],h_c[n];
  printf("Enter the value for vector A:");
  for(int i=0;i<n;i++)
    scanf("%d",&h_a[i]);
  printf("Enter the value for vector B:");
  for(int i=0;i<n;i++)
    scanf("%d",&h_b[i]);
  int *d_a,*d_b,*d_c;
  int size=n*sizeof(int);
  cudaMalloc(&d_a,size);
  cudaMalloc(&d_b,size);
  cudaMalloc(&d_c,size);
  cudaMemcpy(d_a,h_a,size,cudaMemcpyHostToDevice);
  cudaMemcpy(d_b,h_b,size,cudaMemcpyHostToDevice);
  int threadPerBlock=n;
  int blockPerGrid=1;
  add<<<blockPerGrid,threadPerBlock>>>(d_a,d_b,d_c);
  cudaDeviceSynchronize();
  cudaMemcpy(h_c,d_c,size,cudaMemcpyDeviceToHost);
  printf("The value of vector C is: ");
  for(int i=0;i<n;i++)
    printf("%d ",h_c[i]);
  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);
}