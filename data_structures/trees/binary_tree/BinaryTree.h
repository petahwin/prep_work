#include <stdbool.h>
#include <stddef.h>

// Headless binary tree, abstract 
// Issue with element value; we do not know the value at runtime if we pass in
// a void pointer, but we still want the interface functions to be as abstract
// as possible; the best we can do is have a set of functions that do dynamic
// allocation on the type that we want, and have the tree know nothing about the
// type, just copy the void pointer
// But then we'd need that for all accesses and modifications

// Second option is to just have the caller do the memory allocation
// but for this data structure, we'd still have an issue; we have no idea how to
// compare elements for insertion, search, deletion, etc

// Unless we pass in a function pointer, I suppose
// So caller does the memory allocation, and passes in the comparator function pointer

struct TreeNode;
typedef struct TreeNode** BinarySearchTree; 
typedef int (*CompFun) (void *, void *); // -1 => lt, 0 => eq, 1 => gt

bool makeBinaryTree(BinarySearchTree * tree_p);
int insertToTree(BinarySearchTree tree, void * item, size_t size, CompFun c);
bool deleteFromTree(BinarySearchTree tree, void * item, CompFun c);
bool isInTree(BinarySearchTree tree, void * item, CompFun c);
void destroyBinaryTree(BinarySearchTree tree);

void traverse(BinarySearchTree tree, void (*elemFun) (void *));
size_t heightTree(BinarySearchTree tree);

// For debug purposes
typedef void (*ToString) (void *, char *);
void printTree(BinarySearchTree tree, ToString toString);

