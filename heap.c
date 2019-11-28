/**
 * @author Charles Jackson
 * heap.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

Heap* HEAP_INIT(int (*compare)(void*, void*), int maxSize) {
    Heap* self;
    self = malloc(sizeof(Heap));
    self->heap = malloc((maxSize+1) * sizeof(void*));
    self->compare = compare;
    self->length = 0;
    self->maxSize = maxSize + 1;
    return self;
}
void HEAP_DESTROY(Heap* self) {
    free(self->heap);
    free(self);
}
int HEAP_ADD(Heap* self, void* elem) {
    if(self->length+1 >= self->maxSize)
        return 1;
    self->length += 1;
    int i = self->length;   /* index to insert at */
    self->heap[i] = elem;
    /* trickle up */
    int parent = (i % 2 == 0)? i/2 : (i-1)/2;
    while(parent > 0 && self->compare(self->heap[parent], self->heap[i]) > 0) {
        /* swap parent and child */
        void* temp = self->heap[i];
        self->heap[i] = self->heap[parent];
        self->heap[parent] = temp;
        i = parent;
        parent = (i % 2 == 0)? i/2 : (i-1)/2;
    }
    return 0;
}
void* HEAP_PEEK(Heap* self) {
    if(self->length > 0)
        return self->heap[0];
    return NULL;
}
void* HEAP_REMOVE(Heap* self) {
    void* min;
    if(self->length <= 0)
        return NULL;
    else
        min = self->heap[1];
    /* swap replace min with last element */
    self->heap[1] = self->heap[self->length];
    self->length -= 1;
    /* trickle down */
    int i = 1;
    int left = i * 2;
    int right = left + 1;
    while(left <= self->length && right <= self->length &&
          (self->compare(self->heap[i], self->heap[left]) > 0 ||
           self->compare(self->heap[i], self->heap[right]) > 0)) {
        int minChild;
        if(self->compare(self->heap[right],  self->heap[left]) < 0)
            minChild = right;
        else
            minChild = left;
        /* swap min child with parent */
        void* temp = self->heap[minChild];
        self->heap[minChild] = self->heap[i];
        self->heap[i] = temp;
        /* reset variables */
        i = minChild;
        left = i * 2;    
        right = left + 1;
    }
    /* in case the tree is odd */
    if(left <= self->length &&
       self->compare(self->heap[i], self->heap[left]) > 0) {
        /* swap min child with parent */
        void* temp = self->heap[left];
        self->heap[left] = self->heap[i];
        self->heap[i] = temp;
    }
    return min;
}
int HEAP_EMPTY(Heap* self) {
    return self->length == 0;
}
