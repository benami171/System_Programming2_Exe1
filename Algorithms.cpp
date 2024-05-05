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
// BFS function
vector<int> BFS(Graph &graph, int start, int end, vector<int>& prev, int numVertices, vector<vector<int>>& adjacencyMatrix)
{
    // Initialize the visited array with false
    vector<bool> visited(numVertices, false);
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

    return prev;
}

// Dijkstra function
vector<int>  Dijkstra(Graph &graph, int start, int end, vector<int>& dist, vector<int>& prev, int numVertices, vector<vector<int>>& adjacencyMatrix)
{
    // Initialize the visited array with false
    vector<bool> visited(numVertices, false);
    // Initialize the priority queue for Dijkstra's algorithm
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

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

    return prev;
}

// Bellman Ford function
pair<vector<int>, vector<bool>> BellmanFord(Graph &graph, int start, int end, vector<int>& dist, vector<int>& prev, int numVertices, vector<vector<int>>& adjacencyMatrix)
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

    return make_pair(prev, inNegativeCycle);
}

// This function finds the shortest path in a graph using different algorithms based on the graph's weight type
string Algorithms::shortestPath(Graph &graph, int start, int end)
{
    vector<bool> inNegativeCycle;
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
    // Initialize the path vector
    vector<int> path;

    // If the graph is unweighted
    if (weightType == 0)
    {
        prev = BFS(graph, start, end, prev, numVertices, adjacencyMatrix);
    }
    // If the graph has positive weights
    else if (weightType == 1)
    {
        prev = Dijkstra(graph, start, end, dist, prev, numVertices, adjacencyMatrix);
    }
    // If the graph has negative weights
    else if (weightType == -1)
    {
        pair<vector<int>, vector<bool>> result = BellmanFord(graph, start, end, dist, prev, numVertices, adjacencyMatrix);
        prev = result.first;
        inNegativeCycle = result.second;
    }

    // Generate the shortest path
    for (int v = end; v != start; v = prev[v])
    {
        path.push_back(v);
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

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

// // BFS function
// vector<int> BFS(Graph &graph, int start, int end, vector<int>& prev)
// {
//     // Get the number of vertices in the graph
//     int numVertices = graph.getNumVertices();
//     // Get the adjacency matrix of the graph
//     vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();
//     // Initialize the visited array with false
//     vector<bool> visited(numVertices, false);
//     // Initialize the queue for BFS
//     queue<int> q;
//     // Mark the start vertex as visited
//     visited[start] = true;
//     // Add the start vertex to the queue
//     q.push(start);
//     // Set the previous node of the start vertex as itself
//     prev[start] = start;

//     // While the queue is not empty
//     while (!q.empty())
//     {
//         // Get the front vertex of the queue
//         int current = q.front();
//         // Remove the front vertex from the queue
//         q.pop();

//         // If the current vertex is the end vertex, break the loop
//         if (current == end)
//         {
//             break;
//         }

//         // For each vertex in the graph
//         for (int i = 0; i < numVertices; ++i)
//         {
//             // If the current vertex is connected to the i-th vertex and the i-th vertex is not visited
//             if (adjacencyMatrix[current][i] != INT_MAX && !visited[i])
//             {
//                 // Add the i-th vertex to the queue
//                 q.push(i);
//                 // Mark the i-th vertex as visited
//                 visited[i] = true;
//                 // Set the previous node of the i-th vertex as the current vertex
//                 prev[i] = current;
//             }
//         }
//     }

//     return prev;
// }

// // Dijkstra function
// vector<int>  Dijkstra(Graph &graph, int start, int end, vector<int>& dist, vector<int>& prev)
// {
//     // Get the number of vertices in the graph
//     int numVertices = graph.getNumVertices();
//     // Get the adjacency matrix of the graph
//     vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();
//     // Initialize the visited array with false
//     vector<bool> visited(numVertices, false);
//     // Initialize the priority queue for Dijkstra's algorithm
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

//     // Initialize the distance of the start vertex as 0
//     dist[start] = 0;
//     // Add the start vertex to the priority queue
//     pq.push({0, start});

//     // While the priority queue is not empty
//     while (!pq.empty())
//     {
//         // Get the vertex with the smallest distance
//         int u = pq.top().second;
//         // Remove the vertex from the priority queue
//         pq.pop();

//         // If the vertex has been visited, skip it
//         if (visited[u])
//             continue;

//         // Mark the vertex as visited
//         visited[u] = true;

//         // For each vertex in the graph
//         for (int v = 0; v < numVertices; ++v)
//         {
//             // If the u-th vertex is connected to the v-th vertex and the v-th vertex is not visited
//             if (adjacencyMatrix[u][v] != INT_MAX && !visited[v])
//             {
//                 // Calculate the new distance to the v-th vertex
//                 int newDist = dist[u] + adjacencyMatrix[u][v];
//                 // If the new distance is smaller than the current distance
//                 if (newDist < dist[v])
//                 {
//                     // Update the distance to the v-th vertex
//                     dist[v] = newDist;
//                     // Set the previous node of the v-th vertex as the u-th vertex
//                     prev[v] = u;
//                     // Add the v-th vertex to the priority queue
//                     pq.push({dist[v], v});
//                 }
//             }
//         }
//     }

//     return prev;
// }

// // Bellman Ford function
// pair<vector<int>, vector<bool>> BellmanFord(Graph &graph, int start, int end, vector<int>& dist, vector<int>& prev)
// {
//     // Get the number of vertices in the graph
//     int numVertices = graph.getNumVertices();
//     // Get the adjacency matrix of the graph
//     vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();

//     // Initialize the distance of the start vertex as 0
//     dist[start] = 0;

//     // For each vertex in the graph
//     for (int i = 0; i < numVertices; ++i)
//     {
//         // For each edge in the graph
//         for (int u = 0; u < numVertices; ++u)
//         {
//             for (int v = 0; v < numVertices; ++v)
//             {
//                 // If the u-th vertex is connected to the v-th vertex and the new distance to the v-th vertex is smaller
//                 if (adjacencyMatrix[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + adjacencyMatrix[u][v] < dist[v])
//                 {
//                     // Update the distance to the v-th vertex
//                     dist[v] = dist[u] + adjacencyMatrix[u][v];
//                     // Set the previous node of the v-th vertex as the u-th vertex
//                     prev[v] = u;
//                 }
//             }
//         }
//     }

//     // Initialize the array to mark vertices reachable from a negative cycle
//     vector<bool> inNegativeCycle(numVertices, false);
//     // For each edge in the graph
//     for (int u = 0; u < numVertices; ++u)
//     {
//         for (int v = 0; v < numVertices; ++v)
//         {
//             // If the u-th vertex is connected to the v-th vertex and the new distance to the v-th vertex is smaller
//             if (adjacencyMatrix[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + adjacencyMatrix[u][v] < dist[v])
//             {
//                 // Mark the v-th vertex as reachable from a negative cycle
//                 inNegativeCycle[v] = true;
//                 // Update the containsNegativeCycle field of the graph
//                 graph.setContainsNegativeCycle(true);
//             }
//         }
//     }

//     return make_pair(prev, inNegativeCycle);
// }

// // This function finds the shortest path in a graph using different algorithms based on the graph's weight type
// string Algorithms::shortestPath(Graph &graph, int start, int end)
// {
//     vector<bool> inNegativeCycle;
//     // Get the weight type of the graph
//     int weightType = graph.getWeightsType();
//     // Get the number of vertices in the graph
//     int numVertices = graph.getNumVertices();
//     // Get the adjacency matrix of the graph
//     vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();
//     // Initialize the distance array with maximum integer value
//     vector<int> dist(numVertices, INT_MAX);
//     // Initialize the previous node array with -1
//     vector<int> prev(numVertices, -1);
//     // Initialize the visited array with false
//     vector<bool> visited(numVertices, false);
//     // Initialize the path vector
//     vector<int> path;
//     // Initialize the priority queue for Dijkstra's algorithm
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

//     // If the graph is unweighted
//     if (weightType == 0)
//     {
//         prev = BFS(graph, start, end, prev);
//     }
//     // If the graph has positive weights
//     else if (weightType == 1)
//     {
//         prev = Dijkstra(graph, start, end, dist, prev);
//     }
//     // If the graph has negative weights
//     else if (weightType == -1)
//     {
//         pair<vector<int>, vector<bool>> result = BellmanFord(graph, start, end, dist, prev);
//         prev = result.first;
//         inNegativeCycle = result.second;
//     }

//     // Generate the result string
//     string result = "";
//     // For each vertex in the path
//     for (size_t i = 0; i < path.size(); ++i)
//     {
//         // If the vertex is not the start vertex, add an arrow before it
//         if (i != 0)
//         {
//             result += "->";
//         }
//         // Add the vertex to the result string
//         result += to_string(path[i]);
//     }
//     // Return the result string
//     return result;
// }

// // This function finds the shortest path in a graph using different algorithms based on the graph's weight type
// string Algorithms::shortestPath(Graph &graph, int start, int end)
// {
//     // Get the weight type of the graph
//     int weightType = graph.getWeightsType();
//     // Get the number of vertices in the graph
//     int numVertices = graph.getNumVertices();
//     // Get the adjacency matrix of the graph
//     vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();
//     // Initialize the distance array with maximum integer value
//     vector<int> dist(numVertices, INT_MAX);
//     // Initialize the previous node array with -1
//     vector<int> prev(numVertices, -1);
//     // Initialize the visited array with false
//     vector<bool> visited(numVertices, false);
//     // Initialize the path vector
//     vector<int> path;
//     // Initialize the priority queue for Dijkstra's algorithm
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

//     // If the graph is unweighted
//     if (weightType == 0)
//     {
//         // Initialize the queue for BFS
//         queue<int> q;
//         // Mark the start vertex as visited
//         visited[start] = true;
//         // Add the start vertex to the queue
//         q.push(start);
//         // Set the previous node of the start vertex as itself
//         prev[start] = start;

//         // While the queue is not empty
//         while (!q.empty())
//         {
//             // Get the front vertex of the queue
//             int current = q.front();
//             // Remove the front vertex from the queue
//             q.pop();

//             // If the current vertex is the end vertex, break the loop
//             if (current == end)
//             {
//                 break;
//             }

//             // For each vertex in the graph
//             for (int i = 0; i < numVertices; ++i)
//             {
//                 // If the current vertex is connected to the i-th vertex and the i-th vertex is not visited
//                 if (adjacencyMatrix[current][i] != INT_MAX && !visited[i])
//                 {
//                     // Add the i-th vertex to the queue
//                     q.push(i);
//                     // Mark the i-th vertex as visited
//                     visited[i] = true;
//                     // Set the previous node of the i-th vertex as the current vertex
//                     prev[i] = current;
//                 }
//             }
//         }

//         // If there is no path to the end vertex
//         if (prev[end] == -1)
//         {
//             return "No path found";
//         }
//         else
//         {
//             // Construct the path from the end vertex to the start vertex
//             for (int v = end; v != start; v = prev[v])
//             {
//                 path.push_back(v);
//             }
//             // Add the start vertex to the path
//             path.push_back(start);
//             // Reverse the path to get the correct order from start to end
//             reverse(path.begin(), path.end());
//         }
//     }
//     // If the graph has positive weights
//     else if (weightType == 1)
//     {
//         // Initialize the distance of the start vertex as 0
//         dist[start] = 0;
//         // Add the start vertex to the priority queue
//         pq.push({0, start});

//         // While the priority queue is not empty
//         while (!pq.empty())
//         {
//             // Get the vertex with the smallest distance
//             int u = pq.top().second;
//             // Remove the vertex from the priority queue
//             pq.pop();

//             // If the vertex has been visited, skip it
//             if (visited[u])
//                 continue;

//             // Mark the vertex as visited
//             visited[u] = true;

//             // For each vertex in the graph
//             for (int v = 0; v < numVertices; ++v)
//             {
//                 // If the u-th vertex is connected to the v-th vertex and the v-th vertex is not visited
//                 if (adjacencyMatrix[u][v] != INT_MAX && !visited[v])
//                 {
//                     // Calculate the new distance to the v-th vertex
//                     int newDist = dist[u] + adjacencyMatrix[u][v];
//                     // If the new distance is smaller than the current distance
//                     if (newDist < dist[v])
//                     {
//                         // Update the distance to the v-th vertex
//                         dist[v] = newDist;
//                         // Set the previous node of the v-th vertex as the u-th vertex
//                         prev[v] = u;
//                         // Add the v-th vertex to the priority queue
//                         pq.push({dist[v], v});
//                     }
//                 }
//             }
//         }

//         // If there is no path to the end vertex
//         if (dist[end] == INT_MAX)
//         {
//             return "No path found";
//         }
//         else
//         {
//             // Construct the path from the end vertex to the start vertex
//             for (int v = end; v != -1; v = prev[v])
//             {
//                 path.push_back(v);
//             }
//             // Reverse the path to get the correct order from start to end
//             reverse(path.begin(), path.end());
//         }
//     }
//     // If the graph has negative weights
//     else if (weightType == -1)
//     {
//         // Initialize the distance of the start vertex as 0
//         dist[start] = 0;

//         // For each vertex in the graph
//         for (int i = 0; i < numVertices; ++i)
//         {
//             // For each edge in the graph
//             for (int u = 0; u < numVertices; ++u)
//             {
//                 for (int v = 0; v < numVertices; ++v)
//                 {
//                     // If the u-th vertex is connected to the v-th vertex and the new distance to the v-th vertex is smaller
//                     if (adjacencyMatrix[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + adjacencyMatrix[u][v] < dist[v])
//                     {
//                         // Update the distance to the v-th vertex
//                         dist[v] = dist[u] + adjacencyMatrix[u][v];
//                         // Set the previous node of the v-th vertex as the u-th vertex
//                         prev[v] = u;
//                     }
//                 }
//             }
//         }

//         // Initialize the array to mark vertices reachable from a negative cycle
//         vector<bool> inNegativeCycle(numVertices, false);
//         // For each edge in the graph
//         for (int u = 0; u < numVertices; ++u)
//         {
//             for (int v = 0; v < numVertices; ++v)
//             {
//                 // If the u-th vertex is connected to the v-th vertex and the new distance to the v-th vertex is smaller
//                 if (adjacencyMatrix[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + adjacencyMatrix[u][v] < dist[v])
//                 {
//                     // Mark the v-th vertex as reachable from a negative cycle
//                     inNegativeCycle[v] = true;
//                     // Update the containsNegativeCycle field of the graph
//                     graph.setContainsNegativeCycle(true);
//                 }
//             }
//         }

//         // If there is no path to the end vertex
//         if (dist[end] == INT_MAX)
//         {
//             return "No path found from start to end vertex";
//         }
//         else
//         {
//             // Construct the path from the end vertex to the start vertex
//             for (int v = end; v != -1; v = prev[v])
//             {
//                 // If the v-th vertex is reachable from a negative cycle, return an error message
//                 if (inNegativeCycle[v])
//                 {
//                     return "Path includes a vertex in a negative cycle";
//                 }
//                 path.push_back(v);
//             }
//             // Reverse the path to get the correct order from start to end
//             reverse(path.begin(), path.end());
//         }
//     }

//     // Generate the result string
//     string result = "";
//     // For each vertex in the path
//     for (size_t i = 0; i < path.size(); ++i)
//     {
//         // If the vertex is not the start vertex, add an arrow before it
//         if (i != 0)
//         {
//             result += "->";
//         }
//         // Add the vertex to the result string
//         result += to_string(path[i]);
//     }
//     // Return the result string
//     return result;
// }

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

bool Algorithms::isContainsCycle(Graph &graph)
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

string Algorithms::isBipartite(Graph graph) {
    size_t numVertices = graph.getNumVertices();
    vector<int> colorArr(numVertices, -1);
    vector<vector<int>> groups(2);
    vector<vector<int>> adjMatrix = graph.getAdjacencyMatrix();

    for (size_t i = 0; i < numVertices; i++) {
        if (colorArr[i] == -1) {
            queue<int> q;
            q.push(i);
            colorArr[i] = 1;
            groups[0].push_back(i);

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (size_t v = 0; v < numVertices; v++) {
                    if (adjMatrix[node][v] && colorArr[v] == -1) {
                        colorArr[v] = 1 - colorArr[node];
                        q.push(v);
                        groups[colorArr[v]].push_back(v);
                    } else if (adjMatrix[node][v] && colorArr[v] == colorArr[node]) {
                        return "Graph is not bipartite";
                    }
                }
            }
        }
    }

    string set1Str = "A = {";
    for (size_t i = 0; i < groups[0].size(); i++) {
        set1Str += to_string(groups[0][i]);
        if (i != groups[0].size() - 1) {
            set1Str += ",";
        }
    }
    set1Str += "}";

    string set2Str = " B = {";
    for (size_t i = 0; i < groups[1].size(); i++) {
        set2Str += to_string(groups[1][i]);
        if (i != groups[1].size() - 1) {
            set2Str += ",";
        }
    }
    set2Str += "}";

    return set1Str + set2Str;
}

string Algorithms::isNegativeCycle(Graph graph){
    if (graph.getContainsNegativeCycle())
    {
        return "The graph contains a negative cycle";
    }
    if (graph.getWeightsType() != -1)
    {
        return "The graph does not contain a negative cycle";
    }
    string helper = Algorithms::shortestPath(graph, 0, 0);
    if(graph.getContainsNegativeCycle()){
        return "The graph contains a negative cycle";
    } else {
        return "The graph does not contain a negative cycle";
    }
}


