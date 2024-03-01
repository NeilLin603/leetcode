#ifndef LINKED_LIST_BASIC_H
#define LINKED_LIST_BASIC_H

#include <stdbool.h>
#include <stdio.h>
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
bool popHead(Node_t **, int *);
bool popTail(Node_t **, int *);
void printSinglyList(Node_t *);
int freeSinglyList(Node_t **);

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

bool popHead(Node_t **head, int *val) {
    if (*head) {
        Node_t *ret = *head;
        *val = ret->val;
        *head = ret->next;
        free(ret);
        return true;
    }
    return false;
}

bool popTail(Node_t **head, int *val) {
    if (!*head) {
        return false;
    }
    if (!(*head)->next) {
        *val = (*head)->val;
        free(*head);
        *head = (Node_t *)NULL;
        return true;
    }
    Node_t *cur = *head;
    while (cur->next->next) {
        cur = cur->next;
    }
    *val = cur->next->val;
    free(cur->next);
    cur->next = (Node_t *)NULL;
    return true;
}

void printSinglyList(Node_t *head) {
    while (head) {
        printf("(%d)->", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

int freeSinglyList(Node_t **head) {
    int val;
    while (popHead(head, &val));
}

#endif /* LINKED_LIST_BASIC_H */
