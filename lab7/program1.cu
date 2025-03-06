#include<stdio.h>
#include<string.h>
#include<cuda_runtime.h>
__global__ void findPattern(char *str,char *pattern, int *count,int strLen,int patternLen){
    int id=threadIdx.x+blockdim.x*blockIdx.x;
    int k=0;
    if(id<strLen-patternLen){
        for(int i=id;i<pattenLen;i++,k++)
            if(str[i]!=pattern[k])
                return;
        atomicAdd(count,1);
    }
}
int main(){
    char str[100];
    printf("Enter the sentence: ");
    fgets(str,100,stdin);
    int count=0;
    char pattern[100];
    printf("Enter a word you want to search: ");
    fgets(pattern,100,stdin);

    char *d_str;
    int *d_count;
    char *d_pattern;
    cudaMalloc(&d_str,sizeof(char)*strlen(str));
    cudaMalloc(&d_pattern,sizeof(char)*strlen(pattern));
    cudaMalloc(&d_count,sizeof(int));
    cudaMemcpy(d_str,str,sizeof(char)*strlen(str),cudaMemcpyHostToDevice);
    cudaMemcpy(d_pattern,pattern,sizeof(char)*strlen(pattern),cudaMemcpyHostToDevice);
    cudaMemcpy(d_count,count,sizeof(int),cudaMemcpyHostToDevice);
    findPattern<<<strlen(str),256>>>(d_str,d_pattern,d_count,strlen(str),strlen(pattern));
    cudaMemcpy(count,d_count,sizeof(int),cudaMemcpyDeviceToHost);
    printf("The number of count of %s words in %s sentence is %d\n",pattern,str,count);
}   