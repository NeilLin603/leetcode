#include <stdio.h>

#if 0 // Original
int rangeBitwiseAnd(int left, int right) {
    int result = left & right, diff = left ^ right, i = 0;
    while (diff) {
        diff >>= 1;
        i++;
    }
    while (i--) {
        result &= ~(1U << i);
    }
    return result;
}
#else // Further optimize memory usage from above function
int rangeBitwiseAnd(int left, int right) {
    left ^= right;
    right &= left ^ right;
    unsigned int mask = 1;
    while (left) {
        right &= ~mask;
        mask <<= 1;
        left >>= 1;
    }
    return right;
}
#endif

int main() {
    struct TestCase {
        int left, right;
    } tc[] = {
        {.left = 5, .right = 7},
        {.left = 0, .right = 0},
        {.left = 1, .right = 2147483647}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printf("Input: left = %d, right = %d\n", tc[i].left, tc[i].right);
        printf("Output: %d\n\n", rangeBitwiseAnd(tc[i].left, tc[i].right));
    }

    return 0;
}
