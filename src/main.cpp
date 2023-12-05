#include <iostream>
#include "parse.h"


int main(int argc, char* argv[]) {
    Graph g;

    if(argc == 2 && strcmp(argv[1], "help") == 0) {
        printCommands();
        exit(0);
    }

    if(argc == 2 && strcmp(argv[1], "time") == 0) {
        run("generate", g);
        run("time all 1", g);
    }

    // repeatedly get input and feed into parser
    std::string input;
    while(getline(std::cin, input)) {
        run(input, g);
    }
}
