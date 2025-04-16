#include <stdio.h>
#define TILE_WIDTH 8
#define MAX_WIDTH 64
#define MAX_MASK_WIDTH 5

__constant__ float d_mask[MAX_MASK_WIDTH];

__global__ void tiledConvolution1D(float *input, float *output, int width, int mask_width) {
    __shared__ float tile[TILE_WIDTH + MAX_MASK_WIDTH - 1];

    int tid = threadIdx.x;
    int start = blockIdx.x * TILE_WIDTH;
    int halo = mask_width / 2;
    int index = start + tid;

    // Load data into shared memory with halo
    if (index < width)
        tile[tid] = input[index];
    else
        tile[tid] = 0.0f;

    __syncthreads();

    if (tid < TILE_WIDTH && (start + tid) < width) {
        float result = 0.0f;
        for (int j = 0; j < mask_width; j++) {
            int dataIdx = tid + j - halo;
            if (dataIdx >= 0 && dataIdx < TILE_WIDTH + mask_width - 1)
                result += tile[dataIdx] * d_mask[j];
        }
        output[start + tid] = result;
    }
}

int main() {
    int width, mask_width;
    float h_input[MAX_WIDTH], h_output[MAX_WIDTH], h_mask[MAX_MASK_WIDTH];

    printf("Enter width of input array: ");
    scanf("%d", &width);
    printf("Enter input array elements:\n");
    for (int i = 0; i < width; i++) scanf("%f", &h_input[i]);

    printf("Enter mask width (odd number): ");
    scanf("%d", &mask_width);
    printf("Enter mask elements:\n");
    for (int i = 0; i < mask_width; i++) scanf("%f", &h_mask[i]);

    float *d_input, *d_output;
    cudaMalloc(&d_input, width * sizeof(float));
    cudaMalloc(&d_output, width * sizeof(float));
    cudaMemcpy(d_input, h_input, width * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpyToSymbol(d_mask, h_mask, mask_width * sizeof(float));

    int numBlocks = (width + TILE_WIDTH - 1) / TILE_WIDTH;
    tiledConvolution1D<<<numBlocks, TILE_WIDTH + mask_width - 1>>>(d_input, d_output, width, mask_width);
    cudaMemcpy(h_output, d_output, width * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Output after tiled 1D convolution:\n");
    for (int i = 0; i < width; i++) {
        printf("%.2f ", h_output[i]);
    }

    cudaFree(d_input); cudaFree(d_output);
    return 0;
}
