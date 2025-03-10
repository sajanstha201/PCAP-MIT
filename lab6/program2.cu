#include <stdio.h>
#include <cuda.h>

#define N 10

__global__ void selection_sort(int *d_arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (d_arr[j] < d_arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            int temp = d_arr[i];
            d_arr[i] = d_arr[min_index];
            d_arr[min_index] = temp;
        }
        __syncthreads();
    }
}

void parallel_selection_sort(int *h_arr, int n) {
    int *d_arr;
    cudaMalloc((void **)&d_arr, n * sizeof(int));
    cudaMemcpy(d_arr, h_arr, n * sizeof(int), cudaMemcpyHostToDevice);

    selection_sort<<<1, 1>>>(d_arr, n);

    cudaMemcpy(h_arr, d_arr, n * sizeof(int), cudaMemcpyDeviceToHost);
    cudaFree(d_arr);
}

int main() {
    int h_arr[N] = {64, 25, 12, 22, 11, 90, 42, 30, 8, 55};

    printf("Original Array:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", h_arr[i]);
    }
    printf("\n");

    parallel_selection_sort(h_arr, N);

    printf("Sorted Array:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", h_arr[i]);
    }
    printf("\n");

    return 0;
}