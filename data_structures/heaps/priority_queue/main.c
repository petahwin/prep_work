#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "PriorityQueue.h"

#define DIE(str) {fprintf(stderr, "Error: %s\n", (str)); return EXIT_FAILURE;}

int compInts(void * i1, void * i2)
{
    return (*(int *)i1 < *(int *)i2) ? -1 : 
           (*(int *)i1 > *(int *)i2) ? +1 : 0;
}

void testBuildAndKill()
{
    PriorityQueue q;
    
    assert(initPriorityQueue(&q, sizeof(int), MAX, compInts));
    destroyPriorityQueue(&q, free);
}

void testMin()
{
    printf("hello world\n");
}

void testMax()
{
    printf("fuck you\n");
}

int main(int argc, char ** argv)
{
    void (*testArr[])(void) = {
                                testBuildAndKill,
                                testMin,
                                testMax
                              }; 
    if (argc < 2) DIE("You must provide a test no.");
    int testNo = atoi(argv[1]);
    if (testNo < 0) DIE("Test no. must be non-negative");
    printf("%d\n", testNo);
    testArr[testNo]();

    return EXIT_SUCCESS;
}

