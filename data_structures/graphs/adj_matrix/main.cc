#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include "adj_matrix.hh"

#define DIE(e) fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE)

void test_1()
{
    Graph g;
    init_graph(&g, 6, true);
    add_edge(&g, 0,1);
    add_edge(&g, 0,2);
    add_edge(&g, 2,3);
    add_edge(&g, 2,4);
    add_edge(&g, 1,3);
    add_edge(&g, 3,5);

    for (int i = 0; i != 6; ++i) {
        for (int j = 0; j != 6; ++j) {
            std::cout << g.adj[i * MAX_VERTICES + j] << ' ';
        }
        std::cout << '\n';
    }

    std::stack<int> out;
    top_sort(g, out);

    while (!out.empty()) {
        std::cout << out.top() << ' ';
        out.pop();
    }
    std::cout << '\n';
    top_sort(g, out);

    assert(!is_uniq_top_sort(g, out));

    return;
}

void test_2()
{
    Graph g;
    init_graph(&g, 5, true);
    add_edge(&g, 0,1);
    add_edge(&g, 0,2);
    add_edge(&g, 0,3);
    add_edge(&g, 0,4);
    add_edge(&g, 4,3);
    add_edge(&g, 3,2);
    add_edge(&g, 2,1);
    add_edge(&g, 3,1);
    add_edge(&g, 3,2);

    for (int i = 0; i != 5; ++i) {
        for (int j = 0; j != 5; ++j) {
            std::cout << g.adj[i * MAX_VERTICES + j] << ' ';
        }
        std::cout << '\n';
    }

    std::stack<int> out;
    top_sort(g, out);

    while (!out.empty()) {
        std::cout << out.top() << ' ';
        out.pop();
    }
    std::cout << '\n';

    top_sort(g, out);
    assert(is_uniq_top_sort(g, out));
    return;
}

void test_3()
{
    Graph g;
    init_graph(&g, 4, true);
    add_edge(&g, 0,1);
    add_edge(&g, 2,3);

    for (int i = 0; i != 4; ++i) {
        for (int j = 0; j != 4; ++j) {
            std::cout << g.adj[i * MAX_VERTICES + j] << ' ';
        }
        std::cout << '\n';
    }

    std::stack<int> out;
    top_sort(g, out);

    while (!out.empty()) {
        std::cout << out.top() << ' ';
        out.pop();
    }
    std::cout << '\n';

    top_sort(g, out);
    assert(!is_uniq_top_sort(g, out));
    return;
}

// Register tests here
void (*tests[])() = {
    test_1,
    test_2,
    test_3
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
            printf("Test %lu passed\n", i+1);
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

