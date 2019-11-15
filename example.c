/**
 * @author Charles Jackson
 * example.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include "heap.h"
/* using this function will make the heap a MAX heap */
int compareIntsMax(void* one, void* two) {
    int a = (*(int*)(one));
    int b = (*(int*)(two));
    return b - a;
}
/* using this function will make the heap a MIN heap */
int compareIntsMin(void* one, void* two) {
    int a = (*(int*)(one));
    int b = (*(int*)(two));
    return a - b;
}
int main(int argc, char** argv) {
    /* init heap */
    Heap* heap = HEAP_INIT(compareIntsMin, 7);
    /* add an element */
    int a = 5;
    HEAP_ADD(heap, (void*)(&a));
    /* add some more elements */
    int b = 7;
    HEAP_ADD(heap, (void*)(&b));
    int c = 4;
    HEAP_ADD(heap, (void*)(&c));
    int d = 10;
    HEAP_ADD(heap, (void*)(&d));
    int e = 8;
    /* must cast and referenc generic element */
    HEAP_ADD(heap, (void*)(&e));
    int f = 3;
    HEAP_ADD(heap, (void*)(&f));
    int g = 1;
    HEAP_ADD(heap, (void*)(&g));

    /* remove elements until there are none left*/
    while(1) {
        /* print out whole heap  */
        for(int i = 1; i <= heap->length; ++i) {
            /* must cast then dereference generic element */
            int spot = *(int*)(heap->heap[i]);
            printf("%d, ", spot);
        }
        /* print and remove highest priority element */
        void* min = HEAP_REMOVE(heap);
        if(min != NULL)
            printf("\nmin: %d\n", *(int*)min);
        else
            break;
    }
    return 0;
}
