#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

char *addBinary(char *a, char *b) {
    int aLen = 1, bLen = 1;
    while (*++a) {
        aLen++;
    }
    while (*++b) {
        bLen++;
    }
    int idx = MAX(aLen, bLen) + 1;
    char *str = (char *)calloc((idx + 1), sizeof(char));
    str[--idx] = '0';
    while (aLen && bLen) {
        if (str[idx] == '1') {
            str[idx--] = *--a ^ *--b ? '0' : '1';
            str[idx] = *a == '1' || *b == '1' ? '1' : '0';
        } else {
            str[idx--] = *--a ^ *--b ? '1' : '0';
            str[idx] = *a == '1' && *b == '1' ? '1' : '0';
        }
        aLen--;
        bLen--;
    }
    while (aLen--) {
        str[idx - 1] = *--a == '1' && str[idx] == '1' ? '1' : '0';
        str[idx--] = str[idx] ^ *a ? '1' : '0';
    }
    while (bLen--) {
        str[idx - 1] = *--b == '1' && str[idx] == '1' ? '1' : '0';
        str[idx--] = str[idx] ^ *b ? '1' : '0';
    }
    return *str == '1' ? str : str + 1;
}

int main() {
    struct TestCase {
        char *a, *b;
    } tc[] = {
        {.a = "11", .b = "1"},
        {.a = "1010", .b = "1011"},
        {.a = "0", .b = "0"},
        {.a = "100", .b = "110010"}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);
    char *output;

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printf("Input: a = \"%s\", b = \"%s\"\n", tc[i].a, tc[i].b);
        output = addBinary(tc[i].a, tc[i].b);
        printf("Output: %s\n\n", output);
    }

    return 0;
}
