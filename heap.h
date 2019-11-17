/**
 * @author Charles Jackson
 * heap.h
 */
#ifndef HEAP_H
#define HEAP_H

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
 * This function allocates a heap of size `maxSize`
 * prioritized by `compare`.
 * compare: The function to compare elements.
 * maxSize: The maximum number of elements in the heap.
 * Returns a new Heap.
 */
Heap* HEAP_INIT(int (*compare)(void*, void*), int maxSize);
/**
 * This procedure deallocates the given heap.
 */
void HEAP_DESTROY(Heap*);
/**
 * This procedure adds `elem` to the given heap
 * elem: the element to be added to the given heap
 * Returns zero if added succesfully 
 * and a positive number if maxSize was reached.
 */
int HEAP_ADD(Heap*, void* elem);
/**
 * This function returns the first element of the given heap
 * It does not remove the element from the given heap
 * Returns the element of the given heap with the highest priority
 */
void* HEAP_PEEK(Heap*);
/**
 * This function will remove the first element of the given heap and return it.
 * Returns the element of the given heap with the highest priority
 */
void* HEAP_REMOVE(Heap*);

#endif // HEAP_H
