#include <stdio.h>
#include <stdlib.h>

static inline int strLen(const char *s) {
    const char *t = s - 1;
    while (*++t);
    return t - s;
}

char *mergeAlternately(char *word1, char *word2) {
    char *s = (char *)malloc(strLen(word1) + strLen(word2) + 1);
    char *ret = s;
    while (*word1 && *word2) {
        *s++ = *word1++;
        *s++ = *word2++;
    }
    while (*word1) {
        *s++ = *word1++;
    }
    while (*word2) {
        *s++ = *word2++;
    }
    *s = '\0';
    return ret;
}

int main() {
    struct {
        char *word1, *word2;
    } tc[] = {
        {.word1 = "abc", .word2 = "pqr"},
        {.word1 = "ab", .word2 = "pqrs"},
        {.word1 = "abcd", .word2 = "pq"}
    };

    int tcSize = sizeof(tc) / sizeof(tc[0]);
    char *output;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        printf("Input: word1 = \"%s\", word2 = \"%s\"\n",
               tc[i].word1, tc[i].word2);

        // Output
        output = mergeAlternately(tc[i].word1, tc[i].word2);
        printf("Output: \"%s\"\n\n", output);
        free(output);
    }

    return 0;
}
