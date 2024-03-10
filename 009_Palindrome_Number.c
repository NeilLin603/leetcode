#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(int x) {
    if (x < 0) {
        return false;
    }
    int nums[10], i = 0, j = -1;
    while (x) {
        nums[++j] = x % 10;
        x /= 10;
    }
    while (i < j) if (nums[i++] != nums[j--]) {
        return false;
    }
    return true;
}

int main() {
    int x[] = {121, -121, 10}, xSize = sizeof(x) / sizeof(x[0]);

    for (int i = 0; i < xSize; i++) {
        printf("Example %d:\n", i + 1);
        printf("Input: x = %d\n", x[i]);
        if (isPalindrome(x[i])) {
            printf("Output: true\n\n");
        } else {
            printf("Output: false\n\n");
        }
    }

    return 0;
}
