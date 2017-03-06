#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#define MAX(a,b) ((a) > (b)) ? (a) : (b)
#define DIE(str) {fprintf(stderr, "Error: %s\n", (str)); return EXIT_FAILURE;}

void printLIS(int * pred, int * arr, int start)
{
    if (start == -1) return;

    printLIS(pred, arr, pred[start]);
    printf("%d ", arr[start]);
}

size_t getLIS(size_t len, int * arr)
{
    size_t lens[len];
    int pred[len];
    for (size_t i = 0; i != len; ++i) pred[i] = -1;
    for (size_t i = 0; i != len; ++i) lens[i] = 1;
    
    size_t globMaxLen = 1;
    int globMaxLenSuffix = 0;

    for (size_t i = 1; i != len; ++i)
    {
        for (size_t j = 0; j != i; ++j)
        {
            if (arr[j] <= arr[i] && lens[i] < lens[j] + 1)
            {
                lens[i] = lens[j] + 1;
                pred[i] = j;
            }
        }
    }
    
    for (size_t i = 0; i != len; ++i) 
    {
        if (globMaxLen < lens[i])
        {
            globMaxLen = lens[i];
            globMaxLenSuffix = i;
        }
    }
   
    printLIS(pred, arr, globMaxLenSuffix);
    printf("\n");
    
    return globMaxLen;
}

void test1()
{
    int arr[] = { 10, 22, 9, 33, 21, 50, 41, 60, 80 };
    assert(6 == getLIS(9, arr));
}

void test2()
{
    int arr[] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    assert(6 == getLIS(16, arr));
}

void test3()
{
}

int main(int argc, char **argv)
{
    void (*testArr[])(void) = {
                                test1,
                                test2,
                                test3
                              }; 
    if (argc < 2) DIE("You must provide a test no.");
    int testNo = atoi(argv[1]);
    if (testNo < 0) DIE("Test no. must be non-negative");
    printf("%d\n", testNo);
    testArr[testNo]();
    return EXIT_SUCCESS;
}

