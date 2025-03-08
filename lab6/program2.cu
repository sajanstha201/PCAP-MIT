#include<stdio.h>
#include<cuda_runtime.h>
__global__ void swap(int *arr,int *index,int i){
    int temp=arr[i];
    arr[i]=arr[*index];
    arr[*index]=temp;
}
__global __void findMax(int *arr,int *max,int *index,int size){
    int id=threadIdx.x+blockIdx.x*blockDim.x;
    if(id<size){
        if(*max<arr[id]){
            max=arr[id];
            index=id;
        }
    }
}
int main(){
    int n;
    printf("Enter a number of element: ");
    scanf("%d",&n);
    int h_arr[n];
    printf("Enter the element in array: ");
    for(int i=0;i<n;i++)
        scanf("%d",&h_arr[i]);
    int *d_arr;
    cudaMalloc(&d_arr,n*sizeof(int));
    cudaMemcpy(d_arr,h_arr,sizeof(int)*n,cudaMemcpyHostToDevice);
    for(int i=0;i<n;i++){
        int *d_max,*d_index;
        int h_max=0,h_index=0;
        cudaMalloc(&d_max,sizeof(int));
        cudaMalloc(&d_index,sizeof(int));
        cudaMemcpy(d_max,&h_max,sizeof(int),cudaMemcpyHostToDevice);
        cudaMemcpy(d_index,&h_index,sizeof(int),cudaMemcpyHostToDevice);
        findMax<<<1,n>>>(d_arr,d_max,d_index,n-i);
        swap<<<1,1>>>(d_arr,d_index,n-i);
    }
    cudaMemcpy(h_arr,d_arr,sizeof(int)*n,cudaMemcpyDeviceToHost);
    printf("The sorted aray is: ");
    for(int i=0;i<n;i++)
        printf("%d ",h_arr[i]);
}