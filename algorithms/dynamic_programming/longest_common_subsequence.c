#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#define MAX(a,b) ((a) > (b)) ? (a) : (b)
#define DIE(str) {fprintf(stderr, "Error: %s\n", (str)); return EXIT_FAILURE;}


size_t getLCS(size_t l1, size_t l2, char * s1, char * s2)
{
    size_t ** len = malloc(sizeof(size_t *) * l1);
    for (size_t i = 0; i != l1; ++i) len[i] = malloc(sizeof(size_t) * l2);

    len[0][0] = (s1[0] == s2[0]) ? 1 : 0;
    for (size_t i = 0; i != l2; ++i) len[0][i] = (s1[0] == s2[i]) ? 1 : 0;
    for (size_t i = 0; i != l1; ++i) len[i][0] = (s1[i] == s2[0]) ? 1 : 0;

    for (size_t i = 1; i != l1; ++i)
    {
        for (size_t j = 1; j != l2; ++j)
        {
            len[i][j] = MAX(MAX(len[i-1][j], len[i][j-1]), 
                            (len[i-1][j-1] + (s1[i] == s2[j] ? 1 : 0)));
        }
    }

    size_t ret = len[l1-1][l2-1];

    for (size_t i = 0; i != l1; ++i) free(len[i]);
    free(len);

    return ret;
}

void test1()
{
    char s1[] = "AGGTAB";
    char s2[] = "GXTXAYB";
    
    printf("%zu\n", getLCS(6,7,s1,s2));
    assert(4 == getLCS(6, 7, s1, s2));
}

void test2()
{
    char s1[] = "ABCDGH";
    char s2[] = "AEDFHR";
    
    printf("%zu\n", getLCS(6,6,s1,s2));
    assert(3 == getLCS(6, 6, s1, s2));
}

int main(int argc, char **argv)
{
    void (*testArr[])(void) = {
                                test1,
                                test2
                              }; 
    if (argc < 2) DIE("You must provide a test no.");
    int testNo = atoi(argv[1]);
    if (testNo < 0) DIE("Test no. must be non-negative");
    printf("%d\n", testNo);
    testArr[testNo]();
    return EXIT_SUCCESS;
}

