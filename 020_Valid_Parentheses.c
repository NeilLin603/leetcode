#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// #define METHOD_ARRAY // Comment out this line for using linked list method

#ifdef METHOD_ARRAY
#define STACK_SIZE 105

typedef struct {
    char val[STACK_SIZE];
    int top;
} Stack_t;

bool isValid(char *s) {
    Stack_t stack = {.val = {0}, .top = 0};
    while (*s) {
        if (stack.val[stack.top] == '(' && *s == ')' ||
            stack.val[stack.top] == '[' && *s == ']' ||
            stack.val[stack.top] == '{' && *s == '}') {
            stack.top--;
        } else {
            stack.val[++stack.top] = *s;
        }
        s++;
    }
    return !stack.top;
}
#else // Linked list method
typedef struct StackNode {
    char val;
    struct StackNode *next;
} Stack_t;

void push(Stack_t **head, char val) {
    Stack_t *new = (Stack_t *)malloc(sizeof(Stack_t));
    new->next = *head;
    new->val = val;
    *head = new;
}

int pop(Stack_t **head) {
    if (*head) {
        Stack_t *ret = *head;
        *head = ret->next;
        free(ret);
        return 1;
    }
    return 0;
}

bool isValid(char *s) {
    Stack_t *stack = (Stack_t *)NULL;
    push(&stack, '\0'); // Put a '\0' into stack bottom
    while (*s) {
        if (stack->val == '(' && *s == ')' ||
            stack->val == '[' && *s == ']' ||
            stack->val == '{' && *s == '}') {
            pop(&stack);
        } else {
            push(&stack, *s);
        }
        s++;
    }
    bool result = !stack->val;
    while (pop(&stack)); // Free stack
    return result;
}
#endif /* #ifdef METHOD_ARRAY */

int main() {
    char *s[] = {"()", "()[]{}", "(]", "([)]", "([]){}", "(([]){})"};
    int sSize = sizeof(s) / sizeof(s[0]);

    for (int i = 0; i < sSize; i++) {
        printf("Example %d:\n", i + 1);
        printf("Input: s = \"%s\"\n", s[i]);
        if (isValid(s[i])) {
            printf("Output: true\n\n");
        } else {
            printf("Output: false\n\n");
        }
    }

    return 0;
}
