// NAME: GAL BEN AMI

#define NO_EDGE 0
#include <climits>
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <queue>
#include <limits>
#include <algorithm>

using namespace ariel;

vector<int> getAdjVertices(int v, Graph &graph)
{
    vector<int> adjVertices;
    vector<vector<int>> matrix = graph.getAdjacencyMatrix();
    for (int i = 0; i < matrix[v].size(); i++)
    {
        if (matrix[v][i] != 0) // Consider non-zero values as edges
        {
            adjVertices.push_back(i);
        }
    }
    return adjVertices;
}

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
            if (adjacencyMatrix[current][i] != NO_EDGE && !visited[i])
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
            if (adjacencyMatrix[current][i] != NO_EDGE && !visited[i])
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
            if (adjacencyMatrix[u][v] != NO_EDGE && !visited[v])
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
                if (adjacencyMatrix[u][v] != NO_EDGE && dist[u] != NO_EDGE && dist[u] + adjacencyMatrix[u][v] < dist[v])
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
            if (adjacencyMatrix[u][v] != NO_EDGE && dist[u] != NO_EDGE && dist[u] + adjacencyMatrix[u][v] < dist[v])
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


pair<pair<stack<int>, vector<int>>, pair<int, int>> Algorithms::DFS(Graph &g, stack<int> &orderOfVertices) {
    int numVertices = g.getAdjacencyMatrix().size();
    vector<bool> visited(numVertices, false);
    vector<int> parent(numVertices, -1);

    while (!orderOfVertices.empty()) {
        int v = orderOfVertices.top();
        orderOfVertices.pop();
        if (!visited[v]) {
            pair<int, int> cycle = DFSUtil(g, v, visited, parent);
            if (cycle.first != -1) {
                // A cycle was found
                return make_pair(make_pair(orderOfVertices, parent), cycle);
            }
        }
    }

    // No cycle was found
    return make_pair(make_pair(orderOfVertices, parent), make_pair(-1, -1));
}

pair<int, int> Algorithms::DFSUtil(Graph &g, int v, vector<bool> &visited, vector<int> &parent) {
    visited[v] = true;
    vector<int> adjVertices = getAdjVertices(v, g);

    for (int u : adjVertices) {
        if (!visited[u]) {
            parent[u] = v;
            return DFSUtil(g, u, visited, parent);
        } else if (parent[v] != u) {
            // A back edge was found, indicating a cycle
            return make_pair(u, v);
        }
    }

    // No cycle was found from this vertex
    return make_pair(-1, -1);
}


