#include<stdio.h>
#include<cuda_runtime.h>
#include<stdlib.h>
__global__ void concat(char *d_str,char *d_result,int n,int l){
  int id=threadIdx.x+blockDim.x*blockIdx.x;
  if(id<n)
    for(int i=0;i<l;i++)
      d_result[id*l+i]=d_str[i];
}
int main(){
  printf("Enter a string: ");
  char h_str[100];
  fgets(h_str,100,stdin);
  int size=strlen(h_str)-1;
  char *d_str;
  cudaMalloc(&d_str,size);
  cudaMemcpy(d_str,h_str,size,cudaMemcpyHostToDevice);
  int n;
  printf("Enter the number: ");
  scanf("%d",&n);
  char *d_result;
  cudaMalloc(&d_result,n*size);

  printf("The len of stri is %d\n",size);
  concat<<<1,n>>>(d_str,d_result,n,size);
  char h_result[n*size];
  cudaMemcpy(h_result,d_result,n*size,cudaMemcpyDeviceToHost);
  printf("The output string is %s\n",h_result);
}