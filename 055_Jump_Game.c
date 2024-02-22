#include <stdio.h>
#include <stdbool.h>

bool canJump(int *nums, int numsSize) {
    for (int i = 0; i < numsSize - 1; i++) {
        if (!nums[i]) {
            return false;
        }
        if (nums[i + 1] < nums[i] - 1) {
            nums[i + 1] = nums[i] - 1;
        }
    }
    return true;
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
        {.nums = {3,2,1,0,4}, .numsSize = 5}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printArray(tc[i].nums, tc[i].numsSize, "Input: nums");
        if (canJump(tc[i].nums, tc[i].numsSize)) {
            printf("Output: true\n\n");
        } else {
            printf("Output: false\n\n");
        }
    }

    return 0;
}
