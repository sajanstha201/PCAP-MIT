#include<stdio.h>
#include<cuda_runtime.h>
__global__ void  mul(int *a,int *b,int *c,int n){
  int row=blockIdx.y*blockDim.y+threadIdx.y;
  int col=blockIdx.x*blockDim.x+threadIdx.x;
  if(row<n && col<n){
    int sum=0;
    for(int k=0;k<n;k++){
      sum+=a[row*n+k]*b[col+n*k];
    }
    c[row*n+col]=sum;
  }
}
int main(){
  int n;
  printf("Enter the dimension for a square matrix: ");
  scanf("%d",&n);
  int h_A[n*n],h_B[n*n],h_C[n*n];
  printf("Enter Matrix A element: ");
  for(int i=0;i<n*n;i++)
    scanf("%d",&h_A[i]);
  printf("Enter Matrix B element: ");
  for(int i=0;i<n*n;i++)
    scanf("%d",&h_B[i]);
  int *d_A,*d_B,*d_C;
  int size=n*n*sizeof(int);
  cudaMalloc(&d_A,size);
  cudaMalloc(&d_B,size);
  cudaMalloc(&d_C,size);
  cudaMemcpy(d_A,h_A,size,cudaMemcpyHostToDevice);
  cudaMemcpy(d_B,h_B,size,cudaMemcpyHostToDevice);
  dim3 blockD(2,2);
  dim3 gridD(int(n/blockD.x)+1,int(n/blockD.y)+1);
  mul<<<gridD,blockD>>>(d_A,d_B,d_C,n);
  cudaMemcpy(h_C,d_C,size,cudaMemcpyDeviceToHost);
  printf("Result: ");
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++)
      printf("%d ",h_C[i*n+j]);
    printf("\n");
  }
}