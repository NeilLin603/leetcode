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
    struct ListNode * next;
} Node_t;

void pushHead(Node_t **, int);
void pushTail(Node_t **, int);
bool popHead(Node_t **, int *);
bool popTail(Node_t **, int *);
Node_t *createList(const int *, int);
void printSinglyList(Node_t *, const char *);
void freeSinglyList(Node_t **);

/**
 * \brief Add a node to list head.
 * \param head Pointer to the head node of the list.
 * \param val The value for the node to be added.
 * \return None.
 */
void pushHead(Node_t **head, int val) {
    Node_t *new = (Node_t *)malloc(sizeof(Node_t));
    new->val = val;
    new->next = *head;
    *head = new;
}

/**
 * \brief Add a node to list tail.
 * \param head Pointer to the head node of the list.
 * \param val The value for the node to be added.
 * \return None.
 */
void pushTail(Node_t **head, int val) {
    Node_t *new = (Node_t *)malloc(sizeof(Node_t));
    new->val = val;
    new->next = NULL;
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

/**
 * \brief Pop the head node of a list.
 * \param head Pointer to the head node of the list.
 * \param val Pointer to the variable to be popped on.
 * \return \b true - Pop succeeded. \b false - List is empty. Pop failed.
 */
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

/**
 * \brief Pop the tail node of a list.
 * \param head Pointer to the head node of the list.
 * \param val Pointer to the variable to be popped on.
 * \return \b true - Pop succeeded. \b false - List is empty. Pop failed.
 */
bool popTail(Node_t **head, int *val) {
    if (!*head) {
        return false;
    }
    if (!(*head)->next) {
        *val = (*head)->val;
        free(*head);
        *head = NULL;
        return true;
    }
    Node_t *cur = *head;
    while (cur->next->next) {
        cur = cur->next;
    }
    *val = cur->next->val;
    free(cur->next);
    cur->next = NULL;
    return true;
}

/**
 * \brief Create a singly-linked list.
 * \param vals The array of list values.
 * \param valsSize The array size of list values.
 * \return The head node of the singly-linked list.
 */
Node_t *createList(int *vals, int valsSize) {
    Node_t *head = NULL, *new;
    while (valsSize--) {
        new = (Node_t *)malloc(sizeof(Node_t));
        new->val = vals[valsSize];
        new->next = head;
        head = new;
    }
    return head;
}

/**
 * \brief Print singly-linked list.
 * \param head The head node of the list.
 * \param name The list name.
 * \return None.
 */
void printSinglyList(Node_t *head, const char *name) {
    printf("%s = ", name);
    while (head) {
        printf("(%d)->", head->val);
        head = head->next;
    }
    printf("null\n");
}

/**
 * \brief Free singly-linked list.
 * \param head Pointer to the head node of the list.
 * \return None.
 */
void freeSinglyList(Node_t **head) {
    Node_t *ret;
    while (*head) {
        ret = *head;
        *head = ret->next;
        free(ret);
    }
}

#endif /* LINKED_LIST_BASIC_H */
