#include "graph.h"

bool Graph::insertEdge(int source, int dest, int weight) {
    // prevent source == dest
    if (source == dest)
        return false;

    //check for negative
    if (!negativeWeights && weight < 0)
        return false;

    // prevent duplicate edges in the same direction, dest == e.dest already in neighbors, to overwrite weight use changeWeight
    std::vector<Edge> n = mapList[source];
    auto it = std::find_if(n.begin(), n.end(),
        [&dest](const Edge& e) { return e.dest == dest; }
        );
    if (it != n.end())
        return false;

    // not found, so insert
    // insert mapList[dest] just in case
    insertVertex(dest);
    mapList[source].push_back(Edge(dest, weight));
    return true;
}

// if uninitialized or null, creates vector, returns true
// if initialized and nonempty (a.k.a, vertex has edges), returns false
bool Graph::insertVertex(int vert) {
    return mapList[vert].empty();
}

// remove vertex and all edges associated with it
void Graph::removeVertex(int vert) {
    mapList.erase(vert);
    for (auto& it : mapList) {
        // i swear this looks suspicious but it works :^)
        std::vector<Edge>& vec = it.second;
        vec.erase(
            std::remove_if(vec.begin(), vec.end(),
                [&vert](const Edge& e) { return e.dest == vert; }
                ),
            vec.end());
    }
}

void Graph::removeEdge(int source, int dest) {
    mapList[source].erase(
        std::remove_if(
            mapList[source].begin(), mapList[source].end(),
            [dest](Edge& e){ return e.dest == dest; }
        )
    );
}

void Graph::changeWeight(int source, int dest, int weight) {
    for (auto& i : mapList[source]) {
        if (i.dest == dest)
            i.weight = weight;
    }
}

int Graph::vertexCount() {
    return mapList.size();
}

int Graph::edgeCount() {
    int count = 0;
    for (auto v : mapList)
        count += v.second.size();
    return count;
}

std::vector<Edge> Graph::neighbors(int vertex) {
    return mapList[vertex];
}

void Graph::disableNegativeWeights() {
    negativeWeights = false;
    for (auto& v : mapList) {
        for (int i = 0; i < v.second.size(); i++) {
            int a = v.second[i].weight;
            // absolute value, basically
            v.second[i].weight *= (a < 0) ? -1 : 1;
        }
    }
}

void Graph::enableNegativeWeights() {
    negativeWeights = true;
}

void Graph::printGraph() {
    // print vertex, then each edge + weight
    for (auto v : mapList) {
        std::cout << "vertex: " << v.first << std::endl;
        for(auto el : v.second) {
            std::cout << "(" << el.dest << ", " << el.weight << ")" << std::endl;
        }
        std::cout << std::endl;
    }
}

// std::vector<Edge> Graph::Dijkstras(int source) {

// }

// std::vector<Edge> Graph::AStar(int source) {

// }

// std::vector<Edge> Graph::BellmanFord(int source) {

// }

// std::unordered_map<int, std::vector<Edge>> Graph::FloydWarshall() {

// }

// generate a fully connected 350 vertex graph, with random weights for each
// edge. this represents our 100k+ datapoints.
void Graph::generateGraph() {
    srand(time(NULL));

    for (int i = 0; i < 350; i++) {
        for (int j = 0; i < 350; j++) {
            insertEdge(i, j, rand() % 1000 - 1000)
        }
    }
}

// vim: et:sts=4:sw=4:
