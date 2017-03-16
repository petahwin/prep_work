#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>

using namespace std;

#define DIE(e) fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE)

int bool_paren(char ops[], char states[], int n)
{
    int f_c[n][n];
    int t_c[n][n];

    for (int i = 0; i < n; ++i) // init
    {
        t_c[i][i] = states[i] == 'T' ? 1 : 0; 
        f_c[i][i] = states[i] == 'F' ? 1 : 0; 
    }

    for (int l = 1; l < n; ++l) // l representing end index (acutally NOT!!!), 
                                // should have done length though, especially
                                // since I'm adding two indices, which makes
                                // little semantic sense, and just makes it harder;
                                // in fact, it caused tons of bugs!!!
    {
        for (int p = 0; p < n - l; ++p) // p representing starting pos/index
        {
            t_c[p][p+l] = 0;
            f_c[p][p+l] = 0;
            for (int s = p; s < p + l; ++s) // s representing splitter pos/index
                                            // I forgot to add 'p' to 'l'!!!
            {
                const int TT = t_c[p][s] * t_c[s+1][p+l]; // I originally just had 'l' here! Bug! 
                const int TF = t_c[p][s] * f_c[s+1][p+l]; // If 'l' was specified as length, 
                const int FT = f_c[p][s] * t_c[s+1][p+l]; // I would not have forgotten 
                const int FF = f_c[p][s] * f_c[s+1][p+l]; // to add to 'p'
                switch (ops[s]) 
                {
                    case '|': 
                    {
                        t_c[p][p+l] += TT + TF + FT;
                        f_c[p][p+l] += FF;
                        break;
                    }
                    case '&':
                    {
                        t_c[p][p+l] += TT;
                        f_c[p][p+l] += TF + FT + FF;
                        break;
                    }
                    case '^':
                    {
                        t_c[p][p+l] += TF + FT;
                        f_c[p][p+l] += TT + FF;
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i != n; ++i)
    {
        for (int k = 0; k < i*2; ++k) cout << ' ';
        for (int j = i; j != n; ++j)
        {
            cout << t_c[i][j] << ' ';
        }
        cout << '\n';
    }
    return t_c[0][n-1];
}

void test_1()
{
    char ops[] = {'|', '&', '^'};
    char states[] = {'T', 'T', 'F', 'T'};

    assert(4 == bool_paren(ops, states, sizeof(states)/sizeof(states[0])));
    return;
}

void test_2()
{
    char ops[] = {'^', '|'};
    char states[] = {'T', 'F', 'F'};

    assert(2 == bool_paren(ops, states, sizeof(states)/sizeof(states[0])));
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

