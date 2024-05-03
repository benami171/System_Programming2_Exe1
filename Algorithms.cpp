// NAME: GAL BEN AMI

#include <climits>
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <queue>
#include <limits>
#include <algorithm>


using namespace ariel;


    bool Algorithms::isConnected(Graph graph)
{
    size_t numVertices = graph.getNumVertices();
    vector<bool> visited(numVertices, false);
    queue<int> q;

    // Check if the graph has vertices
    if (numVertices == 0) {
        return true; // An empty graph is considered connected
    }

    // Start BFS from the first vertex
    q.push(0);
    visited[0] = true;

    vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix(); // Fetch the adjacency matrix once

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        for (size_t i = 0; i < numVertices; ++i)
        {
            // Check if there is an edge from the current vertex to i and if i has not been visited yet
            if (adjacencyMatrix[current][i] != INT_MAX && !visited[i])
            {
                q.push(i);
                visited[i] = true;
            }
        }
    }

    // Check if all vertices have been visited
    for (bool v : visited)
    {
        if (!v)
            return false;
    }

    return true;
}

       string Algorithms::shortestPath(Graph graph, int start, int end)
{
    int weightType = graph.getWeightsType(graph);
    bool directedType = graph.getIsDirected(graph);
    if (weightType == 0) { // Unweighted graph
    // Use BFS
    vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();
    int numVertices = graph.getNumVertices();
    vector<int> prev(numVertices, -1);
    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == end) {
            break;
        }

        for (int i = 0; i < numVertices; ++i) {
            if (adjacencyMatrix[current][i] != 0 && adjacencyMatrix[current][i] != INT_MAX && prev[i] == -1) {
                q.push(i);
                prev[i] = current;
            }
        }
    }

    if (prev[end] == -1) {
    return "No path between start vertex and end vertex";
} else {
    vector<int> path;
    for (int v = end; v != -1; v = prev[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    string result = "The shortest path from " + to_string(start) + " to " + to_string(end) + " is: ";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i != 0) {
            result += "->";
        }
        result += to_string(path[i]);
    }

    return result;
}
} else if (weightType == 1) { // Graph with positive weights
        // Use Dijkstra's algorithm
        // You'll need to implement this part
    } else if (weightType == -1) { // Graph with negative weights
        // Use Bellman-Ford algorithm
        // Your existing implementation goes here
    }
}

    // bool Algorithms::isContainsCycle(Graph &graph)
    // {
    //     size_t numVertices = graph.getNumVertices();
    //     vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix(); // Fetch the adjacency matrix once
    //     vector<bool> visited(numVertices, false);

    //     for (size_t i = 0; i < numVertices; i++)
    //         if (!visited[i])
    //             if (isCyclicUtil(i, visited, -1, adjacencyMatrix))
    //                 return true;

    //     return false;
    // }

    bool Algorithms::isCyclicUtil(int v, vector<bool> &visited, int parent, vector<vector<int>> &adjacencyMatrix)
    {
        visited[(size_t)v] = true;

        for (size_t i = 0; i < adjacencyMatrix[(size_t)v].size(); ++i)
        {
            if (adjacencyMatrix[(size_t)v][i] && !visited[i])
            {
               if (isCyclicUtil(i, visited, v, adjacencyMatrix))
                  return true;
            }
            else if (i != parent)
               return true;
        }
        return false;
    }

    // string Algorithms::isBipartite(Graph &graph)
    // {
    //     size_t numVertices = graph.getNumVertices();
    //     vector<int> color(numVertices, -1);
    //     vector<size_t> setA, setB;

    //     vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix(); // Fetch the adjacency matrix once

    //     for (size_t i = 0; i < numVertices; ++i)
    //     {
    //         if (color[i] == -1)
    //         {
    //             queue<size_t> q;
    //             q.push(i);
    //             color[i] = 1;

    //             while (!q.empty())
    //             {
    //                 size_t current = q.front();
    //                 q.pop();

    //                 for (size_t j = 0; j < numVertices; ++j)
    //                 {
    //                     if (adjacencyMatrix[current][j])
    //                     {
    //                         if (color[j] == -1)
    //                         {
    //                             color[j] = 1 - color[current];
    //                             q.push(j);
    //                         }
    //                         else if (color[j] == color[current])
    //                         {
    //                             return "No, the graph is not bipartite.";
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }

    //     for (size_t i = 0; i < numVertices; ++i)
    //     {
    //         if (color[i] == 0)
    //             setA.push_back(i);
    //         else
    //             setB.push_back(i);
    //     }

    //     string result = "The graph is bipartite: A={";
    //     for (size_t i = 0; i < setA.size(); ++i)
    //     {
    //         result += to_string(setA[i]);
    //         if (i != setA.size() - 1)
    //             result += ", ";
    //     }
    //     result += "}, B={";
    //     for (size_t i = 0; i < setB.size(); ++i)
    //     {
    //         result += to_string(setB[i]);
    //         if (i != setB.size() - 1)
    //             result += ", ";
    //     }
    //     result += "}.";

    //     return result;
    // }
