#include <stdio.h>
#define MAX_ITEMS 10
#define MAX_FRIENDS 5

__global__ void calculateTotal(int *choices, float *prices, float *total, int itemsPerFriend) {
    int friendId = threadIdx.x;

    float sum = 0;
    for (int i = 0; i < itemsPerFriend; i++) {
        int itemIndex = choices[friendId * itemsPerFriend + i];
        if (itemIndex >= 0)
            sum += prices[itemIndex];
    }
    total[friendId] = sum;
}

int main() {
    int numItems, numFriends, itemsPerFriend;
    float h_prices[MAX_ITEMS];
    int h_choices[MAX_FRIENDS * MAX_ITEMS];
    float h_total[MAX_FRIENDS];

    printf("Enter number of items in menu: ");
    scanf("%d", &numItems);
    printf("Enter prices for %d items:\n", numItems);
    for (int i = 0; i < numItems; i++) {
        printf("Price of item %d: ", i);
        scanf("%f", &h_prices[i]);
    }

    printf("\nEnter number of friends: ");
    scanf("%d", &numFriends);
    printf("Enter number of items each friend will purchase: ");
    scanf("%d", &itemsPerFriend);

    for (int i = 0; i < numFriends; i++) {
        printf("\nEnter item indices (0-%d) for Friend %d:\n", numItems-1, i);
        for (int j = 0; j < itemsPerFriend; j++) {
            printf("Item %d: ", j+1);
            scanf("%d", &h_choices[i * itemsPerFriend + j]);
        }
    }

    float *d_prices, *d_total;
    int *d_choices;
    cudaMalloc(&d_prices, numItems * sizeof(float));
    cudaMalloc(&d_choices, numFriends * itemsPerFriend * sizeof(int));
    cudaMalloc(&d_total, numFriends * sizeof(float));

    cudaMemcpy(d_prices, h_prices, numItems * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_choices, h_choices, numFriends * itemsPerFriend * sizeof(int), cudaMemcpyHostToDevice);

    calculateTotal<<<1, numFriends>>>(d_choices, d_prices, d_total, itemsPerFriend);
    cudaMemcpy(h_total, d_total, numFriends * sizeof(float), cudaMemcpyDeviceToHost);

    float finalTotal = 0;
    for (int i = 0; i < numFriends; i++) {
        printf("Friend %d total: %.2f\n", i, h_total[i]);
        finalTotal += h_total[i];
    }
    printf("Total purchase by all friends: %.2f\n", finalTotal);

    cudaFree(d_prices); cudaFree(d_choices); cudaFree(d_total);
    return 0;
}
