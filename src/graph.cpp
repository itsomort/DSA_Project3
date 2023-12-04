#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
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

    // not found, so insert
    // insert mapList[dest] just in case

    if (it == n.end()) {
        mapList[source].push_back(Edge(dest, weight));
        return true;
    }
    return false;
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

void Graph::clear() {
    mapList.clear();
}

void Graph::changeWeight(int source, int dest, int weight) {
    for (auto& i : mapList[source]) {
        if (i.dest == dest)
            i.weight = weight;
    }
}

// TODO: fix so that way vertices without edges coming out of them are still counted
// maybe make a set with all seen vertices and return the size of that
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

// detects if there is an edge between source and destination
// returns -1 if no such edge exists, otherwise it returns the index of dest for the source vector
int Graph::areNeighbors(int source, int dest) {
    auto vertexNeighbors = neighbors(source);

    for (int i = 0; i < vertexNeighbors.size(); i++) {
        if (vertexNeighbors.at(i).dest == dest) {
            return i;
        }
    }
    return -1;
}

// performs Dijkstras algorithm in n^2 time starting from a source node
std::unordered_map<int, std::pair<int, int>> Graph::Dijkstras(int source) {
    int const numVertices = vertexCount();

    if (source > numVertices) {
        source = mapList.begin()->first;
        std::cout << "Vertex does not exist in graph, defaulting to vertex " << source << "\n";
    }

    // first: distance from source; second: predecessor vertex
    std::unordered_map<int, std::pair<int, int>> outContainer;
    std::unordered_set<int> toProcess;

    // initialization, INT_MAX represents infinity | N/A
    for (auto it = mapList.begin(); it != mapList.end(); it++) {
        outContainer.insert(std::make_pair(it->first, std::make_pair(INT_MAX, INT_MAX)));
        toProcess.insert(it->first);
    }

    // sets distance of source to zero since we start there
    outContainer[source].first = 0;

    int cur = source;
    int tmpWeight;
    int tmpNext;
    int tmpNextWeight;

    while (!toProcess.empty()) {
        tmpNextWeight = INT_MAX;
        for (auto edge : mapList[cur]) {
            tmpWeight = outContainer[cur].first + edge.weight;
            if (tmpWeight < outContainer[edge.dest].first) {
                outContainer[edge.dest].first = tmpWeight;
                outContainer[edge.dest].second = cur;
            }

            // if new weight is less than least seen unprocessed weight, make it next
            if (edge.weight < tmpNextWeight && toProcess.find(edge.dest) != toProcess.end()) {
                tmpNext = edge.dest;
                tmpNextWeight = edge.weight;
            }
        }
        toProcess.erase(cur);
        cur = tmpNext;
    }

    return outContainer;
}

// std::vector<Edge> Graph::AStar(int source) {

// }

// std::vector<Edge> Graph::BellmanFord(int source) {

// }

// std::unordered_map<int, std::vector<Edge>> Graph::FloydWarshall() {

// }

// generate a fully connected 350 vertex graph, with random weights for each
// edge. this represents our 100k+ datapoints.
void Graph::generateGraph(int num) {
    srand(time(NULL));

    clear(); // so previous nodes don't affect

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            insertEdge(i, j, rand() % 1000 + 1);
        }
    }
}

// vim: et:sts=4:sw=4:
