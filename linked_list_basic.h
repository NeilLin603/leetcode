#ifndef LINKED_LIST_BASIC_H
#define LINKED_LIST_BASIC_H

#include <stdlib.h>

/**
 * Definition for singly-linked list.
 */
typedef struct ListNode {
    int val;
    struct ListNode *next;
} Node_t;

void pushHead(Node_t **, int);
void pushTail(Node_t **, int);
int popHead(Node_t **, int *);
int popTail(Node_t **, int *);
int freeList(Node_t **);

void pushHead(Node_t **head, int val) {
    Node_t *new = (Node_t *)malloc(sizeof(Node_t));
    new->val = val;
    new->next = *head;
    *head = new;
}

void pushTail(Node_t **head, int val) {
    Node_t *new = (Node_t *)malloc(sizeof(Node_t));
    new->val = val;
    new->next = (Node_t *)NULL;
    if (!*head) {
        *head = new;
        return;
    }
    Node_t *tail = *head;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = new;
}

int popHead(Node_t **head, int *val) {
    if (*head) {
        Node_t *ret = *head;
        *val = ret->val;
        *head = ret->next;
        free(ret);
        return 1;
    }
    return 0;
}

int popTail(Node_t **head, int *val) {
    if (!*head) {
        return 0;
    }
    if (!(*head)->next) {
        *val = (*head)->val;
        free(*head);
        *head = (Node_t *)NULL;
        return 1;
    }
    Node_t *cur = *head;
    while (cur->next->next) {
        cur = cur->next;
    }
    *val = cur->next->val;
    free(cur->next);
    cur->next = (Node_t *)NULL;
}

int freeList(Node_t **head) {
    int val;
    while (popHead(head, &val));
}

#endif /* LINKED_LIST_BASIC_H */
