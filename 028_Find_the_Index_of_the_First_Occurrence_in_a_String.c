#include <stdio.h>

int strStr(char *haystack, char *needle) {
    int i = 0, j = 0;
    while (needle[j]) {
        if (haystack[i + j] != needle[j++]) {
            if (!haystack[++i]) {
                return -1;
            }
            j = 0;
        }
    }
    return i;
}

int main() {
    struct TestCase {
        char *haystack, *needle;
    } tc[] = {
        {.haystack = "sadbutsad", .needle = "sad"},
        {.haystack = "leetcode", .needle = "leeto"},
        {.haystack = "mississipp", .needle = "issip"}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printf("Input: haystack = \"%s\", needle = \"%s\"\n", tc[i].haystack, tc[i].needle);
        printf("Output: %d\n\n", strStr(tc[i].haystack, tc[i].needle));
    }

    return 0;
}
