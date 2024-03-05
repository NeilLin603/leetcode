#include <stdio.h>

int searchInsert(int *nums, int numsSize, int target) {
    int i = 0, j;
    while (i < numsSize) {
        j = i + numsSize >> 1;
        if (nums[j] > target) {
            numsSize = j;
        } else if (nums[j] < target) {
            i = j + 1;
        } else {
            return j;
        }
    }
    return i;
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
    int nums[] = {1,3,5,6}, numsSize = sizeof(nums) / sizeof(nums[0]);
    int target[] = {5,2,7,0}, targetSize = sizeof(target) / sizeof(target[0]);

    for (int i = 0; i < targetSize; i++) {
        printf("Example %d:\n", i + 1);
        printArray(nums, numsSize, "Input: nums");
        printf(", target = %d\n", target[i]);
        printf("Output: %d\n\n", searchInsert(nums, numsSize, target[i]));
    }

    return 0;
}
