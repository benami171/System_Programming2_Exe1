#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include <vector>
#include "Graph.hpp"

using namespace std;
namespace ariel{

class Algorithms
{
    public:
        // static int checkIfDirected(Graph &graph);
        // static int checkIfWeighted(Graph &graph);
        static bool isConnected(Graph &graph);
        static string shortestPath(Graph &graph, int start, int end);
        static bool isContainsCycle(Graph &graph);
        static string isBipartite(Graph &graph);
        static bool isCyclicUtil(int v, vector<bool> &visited, int parent, vector<vector<int>> &adjacencyMatrix);
};

}

#endif