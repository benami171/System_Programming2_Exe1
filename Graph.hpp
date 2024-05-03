#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

using namespace std;

namespace ariel{
class Graph {
    // we made numVertices as size_t because it will never be negative
    // and also the vector constructor takes size_t as an argument for the size
private:
    vector<vector<int>> adjacencyMatrix;
    bool isDirected; // false for undirected, true for directed
    int isWeighted; // -1 for negative weight, 0 for no weight, 1 for positive weight
    size_t numVertices;

public:
    // inline Concstructor
    Graph(bool directed = false) : isDirected(directed) {}

    void loadGraph(vector<vector<int>> &matrix);
    
    void setIsDirected(bool type);
    
    bool getIsDirected();
        
    void setWeightsType(int type);
    
    int getWeightsType();

    void printGraph();

    size_t getNumVertices();

    vector<vector<int>> getAdjacencyMatrix();

};
}
#endif