/**
 * @author Charles Jackson
 * heap.h
 */
#ifndef HEAP_H
#define HEAP_H
#include <errno.h>
/* This is the Heap type. */
typedef struct {
    /* This is an array of generic pointers. */
    void** heap;
    /**
     * compare function
     * should return a positive number if a is greater than b,
     * a negative number if b is greater than a,
     * and zero if they are equal.
     * Compare should expect two parameters of the type being stored in the heap.
     */
    int (*compare)(void* a, void* b);
    /* This is the number elements are in the heap. */
    /* The last element will be heap[length], not heap[length-1] */
    int length;
    /* This is the maximum number of elements in the heap. */
    int maxSize;
} Heap;
/**
 * This function allocates a heap of size `max`
 * prioritized by `compareFunction`.
 * Initializes `self`.
 * self: the heap that you should have declared
 * compareFunction: The function to compare elements.
 * max: The maximum number of elements in the heap.
 */
#define HEAP_INIT(self, compareFunction, max)       \
    self = malloc(sizeof(Heap));                    \
    self->heap = calloc((max+1),  sizeof(void*));   \
    self->compare = compareFunction;                \
    self->length = 0;                               \
    self->maxSize = max + 1;
/**
 * This procedure deallocates the given heap.
 */
#define HEAP_DESTROY(self)                      \
    free(self->heap);                           \
    free(self)

/**
 * This procedure adds `elem` to the given heap
 * elem: the element to be added to the given heap
 * Returns zero if added succesfully
 * and a positive number if maxSize was reached.
 */
#define HEAP_ADD(self, elem)                                        \
    if (self->length+1 >= self->maxSize) {                          \
        errno = ERANGE;                                             \
        perror("Adding would exceed maximum size");                 \
    } else if (1) {                                                 \
        self->length += 1;                                          \
        int i = self->length;  /* index to insert at */             \
        self->heap[i] = (void*)elem;                                \
        /* trickle up */                                            \
        int parent = (i % 2 == 0)? i/2 : (i-1)/2;                   \
        while (parent > 0 && self->compare(self->heap[parent],      \
                                           self->heap[i]) > 0) {    \
            /* swap parent and child */                             \
            void* temp = self->heap[i];                             \
            self->heap[i] = self->heap[parent];                     \
            self->heap[parent] = temp;                              \
            i = parent;                                             \
            parent = (i % 2 == 0)? i/2 : (i-1)/2;                   \
        }                                                           \
    } else
/**
 * This function returns the first element of the given heap
 * It does not remove the element from the given heap
 * Returns the element of the given heap with the highest priority
 */
#define HEAP_PEEK(self) self->heap[1]
/**
 * This function will remove the first element of the given heap and return it.
 * Returns the element of the given heap with the highest priority
 */
#define HEAP_REMOVE(self)                                               \
    if (self->length <= 0)                                              \
        NULL;                                                           \
    else if (1) {                                                        \
        void* min = self->heap[1];                                      \
        /* swap replace min with last element */                        \
        self->heap[1] = self->heap[self->length];                       \
        self->length -= 1;                                              \
        /* trickle down */                                              \
        int i = 1;                                                      \
        int left = i * 2;                                               \
        int right = left + 1;                                           \
        while (left <= self->length && right <= self->length &&         \
               (self->compare(self->heap[i], self->heap[left]) > 0 ||   \
                self->compare(self->heap[i], self->heap[right]) > 0)) { \
            int minChild;                                               \
            if (self->compare(self->heap[right],  self->heap[left]) < 0)\
                minChild = right;                                       \
            else                                                        \
                minChild = left;                                        \
            /* swap min child with parent */                            \
            void* temp = self->heap[minChild];                          \
            self->heap[minChild] = self->heap[i];                       \
            self->heap[i] = temp;                                       \
            /* reset variables */                                       \
            i = minChild;                                               \
            left = i * 2;                                               \
            right = left + 1;                                           \
        }                                                               \
        /* in case the tree is odd */                                   \
        if (left <= self->length &&                                     \
            self->compare(self->heap[i], self->heap[left]) > 0) {       \
            /* swap min child with parent */                            \
            void* temp = self->heap[left];                              \
            self->heap[left] = self->heap[i];                           \
            self->heap[i] = temp;                                       \
        }                                                               \
    } else
/**
 * Returns the length of the heap.
 */
#define HEAP_EMPTY(self) self->length == 0

#endif // HEAP_H
