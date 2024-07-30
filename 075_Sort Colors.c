#include <stdio.h>

void sortColors(int *nums, int numsSize) {
    int w = numsSize, b = numsSize; // The minimum indexes of white and blue
    for (int i = 0; i < numsSize; i++) {
        // Initialize the indexes
        if (nums[i] == 1 && w > i) {
            w = i;
        } else if (nums[i] == 2 && b > i) {
            b = i;
        } else;

        // Swap colors
        if (!nums[i]) {
            if (i > w) { /* Swap 0 and 1 */
                nums[w++] = 0;
                nums[i] = 1;
            } else if (i > b) { /* Swap 0 and 2 */
                nums[b++] = 0;
                nums[i] = 2;
            } else;
        }
        if (nums[i] == 1 && i > b) { /* Swap 1 and 2 */
            if (w > b) {
                w = b;
            }
            nums[b++] = 1;
            nums[i] = 2;
        }
    }
}

void printArray(int *nums, int numsSize, char *name) {
    printf("%s [", name);
    if (numsSize) {
        printf("%d", *nums);
        for (int i = 1; i < numsSize; i++) {
            printf(",%d", nums[i]);
        }
    }
    printf("]\n");
}

int main() {
    struct {
        int nums[8], numsSize;
    } tc[] = {
        {.nums = {2,0,2,1,1,0}, .numsSize = 6},
        {.nums = {2,0,1}, .numsSize = 3}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        printArray(tc[i].nums, tc[i].numsSize, "Input: nums =");

        // Output
        sortColors(tc[i].nums, tc[i].numsSize);
        printArray(tc[i].nums, tc[i].numsSize, "Output:");
        printf("\n");
    }

    return 0;
}
