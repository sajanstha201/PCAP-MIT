#include<stdio.h>
#include<cuda_runtime.h>
__global__ void conv(int *N,int *M,int *r,int n,int m){
    int id=threadIdx.x+blockIdx.x*blockDim.x;
    if(id<n){
        int value=0;
        int point=id-(int)(m/2);
        for(int i=0;i<m;i++){
            if(0<=point&&point<n){
                value+=M[i]*N[point];
            }
            point++;
        }
        r[id]=value;
    }
}
int main(){
    printf("Enter the number of element: ");
    int n;
    scanf("%d",&n);
    int N[n];
    printf("Enter the elements: ");
    for(int i=0;i<n;i++)
        scanf("%d",&N[i]);
    printf("Entr the numbee of element for Mask; ");
    int m;
    scanf("%d",&m);
    int M[m];
    printf("Enter the elements for Mark: ");
    for(int i=0;i<m;i++)
        scanf("%d",&M[i]);
    int *d_N,*d_M;
    cudaMalloc(&d_N,sizeof(int)*n);
    cudaMalloc(&d_M,sizeof(int)*m);
    cudaMemcpy(d_N,N,sizeof(int)*n,cudaMemcpyHostToDevice);
    cudaMemcpy(d_M,M,sizeof(int)*m,cudaMemcpyHostToDevice);
    int result[n];
    int *d_result;
    cudaMalloc(&d_result,sizeof(int)*n);
    conv<<<n,256>>>(d_N,d_M,d_result,n,m);
    cudaDeviceSynchronize();
    cudaMemcpy(result,d_result,sizeof(int)*n,cudaMemcpyDeviceToHost);
    printf("The result is :\n");
    for(int i=0;i<n;i++)
        printf("%d ",result[i]);
    cudaFree(d_N);
    cudaFree(d_M);
}