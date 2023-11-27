void Graph::generateGraph(int numVertices, int numEdges) { //method that generates a random graph based on the number of vertices and number of edges requested

    srand(time(NULL)); //seeds random so you get different results each compile

    while (Graph::vertexCount() < numVertices) { //a while loop to add the number of requested vertices to the graph
        int generatedVertex = rand() % 999; //generates a number 0-998
        Graph::insertVertex(generatedVertex);  
    }

    while (Graph::edgeCount() < numEdges) { //adds the number of requested edges 
        int randomSource = 0; //the index of the source node 
        int randomDestination = 0; //the index of the destination vertex
        bool disconnected = false; //boolean to track if there are any vertices that are disconnected from the graph
        int randomWeight = rand() % 99; //generates a random weight for the edge, CHANGE FOR DIFFERENT WEIGHT VALUES/CALCULATIONS

        auto checkIterator = mapList.begin(); //iterator that will be used to check if there are any disconnected vertices

        for (checkIterator; checkIterator != mapList.end(); checkIterator++) { //finds the disconnected vertices if any and saves the node location in checkIterator
            if (checkIterator->second.empty()) {
                disconnected = true;
                break; 
            }
        }

        if (disconnected) { //if there are any disconnected vertices
            auto it = mapList.begin();

            randomDestination = rand() % Graph::vertexCount(); //randomly chooses an element to add an edge to

            for (int i = 0; i < randomDestination; i++) { //moves the iterator to where the random vertex is
                it++;
            }

            while (it->first == checkIterator->first) { //while loop that checks if the source and destination are the same node, if so, generate a different destination
                it = mapList.begin();

                randomDestination = rand() % Graph::vertexCount(); //randomly chooses an element to add an edge to

                for (int i = 0; i < randomDestination; i++) {
                    it++;
                }
            }

            Graph::insertEdge(checkIterator->first, it->first, randomWeight); //connects the disconnected node to the graph
        }
        else { //if all vertices are already connected
            auto it = mapList.begin(); //iterator to be used to get source vertex
            auto secondIterator = mapList.begin(); //iterator to be used to get destination vertex

            randomSource = rand() % Graph::vertexCount(); 
            randomDestination = rand() % Graph::vertexCount();

            while (randomDestination == randomSource) { //while loop that checks if the source and destination are the same node, if so, generate a different destination
                randomDestination = rand() % Graph::vertexCount();
            }

            for (int i = 0; i < randomSource; i++) { //uses an iterator to find the source in the map
                it++;
            }

            for (int i = 0; i < randomDestination; i++) { //uses an iterator to find the destination in the map
                secondIterator++;
            }

            Graph::insertEdge(it->first, secondIterator->first, randomWeight); //adds this edge between the two vertices
        }

    }
}
