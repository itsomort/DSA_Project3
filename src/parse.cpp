#include "parse.h"
#include <sstream>
#include <regex>
#include <iostream>
#include <chrono>

#define ISNUM std::regex("^[0-9]+$")
#define FAIL_ARGUMENTS "Wrong number of arguments. Correct usage: "
#define NON_NUMERIC "Non-numeric argument detected. Vertex arguments should be non-negative integers."
#define ZERO_ARG "Number of vertices cannot be zero."
#define COMMAND_ERROR "An error occurred."
#define SUCCESS "success"

void insert(std::vector<std::string> tokens, Graph& graph);
void remove(std::vector<std::string> tokens, Graph& graph);
void print(std::vector<std::string> tokens, Graph& graph);
void generate(std::vector<std::string> tokens, Graph& graph);
void count(std::vector<std::string> tokens, Graph& graph);
void time(std::vector<std::string> tokens, Graph& graph);
void other(std::vector<std::string> tokens, Graph& graph);

enum Option {
    Insert,
    Remove,
    Print,
    Generate,
    Count,
    Time,
    Help,
    Exit,
    None
};

Option transform(std::string command) {
    if(command == "insert") return Insert;
    else if(command == "remove") return Remove;
    else if(command == "print") return Print;
    else if(command == "generate") return Generate;
    else if(command == "count") return Count;
    else if(command == "time") return Time;
    else if(command == "help") return Help;
    else if(command == "exit") return Exit;
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
            count(tokens, graph);
            break;
        case Time:
            time(tokens, graph);
            break;
        case Help:
            printCommands();
            break;
        case None:
            other(tokens, graph);
            break;
        case Exit:
            exit(0);
            break;
    }
}

void insert(std::vector<std::string> tokens, Graph& graph) {
    // tokens[1] = source, tokens[2] = dest, tokens[3] = weight

    if(tokens.size() != 3 && tokens.size() != 5) {
        std::cout << FAIL_ARGUMENTS << "insert (source) (dest) (weight)." << std::endl;
        return;
    }

    // check if tokens[1] - tokens[3] are all digits
    
    if(tokens.size() == 5 && tokens[1] == "edge") {
        for(int i = 2; i < 5; i++) {
            if(!std::regex_match(tokens[i], ISNUM)) {
                std::cout << NON_NUMERIC << std::endl;
                return;
            }
        }

        // all are integers, can safely insert
        bool t = graph.insertEdge(std::stoi(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4]));
        if(t) std::cout << SUCCESS << std::endl;
        else std::cout << COMMAND_ERROR << std::endl;   
    }

    else if(tokens.size() == 3 && tokens[1] == "vertex") {
        if(!std::regex_match(tokens[2], ISNUM)) {
            std::cout << NON_NUMERIC << std::endl;
            return;
        }

        bool t = graph.insertVertex(std::stoi(tokens[2]));
        if(t) std::cout << SUCCESS << std::endl;
        else std::cout << COMMAND_ERROR << std::endl;
    }

    else
        std::cout << FAIL_ARGUMENTS << "insert (source) (dest) (weight)." << std::endl;
    
}

void remove(std::vector<std::string> tokens, Graph& graph) {
    // tokens[1] = source or tokens[1] = source, tokens[2] = dest

    // remove edge (source) (dest)
    // always check size first to prevent out of index errors

    if(tokens.size() == 2 && tokens[1] == "all") {
        graph.clear();
        return;
    }

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
            std::cout << NON_NUMERIC << std::endl;
            return;
        }
        if(std::stoi(tokens[1]) == 0)
            std::cout << ZERO_ARG << std::endl;
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
    if((tokens.size() != 3 && tokens.size() != 4)) {
        std::cout << FAIL_ARGUMENTS << " time all (source) OR time all (source) (dest)" << std::endl;
        return;
    }

    if(tokens.size() != 1 && tokens[1] != "all") {
        std::cout << FAIL_ARGUMENTS << " time all (source) OR time all (source) (dest)" << std::endl;
        return;
    }

    int source = 0, dest = -1;


    // tokens[1] == all, tokens[2] == source, tokens[3] == dest
    if(tokens.size() >= 3) {
        if(!std::regex_match(tokens[2], ISNUM)) {
            std::cout << NON_NUMERIC << std::endl;
            return;
        }
        
        if(std::stoi(tokens[2]) == 0) {
            std::cout << ZERO_ARG << std::endl;
            return;
        }

        source = std::stoi(tokens[2]);
    }

    if(tokens.size() == 4) {
        if(!std::regex_match(tokens[3], ISNUM)) {
            std::cout << NON_NUMERIC << std::endl;
            return;
        }

        if(std::stoi(tokens[3]) == 0) {
            std::cout << ZERO_ARG << std::endl;
            return;
        }

        dest = std::stoi(tokens[3]);
    }

    // time all functions

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;


    std::cout << "Timing Djikstras..." << std::endl;
    auto DijkstraStart = high_resolution_clock::now();
    auto dijkstra = graph.Dijkstras(source);
    auto DijkstraEnd = high_resolution_clock::now();
    duration<double, std::milli> dt = DijkstraEnd - DijkstraStart;

    std::cout << "Timing Bellman-Ford..." << std::endl;
    auto BellmanStart = high_resolution_clock::now();
    auto bellman = graph.BellmanFord(source);
    auto BellmanEnd = high_resolution_clock::now();
    duration<double, std::milli> bt = BellmanEnd - BellmanStart;

    std::cout << "Timing Floyd-Warshall..." << std::endl;
    auto FloydStart = high_resolution_clock::now();
    auto floyd = graph.FloydWarshall();
    auto FloydEnd = high_resolution_clock::now();
    duration<double, std::milli> ft = FloydEnd - FloydStart;

    std::cout << "Dijkstra's: " << dt.count() << " ms" << std::endl;
    std::cout << "Bellman-Ford: " << bt.count() << " ms" << std::endl;
    std::cout << "Floyd-Warshall: " << ft.count() << " ms" << std::endl;

    if(dest != -1) {
        std::cout << "Dijkstra's Path Length: " << dijkstra[dest].first << std::endl;
        std::cout << "Bellman-Ford Path Length: " << bellman[dest].first << std::endl;
        std::cout << "Floyd-Warshall Path Length: " << floyd[source][dest] << std::endl;
    }
}

