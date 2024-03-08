#include <stdio.h>
#include <stdint.h>

int hammingWeight(uint32_t n) {
    int result = 0, i = 32;
    while (i--) {
        result += n & 1;
        n >>= 1;
    }
    return result;
}

void printBinary(uint32_t n, const char *name) {
    uint32_t tmp = 0x80000000;
    printf("%s = ", name);
    for (int i = 0; i < 32; i++) {
        printf(n & tmp ? "1" : "0");
        tmp >>= 1;
    }
    printf("\n");
}

int main() {
    uint32_t n[] = {11, 128, 0xfffffffd};
    int nSize = sizeof(n) / sizeof(n[0]);

    for (int i = 0; i < nSize; i++) {
        printf("Example %d:\n", i + 1);
        printBinary(n[i], "Input: n");
        printf("Output: %d\n\n", hammingWeight(n[i]));
    }

    return 0;
}
