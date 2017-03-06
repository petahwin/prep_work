#include <stdbool.h>
#include <stddef.h>

struct Node;
typedef struct Node Node;

struct List;
typedef struct List List;


List * makeList();

// Should not be a problem, although should check for malloc success
bool addIntNodetoEndofList(List * list_p, int val);

// Returns if successful
bool deleteNthNodefromList(List * list_p, size_t index);

// Get
bool getNthNodefromList(List * list_p, void * out_p);

// Search
int isIntinList(List * list_p, int val);

// Side effects
void printIntsList(List * list_p);

// yup
int getLengthList(List * list_p);

