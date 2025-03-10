#include<stdio.h>
#include<cuda_runtime.h>

__global__ void convert(char *str,char *result,int size){
  int id=threadIdx.x+blockDim.x*blockIdx.x;
  if(id<size){
    int count=0;
    for(int i=0;i<=id;i++)
      count+=i;
    for(int i=count;i<=count+id;i++){
      result[i]=str[id];
    }
  }
}
int main(){
  char h_str[100];
  printf("Enter a string: ");
  fgets(h_str,100,stdin);
  int size=strlen(h_str)-1;
  char *d_str;
  cudaMalloc(&d_str,size);
  char *d_result;
  int result_size=0;
  for(int i=0;i<=size;i++)
    result_size+=i;
  cudaMalloc(&d_result,result_size);
  printf("The result size: %d\n",result_size);
  cudaMemcpy(d_str,h_str,size,cudaMemcpyHostToDevice);
  convert<<<1,size>>>(d_str,d_result,size);
  char result[result_size];
  cudaMemcpy(result,d_result,result_size,cudaMemcpyDeviceToHost);
  printf("The result is %s\n",result);
}