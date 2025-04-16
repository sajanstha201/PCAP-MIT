#include<stdio.h>
#include<cuda_runtime.h>
#define N 5
__global__ void sc(int *a,int n){
  int id=threadIdx.x+blockDim.x*blockIdx.x;
  __shared__ int arr[N];
  if(id<n){
    arr[id]=a[id];
    __syncthreads();
    for(int i=1;i<=threadIdx.x;i=i*2){
      __syncthreads();
      arr[id]=arr[id]+arr[id-i];
    }
    a[id]=arr[id];
  }
}
int main(){
  int n=N;
  int h_a[n],h_r[n];
  printf("%d ",n);
  printf("Enter %d element for scan\n",N);
  for(int i=0;i<N;i++)
    scanf("%d",&h_a[i]);
  int *d_a,*d_r;
  int size=n*sizeof(int);
  cudaMalloc(&d_a,size);
  cudaMalloc(&d_r,size);
  cudaMemcpy(d_a,h_a,size,cudaMemcpyHostToDevice);
  sc<<<1,n>>>(d_a,n);
  cudaMemcpy(h_r,d_a,size,cudaMemcpyDeviceToHost);
  printf("Result: ");
  for(int i=0;i<n;i++){
    printf("%d ",h_r[i]);
  }
}