#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *plusOne(int *digits, int digitsSize, int *returnSize) {
    int *result = (int *)malloc((digitsSize + 1) * sizeof(int));
    *returnSize = digitsSize;
    result[digitsSize] = 0;
    while (digitsSize--) {
        if (digits[digitsSize] != 9) {
            result[digitsSize] = digits[digitsSize] + 1;
            while (digitsSize--) {
                result[digitsSize] = digits[digitsSize];
            }
            return result;
        }
        result[digitsSize] = 0;
    }
    result[0] = 1;
    *returnSize += 1;
    return result;
}

void printArray(const int *nums, int numsSize, const char* name) {
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
        int digits[10], digitsSize;
    } tc[] = {
        {.digits = {1,2,3}, .digitsSize = 3},
        {.digits = {4,3,2,1}, .digitsSize = 4},
        {.digits = {9}, .digitsSize = 1}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);
    int *output, outSize;

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printArray(tc[i].digits, tc[i].digitsSize, "Input: digits");
        output = plusOne(tc[i].digits, tc[i].digitsSize, &outSize);
        printArray(output, outSize, "Output");
        printf("\n");
        free(output);
    }

    return 0;
}
