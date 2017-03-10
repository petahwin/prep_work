// Ref: https://en.wikipedia.org/wiki/Matrix_chain_multiplication

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>

#define DIE(e) fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE)

size_t rod_cutting_cost(size_t price[], size_t n)
{
    int best[n+1];
    best[0] = 0;
    
    for (int i = 1; i != n + 1; ++i)
    {
        best[i] = -1;
        for (int j = 0; j < i; ++j)
        {
            int candidate = price[j] + best[i-j-1];
            best[i] = best[i] < candidate ? candidate : best[i];
        }
    }

    return best[n];
}

void test_1()
{
    size_t price[] = {3,5,8,9,10,17,17,20};
    assert(24 == rod_cutting_cost(price, sizeof(price)/sizeof(price[0])));
    return;
}

void test_2()
{
    size_t price[] = {1,5,8,9,10,17,17,20};
    assert(22 == rod_cutting_cost(price, sizeof(price)/sizeof(price[0])));
    return;
}

// Register tests here
void (*tests[])() = {
    test_1,
    test_2
};

int main(int argc, char ** argv) 
{
    const size_t n_tests = sizeof(tests)/sizeof(tests[0]);

    if (argc != 2)
    {
        DIE("Usage: exe <test_number>");
    }

    const size_t test_no = atoi(argv[1]) - 1;
    if (!(0 <= test_no && test_no < n_tests))
    {
        DIE("Invalid or out of bounds test number");
    }

    tests[test_no]();

    printf("Test %d passed\n", test_no+1);
    
    return EXIT_SUCCESS;
}

