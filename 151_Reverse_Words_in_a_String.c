#include <stdio.h>

static inline void reverseBetween(char *s1, char *s2) {
    while (s1 < s2) {
        *s1 ^= *s2;
        *s2 ^= *s1;
        *s1++ ^= *s2--;
    }
}

char *reverseWords(char *s) {
    // Remove redundant spaces
    int isSpaced = 1;
    char *s1 = s - 1, *s2 = s - 1;
    while (*++s1) {
        if (*s1 != ' ') {
            *++s2 = *s1;
            isSpaced = 0;
        } else {
            if (!isSpaced) {
                *++s2 = *s1;
                isSpaced = 1;
            }
        }
    }
    if (!isSpaced) {
        s2++;
    }
    *s2 = '\0';

    reverseBetween(s, s2 - 1); // Reverse the entire string

    // Reverse each word
    s2 = s - 1;
    do {
        s1 = s2;
        while (*++s2 && *s2 != ' ');
        reverseBetween(s1 + 1, s2 - 1);
    } while (*s2);

    return s;
}

int main() {
    char s[][32] = {"the sky is blue", "  hello world  ", "a good   example"};
    int sSize = sizeof(s) / sizeof(s[0]);

    for (int i = 0; i < sSize; i++) {
        printf("Example %d:\n", i + 1);
        printf("Input: s = \"%s\"\n", s[i]);
        printf("Output: \"%s\"\n\n", reverseWords(s[i]));
    }

    return 0;
}
