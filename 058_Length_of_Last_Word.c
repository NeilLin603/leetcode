#include <stdio.h>
#include <string.h>

int lengthOfLastWord(char *s) {
    int i = strlen(s), result = 0;
    while (i) {
        if (s[--i] != ' ') {
            result++;
        } else if (result) {
            break;
        } else;
    }
    return result;
}

int main() {
    char *s[] = {"Hello World", "   fly me   to   the moon  ", "luffy is still joyboy"};
    int sSize = sizeof(s) / sizeof(s[0]);

    for (int i = 0; i < sSize; i++) {
        printf("Example %d:\nInput: s = \"%s\"\n", i + 1, s[i]);
        printf("Output: %d\n\n", lengthOfLastWord(s[i]));
    }

    return 0;
}
