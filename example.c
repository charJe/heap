/**
 * @author Charles Jackson
 * example.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
/* using this function will make the heap a MAXimum heap */
int compareIntsMax(void* one, void* two) {
    int a = (int)one;
    int b = (int)two;
    return b - a;
}
/* using this function will make the heap a MINimum heap */
int compareIntsMin(void* one, void* two) {
    int a = (int)one;
    int b = (int)two;
    return a - b;
}
int main(int argc, char** argv) {
    /* init heap */
    Heap* heap;
    HEAP_INIT(heap, compareIntsMin, 7);
    /* add an element */
    HEAP_ADD(heap, 5);
    /* add some more elements */
    HEAP_ADD(heap, 7);
    HEAP_ADD(heap, 4);
    HEAP_ADD(heap, 10);
    HEAP_ADD(heap, 8);
    HEAP_ADD(heap, 3);
    HEAP_ADD(heap, 1);
    int min;
    /* remove elements until there are none left*/
    do {
        /* print out whole heap so we can watch it change */
        for(int i = 1; i <= heap->length; ++i) {
            /* must cast then dereference generic element */
            int spot = (int)heap->heap[i];
            printf("%d, ", spot);
        }
        printf("\b\b");         /* remove space and comma :P */
        /* print and remove highest priority element until empty*/
        min = (int)HEAP_PEEK(heap);
        HEAP_REMOVE(heap);
        printf("\nminimum: %d\n", min);
        printf("length: %d\n", heap->length);
    } while (!(HEAP_EMPTY(heap)));
    HEAP_DESTROY(heap);
    return 0;
}
