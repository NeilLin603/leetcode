#include <stdio.h>

int maxProfit(int *prices, int pricesSize) {
    int profit = 0;
    while (--pricesSize) {
        if (*(prices + 1) > *prices) {
            profit += *(prices + 1) - *prices;
        }
        prices++;
    }
    return profit;
}

void printArray(int const *nums, int numsSize, char const *name) {
    printf("%s = [", name);
    if (numsSize) {
        printf("%d", *nums);
        while (--numsSize) {
            printf(",%d", *++nums);
        }
    }
    printf("]\n");
}

int main() {
    struct TestCase {
        int prices[6], pricesSize;
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