void other(std::vector<std::string> tokens, Graph& graph) {
    // individual algorithms
    bool source = false;
    bool dest = false;

    if(tokens.size() >= 2) {
        // check if tokens[1] (source) is a number
        source = std::regex_match(tokens[1], ISNUM);
    }

    if(tokens.size() == 3) {
        // check if tokens[2] (dest) is a number;
        dest = std::regex_match(tokens[2], ISNUM);
    }

    if(!source && tokens[0] == "dijkstras") {
        std::cout << "Dijkstra's requires a source vertex. Correct usage: dijkstras (source) OR dijkstras (source) (dest)." << std::endl;
        return;
    }

    if(!source && tokens[0] == "floyd-warshall") {
        std::cout << "Floyd-Warshall requires a source vertex. Correct usage: floyd-warshall (source) OR floyd-warshall (source) (dest)." << std::endl;
        return;
    }

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    if(tokens[0] == "dijkstras") {
        auto start = high_resolution_clock::now();
        auto d = graph.Dijkstras(std::stoi(tokens[1]));
        auto end = high_resolution_clock::now();

        duration<double, std::milli> time = end - start;
        std::cout << "Dijkstras timing: " << time.count() << " ms" << std::endl;
        if(dest) {
            std::cout << "Shortest path length: " << d[std::stoi(tokens[2])].first << std::endl;
        }
    }

    else if(tokens[0] == "floyd-warshall") {
        auto start = high_resolution_clock::now();
        auto f = graph.FloydWarshall();
        auto end = high_resolution_clock::now();

        duration<double, std::milli> time = end - start;
        std::cout << "Floyd-Warshall timing: " << time.count() << " ms" << std::endl;
        if(source && dest)
            std::cout << "Shortest path length: " << f[std::stoi(tokens[1])][std::stoi(tokens[2])] << std::endl;
    }

    else if(tokens[0] == "bellman-ford") {
        auto start = high_resolution_clock::now();
        auto b = graph.BellmanFord(std::stoi(tokens[1]));
        auto end = high_resolution_clock::now();

        duration<double, std::milli> time = end - start;
        std::cout << "Bellman-Ford timing: " << time.count() << " ms" << std::endl;
        if(dest) 
            std::cout << "Shortest path length: " << b[std::stoi(tokens[2])].first << std::endl;
        
    }

    else
        std::cout << "Command not known." << std::endl;
    
}

void printCommands() {
    std::cout << "commands: " << std::endl;
    std::cout << "parenthesis indicate required arguments, square brackets are optional" << std::endl;
    std::cout << "insert edge (source) (dest) (weight)" << std::endl;
    std::cout << "insert vertex (source)" << std::endl;
    std::cout << "remove edge (source) (dest)" << std::endl;
    std::cout << "remove vertex (source)" << std::endl;
    std::cout << "remove all" << std::endl;
    std::cout << "count vertex" << std::endl;
    std::cout << "count edge" << std::endl;
    std::cout << "print neighbors (source)" << std::endl;
    std::cout << "print graph" << std::endl;
    std::cout << "generate [num]" << std::endl;
    std::cout << "dijkstras (source) [dest]" << std::endl;
    std::cout << "bellman-ford (source) [dest]" << std::endl;
    std::cout << "floyd-warshall [source] [dest]" << std::endl;
    std::cout << "time all (source) [dest]" << std::endl;
    std::cout << "exit" << std::endl << std::endl;

    std::cout << "note: for floyd-warshall, source and dest need to be both provided if one is provided." << std::endl;    
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
// bellman-ford x (y) (source, (dest))
// floyd-warshall (x) (y) ((source), (dest))
// time all x (y) (source, (dest))
// exit


// for insert and remove, will give a "Vertex/Edge inserted/removed" message afterwards
// running djikstras, a-star, bellman-ford, or floyd-warshall will display time stats
// for djikstras, a-star, and bellman-ford, required argument x for source node
// generate has optional argument for number of vertices, otherwise default=350
// optional argument y to print distance from x to y


