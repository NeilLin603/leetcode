#include <stdio.h>

#define SWAP(a, b) do { \
    (a) ^= (b); \
    (b) ^= (a); \
    (a) ^= (b); \
} while (0)

void quickSort(int *nums, int numsSize) {
    if (numsSize > 1) {
        int i = -1, j = numsSize, s = nums[numsSize >> 1];
        for (;;) {
            while (nums[++i] > s);
            while (nums[--j] < s);
            if (i >= j) {
                break;
            }
            SWAP(nums[i], nums[j]);
        }
        quickSort(nums, i);
        quickSort(nums + j + 1, numsSize - j - 1);
    }
}

int hIndex(int *citations, int citationsSize) {
    quickSort(citations, citationsSize);
    while (citationsSize--) {
        if (citations[citationsSize] > citationsSize) {
            break;
        }
    }
    return citationsSize + 1;
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
        int citations[5], citationsSize;
    } tc[] = {
        {.citations = {3,0,6,1,5}, .citationsSize = 5},
        {.citations = {1,3,1}, .citationsSize = 3}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printArray(tc[i].citations, tc[i].citationsSize, "Input: citations");
        printf("Output: %d\n\n", hIndex(tc[i].citations, tc[i].citationsSize));
    }

    return 0;
}
