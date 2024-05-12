#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include "Graph.hpp"

using namespace std;
namespace ariel{

class Algorithms
{
    public:
        static bool isConnected(Graph graph);
        static string shortestPath(Graph& graph, int start, int end);
        static string isContainsCycle(Graph& graph);
        static string isBipartite(Graph& graph);
        static string negativeCycle(Graph& graph);
        static string findCycle(Graph& graph);
        static pair<pair<stack<int>,vector<int>>,pair<int,int>> DFS(Graph &g,stack<int> &orderOfVertices);
        static pair<int, int> DFSUtil(Graph &g, int v, vector<bool> &visited, vector<int> &parent);

};

}

#endif