#include <stdio.h>

int majorityElement(int *nums, int numsSize) {
    int cnt = 1, maj = *nums;
    while (--numsSize) {
        if (maj == *++nums) {
            cnt++;
        } else {
            if (!--cnt) {
                cnt = 1;
                maj = *nums;
            }
        }
    }
    return maj;
}

void printArray(int *nums, int numsSize, const char *name) {
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
        int nums[7];
        int numsSize;
    } tc[] = {
        {.nums = {3,2,3}, .numsSize = 3},
        {.nums = {2,2,1,1,1,2,2}, .numsSize = 7}};

    for (int i = 0; i < sizeof(tc) / sizeof(tc[0]); i++) {
        printf("Example %d:\n", i + 1);
        printArray(tc[i].nums, tc[i].numsSize, "Input: nums");
        printf("Output: %d\n\n", majorityElement(tc[i].nums, tc[i].numsSize));
    }

    return 0;
}
