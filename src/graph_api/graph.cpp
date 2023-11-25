#include "graph.h"


bool Graph::insertEdge(int source, int dest, int weight) {
    // prevent source == dest
    if(source == dest) return false;

    // prevent duplicate edges in the same direction, dest == e.dest already in neighbors, to overwrite weight use changeWeight
    std::vector<Edge> n = mapList[source];
    auto it = std::find_if(n.begin(), n.end(), [&dest](const Edge& e) {e.dest == dest;}); 

    // insert mapList[dest] just in case
    insertVertex(dest);

    // not found, so insert 
    if(it == n.end()) {
        mapList[source].push_back(Edge(dest, weight));
        return true;
    }

    return false;

}

// true if initialized, false if already exists
bool Graph::insertVertex(int vert) {
    return mapList[vert].empty();
}

// remove vertex and all edges associated with it
void Graph::removeVertex(int vert) {
    mapList.erase(vert);
    for(auto it : mapList) {
        // i swear this looks suspicious but it works :^)
        std::vector<Edge>& vec = it.second;
        vec.erase(
            std::remove_if(vec.begin(), vec.end(), [&vert](const Edge& e) {
                return e.dest == vert;
            }), vec.end()
        );
    }
}

void Graph::removeEdge(int source, int dest) {

}

void Graph::changeWeight(int source, int dest, int weight) {

}

int Graph::vertexCount() {
    return 0;
}

int Graph::edgeCount() {
    return 0;
}

std::vector<Edge> Graph::neighbors(int vertex) {
    return mapList[vertex];
}

void Graph::disableNegativeWeights() {

}

void Graph::enableNegativeWeights() {

}

std::vector<Edge> Graph::Dijkstras(int source) {

}

std::vector<Edge> Graph::AStar(int source) {

}

std::vector<Edge> Graph::BellmanFord(int source) {

}

std::unordered_map<int, std::vector<Edge>> Graph::FloydWarshall() {

}