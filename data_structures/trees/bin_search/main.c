#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BinaryTree.h"

#define DIE(str) {fprintf(stderr, "Error: %s\n", (str)); return EXIT_FAILURE;}

size_t bin_search_fill(int*in, int*out, size_t size, size_t writeIdx, 
                                        size_t leftIdx, size_t rightIdx)
{
    if (writeIdx >= size || (leftIdx >= rightIdx && rightIdx != size-1))
    {
        return writeIdx;
    }

    size_t mid = (rightIdx + leftIdx)/2;
    out[writeIdx++] = in[mid];
    

    writeIdx = bin_search_fill(in,out,size, writeIdx,leftIdx,mid);
    return bin_search_fill(in,out,size,writeIdx,mid+1,rightIdx);
}

void bin_search_order(int * in, int * out, size_t size)
{
    size_t writeIndex = 0;
    size_t leftIndex = 0, rightIndex = size - 1;
    bin_search_fill(in,out,size,writeIndex,leftIndex,rightIndex);
}

void intToString(void * i, char * buf)
{
    sprintf(buf, "%d", *(int *)i);
}

int compInts(void * i1, void * i2)
{
    return (*(int *)i1 < *(int *)i2) ? -1 : 
           (*(int *)i1 > *(int *)i2) ? +1 : 0;
}

void testBinSearch()
{
    int in[] = {1,2,3,4,5,6,7};
    int out[7];
    bin_search_order(in,out,7);
    for (size_t i = 0; i != 7; ++i)
    {
        printf("%d\n", out[i]);
    }
}

void testBinTreeIns()
{
    BinarySearchTree tree;
    assert(makeBinaryTree(&tree));
    int in[] = {1,2,3,4,5,6,7};
    int out[7];
    bin_search_order(in,out,7);

    for (size_t i = 0; i != 7; ++i)
    {
        insertToTree(tree, &out[i], sizeof(int), compInts);
    }

    printTree(tree, intToString);
}

int main(int argc, char ** argv) 
{
    void (*testArr[])(void) = {
                                testBinSearch,
                                testBinTreeIns
                              }; 
    if (argc < 2) DIE("You must provide a test no.");
    int testNo = atoi(argv[1]);
    if (testNo < 0) DIE("Test no. must be non-negative");
    printf("%d\n", testNo);
    testArr[testNo]();
    return EXIT_SUCCESS;
}

