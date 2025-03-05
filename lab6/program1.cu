#include<stdio.h>
#include<cuda_runtime.h>
__global__ void convert(int *a,int *b,int n){
    int i=threadIdx.x+blockIdx.x*blockDim.x;
    if(i<n){
        int num=a[i];
        result=0;
        while(num!=0){
            result=result*10+(int)(num%8);
            num=(int)num/8;
        }
        b[i]=num;
    }
}
int main(){
    int n;
    printf("Enter the number of element: ");
    scanf("%d",&n);
    int h_a[n],h_b[n];
    printf("Enter the elements: \n");
    for(int i=0;i<n;i++)
        scanf("%d",&h_a[i]);
    int *d_a,*d_b;
    cudaMalloc(&d_a,sizeof(int)*n);
    cudaMalloc(&d_b ,sizeof(int)*n);
    cudaMemcpy(d_a,h_a,sizeof(int)*n,cudaMemcpyHostToDevice);
    convert<<<n,256>>>(d_a,d_b,n);
    cudaMemcpy(h_b,d_b,sizeof(int)*n,cudaMemcpyDeviceToHost);
    printf("The Octal Form are: \n")
    for(int i=0;i<n;i++)
        printf("%d ",d_b[i]);
    cudaFree(d_a);
    cudaFree(d_b);
}