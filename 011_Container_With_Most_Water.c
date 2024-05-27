#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int maxArea(int *height, int heightSize) {
    int ret = 0, cont, i = 0, j = --heightSize;
    while (i < j) {
        cont = MIN(height[i], height[j]) * heightSize--;
        if (ret < cont) {
            ret = cont;
        }
        if (height[i] < height[j]) {
            i++;
        } else {
            j--;
        }
    }
    return ret;
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
    struct {
        int height[10], heightSize;
    } tc[] = {
        {.height = {1,8,6,2,5,4,8,3,7}, .heightSize = 9},
        {.height = {1,1}, .heightSize = 2},
        {.height = {1,2,4,3}, .heightSize = 4}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printArray(tc[i].height, tc[i].heightSize, "Input: height");
        printf("Output: %d\n\n", maxArea(tc[i].height, tc[i].heightSize));
    }

    return 0;
}
