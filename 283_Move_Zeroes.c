#include <stdio.h>

#define APPROACH 1 // 1 or 2

#if (APPROACH == 1) /* 1st approach */
#define SWAP(a, b)                                                             \
    (a) ^= (b);                                                                \
    (b) ^= (a);                                                                \
    (a) ^= (b)

void moveZeroes(int *nums, int numsSize) {
    while (numsSize && *nums) {
        nums++;
        numsSize--;
    }
    int j = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i]) {
            SWAP(nums[i], nums[j]);
            j++;
        }
    }
}
#elif (APPROACH == 2) /* 2nd approach */
#include <stdlib.h>
void moveZeroes(int *nums, int numsSize) {
    int *nums2 = (int *)malloc(sizeof(int) * numsSize), i;
    for (i = 0; i < numsSize; i++) {
        nums2[i] = nums[i];
    }
    int j = numsSize;
    for (i = 0; i < numsSize; i++) {
        if (nums2[i]) {
            *nums++ = *(nums2 + i);
            j--;
        }
    }
    while (j--) {
        *nums++ = 0;
    }
    free(nums2);
}
#else
#error Invalid APPROACH No.
#endif

void printArray(const int *nums, int numsSize, const char *title) {
    printf("%s [", title);
    if (numsSize) {
        printf("%d", *nums);
        for (int i = 1; i < numsSize; i++) {
            printf(",%d", *(nums + i));
        }
    }
    printf("]\n");
}

int main() {
    struct {
        int nums[5], numsSize;
    } tc[] = {
        {.nums = {0,1,0,3,12}, .numsSize = 5},
        {.nums = {0}, .numsSize = 1}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        printArray(tc[i].nums, tc[i].numsSize, "Input: nums");

        // Output
        moveZeroes(tc[i].nums, tc[i].numsSize);
        printArray(tc[i].nums, tc[i].numsSize, "Output");
        printf("\n");
    }

    return 0;
}
