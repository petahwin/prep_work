
#include <assert.h>
#include "adj_matrix.hh"

// I've practiced this on paper, now to simplify the scope of this implementation
// for specific applications rather than general purpose for quick writeup


// Assume static number of vertices, think about dynamically adding/rm'ing vertices
void init_graph(Graph * g, int n, bool dir) 
{
    assert(n <= MAX_VERTICES);
    g->n_vertices = n;
    for (int i = 0 ; i != MAX_VERTICES * MAX_VERTICES; ++i) g->adj[i] = false;
    g->directed = dir;
}

static int idx(int i, int j) 
{
    return i * MAX_VERTICES + j;
}

void add_edge(Graph * g, int i, int j) 
{
    assert(i < g->n_vertices && j < g->n_vertices);
    g->adj[idx(i,j)] = true;
    if (!g->directed) g->adj[idx(j,i)] = true; // Can remove this if we know we are using top sort
}

static int state[MAX_VERTICES];
enum {
    UNDISCOVERED = 0,
    DISCOVERED,
    PROCESSED
};

// Currently no support for reporting cycle found, could trickle up a bool

static void top_sort_impl(Graph & g, std::stack<int> & out, int v)
{
    if (DISCOVERED == state[v]) return;
    if (PROCESSED == state[v]) return;
    state[v] = DISCOVERED;
    for (int i = 0; i != g.n_vertices; ++i) // Unavoidable loop for adj matrix to find neighbors
    {
        if (g.adj[idx(v, i)]) top_sort_impl(g, out, i);
    }
    out.push(v);
    state[v] = PROCESSED;
    return;
}

void top_sort(Graph & g, std::stack<int> &out) 
{
    while(!out.empty()) out.pop();
    for(int i = 0; i != MAX_VERTICES; ++i) state[i] = UNDISCOVERED;
    int v; 
    bool exists_undiscovered = false;
    for (int i = 0; i != g.n_vertices; ++i) // We only loop in case we don't know
                                            // the number of vertices;
                                            // If we know at compile time, can
                                            // skip this first loop
    {
        if (state[i] == UNDISCOVERED)
        {
            exists_undiscovered = true;
            v = i;
            break;
        }
    }

    while(exists_undiscovered)
    {
        exists_undiscovered = false;
        top_sort_impl(g, out, v);

        for (int i = 0; i != g.n_vertices; ++i) // Loop can be avoided, if we
                                                // use set structures to capture
                                                // state
        {
            if (state[i] == UNDISCOVERED)
            {
                exists_undiscovered = true;
                v = i;
                break;
            }
        }
    }
}

// This can only be used if the edges are not destroyed in the process
// I suppose we could create some temporary duplicate matrix to preserve
// the original edges, if we wanted to use this after Kahn's algorithm, and not
// care about uniqueness checking during Kahn's alg
bool is_uniq_top_sort(Graph & g, std::stack<int> & out)
{
    if (out.empty()) return true;
    int from = out.top(); 
    out.pop();
    if (out.empty()) return true;
    int to;
    while(!out.empty())
    {
        to = out.top();
        out.pop();
        if (!g.adj[idx(from, to)]) return false;
        from = to;
    }

    return true;
}

