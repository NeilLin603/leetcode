#include <stdio.h>

// x^5 = x^2 * x^2 * x = y * y * x
// x^4 = x^2 * x^2     = y * y
// x^n = x^(n/2) * x^(n/2) (* x)
double myPowSub(double x, int n) {
    if (!n) {
        return 1.0;
    }
    double y = myPowSub(x, n >> 1);
    return n & 1 ? y * y * x : y * y;
}

double myPow(double x, int n) {
    if (n >= 0) {
        return myPowSub(x, n);
    }
    if (n != 0x80000000) {
        return 1.0 / myPowSub(x, -n);
    }
    double y = myPowSub(x, 0x40000000);
    y *= y;
    return 1.0 / y;
}

int main() {
    struct TestCase {
        double x;
        int n;
    } tc[] = {
        {.x = 2.0, .n = 10},
        {.x = 2.1, .n = 3},
        {.x = 2.0, .n = -2}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printf("Input: x = %.5f, n = %d\n", tc[i].x, tc[i].n);
        printf("Output: %.5f\n\n", myPow(tc[i].x, tc[i].n));
    }

    return 0;
}
