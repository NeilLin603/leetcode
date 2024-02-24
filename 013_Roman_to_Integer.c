#include <stdio.h>

int romanToInt(char *s) {
    int i = -1, n = 0;
    while (s[++i]) {
        switch (s[i]) {
        case 'I':
            n += s[i + 1] != 'V' && s[i + 1] != 'X' ? 1 : -1;
            break;
        case 'V':
            n += 5;
            break;
        case 'X':
            n += s[i + 1] != 'L' && s[i + 1] != 'C' ? 10 : -10;
            break;
        case 'L':
            n += 50;
            break;
        case 'C':
            n += s[i + 1] != 'D' && s[i + 1] != 'M' ? 100 : -100;
            break;
        case 'D':
            n += 500;
            break;
        case 'M':
            n += 1000;
            break;
        default:
            break;
        }
    }
    return n;
}

int main() {
    char *s[] = {"III", "LVIII", "MCMXCIV"};
    int sSize = sizeof(s) / sizeof(s[0]);

    for (int i = 0; i < sSize; i++) {
        printf("Example %d:\nInput: s = \"%s\"\n", i + 1, s[i]);
        printf("Output: %d\n\n", romanToInt(s[i]));
    }

    return 0;
}
