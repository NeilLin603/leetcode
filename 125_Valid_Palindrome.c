#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isPalindrome(char *s) {
    char *str = (char *)malloc(strlen(s));
    int i = 0, j = 0;
    do {
        if (s[i] >= 'a' && s[i] <= 'z' || s[i] >= '0' && s[i] <= '9') {
            str[j++] = s[i];
        } else if (s[i] >= 'A' && s[i] <= 'Z') {
            str[j++] = s[i] - 'A' + 'a';
        } else;
    } while (s[i++]);
    i = 0;
    int mid = j >> 1;
    while (i < mid) {
        if (str[i++] != str[--j]) {
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
