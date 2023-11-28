.POSIX:

### Constants
CXX = clang++
CXXFLAGS = -Wpedantic -Wall
CLI_OUT = project3
SRCDIR = src
###

.PHONY: pre_all
pre_all:
	$(MAKE) -C $(SRCDIR) all

all: graph.o parse.o main.o
	$(CXX) $(LDFLAGS) -o project3 graph.o parse.o main.o

graph.o: graph.cpp graph.h
parse.o: parse.cpp parse.h
main.o: main.cpp

.SUFFIXES:
.SUFFIXES: .cpp .o
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<
