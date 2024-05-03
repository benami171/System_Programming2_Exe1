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
        static bool isConnected(Graph graph);
        static string shortestPath(Graph graph, int start, int end);
        static bool isContainsCycle(Graph graph);
        static string isBipartite(Graph graph);
        static string isNegativeCycle(Graph graph);
        static bool isCyclicUtil(int v, vector<bool> &visited, int parent, vector<vector<int>> &adjacencyMatrix);
        static string dijkstra(Graph graph, int start, int end);
        static string bellmanFord(Graph graph, int start, int end);
};

}

#endif