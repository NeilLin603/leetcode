#include <stdio.h>

int removeDuplicates(int *nums, int numsSize) {
    int count = 0, j = 0;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] != nums[j]) {
            count = 0;
        } else if (count++) {
            continue;
        } else;
        nums[++j] = nums[i];
    }
    return j + 1;
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
        int nums[9];
        int numsSize;
    } tc[] = {
        {.nums = {1,1,1,2,2,3}, .numsSize = 6},
        {.nums = {0,0,1,1,1,1,2,3,3}, .numsSize = 9}};

    for (int i = 0; i < sizeof(tc) / sizeof(tc[0]); i++) {
        printf("Example %d:\nInput: ", i + 1);
        printArray(tc[i].nums, tc[i].numsSize, "nums");
        printf("Output: %d, ", removeDuplicates(tc[i].nums, tc[i].numsSize));
        printArray(tc[i].nums, tc[i].numsSize, "nums");
        printf("\n");
    }

    return 0;
}
