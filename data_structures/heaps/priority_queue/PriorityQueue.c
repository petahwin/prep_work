#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "PriorityQueue.h"

static int INITSIZE = 5;

struct priorityQueue
{
    void ** arr;
    size_t size_arr;
    size_t num_items;
    
    size_t size_item;
    CompFun comparator;
    EXTREMA ex;
};

// Helpers

size_t leftChild(size_t key) {return 2 * key + 1;}
size_t rightChild(size_t key) {return 2 * key + 2;}

// Just one head and its children, pass in the head, silly
void littleBoHeap(PriorityQueue)
{

}

// Goes 
void heapalizeIt(PriorityQueue q)
{
}

// End helpers

// derp
bool initPriorityQueue(PriorityQueue * q, size_t itemSize, EXTREMA x, CompFun c)
{
    *q = malloc(sizeof(struct priorityQueue));
    if (!*q) return false;
    
    (*q)->arr = malloc(sizeof(void *) * INITSIZE);
    if (!(*q)->arr) return false;
    
    (*q)->size_arr = INITSIZE;
    (*q)->num_items = 0;
    
    (*q)->size_item = itemSize;
    (*q)->comparator = c;
    (*q)->ex = x;

    return true;
}

// Make sure to reallocate when hitting the max size of the array
bool insertToPQ(PriorityQueue q, void * item)
{
    if (q->num_items == q->size_arr) q->arr = realloc(a->arr, q->size_arr *= 2);
    void * new = malloc(q->size_item);
    q->arr[q->num_items++] = new;

    size_t root = 0;
    while()
    {
    }
    return true;
}

// pop off the head, get the last indexed element to replace it, and then
// heapify the new head
bool getExtremum(void * out)
{
    return NULL;
}

void destroyPriorityQueue(PriorityQueue * q, void (*d) (void *))
{
    assert(*q);
    void ** arr = (*q)->arr;
    size_t num_items = (*q)->num_items;
    for (size_t i = 0; i != num_items; ++i) d(arr[i]);
    free(arr);
    free(*q);

    *q = NULL;
}

