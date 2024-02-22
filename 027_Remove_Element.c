#include <stdio.h>

int removeElement(int *nums, int numsSize, int val) {
    int j = 0;
    for (int i = 0; i < numsSize; i++) if (nums[i] != val) {
        nums[j++] = nums[i];
    }
    return j;
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
        int numsSize, val;
    } tc[] = {
        {.nums = {3,2,2,3}, .numsSize = 4, .val = 3},
        {.nums = {0,1,2,2,3,0,4,2}, .numsSize = 8, .val = 2}};

    for (int i = 0; i < sizeof(tc) / sizeof(tc[0]); i++) {
        printf("Example %d:\n", i + 1);
        printArray(tc[i].nums, tc[i].numsSize, "Input: nums");
        printf(", val = %d\n", tc[i].val);
        printf("Output: %d, ", removeElement(tc[i].nums, tc[i].numsSize, tc[i].val));
        printArray(tc[i].nums, tc[i].numsSize, "nums");
        printf("\n\n");
    }

    return 0;
}
