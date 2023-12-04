#include "parse.h"
#include <sstream>
#include <regex>
#include <iostream>

#define ISNUM std::regex("/^[0-9]+$")
#define FAIL_ARGUMENTS "Wrong number of arguments. Correct usage: "
#define NON_NUMERIC "Non-numeric argument detected. Vertex arguments should be non-negative integers."
#define COMMAND_ERROR "An error occurred."
#define SUCCESS "success"



enum Option {
    Insert,
    Remove,
    Print,
    Generate,
    Count,
    Time,
    None
};

Option transform(std::string command) {
    if(command == "insert") return Insert;
    else if(command == "remove") return Remove;
    else if(command == "print") return Print;
    else if(command == "generate") return Generate;
    else if(command == "count") return Count;
    else if(command == "time") return Time;
    else return None;
} 

void run(std::string command, Graph& graph) {
    std::string temp;
    std::stringstream ss(command);
    std::vector<std::string> tokens;

    if(command == "") return;

    while(getline(ss, temp, ' ')) 
        tokens.push_back(temp);

    switch(transform(tokens[0])) {
        case Insert:
            insert(tokens, graph);
            break;
        case Remove:
            remove(tokens, graph);
            break;
        case Print:
            print(tokens, graph);
            break;
        case Generate:
            generate(tokens, graph);
            break;
        case Count:
            generate(tokens, graph);
            break;
        case Time:
            time(tokens, graph);
            break;
        case None:
            other(tokens, graph);
            break;
        default:
            other(tokens, graph);
    }
}

void insert(std::vector<std::string> tokens, Graph& graph) {
    // tokens[1] = source, tokens[2] = dest, tokens[3] = weight

    if(tokens.size() != 4) {
        std::cout << FAIL_ARGUMENTS << "insert (source) (dest) (weight)." << std::endl;
        return;
    }

    // check if tokens[1] - tokens[3] are all digits
    for(int i = 1; i < 4; i++) {
        if(!std::regex_match(tokens[i], ISNUM)) {
            std::cout << NON_NUMERIC << std::endl;
            return;
        }
    }

    // all are integers, can safely insert
    bool t = graph.insertEdge(std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3]));
    if(t) std::cout << SUCCESS << std::endl;
    else std::cout << COMMAND_ERROR << std::endl;
}

void remove(std::vector<std::string> tokens, Graph& graph) {
    // tokens[1] = source or tokens[1] = source, tokens[2] = dest

    // remove edge (source) (dest)
    // always check size first to prevent out of index errors
    if(tokens.size() == 4 && tokens[1] == "edge") {
        for(int i = 2; i < 3; i++) {
            if(!std::regex_match(tokens[i], ISNUM)) {
                std::cout << NON_NUMERIC << std::endl;
                return;
            }
        }

        graph.removeEdge(std::stoi(tokens[2]), std::stoi(tokens[3]));
        std::cout << SUCCESS << std::endl;
    }

    // remove vertex (source)
    else if(tokens.size() == 3 && tokens[1] == "vertex") {
        if(!std::regex_match(tokens[2], ISNUM)) {
            std::cout << NON_NUMERIC << std::endl;
            return;
        }

        graph.removeVertex(std::stoi(tokens[2]));
        std::cout << SUCCESS << std::endl;
    }

    else 
        std::cout << FAIL_ARGUMENTS << "remove vertex (source) OR remove edge (source) (dest)." << std::endl;
    
}

void print(std::vector<std::string> tokens, Graph& graph) {
    // print neighbors (source) or print graph
    if(tokens.size() == 2 && tokens[1] == "graph") {
        graph.printGraph();
    }

    else if(tokens.size() == 3 && tokens[1] == "neighbors") {
        if(!std::regex_match(tokens[2], ISNUM)) {
            std::cout << NON_NUMERIC << std::endl;
            return;
        }

        std::vector<Edge> n = graph.neighbors(std::stoi(tokens[2]));
        std::cout << "(destination, weight): " << std::endl;
        for(auto i : n) {
            std::cout << "(" << i.dest << ", " << i.weight << ")" << std::endl;
        }
    }

    else 
        std::cout << FAIL_ARGUMENTS << "print graph OR print neighbors (source)." << std::endl;
    
}

void generate(std::vector<std::string> tokens, Graph& graph) {
    // generate OR generate (x) 
    if(tokens.size() == 1) {
        graph.generateGraph(350);
        std::cout << SUCCESS << std::endl;
    }

    else if(tokens.size() == 2) {
        if(!std::regex_match(tokens[1], ISNUM)) {
            std::cout << "Number of vertices should be a positive integer." << std::endl;
            return;
        }
        if(std::stoi(tokens[1]) == 0)
            std::cout << "Number of vertices cannot be zero." << std::endl;
        else {
            graph.generateGraph(std::stoi(tokens[1]));
            std::cout << SUCCESS << std::endl;
        } 
    }

    else
        std::cout << FAIL_ARGUMENTS << "generate OR generate (number)." << std::endl;
}

void count(std::vector<std::string> tokens, Graph& graph) {
    // count vertex OR count edge
    if(tokens.size() != 2 && (tokens[1] != "vertex" || tokens[1] != "edge")) std::cout << FAIL_ARGUMENTS << "count vertex OR count edge." << std::endl;
    
    if(tokens[1] == "vertex") 
        std::cout << "Number of vertices: " << graph.vertexCount() << std::endl;
    
    else if(tokens[1] == "edge") 
        std::cout << "Number of edges: " << graph.edgeCount() << std::endl;
}

void time(std::vector<std::string> tokens, Graph& graph) {
    // will do after pr
}

void other(std::vector<std::string> tokens, Graph& graph) {
    // will do after pr
}

// insert edge x y z (source, dest, weight)
// insert vertex x (source)
// remove edge x y (source, dest)
// remove vertex x (source)
// remove all (clear graph)
// change weight x y z (source, dest, weight)
// count vertex
// count edge
// print neighbors x (source)
// print graph 
// generate (x) (num)
// dijkstras x (y) (source, (dest))
// a-star x (y) (source, (dest))
// bellman-ford x (y) (source, (dest))
// floyd-warshall
// time all x (y) (source, (dest))


// for insert and remove, will give a "Vertex/Edge inserted/removed" message afterwards
// running djikstras, a-star, bellman-ford, or floyd-warshall will display time stats
// for djikstras, a-star, and bellman-ford, required argument x for source node
// generate has optional argument for number of vertices, otherwise default=350
// optional argument y to print distance from x to y


