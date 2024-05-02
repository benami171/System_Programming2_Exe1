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
    int isDirected; // -1 for undirected, 1 for directed
    int isWeighted; // -1 for negative weight, 0 for no weight, 1 for positive weight
    size_t numVertices;

public:
    //
    void loadGraph(vector<vector<int>> &matrix);
    int getDirectedUndirected(Graph graph);
    int getWeightsType(Graph graph);
    void setDirectedUndirected(int type);
    void setWeightsType(int type);

    void printGraph();

    size_t getNumVertices();

    vector<vector<int>> getAdjacencyMatrix();

};
}
#endif