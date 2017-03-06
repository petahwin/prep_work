#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "AvlTree.h"
#define DIE(str) {fprintf(stderr, "Error: %s\n", (str)); return EXIT_FAILURE;}

int compInts(void * i1, void * i2)
{
    return (*(int *)i1 < *(int *)i2) ? -1 : 
           (*(int *)i1 > *(int *)i2) ? +1 : 0;
}

void intToString(void * i, char * buf)
{
    sprintf(buf, "%d", *(int *)i);
}

void scaleDouble(void * i)
{
    *(int *)i *= 2;
}

void printOut(void * i)
{
    printf("%d\n", *(int*)i);
}

void addInt_(AvlTree * tree, int i)
{
    assert(!insertToTree(*tree, &i, sizeof(int), compInts)); printf("Adding %d\n", i);
}

void delInt_(AvlTree * tree, int i)
{
    assert(deleteFromTree(*tree, &i, compInts)); printf("Deleting %d\n", i);
}

void testSingRotOnlyInsOnly()
{
    printf("Testing Single Rotation Only/Insert Only\n");
    AvlTree tree;
    if (!makeAvlTree(&tree))
    {
        printf("Failed to init tree\n");
    }
    else
    {
        int arr[] = {1,2,3,4,5,-1,-2,-3,-4,};
        assert(!insertToTree(tree, &arr[0], sizeof(int), compInts));
        assert(!insertToTree(tree, &arr[1], sizeof(int), compInts));
        assert(!insertToTree(tree, &arr[2], sizeof(int), compInts));
        printTree(tree, intToString);
        printf("**************************************\n");
        assert(!insertToTree(tree, &arr[3], sizeof(int), compInts));
        assert(!insertToTree(tree, &arr[4], sizeof(int), compInts));
        printTree(tree, intToString);
        printf("**************************************\n");
        assert(!insertToTree(tree, &arr[5], sizeof(int), compInts));
        assert(!insertToTree(tree, &arr[6], sizeof(int), compInts));
        printTree(tree, intToString);
        printf("**************************************\n");
        assert(!insertToTree(tree, &arr[7], sizeof(int), compInts));
        assert(!insertToTree(tree, &arr[8], sizeof(int), compInts));
        printTree(tree, intToString);
        destroyAvlTree(tree);
    }
    printf("End of test\n");
}

void testSingRotOnlyInsFollowedByDeletes()
{
    printf("Testing Single Rotation Only/Inserts Followed By Deletes\n");
    AvlTree tree;
    if (!makeAvlTree(&tree))
    {
        printf("Failed to init tree\n");
    }
    else
    {
        int arr[] = {1,2,3,4,6,-1,-2,-3,-4,5,7};
        assert(!insertToTree(tree, &arr[0], sizeof(int), compInts)); printf("Adding %d\n", arr[0]);
        assert(!insertToTree(tree, &arr[1], sizeof(int), compInts)); printf("Adding %d\n", arr[1]);
        assert(!insertToTree(tree, &arr[2], sizeof(int), compInts)); printf("Adding %d\n", arr[2]);
        assert(!insertToTree(tree, &arr[3], sizeof(int), compInts)); printf("Adding %d\n", arr[3]);
        assert(!insertToTree(tree, &arr[4], sizeof(int), compInts)); printf("Adding %d\n", arr[4]);
        assert(!insertToTree(tree, &arr[5], sizeof(int), compInts)); printf("Adding %d\n", arr[5]);
        assert(!insertToTree(tree, &arr[6], sizeof(int), compInts)); printf("Adding %d\n", arr[6]);
        assert(!insertToTree(tree, &arr[7], sizeof(int), compInts)); printf("Adding %d\n", arr[7]);
        assert(!insertToTree(tree, &arr[8], sizeof(int), compInts)); printf("Adding %d\n", arr[8]);
        printTree(tree, intToString);
        printf("**************************************\n");
        assert(deleteFromTree(tree, &arr[0], compInts)); printf("Deleting %d\n", arr[0]);
        printTree(tree, intToString);
        printf("**************************************\n");
        addInt_(&tree, arr[9]);
        // assert(!insertToTree(tree, &arr[9], sizeof(int), compInts)); printf("Adding %d\n", arr[9]);
        assert(!insertToTree(tree, &arr[10], sizeof(int), compInts)); printf("Adding %d\n", arr[10]);
        printTree(tree, intToString);
        printf("**************************************\n");
        delInt_(&tree, arr[2]);
        // assert(deleteFromTree(tree, &arr[2], compInts)); printf("Deleting %d\n", arr[2]);
        printTree(tree, intToString);
        destroyAvlTree(tree);
    }
    printf("End of test\n");
}

void testDoubRotInsOnly()
{
    printf("Testing Double Rotation /Inserts Only\n");
    AvlTree tree;
    if (!makeAvlTree(&tree))
    {
        printf("Failed to init tree\n");
    }
    else
    {
        int arr[] = {1,10,5,-10,-5,13,17,19};
        // int arr[] = {1,-10,-5};
        addInt_(&tree, arr[0]);
        addInt_(&tree, arr[1]);
        printTree(tree, intToString);
        printf("**************************************\n");
        addInt_(&tree, arr[2]);
        printTree(tree, intToString);
        printf("**************************************\n");
        addInt_(&tree, arr[3]);
        printTree(tree, intToString);
        printf("**************************************\n");
        addInt_(&tree, arr[4]);
        printTree(tree, intToString);
        destroyAvlTree(tree);
    }
    printf("End of test\n");
}

void testDoubRotInsFollowedByDeletes()
{
    printf("Testing Double Rotation /Inserts Followed by Deletes\n");
    AvlTree tree;
    if (!makeAvlTree(&tree))
    {
        printf("Failed to init tree\n");
    }
    else
    {
        int arr[] = {1,10,5,-10,-5,13,17,19};
        addInt_(&tree, arr[0]);
        addInt_(&tree, arr[1]);
        printTree(tree, intToString);
        printf("**************************************\n");
        addInt_(&tree, arr[2]);
        printTree(tree, intToString);
        printf("**************************************\n");
        addInt_(&tree, arr[3]);
        printTree(tree, intToString);
        printf("**************************************\n");
        addInt_(&tree, arr[4]);
        printTree(tree, intToString);
        printf("**************************************\n");
        delInt_(&tree, arr[1]);
        printTree(tree, intToString);
        destroyAvlTree(tree);
    }
    printf("End of test\n");
}

int main(int argc, char ** argv) 
{
    void (*testArr[])(void) = {
                                testSingRotOnlyInsOnly, 
                                testSingRotOnlyInsFollowedByDeletes,
                                testDoubRotInsOnly,
                                testDoubRotInsFollowedByDeletes
                              }; 
    if (argc < 2) DIE("You must provide a test no.");
    int testNo = atoi(argv[1]);
    if (testNo < 0) DIE("Test no. must be non-negative");
    printf("%d\n", testNo);
    testArr[testNo]();
    return EXIT_SUCCESS;
}

