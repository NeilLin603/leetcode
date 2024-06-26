#include <stdio.h>

//! ****************************************************************************
//! Solution concept: check a directory between s1 and s2 one at a time
//!         s    s1   s2
//!         v    v    v
//! path = "/home/dir1/dir2"
//!
//! Time complexity: O(n), Space complexity: O(1)
//! ****************************************************************************
char *simplifyPath(char *path) {
    char *s = path, *s1 = path, *s2 = path;
    while (*s1) {
        while (*++s2 && *s2 != '/'); // Move s2 to the next '/'
        if (s1 == s2 - 1 || s1 == s2 - 2 && s1[1] == '.') {
            s1 = s2;
        } else if (s1 == s2 - 3 && s1[1] == '.' && s1[2] == '.') {
            if (s != path) {
                while (*--s != '/'); // Moving up one directory level
            }
            s1 = s2;
        } else {
            while (s1 != s2) {
                *++s = *++s1; // Add one directory
            }
        }
    }
    if (s != path) {
        *s = '\0';
    } else {
        s[1] = '\0';
    }
    return path;
}

int main() {
    char path[][128] = {
        "/home/", "/home//foo/", "/home/user/Documents/../Pictures", "/../",
        "/.../a/../b/c/../d/./"
    };
    int pathSize = sizeof(path) / sizeof(path[0]);

    for (int i = 0; i < pathSize; i++) {
        printf("Example %d:\n", i + 1);
        printf("Input: path = \"%s\"\n", path[i]);
        printf("Output: \"%s\"\n\n", simplifyPath(path[i]));
    }

    return 0;
}
