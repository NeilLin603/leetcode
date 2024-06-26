#include <stdio.h>
#include <stdlib.h>

//! ****************************************************************************
//! Solving concept:
//! 1. Since the problem does not specify constraints on stack size, we then
//!    deal this problem using the linked list approach.
//! 2. Use another stack to store the min values, for the purpose of achieving
//!    the objective of O(1) time complexity for each API.
//!
//! Base stack:
//! |    |    |    |    |    |    | -3 |    |    |    |    |    |    |
//! |    | => |    | => |  0 | => |  0 | => |  0 | => |    | => |    |
//! |____|    |_-2_|    |_-2_|    |_-2_|    |_-2_|    |_-2_|    |____|
//!
//! Min stack:
//! |    |    |    |    |    |    |    |    |    |    |    |    |    |
//! |    | => |    | => |    | => | -3 | => |    | => |    | => |    |
//! |____|    |_-2_|    |_-2_|    |_-2_|    |_-2_|    |_-2_|    |____|
//!
//! ****************************************************************************
typedef struct StackNode {
    int val;
    struct StackNode *next;
} Node_t;

typedef struct {
    Node_t *top;
    Node_t *min;
} MinStack;

MinStack *minStackCreate() {
    MinStack *s = (MinStack *)malloc(sizeof(MinStack));
    s->top = s->min = NULL;
    return s;
}

void minStackPush(MinStack *obj, int val) {
    Node_t *top = (Node_t *)malloc(sizeof(Node_t));
    top->val = val;
    top->next = obj->top;
    obj->top = top;
    if (!obj->min || obj->min->val >= val) {
        Node_t *min = (Node_t *)malloc(sizeof(Node_t));
        min->val = val;
        min->next = obj->min;
        obj->min = min;
    }
}

void minStackPop(MinStack *obj) {
    Node_t *ret = obj->top;
    int val = ret->val;
    obj->top = ret->next;
    free(ret);
    if (val == obj->min->val) {
        ret = obj->min;
        obj->min = ret->next;
        free(ret);
    }
}

int minStackTop(MinStack *obj) {
    return obj->top->val;
}

int minStackGetMin(MinStack *obj) {
    return obj->min->val;
}

void minStackFree(MinStack *obj) {
    Node_t *ret;
    while (obj->top) {
        ret = obj->top;
        obj->top = ret->next;
        free(ret);
    }
    while (obj->min) {
        ret = obj->min;
        obj->min = ret->next;
        free(ret);
    }
    free(obj);
}

int main() {
    int vals[] = {-2,0,-3};
    int valsSize = sizeof(vals) / sizeof(vals[0]);

    MinStack *minStack = minStackCreate(); // Create a min stack

    // Push stack
    for (int i = 0; i < valsSize; i++) {
        minStackPush(minStack, vals[i]);
    }

    printf("Min val = %d\n", minStackGetMin(minStack)); // Get min
    minStackPop(minStack); // Pop
    printf("Top val = %d\n", minStackTop(minStack)); // Get top
    printf("Min val = %d\n", minStackGetMin(minStack)); // Get min
    minStackFree(minStack); // Free stack

    return 0;
}
