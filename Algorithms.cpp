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

// This function finds the shortest path in a graph using different algorithms based on the graph's weight type
string Algorithms::shortestPath(Graph &graph, int start, int end)
{
    // Get the weight type of the graph
    int weightType = graph.getWeightsType();
    // Get the number of vertices in the graph
    int numVertices = graph.getNumVertices();
    // Get the adjacency matrix of the graph
    vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();
    // Initialize the distance array with maximum integer value
    vector<int> dist(numVertices, INT_MAX);
    // Initialize the previous node array with -1
    vector<int> prev(numVertices, -1);
    // Initialize the visited array with false
    vector<bool> visited(numVertices, false);
    // Initialize the path vector
    vector<int> path;
    // Initialize the priority queue for Dijkstra's algorithm
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // If the graph is unweighted
    if (weightType == 0)
    {
        // Initialize the queue for BFS
        queue<int> q;
        // Mark the start vertex as visited
        visited[start] = true;
        // Add the start vertex to the queue
        q.push(start);
        // Set the previous node of the start vertex as itself
        prev[start] = start;

        // While the queue is not empty
        while (!q.empty())
        {
            // Get the front vertex of the queue
            int current = q.front();
            // Remove the front vertex from the queue
            q.pop();

            // If the current vertex is the end vertex, break the loop
            if (current == end)
            {
                break;
            }

            // For each vertex in the graph
            for (int i = 0; i < numVertices; ++i)
            {
                // If the current vertex is connected to the i-th vertex and the i-th vertex is not visited
                if (adjacencyMatrix[current][i] != INT_MAX && !visited[i])
                {
                    // Add the i-th vertex to the queue
                    q.push(i);
                    // Mark the i-th vertex as visited
                    visited[i] = true;
                    // Set the previous node of the i-th vertex as the current vertex
                    prev[i] = current;
                }
            }
        }

        // If there is no path to the end vertex
        if (prev[end] == -1)
        {
            return "No path found";
        }
        else
        {
            // Construct the path from the end vertex to the start vertex
            for (int v = end; v != start; v = prev[v])
            {
                path.push_back(v);
            }
            // Add the start vertex to the path
            path.push_back(start);
            // Reverse the path to get the correct order from start to end
            reverse(path.begin(), path.end());
        }
    }
    // If the graph has positive weights
    else if (weightType == 1)
    {
        // Initialize the distance of the start vertex as 0
        dist[start] = 0;
        // Add the start vertex to the priority queue
        pq.push({0, start});

        // While the priority queue is not empty
        while (!pq.empty())
        {
            // Get the vertex with the smallest distance
            int u = pq.top().second;
            // Remove the vertex from the priority queue
            pq.pop();

            // If the vertex has been visited, skip it
            if (visited[u])
                continue;

            // Mark the vertex as visited
            visited[u] = true;

            // For each vertex in the graph
            for (int v = 0; v < numVertices; ++v)
            {
                // If the u-th vertex is connected to the v-th vertex and the v-th vertex is not visited
                if (adjacencyMatrix[u][v] != INT_MAX && !visited[v])
                {
                    // Calculate the new distance to the v-th vertex
                    int newDist = dist[u] + adjacencyMatrix[u][v];
                    // If the new distance is smaller than the current distance
                    if (newDist < dist[v])
                    {
                        // Update the distance to the v-th vertex
                        dist[v] = newDist;
                        // Set the previous node of the v-th vertex as the u-th vertex
                        prev[v] = u;
                        // Add the v-th vertex to the priority queue
                        pq.push({dist[v], v});
                    }
                }
            }
        }

        // If there is no path to the end vertex
        if (dist[end] == INT_MAX)
        {
            return "No path found";
        }
        else
        {
            // Construct the path from the end vertex to the start vertex
            for (int v = end; v != -1; v = prev[v])
            {
                path.push_back(v);
            }
            // Reverse the path to get the correct order from start to end
            reverse(path.begin(), path.end());
        }
    }
    // If the graph has negative weights
    else if (weightType == -1)
    {
        // Initialize the distance of the start vertex as 0
        dist[start] = 0;

        // For each vertex in the graph
        for (int i = 0; i < numVertices; ++i)
        {
            // For each edge in the graph
            for (int u = 0; u < numVertices; ++u)
            {
                for (int v = 0; v < numVertices; ++v)
                {
                    // If the u-th vertex is connected to the v-th vertex and the new distance to the v-th vertex is smaller
                    if (adjacencyMatrix[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + adjacencyMatrix[u][v] < dist[v])
                    {
                        // Update the distance to the v-th vertex
                        dist[v] = dist[u] + adjacencyMatrix[u][v];
                        // Set the previous node of the v-th vertex as the u-th vertex
                        prev[v] = u;
                    }
                }
            }
        }

        // Initialize the array to mark vertices reachable from a negative cycle
        vector<bool> inNegativeCycle(numVertices, false);
        // For each edge in the graph
        for (int u = 0; u < numVertices; ++u)
        {
            for (int v = 0; v < numVertices; ++v)
            {
                // If the u-th vertex is connected to the v-th vertex and the new distance to the v-th vertex is smaller
                if (adjacencyMatrix[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + adjacencyMatrix[u][v] < dist[v])
                {
                    // Mark the v-th vertex as reachable from a negative cycle
                    inNegativeCycle[v] = true;
                    // Update the containsNegativeCycle field of the graph
                    graph.setContainsNegativeCycle(true);
                }
            }
        }

        // If there is no path to the end vertex
        if (dist[end] == INT_MAX)
        {
            return "No path found from start to end vertex";
        }
        else
        {
            // Construct the path from the end vertex to the start vertex
            for (int v = end; v != -1; v = prev[v])
            {
                // If the v-th vertex is reachable from a negative cycle, return an error message
                if (inNegativeCycle[v])
                {
                    return "Path includes a vertex in a negative cycle";
                }
                path.push_back(v);
            }
            // Reverse the path to get the correct order from start to end
            reverse(path.begin(), path.end());
        }
    }

    // Generate the result string
    string result = "";
    // For each vertex in the path
    for (size_t i = 0; i < path.size(); ++i)
    {
        // If the vertex is not the start vertex, add an arrow before it
        if (i != 0)
        {
            result += "->";
        }
        // Add the vertex to the result string
        result += to_string(path[i]);
    }
    // Return the result string
    return result;
}

vector<int> getAdjVertices(int v, Graph &graph)
{
    vector<int> adjVertices;
    vector<vector<int>> matrix = graph.getAdjacencyMatrix();
    for (int i = 0; i < matrix[v].size(); i++)
    {
        if (matrix[v][i] != INT_MAX)
        {
            adjVertices.push_back(i);
        }
    }
    return adjVertices;
}

bool isCyclicUtil(int v, vector<bool> &visited, vector<bool> &recStack, Graph &graph)
{
    if (!visited[v])
    {
        visited[v] = true;
        recStack[v] = true;

        vector<int> adjVertices = getAdjVertices(v, graph);
        for (int i = 0; i < adjVertices.size(); i++)
        {
            if (!visited[adjVertices[i]] && isCyclicUtil(adjVertices[i], visited, recStack, graph))
            {
                return true;
            }
            else if (recStack[adjVertices[i]])
            {
                return true;
            }
        }
    }
    recStack[v] = false;
    return false;
}

bool isContainsCycle(Graph &graph)
{
    int numVertices = graph.getNumVertices();
    bool isContainsNegativeCycle = graph.getContainsNegativeCycle();
    if (numVertices < 3)
    {
        return false;
    }
    if (isContainsNegativeCycle)
    {
        return true;
    }
    vector<bool> visited(numVertices, false);
    vector<bool> recStack(numVertices, false);

    for (int i = 0; i < numVertices; i++)
    {
        if (isCyclicUtil(i, visited, recStack, graph))
        {
            return true;
        }
    }
    return false;
}

string isBipartite(Graph graph)
{
    int numVertices = graph.getNumVertices();
    vector<int> colorArr(numVertices, -1);
    vector<int> set1, set2;

    for (int i = 0; i < numVertices; i++)
    {
        if (colorArr[i] == -1)
        {
            if (!isBipartiteUtil(graph, i, colorArr, set1, set2))
            {
                return "Graph is not bipartite";
            }
        }
    }

    string set1Str = "A = {";
    for (int i = 0; i < set1.size(); i++)
    {
        set1Str += to_string(set1[i]);
        if (i != set1.size() - 1)
        {
            set1Str += ",";
        }
    }
    set1Str += "}";

    string set2Str = " B = {";
    for (int i = 0; i < set2.size(); i++)
    {
        set2Str += to_string(set2[i]);
        if (i != set2.size() - 1)
        {
            set2Str += ",";
        }
    }
    set2Str += "}";

    return set1Str + set2Str;
}

bool isBipartiteUtil(Graph graph, int src, vector<int> &colorArr, vector<int> &set1, vector<int> &set2)
{
    colorArr[src] = 1;
    set1.push_back(src);
    queue<int> q;
    q.push(src);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        vector<int> adjVertices = getAdjVertices(u, graph);
        for (int i = 0; i < adjVertices.size(); i++)
        {
            int v = adjVertices[i];

            if (colorArr[v] == -1)
            {
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
                if (colorArr[v] == 1)
                {
                    set1.push_back(v);
                }
                else
                {
                    set2.push_back(v);
                }
            }
            else if (colorArr[v] == colorArr[u])
            {
                return false;
            }
        }
    }
    return true;
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
