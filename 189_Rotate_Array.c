#include <stdio.h>

void swap(int *a, int *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void rotate(int *nums, int numsSize, int k) {
    k %= numsSize;
    if (!k) {
        return;
    }
    for (int i = 0; i < k; i++) {
        swap(nums + i, nums + numsSize - k + i);
    }
    numsSize -= k;
    rotate(nums + k, numsSize, numsSize < k ? k - numsSize : k);
}

void printArray(const int *nums, int numsSize, const char *name) {
    printf("%s = [", name);
    if (numsSize) {
        printf("%d", nums[0]);
        for (int i = 1; i < numsSize; i++) {
            printf(",%d", nums[i]);
        }
    }
    printf("]");
}

int main() {
    struct TestCase {
        int nums[8];
        int numsSize, k;
    } tc[] = {
        {.nums = {1,2,3,4,5,6,7}, .numsSize = 7, .k = 3},
        {.nums = {-1,-100,3,99}, .numsSize = 4, .k = 2}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printArray(tc[i].nums, tc[i].numsSize, "Input: nums");
        rotate(tc[i].nums, tc[i].numsSize, tc[i].k);
        printf(", k = %d\n", tc[i].k);
        printArray(tc[i].nums, tc[i].numsSize, "Output: nums");
        printf("\n\n");
    }

    return 0;
}
