#include <map>
#include <stddef.h>
#include <string>
#include <vector>
#include <ostream>

// String key'd graph ADT, no metadata
class Graph
{
public:
    Graph() : count_(0) { }
    bool addVertex(const std::string& str_key);
    bool addEdge(const std::string& s1, const std::string& s2);
    bool neighbors(const std::string& key, std::vector<std::string>& outList) const;
    
    // 0 if adjacent, 1 if not, -1 if either or both keys not found in graph
    int isAdjacent(const std::string& s1, const std::string& s2) const;
    
    bool isBipartite() const;

private:
    enum COLOR {
        RED,
        BLUE,
        UNSET
    };
    
    bool isBipartite_(size_t vertex, std::vector<COLOR>& coloring) const;

    std::vector<std::vector<int> > adj_list_;

    typedef std::map<std::string, size_t> KeyMap;
    typedef std::map<size_t, std::string> ReverseKeyMap;
    KeyMap keyMap_;
    ReverseKeyMap reverseKeyMap_;

    size_t count_; // Number of vertices added, as well as identifying vertices   
    
    friend std::ostream& operator<<(std::ostream& os, const Graph& g);
};

