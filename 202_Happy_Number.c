#include <stdbool.h>
#include <stdio.h>

int hash(int n) {
    int hashVal = 0, a;
    while (n) {
        a = n % 10;
        n /= 10;
        hashVal += a * a;
    }
    return hashVal;
}

#if 0
//! Since the number with the maximum square sum of digits is 1999999999, and
//! the max squre sum is 9 * 9^2 = 729. Besides, the min square sum is 1. Thus,
//! we can define the hash table with a size of 729, which is enough for
//! containing all the possible hashed number.
#define HASH_SIZE 730

bool isHappy(int n) {
    int hashTable[HASH_SIZE] = {0};
    while (n != 1) {
        n = hash(n);
        if (hashTable[n - 1]) {
            return false;
        }
        hashTable[n - 1] = 1;
    }
    return true;
}
#else
//! According to the above solution, we can observe that each number in the hash
//! table would be either 0 or 1. Thus, we can replace an entire 32-bit number
//! with just a single bit for the purpose of saving memory usage.
//!
//! An integer array of size 23 can exactly cover the 730 bits that are
//! required.
bool isHappy(int n) {
    int hashTable[23] = {0};
    unsigned int i, j;
    while (n != 1) {
        n = hash(n);
        i = n / 32;
        j = 1u << n % 32;
        if (hashTable[i] & j) {
            return false;
        }
        hashTable[i] |= j;
    }
    return true;
}
#endif

int main() {
    int n[] = {19, 2};
    int nSize = sizeof(n) / sizeof(n[0]);

    char *s;
    for (int i = 0; i < nSize; i++) {
        printf("Example %d:\n", i + 1);
        printf("Input = %d\n", n[i]);

        s = isHappy(n[i]) ? "true" : "false";
        printf("Output: %s\n\n", s);
    }
    return 0;
}
