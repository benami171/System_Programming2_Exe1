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

    if (numVertices == 0)
    {
        return true; // An empty graph is considered connected
    }

    q.push(0);
    visited[0] = true;

    vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix(); // Fetch the adjacency matrix once

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        for (size_t i = 0; i < numVertices; ++i)
        {
            if (adjacencyMatrix[current][i] != INT_MAX && !visited[i])
            {
                q.push(i);
                visited[i] = true;
            }
        }
    }

    for (bool v : visited)
    {
        if (!v)
            return false;
    }

    return true;
}

string Algorithms::shortestPath(Graph &graph, int start, int end)
{
    int weightType = graph.getWeightsType();
    bool directedType = graph.getIsDirected();
    int numVertices = graph.getNumVertices();
    vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();
    if (weightType == 0)
    { // Unweighted graph
        vector<int> prev(numVertices, -1);
        vector<bool> visited(numVertices, false);
        queue<int> q;
        cout << "REACHED HERE FOR UNWEIGHTED GRAPH !\n" << endl;
        visited[start] = true;
        q.push(start);
        prev[start] = start; // Mark the start vertex as visited

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            if (current == end)
            {
                break;
            }

            for (int i = 0; i < numVertices; ++i)
            {
                if (adjacencyMatrix[current][i] != INT_MAX && !visited[i])
                {
                    q.push(i);
                    visited[i] = true;
                    prev[i] = current;
                }
            }
        }

        if (prev[end] == -1)
        {
            return "No path found";
        }
        else
        {
            vector<int> path;
            for (int v = end; v != start; v = prev[v])
            {
                path.push_back(v);
            }
            path.push_back(start); // Don't forget to add the start vertex
            reverse(path.begin(), path.end());

            string result = "";
            for (size_t i = 0; i < path.size(); ++i)
            {
                if (i != 0)
                {
                    result += "->";
                }
                result += to_string(path[i]);
            }

            return result;
        }
    } else if (weightType == 1 && directedType == false) {

        // Undirected graph with positive weights 
        // Use Dijkstra's algorithm
        // You'll need to implement this part
    } else if (weightType == 1 && directedType == true) { 
        // Directed graph with positive weights
        // Use Dijkstra's algorithm
        // You'll need to implement this part

    } else if (weightType == -1) {
        // Graph with negative weights
        // Use Bellman-Ford algorithm
        // Your existing implementation goes here
    }
    return "gay";
}
// } else if (weightType == 1) { // Graph with positive weights
//         // Use Dijkstra's algorithm
//         // You'll need to implement this part
//     } else if (weightType == -1) { // Graph with negative weights
//         // Use Bellman-Ford algorithm
//         // Your existing implementation goes here
//     }

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
