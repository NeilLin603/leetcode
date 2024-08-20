#include <stdio.h>
#include <stdlib.h>

//!*****************************************************************************
//! Solving concept:
//! 1. Implement a doubly-linked list and a hash table. Where the linked list is
//!    used to indicate the recently used order. And the hash table is used for
//!    getting and putting nodes with O(1) time complexity.
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
//! Rule of the list: add to tail and remove from head.
//!
//!*****************************************************************************
//
// Start of the submission code
//
/**
 * Definition of a list node
 */
typedef struct Node {
    int key, val;          // Information to be saved
    struct Node *listPrev, // Pointer to the previous node of the list
                *listNext, // Pointer to the next node of the list
                *hashNext; // Pointer to the next node in the same bucket
} Node_t;

typedef struct {
    int capacity,       // Maximum element count that can reside in the cache
        count;          // Element count in the cache
    Node_t *head,       // Head (LRU) node of the list
           *tail,       // Tail (MRU) node of the list
           **hashTable; // Hash table
} LRUCache;

/**
 * The hash function.
 */
#define hash(key, capacity) ((key) % (capacity))

/**
 * Macro to move a node to become the tail (MRU) node of the list.
 */
#define moveNodeToTail(node, head, tail) if ((node)->listNext) {               \
    (node)->listNext->listPrev = (node)->listPrev;                             \
    if ((node)->listPrev) {                                                    \
        (node)->listPrev->listNext = (node)->listNext;                         \
    } else {                                                                   \
        (head) = (node)->listNext;                                             \
    }                                                                          \
    (node)->listPrev = (tail);                                                 \
    (tail) = (tail)->listNext = (node);                                        \
    (node)->listNext = NULL;                                                   \
}

/**
 * Macro to insert a node to a bucket of the hash table.
 */
#define insertIntoHashTable(pre, bucket, node) if (pre) {                      \
    (pre)->hashNext = (node);                                                  \
} else {                                                                       \
    (bucket) = (node);                                                         \
}                                                                              \
(node)->hashNext = NULL

LRUCache *lRUCacheCreate(int capacity) {
    LRUCache *cache = (LRUCache *)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->count = 0;
    cache->head = cache->tail = NULL;
    cache->hashTable = (Node_t **)malloc(sizeof(Node_t *) * capacity);
    while (capacity--) {
        *(cache->hashTable + capacity) = NULL;
    }
    return cache;
}

int lRUCacheGet(LRUCache *obj, int key) {
    Node_t *cur = *(obj->hashTable + hash(key, obj->capacity));
    while (cur) {
        if (cur->key == key) { /* Cache hit */
            moveNodeToTail(cur, obj->head, obj->tail);
            return cur->val;
        }
        cur = cur->hashNext;
    }
    return -1; // Cache miss
}

void lRUCachePut(LRUCache *obj, int key, int value) {
    // Search if the key is in the cache
    int i = hash(key, obj->capacity); // Hash value of the input key
    Node_t *pre = NULL, *cur = *(obj->hashTable + i);
    while (cur) {
        if (cur->key == key) { /* Cache hit */
            cur->val = value;
            moveNodeToTail(cur, obj->head, obj->tail);
            return;
        }
        pre = cur;
        cur = cur->hashNext;
    }

    // The key is not in the cache
    if (obj->capacity == obj->count) { /* Cache is full */
        cur = obj->head; // The LRU node
        moveNodeToTail(cur, obj->head, obj->tail); // Make the node to be MRU

        // Move the node to the new bucket of the hash table
        int j = hash(cur->key, obj->capacity); // Hash value of the LRU key
        if (i != j) {
            // Remove the node from the old bucket
            Node_t *prev = NULL, *curr = *(obj->hashTable + j);
            while (curr->key != cur->key) {
                prev = curr;
                curr = curr->hashNext;
            }
            if (prev) {
                prev->hashNext = curr->hashNext;
            } else {
                *(obj->hashTable + j) = curr->hashNext;
            }

            // Add the node to the new bucket
            insertIntoHashTable(pre, *(obj->hashTable + i), cur);
        }

        // Update contents that stored in the node
        cur->key = key;
        cur->val = value;
    } else { /* Cache is not full */
        obj->count++;

        // Create a new node
        cur = (Node_t *)malloc(sizeof(Node_t));
        cur->key = key;
        cur->val = value;

        // Add the node to the linked list
        cur->listPrev = obj->tail;
        obj->tail = obj->tail ? (obj->tail->listNext = cur) : (obj->head = cur);
        cur->listNext = NULL;

        // Insert the node into the hash table
        insertIntoHashTable(pre, *(obj->hashTable + i), cur);
    }
}

void lRUCacheFree(LRUCache *obj) {
    // Free up list nodes
    if (obj->head) {
        Node_t *cur = obj->head;
        while (cur->listNext) {
            cur = cur->listNext;
            free(cur->listPrev);
        }
        free(cur);
    }

    free(obj->hashTable); // Free up hash table
    free(obj);            // Free up cache
}
//
// End of the submission code
//

void Debug_printListForward(const Node_t *head, const char *name) {
    printf("%s = ", name);
    while (head) {
        printf("(%d,%d)->", head->key, head->val);
        head = head->listNext;
    }
    printf("null\n");
}

void Debug_printListBackward(const Node_t *tail, const char *name) {
    printf("%s = ", name);
    while (tail) {
        printf("(%d,%d)->", tail->key, tail->val);
        tail = tail->listPrev;
    }
    printf("null\n");
}

void Debug_printHashTable(Node_t **table, int tableSize) {
    Node_t *cur;
    printf("--- Start of hash table ---\n");
    while (tableSize--) {
        cur = *table++;
        while (cur) {
            printf("(%d,%d)->", cur->key, cur->val);
            cur = cur->hashNext;
        }
        printf("null\n");
    }
    printf("---- End of hash table ----\n");
}

#define DEBUG(obj) printf("\n<Debug info>\n");                                 \
    Debug_printListForward((obj)->head, "LRU order");                          \
    Debug_printListBackward((obj)->tail, "MRU order");                         \
    Debug_printHashTable((obj)->hashTable, (obj)->capacity);                   \
    printf("\n")

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
 */
int main() {
    enum {
        Cache_Put,
        Cache_Get,
        Cache_End
    } cacheOp;

    int capacity;
    printf("Enter the capacity of the cache: ");
    scanf("%d", &capacity);

    // Create cache
    LRUCache *cache = lRUCacheCreate(capacity);
    printf("//-------------------------------------------------------//\n");
    printf("// A cache with size %d has been created\n", capacity);
    printf("//-------------------------------------------------------//\n");
    DEBUG(cache);

    int key, value, step = 0;
    while (cacheOp != Cache_End) {
        printf("//-------------------------------------------------------//\n");
        printf("// Step %d\n", ++step);
        printf("//-------------------------------------------------------//\n");
        printf("Enter an op code (0 = put, 1 = get, 2 = end): ");
        scanf("%d", &cacheOp);
        switch (cacheOp) {
        case Cache_Put:
            printf("Enter the key: ");
            scanf("%d", &key);
            printf("Enter the value: ");
            scanf("%d", &value);
            lRUCachePut(cache, key, value);
            DEBUG(cache);
            break;
        case Cache_Get:
            printf("Enter the key: ");
            scanf("%d", &key);
            printf("Get(%d) = %d\n", key, lRUCacheGet(cache, key));
            DEBUG(cache);
            break;
        default:
            printf("Invalid operation.\n");
        case Cache_End:
            break;
        }
    }

    // Free up cache
    lRUCacheFree(cache);
    return 0;
}
