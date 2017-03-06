#include <algorithm>
#include <assert.h>
#include <iterator>

#include "Graph.hh"



// Inspect the color of the current node
// Foreach neighbor:
//      if uncolored, then color and recursively call
//      else if colored, then continue if opposite color, false otherwise
bool Graph::isBipartite_(size_t vertex, std::vector<Graph::COLOR>& coloring) const
{
    Graph::COLOR this_color = coloring[vertex];
    assert(this_color != UNSET);

    const std::vector<int>& neighbors = adj_list_[vertex];
    for (size_t i = 0; i != neighbors.size(); ++i)
    {
        if (UNSET == coloring[neighbors[i]]) 
        {
            coloring[neighbors[i]] = (this_color == RED) ? BLUE : RED;
            if (!isBipartite_(neighbors[i], coloring)) return false;
        }
        else if (this_color == coloring[neighbors[i]])
        {
            return false;
        }
    }

    return true;
}

// Will go thru all (disjoint) graph(s), driven by the priv function that analyzes
// a single graph

// Iterate thru the vertices; 
// if uncolored, then color the vertex and then drill down with the priv
// function, it'll return if a two coloring was possible
// We want all sub calls to return true, any false return will fail the whole function

bool Graph::isBipartite() const
{   
    std::vector<Graph::COLOR> coloring(adj_list_.size(), UNSET);
    for (size_t i = 0; i != adj_list_.size(); ++i)
    {
        if (UNSET == coloring[i]) coloring[i] = BLUE;
        if (!isBipartite_(i, coloring)) return false;
    }

    return true;
}


bool Graph::addVertex(const std::string& str_key)
{
    if (keyMap_.find(str_key) != keyMap_.end()) return false;
    
    keyMap_[str_key] = count_;
    reverseKeyMap_[count_++] = str_key;

    adj_list_.push_back(std::vector<int>());

    return true;
}

bool Graph::addEdge(const std::string& s1, const std::string& s2)
{   
    Graph::KeyMap::const_iterator st1, st2;
    st1 = keyMap_.find(s1); 
    st2 = keyMap_.find(s2);
    if (st1 == keyMap_.end() || st2 == keyMap_.end()) return false;
    if (adj_list_[st1->second].end() != std::find(adj_list_[st1->second].begin(), 
                                                  adj_list_[st1->second].end(), 
                                                  st2->second)) 
    {
        return false; // already added edge
    }

    adj_list_[st1->second].push_back(st2->second);
    adj_list_[st2->second].push_back(st1->second);
    
    return true;
}

bool Graph::neighbors(const std::string& key, std::vector<std::string>& outList) const
{
    Graph::KeyMap::const_iterator st = keyMap_.find(key);
    if (st == keyMap_.end()) return false;

    std::vector<int>::const_iterator it = adj_list_[st->second].begin();
    for (; it != adj_list_[st->second].end(); ++it)
    {
        ReverseKeyMap::const_iterator jt = reverseKeyMap_.find(*it);
        outList.push_back(jt->second);
    }

    return true;
}

// 0 if adjacent, 1 if not, -1 if either or both keys not found in graph
int Graph::isAdjacent(const std::string& s1, const std::string& s2) const
{
    return 0;
}

std::ostream& operator<<(std::ostream& os, const Graph& g)
{
    std::vector<std::vector<int> >::const_iterator it = g.adj_list_.begin();
    for (; it != g.adj_list_.end(); ++it)
    {
        size_t index = std::distance(g.adj_list_.begin(), it);
        Graph::ReverseKeyMap::const_iterator t = g.reverseKeyMap_.find(index);
        assert(t != g.reverseKeyMap_.end());
        
        os << t->second << " : ";
        std::vector<int>::const_iterator jt = it->begin();
        for (; jt != it->end(); ++jt)
        {
            Graph::ReverseKeyMap::const_iterator v = g.reverseKeyMap_.find(*jt);
            assert(v != g.reverseKeyMap_.end());
            os << v->second << " -> ";
        }
        os << "[]" << std::endl;
    }

    return os;
}

