#include<stdio.h>
#include<cuda_runtime.h>
__constant__ int Mask[3];
__global__ void conv(int *N,int *r,int m,int n){
  int id=blockDim.x*blockIdx.x+threadIdx.x;
  if(id<n){
    int sum=0;
    for(int i=0;i<m;i++){
        if(!(id+i<(int)(m/2)) && !(id+i>n-(int)(m/2))){
          sum=sum+N[id+i-(int)(m/2)]*Mask[i];
        }
    }
    r[id]=sum;
  }
}
int main(){
  int n;
  printf("Enter the element: ");
  scanf("%d",&n);
  int m=3;
  int N[n],M[m],r[n];
  printf("Enter N: ");
  for(int i=0;i<n;i++)
    scanf("%d",&N[i]);
  printf("Enter 3 element of  M: ");
  for(int i=0;i<m;i++)
    scanf("%d",&M[i]);
  int *d_n,*d_r;
  cudaMalloc(&d_n,n*sizeof(int));
  cudaMalloc(&d_r,n*sizeof(int));
  cudaMemcpy(d_n,N,n*sizeof(int),cudaMemcpyHostToDevice);
  cudaMemcpyToSymbol(Mask,M,m*sizeof(int));
  conv<<<1,n>>>(d_n,d_r,m,n);
  cudaMemcpy(r,d_r,n*sizeof(int),cudaMemcpyDeviceToHost);
  printf("Result: ");
  for(int i=0;i<n;i++)
    printf("%d ",r[i]);
}