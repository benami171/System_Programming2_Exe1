#include <climits>
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <queue>

using namespace ariel;
    #include <limits>

    // int Algorithms::checkIfWeighted(Graph &graph)
    // {
    //     vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix(); // Fetch the adjacency matrix once
    //     int infinity = std::numeric_limits<int>::max(); // Define infinity

    //     for (size_t i = 0; i < adjacencyMatrix.size(); ++i)
    //     {
    //         for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j)
    //         {
    //             if (i != j && adjacencyMatrix[i][j] == 0)
    //             {
    //                 adjacencyMatrix[i][j] = infinity; // Set to infinity
    //             }
    //             else if (adjacencyMatrix[i][j] < 0)
    //             {
    //                 return -1; // Negative weight
    //             }
    //             else if (adjacencyMatrix[i][j] > 0)
    //             {
    //                 return 1; // Positive weight
    //             }
    //         }
    //     }
    //     return 0; // Unweighted
    // }

    // // check if the graph is directed or undirected 
    // // by comparing the adjacency matrix with its transpose
    // int Algorithms::checkIfDirected(Graph &graph)
    // {
    //     vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix(); // Fetch the adjacency matrix once

    //     for (size_t i = 0; i < adjacencyMatrix.size(); ++i)
    //     {
    //         for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j)
    //         {
    //             if (adjacencyMatrix[i][j] != adjacencyMatrix[j][i])
    //             {
                    
    //                 return 1; // Directed
    //             }
    //         }
    //     }
    //     return 0; // Undirected
    // }

    bool Algorithms::isConnected(Graph &graph)
    {
        size_t numVertices = graph.getNumVertices();
        vector<bool> visited(numVertices, false);
        queue<int> q;
        q.push(0);
        visited[0] = true;

        vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix(); // Fetch the adjacency matrix once

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            for (size_t i = 0; i < numVertices; ++i)
            {
                if (adjacencyMatrix[(size_t)current][i] && !visited[i])
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
        size_t numVertices = graph.getNumVertices();
        vector<int> distance(numVertices, INT_MAX);
        vector<int> parent(numVertices, -1);
        distance[(size_t)start] = 0;

        vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix(); // Fetch the adjacency matrix once

        for (size_t i = 1; i <= numVertices - 1; ++i)
        {
            for (size_t u = 0; u < numVertices; ++u)
            {
                for (size_t v = 0; v < numVertices; ++v)
                {
                    if (adjacencyMatrix[u][v] && distance[u] != INT_MAX && distance[u] + adjacencyMatrix[u][v] < distance[v])
                    {
                        parent[v] = u;
                        distance[v] = distance[u] + adjacencyMatrix[u][v];
                    }
                }
            }
        }

        for (size_t u = 0; u < numVertices; ++u)
        {
            for (size_t v = 0; v < numVertices; ++v)
            {
                if (adjacencyMatrix[u][v] && distance[u] != INT_MAX && distance[u] + adjacencyMatrix[u][v] < distance[v])
                {
                    return "Graph contains negative weight cycle";
                }
            }
        }

        if (distance[(size_t)end] == INT_MAX)
            return "-1"; 

        string path = to_string(end);
        size_t current = (size_t)end;
        while (parent[current] != -1)
        {
            path = to_string(parent[current]) + "->" + path;
            current = (size_t)parent[current];
        }

        return path;
    }

    bool Algorithms::isContainsCycle(Graph &graph)
    {
        size_t numVertices = graph.getNumVertices();
        vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix(); // Fetch the adjacency matrix once
        vector<bool> visited(numVertices, false);

        for (size_t i = 0; i < numVertices; i++)
            if (!visited[i])
                if (isCyclicUtil(i, visited, -1, adjacencyMatrix))
                    return true;

        return false;
    }

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

    string Algorithms::isBipartite(Graph &graph)
    {
        size_t numVertices = graph.getNumVertices();
        vector<int> color(numVertices, -1);
        vector<size_t> setA, setB;

        vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix(); // Fetch the adjacency matrix once

        for (size_t i = 0; i < numVertices; ++i)
        {
            if (color[i] == -1)
            {
                queue<size_t> q;
                q.push(i);
                color[i] = 1;

                while (!q.empty())
                {
                    size_t current = q.front();
                    q.pop();

                    for (size_t j = 0; j < numVertices; ++j)
                    {
                        if (adjacencyMatrix[current][j])
                        {
                            if (color[j] == -1)
                            {
                                color[j] = 1 - color[current];
                                q.push(j);
                            }
                            else if (color[j] == color[current])
                            {
                                return "No, the graph is not bipartite.";
                            }
                        }
                    }
                }
            }
        }

        for (size_t i = 0; i < numVertices; ++i)
        {
            if (color[i] == 0)
                setA.push_back(i);
            else
                setB.push_back(i);
        }

        string result = "The graph is bipartite: A={";
        for (size_t i = 0; i < setA.size(); ++i)
        {
            result += to_string(setA[i]);
            if (i != setA.size() - 1)
                result += ", ";
        }
        result += "}, B={";
        for (size_t i = 0; i < setB.size(); ++i)
        {
            result += to_string(setB[i]);
            if (i != setB.size() - 1)
                result += ", ";
        }
        result += "}.";

        return result;
    }
