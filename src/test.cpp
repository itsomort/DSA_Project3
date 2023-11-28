#include "graph.h"

int main() {
    Graph g;
    g.insertEdge(0, 1, 2);
    g.insertEdge(0, 1, 3);
    g.insertEdge(0, 2, 4);
    g.insertEdge(1, 2, 3);
    g.printGraph();
}

