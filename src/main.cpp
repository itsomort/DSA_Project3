#include "graph.h"

int main() {
    Graph g;
    g.generateGraph();
    std::cout << "vertices: " << g.vertexCount() << std::endl;
    std::cout << "edges: " << g.edgeCount() << std::endl;
}