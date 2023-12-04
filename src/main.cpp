#include <iostream>
#include "graph.h"

int main() {
    Graph g;
    g.generateGraph(350);
    std::cout << "vertices: " << g.vertexCount() << std::endl;
    std::cout << "edges: " << g.edgeCount() << std::endl;
    auto dijkstraMap = g.Dijkstras(0);
    std::cout << "shortest path length from 0 to 24 (dijkstra): " << dijkstraMap[24].first << std::endl;
    auto bellmanMap = g.BellmanFord(0);
    std::cout << "shortest path length from 0 to 24 (bellman-ford): " << bellmanMap[24].first << std::endl;
    auto floydMatrix = g.FloydWarshall();
    std::cout << "shortest path length from 0 to 24 (floyd-warshall): " << floydMatrix[0][24] << std::endl;
}
