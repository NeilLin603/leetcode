#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isPalindrome(char *s) {
    char *str = (char *)malloc(strlen(s)), *ptr = str;
    do {
        if (*s >= 'a' && *s <= 'z' || *s >= '0' && *s <= '9') {
            *ptr++ = *s;
        } else if (*s >= 'A' && *s <= 'Z') {
            *ptr++ = *s - 'A' + 'a';
        } else;
    } while (*s++);
    s = str;
    while (s < --ptr) {
        if (*s++ != *ptr) {
            free(str);
            return false;
        }
    }
    free(str);
    return true;
}

int main() {
    char *s[] = {"A man, a plan, a canal: Panama",
                 "race a car", " ", "0P"};
    int sSize = sizeof(s) / sizeof(s[0]);

    for (int i = 0; i < sSize; i++) {
        printf("Example %d:\n", i + 1);
        printf("Input: s = \"%s\"\n", s[i]);
        if (isPalindrome(s[i])) {
            printf("Output: true\n\n");
        } else {
            printf("Output: false\n\n");
        }
    }

    return 0;
}
