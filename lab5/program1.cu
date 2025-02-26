#include <stdio.h>
#include <cuda_runtime.h>

__global__ void add(int *a, int *b, int *c, int n) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    if (idx < n) { // Ensure we don't go out of bounds
        c[idx] = a[idx] + b[idx];
        printf("a: %d b: %d index: %d c: %d\n", a[idx], b[idx], idx, c[idx]);
    }
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int h_a[n], h_b[n], h_c[n];

    printf("Enter the values for vector A: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &h_a[i]);

    printf("Enter the values for vector B: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &h_b[i]);

    int *d_a, *d_b, *d_c;
    int size = n * sizeof(int);

    // Fix: Use (void**) instead of (int**)
    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    cudaMalloc((void**)&d_c, size);

    cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);

    // Fix: Use a more efficient grid/block size
    int threadsPerBlock = 256;
    int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

    add<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, n);
    cudaDeviceSynchronize();

    cudaMemcpy(h_c, d_c, size, cudaMemcpyDeviceToHost);

    printf("The values of vector C are: ");
    for (int i = 0; i < n; i++)
        printf("%d ", h_c[i]);
    printf("\n");

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
