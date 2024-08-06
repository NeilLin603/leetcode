#include <stdint.h>
#include <stdio.h>

#define METHOD 1

#if (METHOD == 1)
uint32_t reverseBits(uint32_t n) {
    uint32_t m = 0;
    for (int i = 0; i < 32; i++) {
        m = m << 1 | n & 1;
        n >>= 1;
    }
    return m;
}
#elif (METHOD == 2)
uint32_t reverseBits(uint32_t n) {
    n = (n & 0xffff0000) >> 16 | (n & 0x0000ffff) << 16;
    n = (n & 0xff00ff00) >> 8 | (n & 0x00ff00ff) << 8;
    n = (n & 0xf0f0f0f0) >> 4 | (n & 0x0f0f0f0f) << 4;
    n = (n & 0xcccccccc) >> 2 | (n & 0x33333333) << 2;
    n = (n & 0xaaaaaaaa) >> 1 | (n & 0x55555555) << 1;
    return n;
}
#else
#error "Unrecognized define of METHOD."
#endif

void printBinary(uint32_t n) {
    uint32_t tmp = 0x80000000;
    for (int i = 0; i < 32; i++) {
        printf(n & tmp ? "1" : "0");
        tmp >>= 1;
    }
}

int main() {
    uint32_t n[] = {43261596, 4294967293}, nSize = sizeof(n) / sizeof(n[0]);

    for (int i = 0; i < nSize; i++) {
        printf("Example %d:\nInput: n = ", i + 1);
        printBinary(n[i]);
        n[i] = reverseBits(n[i]);
        printf("\nOutput: %u (", n[i]);
        printBinary(n[i]);
        printf(")\n\n");
    }

    return 0;
}
