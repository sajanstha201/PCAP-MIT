#include<stdio.h>
#include<cuda_runtime.h>
__global__ void odd_even_sort(int *arr,int n,int phase){
    int id=threadIdx.x+blockDim.x*blockIdx.x;
    if(id<(int)n/2){
        int j=(phase==0)?2*id:2*id+1;
        if(j>=n||j+1>=n)
          return;
        if(arr[j]>arr[j+1]){
            int temp=arr[j+1];
            arr[j+1]=arr[j];
            arr[j]=temp;
        }
    }

}
int main(){
    int n;
    printf("Enter the number of element: ");
    scanf("%d",&n);
    int h_arr[n];
    printf("Enter the elements: ");
    for(int i=0;i<n;i++)
        scanf("%d",&h_arr[i]);
    int *d_arr;
    cudaMalloc(&d_arr,sizeof(int)*n);
    cudaMemcpy(d_arr,h_arr,sizeof(int)*n,cudaMemcpyHostToDevice);
    for(int i=0;i<n;i++){
        odd_even_sort<<<1,n>>>(d_arr,n,i%2);
    }
    cudaMemcpy(h_arr,d_arr,sizeof(int)*n,cudaMemcpyDeviceToHost);
    printf("The sorted array is: ");
    for(int i=0;i<n;i++)
        printf("%d ",h_arr[i]);
}