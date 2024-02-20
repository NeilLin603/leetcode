#include <stdio.h>

typedef struct {
    int nums[8];
    int val, numsSize;
} Example_t;

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
    Example_t ex[] = {
        {.nums = {3,2,2,3}, .val = 3, .numsSize = 4},
        {.nums = {0,1,2,2,3,0,4,2}, .val = 2, .numsSize = 8}};

    for (int i = 0; i < sizeof(ex) / sizeof(ex[0]); i++) {
        printf("Example %d:\n", i + 1);
        printArray(ex[i].nums, ex[i].numsSize, "Input: nums");
        printf(", val = %d\n", ex[i].val);
        printf("Output: %d, ", removeElement(ex[i].nums, ex[i].numsSize, ex[i].val));
        printArray(ex[i].nums, ex[i].numsSize, "nums");
        printf("\n\n");
    }

    return 0;
}
