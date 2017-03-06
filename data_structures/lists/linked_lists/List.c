#include "List.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct Node {
    void * val; // Any data type (be careful...)
    struct Node * next;
};

struct List {
    Node * items;
    int length;
};

List * makeList()
{
    List * list_p = malloc(sizeof(List));
    list_p->items = 0;
    list_p->length = 0;
    return list_p;
}

Node ** getTailEndofList(List * list_p) // Implementation detail
{
    Node ** items = &list_p->items;
    
    while (*items)
    {
        items = &((*items)->next);
    }
    return items;
}



bool addIntNodetoEndofList(List * list_p, int val)
{
    int * val_p = malloc(sizeof(int)); // check for NULL
    Node * new_node_p = malloc(sizeof(Node));
    if (! (val_p && new_node_p) )
    {
        return false;
    }
    
    *val_p = val;
    new_node_p->val = val_p;
    new_node_p->next = 0;
    
    Node ** end_p = getTailEndofList(list_p);
    assert(end_p != 0);
    
    *end_p = new_node_p;
    ++list_p->length;
    return true;
}

void printIntsList(List * list_p)
{
    Node * items = list_p->items;
    while(items)
    {
        printf("%d -> ", *(int *)items->val);
        items = items->next;
    }
    printf("[]\n");
}

int getLengthList(List * list_p)
{
    return list_p->length;
}

