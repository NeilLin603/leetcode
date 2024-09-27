#include <stdbool.h>
#include <stdio.h>

#define TABLE_SIZE 26 // Total count of the lowercase English letters

#define HASH(letter) ((letter) - 'a') // Macro for the hash function

bool isAnagram(char *s, char *t) {
    // Initialize a hash table
    int table[TABLE_SIZE], letterCount = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = 0;
    }

    // Put all letters in s to the hash table
    while (*s) {
        table[HASH(*s++)]++;
        letterCount++;
    }

    // Check if every letters in t is in the hash table
    while (*t) {
        if (!table[HASH(*t++)]--) {
            return false;
        }
        letterCount--;
    }
    return !letterCount;
}

int main() {
    struct {
        char *s, *t;
    } tc[] = {
        {.s = "anagram", .t = "nagaram"},
        {.s = "rat", .t = "car"}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printf("Input: s = \"%s\", t = \"%s\"\n", tc[i].s, tc[i].t);
        if (isAnagram(tc[i].s, tc[i].t)) {
            printf("Output: true\n\n");
        } else {
            printf("Output: false\n\n");
        }
    }
    return 0;
}
