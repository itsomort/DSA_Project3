CXX = clang++
CXXFLAGS = -Wpedantic -Wall
ODOR = build
OUT = project3
SRCDIR = src

.PHONY: clean

all: build/graph.o build/parse.o build/main.o
	$(CXX) $(LDFLAGS) -o project3 build/graph.o build/parse.o build/main.o

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(ODIR)/*.o project3