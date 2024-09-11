#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Since the input strings contain only lower case English letters, a hash table
// with size of 26 can avoid any hash collision
#define TABLE_SIZE 26

/**
 * The hash function macro.
 */
#define hash(letter) ((letter) % TABLE_SIZE)

bool canConstruct(char *ransomNote, char *magazine) {
    // Init a hash table
    int table[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = 0;
    }

    // Add all letters in "magazine" into hash table
    while (*magazine) {
        table[hash(*magazine++)]++;
    }

    // Look up hash table for "ransomNote"
    while (*ransomNote) {
        if (!table[hash(*ransomNote++)]--) {
            return false;
        }
    }
    return true;
}

int main() {
    struct {
        char *ransomNote, *magazine;
    } tc[] = {
        {.ransomNote = "a", .magazine = "b"},
        {.ransomNote = "aa", .magazine = "ab"},
        {.ransomNote = "aa", .magazine = "aab"}
    };

    int tcSize = sizeof(tc) / sizeof(tc[0]);
    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        printf("Input: ransomNote = \"%s\", magazine = \"%s\"\n",
               tc[i].ransomNote, tc[i].magazine);

        // Output
        if (canConstruct(tc[i].ransomNote, tc[i].magazine)) {
            printf("Output: true\n\n");
        } else {
            printf("Output: false\n\n");
        }
    }
    return 0;
}
