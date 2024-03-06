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
    int strLen = MAX(aLen, bLen) + 1;
    char *str = (char *)malloc((strLen + 1) * sizeof(char)), ovf = '0';
    str[strLen--] = '\0';
    while (aLen && bLen) {
        if (ovf == '1') {
            str[strLen--] = *--a ^ *--b ? '0' : '1';
            ovf = *a == '1' || *b == '1' ? '1' : '0';
        } else {
            str[strLen--] = *--a ^ *--b ? '1' : '0';
            ovf = *a & *b;
        }
        aLen--;
        bLen--;
    }
    while (aLen--) {
        if (ovf == '1') {
            if (*--a == '1') {
                str[strLen--] = '0';
            } else {
                str[strLen--] = '1';
                ovf = '0';
            }
        } else {
            str[strLen--] = *--a;
        }
    }
    while (bLen--) {
        if (ovf == '1') {
            if (*--b == '1') {
                str[strLen--] = '0';
            } else {
                str[strLen--] = '1';
                ovf = '0';
            }
        } else {
            str[strLen--] = *--b;
        }
    }
    if (ovf == '1') {
        str[0] = '1';
    } else {
        do {
            str[strLen] = str[strLen + 1];
        } while (str[++strLen]);
    }
    return str;
}

int main() {
    struct TestCase {
        char *a, *b;
    } tc[] = {
        {.a = "11", .b = "1"},
        {.a = "1010", .b = "1011"},
        {.a = "0", .b = "0"}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);
    char *output;

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printf("Input: a = \"%s\", b = \"%s\"\n", tc[i].a, tc[i].b);
        output = addBinary(tc[i].a, tc[i].b);
        printf("Output: %s\n\n", output);
        free(output);
    }

    return 0;
}
