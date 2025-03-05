#include<stido.h>
#include<stdlib.h>

__global__ void add(int *a,int *b,int *c,int n){
    
    int idx=threadIdx.x+blockIdx.x*blockDim.x;
    if(idx<n){
        c[idx]=a[idx]+b[idx];
    }
}
int main(){
    int n;
    printf("Enter the number of element: ");
    scanf("%d",&n);
    int h_a[n],h_b[n],h_c[n];
    printf("Enter the element of A vector: ");
    for(int i=0;i<n;i++)
        scanf("%d",&h_a[i]);
    printf("Enter the element of B vector: ");
    for(int i=0;i<n;i++)
        scanf("%d",&h_b[i]);
    int *d_a,*d_b,*d_c;
    int size=sizeof(int)*n;
    cudaMalloc(&d_a,size);
    cudaMalloc(&d_b,size);
    cudaMalloc(&d_c,size);
    cudaMemcpy(d_a,h_a,size,cudaMemcpyHostToDevice);
    cudaMemcoy(d_b,h_b,size,cudaMemcpyHostToDevice);
    int threadPerBlock=256;
    int blockNum=(int)(n/threadPerBlock+1);
    add<<<blockNum,threarPerBlock>>>(d_a,d_b,d_c,n);
    cudaDeviceSynchronize();
    cudaMemcpy(h_c,d_c,size,cudaMemcpyDeviceToHost);
    printf("The value of C vector: ");
    for(int i;i<n;i++)
        printf("%d ",&h_c[i]);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
}
