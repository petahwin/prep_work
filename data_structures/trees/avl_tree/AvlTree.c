#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "AvlTree.h"

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

typedef struct TreeNode {
    void * value;
    struct TreeNode * left;
    struct TreeNode * right;
    size_t height;
} TreeNode;

// Helper Enums
typedef enum SING_ROT_DIR {
    left = 0,
    right,
} SING_ROT_DIR;

typedef enum DOUB_ROT_DIR {
    left_right = 2,
    right_left
} DOUB_ROT_DIR;

// End helper Enums

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

void printTreeHelper(AvlTree tree, ToString toString, size_t depth)
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

AvlTree getSuccessor(AvlTree tree)
{
    assert(*tree != NULL);
    AvlTree succ = &(*tree)->right;
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

void singleRotation(AvlTree tree, SING_ROT_DIR dir)
{
    // rotate left, uses a bunch of right subtrees, and vice-versa
    assert(*tree && ((*tree)->right || (*tree)->left));
    TreeNode ** oldroot_sub_p = (dir == left) ? &(*tree)->right : &(*tree)->left;
    TreeNode ** newroot_sub_p = (dir == left) ? &(*oldroot_sub_p)->left : 
                                                &(*oldroot_sub_p)->right;
    TreeNode * oldroot = *tree;
    TreeNode * newroot = *oldroot_sub_p;

    *oldroot_sub_p = *newroot_sub_p;
    *newroot_sub_p = oldroot;
    *tree = newroot;

    setHeight(oldroot);
    setHeight(newroot);
    // old root is new leaf
    // old right subnode is new root, pivot
}

// Assumption will be that the side that is longer is the side for the first
// rotation
void doubleRotation(AvlTree tree, DOUB_ROT_DIR dir)
{
    SING_ROT_DIR r1, r2;
    AvlTree sub_tree;
    (dir == left_right) ? (r1 = left, r2 = right, sub_tree = &(*tree)->left) : 
                          (r1 = right, r2 = left, sub_tree = &(*tree)->right);
    
    singleRotation(sub_tree, r1);
    singleRotation(tree, r2);
}

int balanceFactor(TreeNode * tree)
{
    return (tree) ? heightTree(&tree->right) - heightTree(&tree->left) : 0;
}

void rebalanceTree(AvlTree tree)
{
    if (!*tree) return;
    int rot_type = -1;

    // The le and ge's are set to settle tie breaks, always go for single rots
    if (balanceFactor(*tree) >= 2) // Right heavy
    {
        rot_type = balanceFactor((*tree)->right) >= 0 ? 0  // Left rot
                                                      : 3; // Right-left rot
    }
    else if (balanceFactor(*tree) <= -2) // Left heavy
    {
        rot_type = balanceFactor((*tree)->left) <= 0 ? 1  // Right rot
                                                     : 2; // Left-right rot
    }
    else 
    {
        return; // No rebalancing necessary at this node
    }

    rot_type < 2 ? singleRotation(tree, rot_type) : doubleRotation(tree, rot_type);
}
// End Helpers

void printTree(AvlTree tree, ToString toString)
{
    printTreeHelper(tree, toString, 0);
}

bool makeAvlTree(AvlTree * tree_p)
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

bool isInTree(AvlTree tree, void * item, CompFun c)
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
int insertToTree(AvlTree tree, void * item, size_t size, CompFun c)
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
        rebalanceTree(tree);
    }
    return rc; 
}

bool deleteFromTree(AvlTree tree, void * item, CompFun c)
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
                AvlTree succ = getSuccessor(tree);
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

    if (rc && *tree) 
    {
        setHeight(*tree);
        rebalanceTree(tree);
    }

    return rc; 
}

void destroyAvlTree(AvlTree tree)
{
    // malloc node, value, and tree
    if (tree)
    {
        destroyBinaryTreeHelper(*tree);
    }
    free(tree);
    return;
}

void traverse(AvlTree tree, void (*elemFun) (void *))
{
    if (!*tree) return;
    traverse(&(*tree)->left, elemFun);
    elemFun((*tree)->value);
    traverse(&(*tree)->right, elemFun);
}

size_t heightTree(AvlTree tree)
{
    return (*tree) ? (*tree)->height : 0;
}

