#include <unordered_map>
#include <vector>
#include <utility>

struct Edge {
    int dest;
    int weight;
    Edge(int d, int w) : dest(d), weight(w) {};
};

class Graph {
    private:
    // int -> vector<Edge> for mapping a vertex to a list of edges
    std::unordered_map<int, std::vector<Edge>> mapList;
    bool negativeWeights; 

    public:
    // insert/remove functions
    bool insertEdge(int source, int dest, int weight); // insert edge from origin to dest with weight
    bool insertVertex(int vert); // initialized vertex with empty list
    void removeVertex(int vert); // remove vertex and associated edge list
    void removeEdge(int source, int dest); // removes edge associated with origin and dest
    void changeWeight(int source, int dest, int weight); // changes weight associated with the edge between origin and dest
    void clear(); // completely clears graph
    
    // utility functions
    int vertexCount(); // number of vertices
    int edgeCount(); // number of edges
    std::vector<Edge> neighbors(int vertex); // all neighbors of a specified vertex
    void disableNegativeWeights(); // disable/enable negative weights within GUI
    // if negative weights are present when negative weights are disabled, they will all be set to abs(weight)
    void enableNegativeWeights(); // if negative weights are enabled, only bellman-ford and floyd-warshall can be used
    int areNeighbors(int source, int dest); //method that checks if two vertices are neighbors

    void printGraph(); //for debugging purposes
    void generateGraph(int num); // num to allow for custom connected graphs

    // algorithms
    std::unordered_map<int, std::pair<int, int>> Dijkstras(int source);
    std::unordered_map<int, std::pair<int, int>> BellmanFord(int source);
    std::unordered_map<int, std::unordered_map<int, int>> FloydWarshall(); // returns all shortest paths
};

// vim: et:sts=4:sw=4:
