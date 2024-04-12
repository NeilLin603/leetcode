//!
//! \e https://www.geeksforgeeks.org/c-multiple-choice-questions/
//!

// Set 1 Q5
char *getString() {
    char *str = "Nice test for strings";
    return str;
}

int main() {
    printf("%s", getString());
    return 0;
}

// Set 2 Q5
int main() {
    for (int i = 0; i < 20; i++) {
        switch (i) {
        case 0:
            i += 5;
        case 1:
            i += 2;
        case 5:
            i += 5;
        default:
            i += 4;
            break;
        }
        printf("%d  ", i);
    }
    return 0;
}

// Set 3 Q5
int main() {
    int first = 50, second = 60, third;
    third = first /* Will this comment work? */ + second;
    printf("%d /* And this? */ \n", third);
    return 0;
}

// Set 9 Q1
int main() {
    int c = 5;
    printf("%d\n%d\n%d\n", c, (c <<= 2), (c >>= 2));
    return 0;
}

// Set 9 Q2
int main() {
    char arr[] = {1, 2, 3};
    if ((char (*)[])arr == &arr)
        printf("Same");
    else
        printf("Not same");
    return 0;
}

// Set 11 Q1
int fun(int n, int *fg) {
    int t, f;
    if (n <= 1) {
        *fg = 1;
        return 1;
    }
    t = fun(n - 1, fg);
    f = t + *fg;
    *fg = t;
    return f;
}

int main() {
    int x = 15;
    printf("%d\n", fun(5, &x));
    return 0;
}

// Set 13 Q4
int main() {
    printf(" \"GEEKS %% FOR %% GEEKS\"");
    return 0;
}

// Set 15 Q1
int main(void) {
    int a = 1;
    int b = ++a + ++a;
    printf("%d %d", a, b);
    return 0;
}

// Set 15 Q2
int main() {
    int a[] = {1, 2, 3, 4, 5, 6};
    int *ptr = (int *)(&a + 1);
    printf("%d ", *(ptr - 1));
    return 0;
}
