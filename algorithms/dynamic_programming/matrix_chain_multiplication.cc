// Ref: https://en.wikipedia.org/wiki/Matrix_chain_multiplication

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DIE(e) fprintf(stderr, "%s", e); exit(EXIT_FAILURE)

// 1. Define struct to represent matrix dimensions
// 2. Create test cases, matrix multiplication chains
// 3. Implement algorithm to compute min operations
// 4. Get test cases to *verify* correctness of the cases
// Bonus: Print the parenthesization

void test_1()
{
    return;
}

void test_2()
{
    assert(false);
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

