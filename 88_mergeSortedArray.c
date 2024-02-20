#include <stdio.h>

typedef struct {
    int nums1[6];
    int nums2[6];
    int m, n;
} Test_t;

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
    Test_t test[] = {
        {.nums1 = {1,2,3,0,0,0}, .m = 3, .nums2 = {2,5,6}, .n = 3},
        {.nums1 = {1}, .m = 1, .n = 0},
        {.nums1 = {0}, .m = 0, .nums2 = {1}, .n = 1}};
    for (int i = 0; i < sizeof(test) / sizeof(test[0]); i++) {
        printArray(test[i].nums1, test[i].m + test[i].n, "Input: nums1");
        printf(", m = %d, ", test[i].m);
        printArray(test[i].nums2, test[i].n, "nums2");
        printf(", n = %d\n", test[i].n);
        merge(test[i].nums1, 0, test[i].m, test[i].nums2, 0, test[i].n);
        printArray(test[i].nums1, test[i].m + test[i].n, "Output");
        printf("\n\n");
    }
    return 0;
}
