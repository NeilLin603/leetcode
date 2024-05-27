#include <stdbool.h>
#include <stdio.h>

int strLen(char *s) {
    char *t = s - 1;
    while (*++t);
    return t - s;
}

bool isPalindrome(char *s) {
    int i = -1, j = strLen(s);
    char c1, c2;
    for (;;) {
        do {
            if (++i >= j) {
                return true;
            }
            c1 = s[i];
            if (c1 >= 'A' && c1 <= 'Z') {
                c1 -= 'S' - 's';
            }
        } while ((c1 < 'a' || c1 > 'z') && (c1 < '0' || c1 > '9'));
        do {
            if (--j <= i) {
                return true;
            }
            c2 = s[j];
            if (c2 >= 'A' && c2 <= 'Z') {
                c2 += 'n' - 'N';
            }
        } while ((c2 < 'a' || c2 > 'z') && (c2 < '0' || c2 > '9'));
        if (c1 != c2) {
            return false;
        }
    }
}

int main() {
    char *s[] = {"A man, a plan, a canal: Panama",
                 "race a car", " ", "0P"};
    int sSize = sizeof(s) / sizeof(s[0]);

    for (int i = 0; i < sSize; i++) {
        printf("Example %d:\n", i + 1);
        printf("Input: s = \"%s\"\n", s[i]);
        printf("Output: %s\n\n", isPalindrome(s[i]) ? "true" : "false");
    }

    return 0;
}
