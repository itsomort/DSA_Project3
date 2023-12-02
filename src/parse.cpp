#include "parse.h"
#include <sstream>

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

}

void remove(std::vector<std::string> tokens, Graph& graph) {

}

void print(std::vector<std::string> tokens, Graph& graph) {

}

void generate(std::vector<std::string> tokens, Graph& graph) {

}

void count(std::vector<std::string> tokens, Graph& graph) {

}

void time(std::vector<std::string> tokens, Graph& graph) {

}

void other(std::vector<std::string> tokens, Graph& graph) {

}
// insert edge x y z
// insert vertex x
// remove edge x y
// remove vertex x
// remove all
// change weight x y z
// count vertex
// count edge
// print neighbors x
// print graph 
// generate (x)
// dijkstras x (y)
// a-star x (y)
// bellman-ford x (y)
// floyd-warshall
// time all x (y)


// for insert and remove, will give a "Vertex/Edge inserted/removed" message afterwards
// running djikstras, a-star, bellman-ford, or floyd-warshall will display time stats
// for djikstras, a-star, and bellman-ford, required argument x for source node
// generate has optional argument for number of vertices, otherwise default=350
// optional argument y to print distance from x to y


