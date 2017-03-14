#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DIE(e) fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE)
#define MIN(a,b) ((a) < (b) ? (a) : (b))

using namespace std;

// 45 degree clockwise rotation for matrices

// Two ways to print out a run of an array or a matrix
// 1. Pick the coordinates
// 2. Pin down one coordinate, specify a length, and then use both
//    to compute the coordinates
//    - Usually, we can assume the same starting coordinate for the unspecified
//      coordinate (i.e. always starts on same row, or on same column)

// Row major order
char idx(char * arr, int i, int j, int m, int n)
{
    return arr[n * i + j];
}

void print_mat(char * arr, int m, int n)
{
    for (int i = 0; i != m; ++i)
    {
        for (int j = 0; j != n; ++j)
        {
            cout << idx(arr, i, j, m, n) << ' ';
        }
        cout << '\n';
    }
}

void print_diamond(char * arr, int m, int n) 
{
    // Get min dimension, that will bound the diagonal walk
    const int minDim = MIN(m,n);

    for (int i = 0; i != m; ++i) // iterate up to bottom left corner
    { 
        for (int s = 0; s != m - 1 - i; ++s) cout << ' '; // get spaces first
        for (int j = 0; j != MIN(i + 1, minDim); ++j) 
        {
            cout << idx(arr, i - j, j,m,n) << ' '; 
        }
        cout << '\n';
    }

    for (int j = 1; j != n; ++j)
    {
        for (int s = 0; s != j; ++s) cout << ' ';
        for (int i = 0; i != MIN(minDim, n - j); ++i)
        {
            cout << idx(arr, m-1-i, j + i,m,n) << ' ';
        }
        cout << '\n';
    }
}


void test_1()
{
    const int m = 6;
    const int n = 3;
    
    char arr[] = {
        'a','b','c',
        'd','e','f',
        'g','h','i',
        'j','k','l',
        'm','n','o',
        'p','q','r'
    }; 

    print_mat(arr,m,n);
    print_diamond(arr,m,n);
    return;
}

void test_2()
{
    const int m = 3;
    const int n = 6;

    char arr[] = {
        'a','b','c','d','e','f',
        'g','h','i','j','k','l',
        'm','n','o','p','q','r'
    };

    print_mat(arr,m,n);
    print_diamond(arr,m,n);
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
        for (int i = 0; i != n_tests; ++i)
        {
            tests[i]();
        }
        printf("All tests passed\n");
    }
    else
    {
        tests[test_no-1]();
        printf("Test %d passed\n", test_no);
    }

    
    return EXIT_SUCCESS;
}

