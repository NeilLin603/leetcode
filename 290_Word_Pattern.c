#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//!*****************************************************************************
//! Solving Concept:
//! 1. Implement two hash tables.
//! 2. Define the table size as the total count of the lowercase English letters
//!    in order to avoid table 1 from any hash collision.
//! 3. Use open addressing approach to handle the hash collisions of table 2.
//!
//! Table 1:                        Table 2:
//! +------------+--------+         +--------------+--------+
//! | Index      | Word   |         | Index        | Letter |
//! +------------+--------+         +--------------+--------+
//! | hash1('a') | "dog"  |         | hash2("dog") |  'a'   |
//! | hash1('b') | "cat"  |         | hash2("cat") |  'b'   |
//! |    ...     |  ...   |         |     ...      |  ...   |
//! +------------+--------+         +--------------+--------+
//!
//!*****************************************************************************
//
// Start of the submission code
//
#define TABLE_SIZE 26 // Total count of the lowercase English letters
#define WORD_LENGTH 32 // Define the maximum word length in s

/**
 * Macro for the hash function 1.
 */
#define hash1(letter) ((int)(letter) % TABLE_SIZE)

/**
 * The hash function 2.
 */
int hash2(char *word, char **s) {
    int ret = 0;
    do {
        *word = *(*s)++;
        ret += *word++;
        if (**s == ' ') {
            (*s)++;
            break;
        }
    } while (**s);
    *word = '\0';
    return ret % TABLE_SIZE;
}

/**
 * Function to compare if two strings are the same.
 */
bool isSameString(const char *s, const char *t) {
    while (*s && *t) {
        if (*s++ != *t++) {
            return false;
        }
    }
    return !(*s || *t);
}

/**
 * Function to copy string from \e src to \e dst.
 */
void copyString(char *dst, const char *src) {
    do {
        *dst++ = *src;
    } while (*src++);
}

bool wordPattern(char *pattern, char *s) {
    char table1[TABLE_SIZE][WORD_LENGTH], table2[TABLE_SIZE],
         word[WORD_LENGTH]; // Buffer to store the word of s
    int i, j; // Indices or hash values of table 1 & 2

    // Initialize the hash tables
    for (i = 0; i < TABLE_SIZE; i++) {
        table1[i][0] = table2[i] = '\0';
    }

    do {
        i = hash1(*pattern); // Key of table 1 is the letter in pattern
        j = hash2(word, &s); // Key of table 2 is the word in s

        // Table 1 hash hit
        if (table1[i][0]) {
            if (!isSameString(table1[i], word)) {
                return false;
            }
            continue;
        }

        // Table 2 hash hit or collision
        while (table2[j]) {
            if (isSameString(table1[hash1(table2[j])], word)) {
                return false; // Hash hit, return false
            }
            j = (j + 1) % TABLE_SIZE; // Hash collision, check the next bucket
        }

        // Add members to both tables
        copyString(table1[i], word);
        table2[j] = *pattern;
    } while (*++pattern && *s);

    return !(*pattern || *s);
}
//
// End of the submission code
//

int main() {
    struct {
        char *pattern, *s;
    } tc[] = {
        {.pattern = "abba", .s = "dog cat cat dog"},
        {.pattern = "abba", .s = "dog cat cat fish"},
        {.pattern = "aaaa", .s = "dog cat cat dog"}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);

        // Input
        printf("Input: pattern = \"%s\", s = \"%s\"\n", tc[i].pattern, tc[i].s);

        // Output
        if (wordPattern(tc[i].pattern, tc[i].s)) {
            printf("Output: true\n\n");
        } else {
            printf("Output: false\n\n");
        }
    }
    return 0;
}
