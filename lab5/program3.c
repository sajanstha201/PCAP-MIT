#include<stdio.h>
#include<stdlib.h>
__global__ void convert(int *a,int *b,int *n){
    int idx=threadIdx.x+blockDim.x*blockIdx.x;
    if(idx<n){
        b[idx]=sine(a[idx]);
    }
}
int main(){
    printf("Enter the number of array length: ");
    int n;
    scanf("%d",&n);
    printf("Enter the element of vector: ");
    int h_a[n],h_b[n];
    for(int i=0;i<n;i++)
        scanf("%d",&h_a[i]);
    int *d_a,*d_b;
    int size=sizeof(int)*n;
    cudaMalloc(&d_a,size);
    cudaMalloc(&d_b,size);
    cudaMemcpy(d_a,h_a,size,cudaMemcpyHostToDevice);
    int threadPerBlock=256;
    int blockNum=(int)(n/threadPerBlock+1);
    convert<<<blockNum,threadPerBlock>>>(d_a,d_b,n);
    cudaDeviceSynchronize();
    cudaMemcpy(h_b,d_b,size,cudaMemcpyDeviceToHost);
    printf("The result: ");
    for(int i;i<n;i++)
        printf("%d ",h_b[i]);
}