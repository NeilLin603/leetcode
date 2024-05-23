#include <stdio.h>

int removeDuplicates(int* nums, int numsSize) {
    int cnt = 0, k = 0;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] != nums[k]) {
            nums[++k] = nums[i];
            cnt = 0;
        } else {
            if (!cnt) {
                nums[++k] = nums[i];
                cnt++;
            }
        }
    }
    return k + 1;
}

void printArray(int *nums, int numsSize, char *name) {
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
