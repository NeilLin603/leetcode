#include <stdio.h>

int maxProfit(int *prices, int pricesSize) {
    int profit = 0;
    for (int i = 1; i < pricesSize; i++) if (prices[i] > prices[i - 1]) {
        profit += prices[i] - prices[i - 1];
    }
    return profit;
}

void printArray(const int *nums, int numsSize, const char *name) {
    printf("%s = [", name);
    if (numsSize) {
        printf("%d", nums[0]);
        for (int i = 1; i < numsSize; i++) {
            printf(",%d", nums[i]);
        }
    }
    printf("]\n");
}

int main() {
    struct TestCase {
        int prices[6];
        int pricesSize;
    } tc[] = {
        {.prices = {7,1,5,3,6,4}, .pricesSize = 6},
        {.prices = {1,2,3,4,5}, .pricesSize = 5},
        {.prices = {7,6,4,3,1}, .pricesSize = 5}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printArray(tc[i].prices, tc[i].pricesSize, "Input: prices");
        printf("Output: %d\n\n", maxProfit(tc[i].prices, tc[i].pricesSize));
    }

    return 0;
}
