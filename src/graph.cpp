#include "graph.h"

bool Graph::insertEdge(int source, int dest, int weight) {
    // prevent source == dest
    if(source == dest) return false;

    //check for negative
    if(!negativeWeights && weight < 0) return false;

    // prevent duplicate edges in the same direction, dest == e.dest already in neighbors, to overwrite weight use changeWeight
    std::vector<Edge> n = mapList[source];
    auto it = std::find_if(n.begin(), n.end(), [&dest](const Edge& e) {return e.dest == dest;});

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
    for(auto& it : mapList) {
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
    mapList[source].erase(
        std::remove_if(
            mapList[source].begin(),
            mapList[source].end(),
            [dest](Edge& e){return e.dest == dest;}
        )
    );
}

void Graph::changeWeight(int source, int dest, int weight) {
    for(auto& i : mapList[source]) {
        if(i.dest == dest) i.weight = weight;
    }
}

int Graph::vertexCount() {
    return mapList.size();
}

int Graph::edgeCount() {
    int count = 0;
    for(auto v : mapList) count += v.second.size();
    return count;
}

std::vector<Edge> Graph::neighbors(int vertex) {
    return mapList[vertex];
}

void Graph::disableNegativeWeights() {
    negativeWeights = false;
    for(auto& v : mapList) {
        for(int i = 0; i < v.second.size(); i++) {
            int a = v.second[i].weight;
            v.second[i].weight *= (a > 0) - (a < 0);
            // hacky abs so i dont have to import math
        }
    }
}

void Graph::enableNegativeWeights() {
    negativeWeights = true;
}

void Graph::printGraph() {
    // print vertex, then each edge + weight
    for(auto v : mapList) {
        std::cout << "vertex: " << v.first << std::endl;
        for(auto el : v.second) {
            std::cout << "(" << el.dest << ", " << el.weight << ") " << std::endl;
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

//method that generates a random graph based on the number of vertices and number of edges requested
void Graph::generateGraph(int numVertices, int numEdges) {

    // seeds random so you get different results each compile
    srand(time(NULL));

    // a while loop to add the number of requested vertices to the graph
    while (Graph::vertexCount() < numVertices) {
        int generatedVertex = rand() % 999;
        Graph::insertVertex(generatedVertex); 
    }

    while (Graph::edgeCount() < numEdges) { // adds the number of requested edges
        int randomSource = 0; // the index of the source node
        int randomDestination = 0; // the index of the destination vertex
        bool disconnected = false; // boolean to track if there are any vertices that are disconnected from the graph
        int randomWeight = rand() % 99; // gens random weight for edge

        // iterator that checks for disconnected vertices
        auto checkIterator = mapList.begin();

        // finds the disconnected vertices if any and saves the node location in checkIterator
        for (checkIterator; checkIterator != mapList.end(); checkIterator++) {
            if (checkIterator->second.empty()) {
                disconnected = true;
                break;
            }
        }


        if (disconnected) {
            auto it = mapList.begin();

            // randomly chooses an element to add an edge to
            randomDestination = rand() % Graph::vertexCount();

            // moves the iterator to where the random vertex is
            for (int i = 0; i < randomDestination; i++) {
                it++;
            }
            // while loop that checks if the source and destination are the same node
            // if so, generate a different destination
            while (it->first == checkIterator->first) {
                it = mapList.begin();

                 // randomly chooses an element to add an edge to
                randomDestination = rand() % Graph::vertexCount();

                for (int i = 0; i < randomDestination; i++) {
                    it++;
                }
            }

            // connects the disconnected node to the graph
            Graph::insertEdge(checkIterator->first, it->first, randomWeight);
        }
        else { // if all vertices are already connected
            auto it = mapList.begin(); // iterator to be used to get source vertex
            auto secondIterator = mapList.begin(); // iterator to be used to get destination vertex

            randomSource = rand() % Graph::vertexCount();
            randomDestination = rand() % Graph::vertexCount();

            // while loop that checks if the source and destination are the same node
            // if so, generate a different destination
            while (randomDestination == randomSource) {
                randomDestination = rand() % Graph::vertexCount();
            }

            // uses an iterator to find the source in the map
            for (int i = 0; i < randomSource; i++) {
                it++;
            }

            // uses an iterator to find the destination in the map
            for (int i = 0; i < randomDestination; i++) {
                secondIterator++;
            }

            // adds this edge between the two vertices
            Graph::insertEdge(it->first, secondIterator->first, randomWeight);
        }

    }
}

// vim: et:sts=4:tw=4:
