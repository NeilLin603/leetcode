#include <stdio.h>

void swap(int *a, int *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

void quickSort(int *nums, int numsSize) {
    if (numsSize > 1) {
        int s = nums[numsSize >> 1], i = -1, j = numsSize;
        while (1) {
            while (nums[++i] > s);
            while (nums[--j] < s);
            if (i >= j) {
                break;
            }
            swap(nums + i, nums + j);
        }
        quickSort(nums, i);
        quickSort(nums + j + 1, numsSize - j - 1);
    }
}

int hIndex(int *citations, int citationsSize) {
    quickSort(citations, citationsSize);
    int i;
    for (i = 0; i < citationsSize; i++) if (citations[i] < i + 1) {
        break;
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
    printf("]\n");
}

int main() {
    struct TestCase {
        int citations[5], citationsSize;
    } tc[] = {
        {.citations = {3,0,6,1,5}, .citationsSize = 5},
        {.citations = {1,3,1}, .citationsSize = 3}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);
    
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printArray(tc[i].citations, tc[i].citationsSize, "Input: citations");
        printf("Output: %d\n\n", hIndex(tc[i].citations, tc[i].citationsSize));
    }

    return 0;
}
