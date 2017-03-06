#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define DIE(e) fprintf(stderr, "%s", e); exit(EXIT_FAILURE)
#define MAXSIZE 15

namespace PP {
void printInt(int i)
{
    std::cout << ' ' << i;
}

void printArr(int * arr, size_t n)
{
    static size_t count = 0;
    std::cout << ++count << ".\t";
    std::for_each(arr, arr + n, printInt);
    std::cout << '\n';
}
} // end namespace PP

void printPermutations(size_t n);

int main(int argc, char ** argv) 
{
    if (argc != 2)
    {
        DIE("Usage: ./exe <array_len>");        
    }

    printPermutations(atoi(argv[1]));
    return EXIT_SUCCESS;
}

void printPermutationsDriver(size_t k, const int * arr, bool * aux)
{
    static int out[MAXSIZE];
    static const size_t n = k;

    for (size_t i = 0; i != n; ++i)
    {
        if (!aux[i]) 
        {
            aux[i] = true;
            out[n-k] = arr[i];

            if (k == 1) // base case 
            {
                PP::printArr(out, n);
            } 
            else
            {
                printPermutationsDriver(k-1, arr, aux);
            }
        
            aux[i] = false;
        }
    }
}

// Impure functor to generate monotically increasing integers
// Create an explicit instance before use, cannot use an inline constructed object
struct IntGen 
{
    int _i;
    IntGen(int i=0) : _i(i) { }
    int operator()() { return _i++; }
};

int intGenFun()
{
    static int i = 0;
    return i++;
}

// Prints out all permutations of an array of size n,
// elements from 1..n
void printPermutations(size_t n)
{
    // Init the array to permute
    int arr[n];

    IntGen intGen;
    std::generate(arr, arr+n, intGenFun);
    
    // Init the auxiliary array 
    bool aux[n];
    std::fill(aux, aux+n, false);

    printPermutationsDriver(n, arr, aux);
}

