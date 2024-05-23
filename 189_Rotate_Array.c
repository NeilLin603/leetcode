#include <stdio.h>

#define SWAP(a, b) do { \
    (a) ^= (b); \
    (b) ^= (a); \
    (a) ^= (b); \
} while (0)

void rotate(int *nums, int numsSize, int k) {
    k %= numsSize;
    if (k) {
        for (int i = 0; i < k; i++) {
            SWAP(nums[i], nums[i + numsSize - k]);
        }
        rotate(nums + k, numsSize - k, k);
    }
}

void printArray(const int *nums, int numsSize, const char *name) {
    printf("%s [", name);
    if (numsSize) {
        printf("%d", *nums);
        while (--numsSize) {
            printf(",%d", *++nums);
        }
    }
    printf("]");
}

int main() {
    struct {
        int nums[100], numsSize, k;
    } tc[] = {
        {.nums = {1,2,3,4,5,6,7}, .numsSize = 7, .k = 3},
        {.nums = {-1,-100,3,99}, .numsSize = 4, .k = 2}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d\n", i + 1);

        // Input
        printArray(tc[i].nums, tc[i].numsSize, "Input: nums =");
        printf(", k = %d\n", tc[i].k);

        // Output
        rotate(tc[i].nums, tc[i].numsSize, tc[i].k);
        printArray(tc[i].nums, tc[i].numsSize, "Output:");
        printf("\n\n");
    }

    return 0;
}
