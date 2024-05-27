#include <stdbool.h>
#include <stdio.h>

bool isSubsequence(char *s, char *t) {
    while (*s) {
        if (!*t) {
            return false;
        }
        if (*s == *t++) {
            s++;
        }
    }
    return true;
}

int main() {
    struct {
        char *s, *t;
    } tc[] = {
        {.s = "abc", .t = "ahbgdc"},
        {.s = "axc", .t = "ahbgdc"},
        {.s = "", .t = "ahbgdc"}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printf("Input: s = \"%s\", t = \"%s\"\n", tc[i].s, tc[i].t);
        printf("Output: %s\n\n", isSubsequence(tc[i].s, tc[i].t) ? "true" : "false");
    }

    return 0;
}
