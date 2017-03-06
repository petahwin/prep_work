#include "BinaryTree.h"
#include <stdlib.h>
#include <stdio.h>

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

int main() 
{
    BinarySearchTree tree;
    if (!makeBinaryTree(&tree)) return EXIT_FAILURE;

    printTree(tree, intToString);
    int arr[] = {1,3, -6,5,2, -3};
    
    if (0 != insertToTree(tree, &arr[0], sizeof(int), compInts) ||
             insertToTree(tree, &arr[1], sizeof(int), compInts) ||
             insertToTree(tree, &arr[2], sizeof(int), compInts) ||
             insertToTree(tree, &arr[3], sizeof(int), compInts) ||
             insertToTree(tree, &arr[4], sizeof(int), compInts) ||
             insertToTree(tree, &arr[5], sizeof(int), compInts))
    {
        destroyBinaryTree(tree);
        return EXIT_FAILURE;
    }
    else
    {
        // printf("Before doubling\n");
        printTree(tree, intToString);
        if (!(deleteFromTree(tree, &arr[0], compInts) &&
              deleteFromTree(tree, &arr[4], compInts) &&
              deleteFromTree(tree, &arr[1], compInts) &&
              deleteFromTree(tree, &arr[3], compInts)))
        {
            printf("delete failed\n");
            return EXIT_FAILURE;
        }
        // printf("After doubling\n");
        // printTree(tree, intToString);
        // printf("In order dump\n");
        printf("after deletion\n");
        printTree(tree, intToString);

        if (!isInTree(tree, &arr[0], compInts))
        {
            printf("%d not in tree\n", arr[0]);
        }
        if (isInTree(tree, &arr[2], compInts))
        {
            printf("%d is in tree\n", arr[2]);
        }
        traverse(tree, scaleDouble);
        traverse(tree, printOut);

        destroyBinaryTree(tree);
        return EXIT_SUCCESS;
    }
    
}

