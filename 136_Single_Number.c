#include <stdio.h>

int singleNumber(int *nums, int numsSize) {
    while (--numsSize) {
        *nums ^= *nums++;
    }
    return *nums;
}

void printArray(const int *nums, int numsSize, const char *name) {
    printf("%s = [", name);
    if (numsSize) {
        printf("%d", *nums++);
        while (--numsSize) {
            printf(",%d", *nums++);
        }
    }
    printf("]\n");
}

int main() {
    struct TestCase {
        int nums[5], numsSize;
    } tc[] = {
        {.nums = {2,2,1}, .numsSize = 3},
        {.nums = {4,1,2,1,2}, .numsSize = 5},
        {.nums = {1}, .numsSize = 1}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printArray(tc[i].nums, tc[i].numsSize, "Input: nums");
        printf("Output: %d\n\n", singleNumber(tc[i].nums, tc[i].numsSize));
    }

    return 0;
}
