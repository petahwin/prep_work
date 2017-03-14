#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DIE(e) fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE)

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

    const size_t test_no = atoi(argv[1]);
    if (!(0 <= test_no && test_no <= n_tests))
    {
        DIE("Invalid or out of bounds test number");
    }

    if (test_no == 0)
    {
        printf("Running all tests\n");
        for (size_t i = 0; i != n_tests; ++i)
        {
            tests[i]();
            printf("Test %lu passed\n", i);
        }
        printf("All tests passed\n");
    }
    else
    {
        tests[test_no-1]();
        printf("Test %lu passed\n", test_no);
    }

    
    return EXIT_SUCCESS;
}

