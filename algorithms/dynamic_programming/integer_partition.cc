// Ref: https://en.wikipedia.org/wiki/Matrix_chain_multiplication

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DIE(e) fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE)

bool integer_partition(size_t arr[], size_t n)
{
    size_t sum = 0;
    for (size_t i = 0; i != n; ++i) sum += arr[i];
    if (sum % 2 != 0) return false;
    const size_t target = sum / 2;

    // bool ** hasTarget = (bool **)malloc(sizeof(bool *) * (target + 1));
    // for (size_t i = 0; i != target + 1; ++i) hasTarget[i] = (bool *)malloc(sizeof(bool) * (n+1));
    bool hasTarget[target+1][n+1];
    
    // Defining array bounds; we use target + 1 to be able to index 0..target representing all sums
    // we use n + 1 to represent up to what index to include; 0..n -> empty set up to whole set

    // hasTarget[target + 1][n] <- appeared not to work, with j index up to n, not n + 1
    // Represents what sums can be made with some subset from the range [0, i..n]
    
    // hasTarget[arr[0]][0..n] = true;
    // hasTarget[0][0..n] = true;
    for (size_t i = 0; i != target+1; ++i)
    {
        for (size_t j = 0; j != n + 1; ++j)
        {
            // arr[0] == i; First element in arr can be made anywhere
            // 0 == i;      Empty set can always yield zero
            hasTarget[i][j] = 0 == i;
        }
    }

    for (size_t i = 1; i != target+1; ++i)
    {
        for (size_t j = 1; j != n+1; ++j)
        {
            hasTarget[i][j] = hasTarget[i][j-1] || (i >= arr[j-1] ? hasTarget[i-arr[j-1]][i-1]: false);
        }
    }

    return hasTarget[target][n];
}

void test_1()
{
    size_t arr[] = {3,1,1,2,2,1};
    assert( true == integer_partition(arr, sizeof(arr)/sizeof(arr[0]) ));
}

void test_2()
{
    size_t arr[] = {2,5};
    assert( false == integer_partition(arr, sizeof(arr)/sizeof(arr[0]) ));
}

void test_3()
{
    size_t arr[] = {1,5,11,5};
    assert( true == integer_partition(arr, sizeof(arr)/sizeof(arr[0]) ));
}

void test_4()
{
    size_t arr[] = {1,5,3};
    assert( false == integer_partition(arr, sizeof(arr)/sizeof(arr[0]) ));
}

// Register tests here
void (*tests[])() = {
    test_1,
    test_2,
    test_3,
    test_4
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

