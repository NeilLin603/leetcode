#include <stdio.h>
#include <stdlib.h>

//!*****************************************************************************
//! Solving concept:
//! 1. Implement a doubly-linked list and a hash table. Where the linked list is
//!    used to indicate the recently used order. And the hash table is used for
//!    O(1) time complecity getting and putting nodes.
//! 2. Use the chaining approach to handle the hash collisions.
//!
//! Hash table:
//! +------------+-----------------+
//! | Hash value | Pointer to node |
//! +------------+-----------------+
//! |     0      |    Node_t *p    |
//! +------------+-----------------+
//! |     1      |    Node_t *q    |
//! +------------+-----------------+
//! |    ...     |       ...       |
//! +------------+-----------------+
//!
//! Doubly-linked list:
//! (head)<->...<->q<->...<->p<->...<->(tail)
//!  LRU ------------------------------> MRU
//! Rule: add to tail, remove from head.
//!
//!*****************************************************************************

/**
 * Definition of a list node
 */
typedef struct Node {
} Node_t;

typedef struct {
} LRUCache;

LRUCache *lRUCacheCreate(int capacity) {
}

int lRUCacheGet(LRUCache *obj, int key) {
}

void lRUCachePut(LRUCache *obj, int key, int value) {
}

void lRUCacheFree(LRUCache *obj) {
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
 */
int main() {
    return 0;
}
