#include <unordered_map>
#include <vector>
#include <algorithm>

/*
- necessary graph functions:
    - add edge
    - remove edge
    - add node (manually)
    - remove node (and all associated edges)
    - are two nodes neighbors
- some implementation details:
    - nodes will be integers, weights will also be integers
    - negative weights will be allowed
    - different graph algorithms will be class methods
    - graph is directed AND weighted
*/

struct Edge {
    int dest;
    int weight;
    Edge::Edge(int d, int w) : dest(d), weight(w) {};
};

class Graph {
    private:
    // int -> vector<Edge> for mapping a vertex to a list of edges
    std::unordered_map<int, std::vector<Edge>> adjacencyList;
    bool negativeWeights;

    public:

    // insert/remove functions
    void insertEdge(int source, int dest, int weight); // insert edge from origin to dest with weight
    void insertVertex(int vert); // initialized vertex with empty list
    void removeVertex(int vert); // remove vertex and associated edge list
    void removeEdge(int source, int dest); // removes edge associated with origin and dest
    void changeWeight(int source, int dest, int weight); // changes weight associated with the edge between origin and dest
    
    // utility functions
    int vertexCount(); // number of vertices
    int edgeCount(); // number of edges
    std::vector<Edge> neighbors(int vertex); // all neighbors of a specified vertex
    void disableNegativeWeights(); // disable/enable negative weights within GUI
    // if negative weights are present when negative weights are disabled, they will all be set to abs(weight)
    void enableNegativeWeights(); // if negative weights are enabled, only bellman-ford and floyd-warshall can be used


    // algorithms
    std::vector<std::pair<int, int>> Dijkstras(int source);
    std::vector<std::pair<int, int>> AStar(int source);
    std::vector<std::pair<int, int>> BellmanFord(int source);
    std::unordered_map<int, std::pair<int, int>> FloydWarshall(); // returns all shortest paths
};