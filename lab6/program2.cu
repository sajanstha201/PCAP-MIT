#include<stdio.h>
#include<stdlib.h>
#include<cuda_runtime.h>
__global__ void convert(int *a,int *b,int n){
    int i=threadIdx.x+blockIdx.x*blockDim.x;
    if(i<n){
        b[i]=~a[i];
    }
}
int main(){
    printf("Enter the number of element: ");
    int n;
    scanf("%d",&n);
    printf("Enter the elements: \n");
    int h_a[n],h_b[n];
    for(int i=0;i<n;i++)
        scanf("%d",&h_a[i]);
    int *d_a,*d_b;
    cudaMalloc(&d_a,sizeof(int)*n);
    cudaMalloc(&d_b,sizeof(int)*n);
    cudaMemcpy(d_a,h_a,sizeof(int)*n,cudaMemcpyHostToDevice);
    convert<<<n,256>>>(d_a,d_b,n);
    cudaMemcpy(h_b,d_b,sizeof(int)*n,cudaMemcpyDeviceToHost);
    printf("The result are:\n");
    for(int i=0;i<n;i++)
        printf("%d",h_b[i]);
    

}