string Algorithms::shortestPath(Graph &graph, int start, int end)
{
    // Get the weight type of the graph
    int weightType = graph.getWeightsType();
    // Get the number of vertices in the graph
    int numVertices = graph.getNumVertices();
    // Initialize the inNegativeCycle vector with false
    vector<bool> inNegativeCycle(numVertices, false);
    // Get the adjacency matrix of the graph
    vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();
    // Initialize the distance array with maximum integer value
    vector<int> dist(numVertices, NO_EDGE);
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

    // If the end vertex is reachable from a negative cycle, return "NO PATH FROM START TO END"
    if (inNegativeCycle[end])
    {
        return "NO PATH FROM START TO END";
    }
    // Generate the shortest path
    for (int v = end; v != start; v = prev[v])
    {
        // Check if prev[v] is a valid index
        if (prev[v] < 0 || prev[v] >= prev.size())
        {
            return "NO PATH FROM START TO END";
        }
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


enum Color {WHITE, GRAY, BLACK};


bool Algorithms::isContainsCycle(Graph& graph) {
    vector<vector<int>> adjMatrix = graph.getAdjacencyMatrix();
    size_t numVertices = adjMatrix.size();
    vector<Color> color(numVertices, WHITE);

    for (size_t startVertex = 0; startVertex < numVertices; ++startVertex) {
        if (color[startVertex] != WHITE) // Vertex already visited
            continue;

        stack<int> dfsStack;
        dfsStack.push(startVertex);

        while (!dfsStack.empty()) {
            int v = dfsStack.top();
            dfsStack.pop();

            if (color[v] == GRAY) // Found a cycle
                return true;

            color[v] = GRAY;

            for (size_t i = 0; i < numVertices; ++i) {
                if (adjMatrix[v][i] != NO_EDGE) { // Edge exists
                    if (color[i] == WHITE) { // Not visited
                        dfsStack.push(i);
                    }
                }
            }

            color[v] = BLACK; // Finished visiting neighbors
        }
    }

    return false;
}


// enum Color {WHITE, GRAY, BLACK};

// bool isCyclicUtil(int v, vector<Color> &color, vector<vector<int>> &adjMatrix) {
//     color[v] = GRAY;

//     for (size_t i = 0; i < adjMatrix[v].size(); i++) {
//         if (adjMatrix[v][i] != NO_EDGE) {
//             if (color[i] == WHITE) {
//                 if (isCyclicUtil(i, color, adjMatrix)) {
//                     return true;
//                 }
//             } else if (color[i] == GRAY) {
//                 return true;
//             }
//         }
//     }

//     color[v] = BLACK;
//     return false;
// }

// bool Algorithms::isContainsCycle(Graph &graph) {
//     size_t numVertices = graph.getNumVertices();
//     cout << numVertices << endl;
//     vector<Color> color(numVertices, WHITE);
//     vector<vector<int>> adjMatrix = graph.getAdjacencyMatrix();
    


//     for (size_t i = 0; i < numVertices; i++) {
//         if (color[i] == WHITE) {
//             if (isCyclicUtil(i, color, adjMatrix)) {
//                 return true;
//             }
//         }
//     }

//     return false;
// }

vector<vector<int>> convertToUndirected(Graph &graph) {
    vector<vector<int>> adjMatrix = graph.getAdjacencyMatrix(); // Original adjacency matrix
    vector<vector<int>> newAdjMatrix = adjMatrix; // Copy of the adjacency matrix
    int numVertices = graph.getNumVertices();

    for (int i = 0; i < numVertices; i++) {
        for (int j = i+1; j < numVertices; j++) {
            if (newAdjMatrix[i][j] != NO_EDGE && newAdjMatrix[j][i] != NO_EDGE) {
                // If there are edges in both directions, take the average of the two weights
                newAdjMatrix[i][j] = newAdjMatrix[j][i] = (newAdjMatrix[i][j] + newAdjMatrix[j][i]) / 2;
            } else if (newAdjMatrix[i][j] != NO_EDGE) {
                // If there's only an edge from i to j, use its weight for the edge from j to i
                newAdjMatrix[j][i] = newAdjMatrix[i][j];
            } else if (newAdjMatrix[j][i] != NO_EDGE) {
                // If there's only an edge from j to i, use its weight for the edge from i to j
                newAdjMatrix[i][j] = newAdjMatrix[j][i];
            }
        }
    }

    return newAdjMatrix;
}

string Algorithms::isBipartite(Graph &graph) {
    size_t numVertices = graph.getNumVertices();
    vector<int> colorArr(numVertices, -1);
    vector<vector<int>> groups(2);
    vector<vector<int>> adjMatrix;

    // Check if the graph is directed
    if (graph.getIsDirected()) {
        // If the graph is directed, convert it to undirected
        adjMatrix = convertToUndirected(graph);
    } else {
        // If the graph is undirected, use its adjacency matrix as is
        adjMatrix = graph.getAdjacencyMatrix();
    }

    for (size_t i = 0; i < numVertices; i++) {
        if (colorArr[i] == -1) {
            queue<int> q;
            q.push(i);
            colorArr[i] = groups[0].empty() ? 0 : 1; // Color the first vertex with color 0 if group 0 is empty, else color it with 1
            groups[colorArr[i]].push_back(i); // Push it to the corresponding group

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (size_t v = 0; v < numVertices; v++) {
                    if (adjMatrix[node][v] != NO_EDGE && colorArr[v] == -1) {
                        colorArr[v] = 1 - colorArr[node]; // Color the vertex with the opposite color of its neighbor
                        groups[colorArr[v]].push_back(v); // Push it to the corresponding group
                        q.push(v);
                    } else if (adjMatrix[node][v] != NO_EDGE && colorArr[v] == colorArr[node]) {
                        return "Graph is not Bipartite";
                    }
                }
            }
        }
    }

    // If we reach here, then all vertices can be colored with alternate color
    // So, we return the two sets of vertices
    string result = "Graph is Bipartite and those are the two sets: ";
    result += "A={";
    for (int i = 0; i < groups[0].size(); i++) {
        result += to_string(groups[0][i]);
        if (i != groups[0].size() - 1) {
            result += ",";
        }
    }
    result += "} B={";
    for (int i = 0; i < groups[1].size(); i++) {
        result += to_string(groups[1][i]);
        if (i != groups[1].size() - 1) {
            result += ",";
        }
    }
    result += "}";
    return result;
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
