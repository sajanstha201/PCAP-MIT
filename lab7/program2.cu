#include<stdio.h>
#include<cuda_runtime.h>
#include<string.h>
__global__ void copy(char *str,char *result,int size){
    int id=threadIdx.x+blockIdx.x*blockDim.x;
    if(id<size){
        int k=0;
        for(int i=0;i<id;i++)
            k=k+(size-i-1);
        for(int i=0;i<(size-id-1);i++){
            result[k+i]=str[i];
        }
    }
}
int main(){
    char h_str[100];
    printf("Entr a string: ");
    fgets(h_str,100,stdin);
    char *d_str;
    cudaMalloc(&d_str,strlen(h_str)*sizeof(char));
    int count=0;
    for(int i=1;i<=strlen(h_str);i++)
        count+=i;
    char h_result[count];
    printf("count: %d\n",count);
    char *d_result;
    cudaMalloc(&d_str,strlen(h_str)*sizeof(char));
    cudaMalloc(&d_result,count*sizeof(char));
    cudaMemcpy(d_str,h_str,strlen(h_str)*sizeof(char),cudaMemcpyHostToDevice);
    copy<<<1,strlen(h_str)>>>(d_str,d_result,strlen(h_str));
    cudaMemcpy(h_result,d_result,count*sizeof(char),cudaMemcpyDeviceToHost);
    printf("The result output is %s\n",h_result);
}