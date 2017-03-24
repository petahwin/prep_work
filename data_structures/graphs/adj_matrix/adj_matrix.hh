#define MAX_VERTICES 100
#include <stack>

// Very C style interface for barebones adj matrix implementation of a graph
// Not thread safe, not reentrant

// If I want to hide the data members of this structure, I would have to 
// expose just the pointer to the struct, and in the implementation, dynamically
// allocate and deallocate memory for the struct via function calls
typedef struct Graph Graph;
struct Graph {
    int n_vertices;
    bool adj[MAX_VERTICES*MAX_VERTICES];
    bool directed;
};

void init_graph(Graph * g, int n, bool dir);

void add_edge(Graph * g, int i, int j);

// Using DFS implementation of topological sort, for the advantage of
// 1. Not having to delete edges during run
// 2. Detecting cycles relatively earlier/easier
// 3. Not deleting edges => can easily check for hamiltonian path => unique top sort
//    by finding edges between adjacent vertices in the top sort
// Cons:
// -1. Having to keep track of state of a vertex (undiscovered, discovered, processed)
// -2. Cannot determine uniqueness of the top sort until after the alg terminates;
//     in Kahn's algorithm, can figure it out early during alg if not unique
void top_sort(Graph & g, std::stack<int> &out);

// By searching for edges between adjacent vertices in ordering
bool is_uniq_top_sort(Graph & g, std::stack<int> & out);

