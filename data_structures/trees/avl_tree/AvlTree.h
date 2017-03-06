#include <stdbool.h>
#include <stddef.h>

struct TreeNode;
typedef struct TreeNode** AvlTree; 
typedef int (*CompFun) (void *, void *); // -1 => lt, 0 => eq, 1 => gt

bool makeAvlTree(AvlTree * tree_p);
int insertToTree(AvlTree tree, void * item, size_t size, CompFun c);
bool deleteFromTree(AvlTree tree, void * item, CompFun c);
bool isInTree(AvlTree tree, void * item, CompFun c);
void destroyAvlTree(AvlTree tree);

void traverse(AvlTree tree, void (*elemFun) (void *));
size_t heightTree(AvlTree tree);

// For debug purposes
typedef void (*ToString) (void *, char *);
void printTree(AvlTree tree, ToString toString);

