#include <stdio.h>

// sqrt(2^31 - 1) < sqrt(2^31) = sqrt(2) * sqrt(2^30)
// = 1.414 * 2^15 < 1.5 * 0x8000 = 0xc000
int mySqrt(int x) {
    unsigned int lower = 0, upper = 0xc000, mid, midSqr;
    while (upper - lower > 1) {
        mid = lower + upper >> 1;
        midSqr = mid * mid;
        if (x > midSqr) {
            lower = mid;
        } else if (x < midSqr) {
            upper = mid;
        } else {
            return mid;
        }
    }
    return lower;
}

int main() {
    int x[] = {4,8}, xSize = sizeof(x) / sizeof(x[0]);

    for (int i = 0; i < xSize; i++) {
        printf("Example %d:\n", i + 1);
        printf("Input: x = %d\n", x[i]);
        printf("Output: %d\n\n", mySqrt(x[i]));
    }

    return 0;
}
