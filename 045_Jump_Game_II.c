#include <stdio.h>

int jump(int *nums, int numsSize) {
    if (numsSize == 1) {
        return 0;
    }
    int ret = nums[0], step = 1;
    for (int i = 1; i < numsSize - 1; i++) {
        if (nums[i] < nums[i - 1] - 1) {
            nums[i] = nums[i - 1] - 1;
        }
        if (!--ret) {
            ret = nums[i];
            step++;
        }
    }
    return step;
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
        int nums[5], numsSize;
    } tc[] = {
        {.nums = {2,3,1,1,4}, .numsSize = 5},
        {.nums = {2,3,0,1,4}, .numsSize = 5}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printArray(tc[i].nums, tc[i].numsSize, "Input: nums");
        printf("Output: %d\n\n", jump(tc[i].nums, tc[i].numsSize));
    }

    return 0;
}
