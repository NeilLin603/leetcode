#include <stdio.h>

int singleNumber(int *nums, int numsSize) {
    int bitSum, result = 0;
    for (int i = 0; i < 32; i++) {
        bitSum = 0;
        for (int j = 0; j < numsSize; j++) {
            bitSum += nums[j] & 1;
            nums[j] >>= 1;
        }
        result |= (unsigned int)bitSum % 3 << i;
    }
    return result;
}

void printArray(const int *nums, int numsSize, const char *name) {
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
        int nums[10], numsSize;
    } tc[] = {
        {.nums = {2,2,3,2}, .numsSize = 4},
        {.nums = {0,1,0,1,0,1,99}, .numsSize = 7}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printArray(tc[i].nums, tc[i].numsSize, "Input: nums");
        printf("Output: %d\n\n", singleNumber(tc[i].nums, tc[i].numsSize));
    }

    return 0;
}
