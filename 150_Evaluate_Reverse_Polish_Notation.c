#include <stdio.h>
#include <stdlib.h>

#define CHAR_TO_NUM(x) (int)((x) - '0')

typedef struct StackNode {
    int val;
    struct StackNode *next;
} Node_t;

typedef struct {
    Node_t *top;
} Stack_t;

void push(Stack_t *s, int val) {
    Node_t *top = (Node_t *)malloc(sizeof(Node_t));
    top->val = val;
    top->next = s->top;
    s->top = top;
}

int pop(Stack_t *s) {
    Node_t *top = s->top;
    int val = top->val;
    s->top = top->next;
    free(top);
    return val;
}

int str2Num(char *s) {
    int num = 0, multiplier = 1;
    if (*s == '-') {
        s++;
        multiplier = -1;
    }
    while (*s) {
        num = num * 10 + CHAR_TO_NUM(*s++);
    }
    return multiplier * num;
}

#if 1 /* Functional test on GCC */
int evalRPN(char tokens[][5], int tokensSize) {
#else /* Leetcode submittion */
int evalRPN(char **tokens, int tokensSize) {
#endif
    Stack_t s = {NULL};
    int val;
    for (int i = 0; i < tokensSize; i++) {
        if (tokens[i][1]) { /* Length of tokens[i] > 1 */
            push(&s, str2Num(tokens[i]));
        } else {
            switch (*tokens[i]) {
            case '+':
                val = pop(&s);
                val = pop(&s) + val;
                push(&s, val);
                break;
            case '-':
                val = pop(&s);
                val = pop(&s) - val;
                push(&s, val);
                break;
            case '*':
                val = pop(&s);
                val = pop(&s) * val;
                push(&s, val);
                break;
            case '/':
                val = pop(&s);
                val = pop(&s) / val;
                push(&s, val);
                break;
            default:
                push(&s, CHAR_TO_NUM(*tokens[i]));
            }
        }
    }
    return pop(&s);
}

void printTokens(char tokens[][5], int tokensSize, char *name) {
    printf("%s = [", name);
    if (tokensSize) {
        printf("\"%s\"", *tokens);
        for (int i = 1; i < tokensSize; i++) {
            printf(",\"%s\"", tokens[i]);
        }
    }
    printf("]\n");
}

int main() {
    struct {
        char tokens[13][5];
        int tokensSize;
    } tc[] = {
        {.tokens = {"2","1","+","3","*"}, .tokensSize = 5},
        {.tokens = {"4","13","5","/","+"}, .tokensSize = 5},
        {.tokens = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"},
         .tokensSize = 13}
    };
    int tcSize = sizeof(tc) / sizeof(tc[0]);

    for (int i = 0; i < tcSize; i++) {
        printf("Example %d:\n", i + 1);
        printTokens(tc[i].tokens, tc[i].tokensSize, "Input: tokens");
        printf("Output: %d\n\n", evalRPN(tc[i].tokens, tc[i].tokensSize));
    }

    return 0;
}
