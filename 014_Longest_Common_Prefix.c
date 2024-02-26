#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longestCommonPrefix(char **strs, int strsSize) {
    char *str = (char *)malloc(strlen(strs[0]) + 1);
    int j = 0;
    do {
        str[j] = strs[0][j];
    } while (str[j++]);
    if (strsSize > 1) {
        for (int i = 1; i < strsSize; i++) {
            j = -1;
            while (str[++j] && str[j] == strs[i][j]);
            str[j] = '\0';
        }
    }
    return str;
}

void printArray(char **strs, int strsSize, char *name) {
    printf("%s = [", name);
    if (strsSize) {
        printf("\"%s\"", strs[0]);
        for (int i = 1; i < strsSize; i++) {
            printf(",\"%s\"", strs[i]);
        }
    }
    printf("]\n");
}

int main() {
    struct TestCase {
        char *strs[200];
        int strsSize;
    } tc[] = {
        {.strs = {"flower", "flow", "flight"}, .strsSize = 3},
        {.strs = {"dog", "racecar", "car"}, .strsSize = 3}};
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    char *str;
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printArray(tc[i].strs, tc[i].strsSize, "Input: strs");
        str = longestCommonPrefix(tc[i].strs, tc[i].strsSize);
        printf("Output: \"%s\"\n\n", str);
        free(str);
    }

    return 0;
}
