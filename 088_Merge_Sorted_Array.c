#include <stdio.h>

void merge(int *nums1, int nums1Size, int m, int *nums2, int nums2Size, int n) {
    while (m && n) {
        nums1[m + n] = nums1[m - 1] > nums2[n - 1] ? nums1[--m] : nums2[--n];
    }
    while (n) {
        nums1[n] = nums2[--n];
    }
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
        int nums1[6];
        int nums2[6];
        int m, n;
    } tc[] = {
        {.nums1 = {1,2,3,0,0,0}, .m = 3, .nums2 = {2,5,6}, .n = 3},
        {.nums1 = {1}, .m = 1, .n = 0},
        {.nums1 = {0}, .m = 0, .nums2 = {1}, .n = 1}};

    for (int i = 0; i < sizeof(tc) / sizeof(tc[0]); i++) {
        printf("Example %d:\n", i + 1);
        printArray(tc[i].nums1, tc[i].m + tc[i].n, "Input: nums1");
        printf(", m = %d, ", tc[i].m);
        printArray(tc[i].nums2, tc[i].n, "nums2");
        printf(", n = %d\n", tc[i].n);
        merge(tc[i].nums1, 0, tc[i].m, tc[i].nums2, 0, tc[i].n);
        printArray(tc[i].nums1, tc[i].m + tc[i].n, "Output");
        printf("\n\n");
    }

    return 0;
}
