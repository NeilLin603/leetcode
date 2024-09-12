#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 256 // Total count of all ascii characters

bool isIsomorphic(char *s, char *t) {
    // Init two hash tables
    char sTable[TABLE_SIZE], tTable[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        sTable[i] = tTable[i] = '\0';
    }

    do {
        if (sTable[*s]) { /* Hash hit */
            if (sTable[*s] != *t) {
                return false; // Return false if the characters not match
            }
        } else { /* Hash miss */
            sTable[*s] = *t; // Add *t into table
        }

        if (tTable[*t]) { /* Hash hit */
            if (tTable[*t] != *s) {
                return false; // Return false if the characters not match
            }
        } else { /* Hash miss */
            tTable[*t] = *s; // Add *s into table
        }
        t++;
    } while (*++s);
    return true;
}

int main() {
    struct {
        char *s, *t;
    } tc[] = {
        {.s = "egg", .t = "add"},
        {.s = "foo", .t = "bar"},
        {.s = "paper", .t = "title"},
        {.s = "babc", .t = "baba"}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        printf("Input: s = \"%s\", t = \"%s\"\n", tc[i].s, tc[i].t);

        // Output
        if (isIsomorphic(tc[i].s, tc[i].t)) {
            printf("Output: true\n\n");
        } else {
            printf("Output: false\n\n");
        }
    }
    return 0;
}
