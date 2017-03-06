#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "BinaryTree.h"

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

typedef struct TreeNode {
    void * value;
    struct TreeNode * left;
    struct TreeNode * right;
    size_t height;
} TreeNode;


// Helper functions
TreeNode * makeTreeNode(void * item, size_t size)
{
    TreeNode * tree_node_p = malloc(sizeof(TreeNode));
    if (!tree_node_p) return NULL;

    tree_node_p->value = malloc(size);
    memcpy(tree_node_p->value, item, size);

    tree_node_p->left  = NULL;
    tree_node_p->right = NULL;
    tree_node_p->height = 1;
    return tree_node_p;
}

void printTreeHelper(BinarySearchTree tree, ToString toString, size_t depth)
{
    if (*tree == NULL) 
    {
        for (size_t i = 0; i != depth; ++i)
        {
            printf("\t");
        }
        printf("*\n");
        return;
    }
    
    printTreeHelper(&(*tree)->right, toString, depth + 1);
    
    for (size_t i = 0; i != depth; ++i)
    {
        printf("\t");
    }
    char buf[256];
    toString((*tree)->value, buf);
    printf("%s/%zu\n", buf, (*tree)->height);
    
    printTreeHelper(&(*tree)->left, toString, depth + 1);
}

void destroyBinaryTreeHelper(TreeNode * tree)
{
    if (tree)
    {
        free(tree->value);
        destroyBinaryTreeHelper(tree->left);
        destroyBinaryTreeHelper(tree->right);
        free(tree);
    }
    return;
}

BinarySearchTree getSuccessor(BinarySearchTree tree)
{
    assert(*tree != NULL);
    BinarySearchTree succ = &(*tree)->right;
    while((*succ)->left)
    {
        succ = &(*succ)->left;
    }
    return succ;
}

void setHeight(TreeNode * tree)
{
    assert(tree != NULL);
    tree->height = 1 + MAX(heightTree(&tree->left), heightTree(&tree->right));
}
// End Helpers

void printTree(BinarySearchTree tree, ToString toString)
{
    printTreeHelper(tree, toString, 0);
}

bool makeBinaryTree(BinarySearchTree * tree_p)
{
    
    *tree_p = malloc(sizeof(TreeNode *));
    if (NULL == *tree_p)
    {
        return false;
    }
    else
    {
        **tree_p = NULL;
        return true;
    }
}

bool isInTree(BinarySearchTree tree, void * item, CompFun c)
{   
    if (*tree == NULL) return false; 
    switch (c(item, (*tree)->value)) 
    {
        case -1 : return isInTree(&(*tree)->left, item, c);
        case  0 : return true;
        case  1 : return isInTree(&(*tree)->right, item, c);
    }

    return false; // Cannot be reached
}

// 0 for good,
// 1 for bad -- malloc
// -1 for sorta bad -- duplicate
int insertToTree(BinarySearchTree tree, void * item, size_t size, CompFun c)
{
    if (*tree == NULL)
    {
        TreeNode * new_node_p = makeTreeNode(item, size);
        if (!new_node_p) return 1;
    
        *tree = new_node_p;
        return 0;
    }

    int rc = 0;
    switch (c(item, (*tree)->value)) {
        case -1 : rc = insertToTree(&(*tree)->left, item, size, c); break;
        case  0 : rc = -1; break;
        case  1 : rc = insertToTree(&(*tree)->right, item, size, c); break;
    }
    
    if (0 == rc) // Successful insert
    {
        setHeight(*tree);
    }
    return rc; 
}

bool deleteFromTree(BinarySearchTree tree, void * item, CompFun c)
{
    if (!*tree) return false;

    bool rc;
    switch (c(item, (*tree)->value)) 
    {
        case -1 : rc = deleteFromTree(&(*tree)->left, item, c); break;
        case  1 : rc = deleteFromTree(&(*tree)->right, item, c); break;
        case  0 : 
        {
            TreeNode * tmp = *tree;
            // Leaf
            if (!((*tree)->left || (*tree)->right)) 
            {
                *tree = NULL;
                free(tmp->value);
                free(tmp);
                rc = true;
            }
            // One child
            else if (!((*tree)->left && (*tree)->right))
            {
                *tree = (*tree)->left ? (*tree)->left : (*tree)->right;
                free(tmp->value);
                free(tmp);
                rc = true;
            }
            // Two Children
            else
            {
                BinarySearchTree succ = getSuccessor(tree);
                // SUCC MUST BE FOUND, DUE TO IF CONDITION
                assert(*succ != NULL);
                void * oldval = (*tree)->value;
                (*tree)->value = (*succ)->value;
                
                (*succ)->value = oldval; // Swap merely for cleanup
                rc = deleteFromTree(succ, (*succ)->value, c);
            }
            break;
        }
    }

    if (rc && *tree) setHeight(*tree);
    return rc; 
}

void destroyBinaryTree(BinarySearchTree tree)
{
    // malloc node, value, and tree
    if (tree)
    {
        destroyBinaryTreeHelper(*tree);
    }
    free(tree);
    return;
}

void traverse(BinarySearchTree tree, void (*elemFun) (void *))
{
    if (!*tree) return;
    traverse(&(*tree)->left, elemFun);
    elemFun((*tree)->value);
    traverse(&(*tree)->right, elemFun);
}

size_t heightTree(BinarySearchTree tree)
{
    return (*tree) ? (*tree)->height : 0;
}


