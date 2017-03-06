#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include "Graph.hh"

#define DIE(str) {std::cerr << "Error: " << (str) << std::endl; return EXIT_FAILURE;}

void testNull()
{
    Graph g;
    std::cout << g << std::endl;
}

void testIns()
{
    Graph g;
    assert(g.addVertex("Peter"));
    assert(g.addVertex("Parker"));
    assert(!g.addVertex("Parker"));
    assert(g.addEdge("Peter", "Parker"));
    assert(!g.addEdge("Peter", "Parker"));
    std::cout << g << std::endl;
}

void testNeighbors()
{
    Graph g;
    assert(g.addVertex("Peter"));
    assert(g.addVertex("Parker"));
    assert(g.addVertex("Ben"));
    assert(g.addEdge("Peter", "Parker"));
    assert(g.addEdge("Ben", "Parker"));
    
    std::vector<std::string> out;
    assert(g.neighbors("Parker", out));
    for (size_t i=0; i != out.size(); ++i) std::cout << out[i] << "\n";
    std::cout << g << std::endl;
}

void testBipartite()
{
    Graph g;
    assert(g.addVertex("Peter"));
    assert(g.addVertex("MJ"));
    assert(g.addVertex("Ben"));
    assert(g.addVertex("May"));
    assert(g.addVertex("Gwen"));
    assert(g.addVertex("JJ"));
    
    assert(g.addEdge("Peter", "MJ"));
    assert(g.addEdge("MJ", "Ben"));
    assert(g.addEdge("Ben", "May"));
    assert(g.addEdge("May", "Gwen"));
    assert(g.addEdge("Gwen", "JJ"));
    assert(g.addEdge("JJ", "Peter"));


    assert(g.isBipartite());

    assert(g.addEdge("May", "Peter"));

    assert(g.isBipartite());

    assert(g.addEdge("Peter", "Ben"));
    
    assert(!g.isBipartite());

    std::cout << g << std::endl;
}

int main(int argc, char ** argv) 
{
    void (*testArr[])(void) = {
                                testNull,
                                testIns,
                                testNeighbors,
                                testBipartite
                              }; 
    if (argc < 2) DIE("You must provide a test no.");
    int testNo = atoi(argv[1]);
    if (testNo < 0) DIE("Test no. must be non-negative");
    printf("%d\n", testNo);
    testArr[testNo]();
    return EXIT_SUCCESS;
}

