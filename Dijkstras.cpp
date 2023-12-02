std::vector<Edge> Graph::Dijkstras(int source) { //performs Dijkstras algorithm in n^2 time starting from a source node
    std::vector<Edge> shortestPath; //will store the shortest path 
    int const numVertices = vertexCount();

    int distance[350]; //will hold the shortest distance from source to the last node
    bool shortestSet[350]; //shortestSet[vertex] will be true if it is included in the shortest path to the final node

    for (int i = 0; i < numVertices; i++) { //goes through all the vertices, sets all of their distances to infinite and makes all nodes not included in the shortest path
        distance[i] = INT_MAX;
        shortestSet[i] = false;
    }

    distance[source] = 0; //sets distance of source to zero since we start there

    for (int i = 0; i < numVertices - 1; i++) { 
        int minDistance = INT_MAX; //sets the minDistance of each vertex to infinity
        int minIndex = INT_MAX; //sets the minIndex to be infinity

        for (int j = 0; j < numVertices; j++) { 
            if (shortestSet[j] == false && distance[j] <= minDistance) { //if we find a vertex that is not already part of the path and the distance it has from source is smaller than the current smallest distance, update minIndex and minDistance
                minDistance = distance[j];
                minIndex = j;
            }
        }

        shortestSet[minIndex] = true; //says that the minIndex will automatically be part of the path
        

        for (int j = 0; j < numVertices; j++) { //constructs the shortest path
            //if the node is not already part of the path, if the vertices are neighbors, if the distance of minIndex is not infinity, and if the distance currently stored is greater than the distance from minIndex plus the weight of this connection, add to shortest path
            if (!shortestSet[j] && areNeighbors(minIndex, j) != -1 && distance[minIndex] != INT_MAX && distance[minIndex] + mapList[minIndex].at(areNeighbors(minIndex, j)).weight < distance[j]) {
                shortestPath.push_back(mapList[minIndex].at(areNeighbors(minIndex, j)));
            }
        }

    }

    return shortestPath;


}
