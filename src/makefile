CXX = clang++
CXXFLAGS = -Wpedantic -Wall -Werror
OUT = graph_test
ODIR = graph_api/build
SRC = graph_api

graph_test: $(ODIR)/test.o $(ODIR)/graph.o
	$(CXX) -o $(OUT) $(CXXFLAGS) $(ODIR)/test.o $(ODIR)/graph.o


$(ODIR)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o graph_test