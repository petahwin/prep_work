#include <stdbool.h>
#include <stddef.h>

typedef struct priorityQueue * PriorityQueue;

typedef enum EXTREMA 
{
    MIN = 0,
    MAX
} EXTREMA;

typedef int (*CompFun) (void *, void *);

bool initPriorityQueue(PriorityQueue * q, size_t itemSize, EXTREMA x, CompFun c);
bool insertToPQ(PriorityQueue q, void * item);

// Null if empty
bool getExtremum(void * out);
void destroyPriorityQueue(PriorityQueue * q, void (*d) (void *));
