#include <stdio.h>
#include "List.h"
// add two elements, remove one, add two, print all

int main()
{
    List *list = makeList();
    addIntNodetoEndofList(list, 1);
    addIntNodetoEndofList(list, 2);
    addIntNodetoEndofList(list, 3);

    printIntsList(list);

    printf("length: %d\n", getLengthList(list));
    return 0;
}


/*

[1,2,3]


*/
