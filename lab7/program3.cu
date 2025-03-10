#include<stdio.h>
#include<stdlib.h>
#include<cuda_runtime.h>
__global__ void reverse(char *str,int l){
  int id=threadIdx.x+blockIdx.x*blockDim.x;
  if(id<l/2){
    char temp=str[id];
    str[id]=str[l-id-1];
    str[l-id-1]=temp;
  }

}
int main(){
  char h_str[100];
  printf("Enter a string: ");
  fgets(h_str,100,stdin);
  char *d_str;
  cudaMalloc(&d_str,strlen(h_str));
  cudaMemcpy(d_str,h_str,strlen(h_str),cudaMemcpyHostToDevice);
  reverse<<<sizeof(h_str),1>>>(d_str,strlen(h_str));
  cudaMemcpy(h_str,d_str,strlen(h_str),cudaMemcpyDeviceToHost);
  printf("The reverse is %s\n",h_str);

}