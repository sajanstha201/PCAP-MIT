#include<stdio.h>
#include<string.h>
#include<cuda_runtime.h>
__global__ void findPattern(char *str,char *pattern, int *count,int strLen,int patternLen){
    int id=threadIdx.x+blockDim.x*blockIdx.x;
    int k=0;
    if(id<strLen-patternLen+1){
        for(int i=id;i<id+patternLen-1;i++,k++){
            if(str[i]!=pattern[k])
                return;
        }
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
    int strLen=strlen(str),patternLen=strlen(pattern);
    cudaMalloc(&d_str,strLen);
    cudaMalloc(&d_pattern,patternLen);
    cudaMalloc(&d_count,sizeof(int));
    cudaMemcpy(d_str,str,strLen,cudaMemcpyHostToDevice);
    cudaMemcpy(d_pattern,pattern,patternLen,cudaMemcpyHostToDevice);
    cudaMemcpy(d_count,&count,sizeof(int),cudaMemcpyHostToDevice);
    printf("%d %d\n",strLen,patternLen);
    findPattern<<<1,strLen>>>(d_str,d_pattern,d_count,strLen,patternLen);
    cudaDeviceSynchronize();
    cudaMemcpy(&count,d_count,sizeof(int),cudaMemcpyDeviceToHost);

    printf("The number of count of %s words in %s sentence is %d\n",pattern,str,count);
}