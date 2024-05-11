// NAME: GAL BEN AMI


#include <climits>
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <queue>
#include <limits>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
using namespace ariel;

enum Color {WHITE, GRAY, BLACK};


vector<int> getAdjVertices(int v, Graph &graph)
{
    vector<int> adjVertices;
    vector<vector<int>> matrix = graph.getAdjacencyMatrix();
    for (size_t i = 0; i < matrix[(size_t)v].size(); i++)
    {
        if (matrix[(size_t)v][i] != 0) // Consider non-zero values as edges
        {
            adjVertices.push_back(i);
        }
    }
    return adjVertices;
}

string constructPath(const vector<int>& parent, int start, int end)
{
    if (parent[(size_t)end] == -1)
        return "No path found";

    string path = to_string(end);
    while (end != start)
    {
        end = parent[(size_t)end];
        path = to_string(end) + "->" + path;
    }
    return path;
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
            if (adjacencyMatrix[(size_t)current][i] != 0 && !visited[i])
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
string BFS(Graph &graph, int start, int end)
{
    vector<vector<int>> adjMatrix = graph.getAdjacencyMatrix();
    size_t numVertices = graph.getNumVertices();
    vector<int> parentVertx(numVertices, -1);
    vector<bool> visited(numVertices, false);
    string shortestpath = "";
    queue<int> q;
    // Mark the start vertex as visited
    visited[(size_t)start] = true;
    // Set the parentVertxious node of the start vertex as itself
   // parentVertx[start] = start;
    // Add the start vertex to the queue
    q.push(start);

    // While the queue is not empty
    while (!q.empty())
    {
        // Get the front vertex of the queue
        int current = q.front();
        // Remove the front vertex from the queue
        q.pop();

        // If the current vertex is the end vertex, break the loop
        if (current == end)
            break;

        // For each vertex in the graph
        for (size_t i = 0; i < numVertices; ++i)
        {
            // If the current vertex is connected to the i-th vertex and the i-th vertex is not visited
            if (adjMatrix[(size_t)current][i] != 0 && !visited[i])
            {
                // Add the i-th vertex to the queue
                q.push(i);
                // Mark the i-th vertex as visited
                visited[i] = true;
                // Set the parentVertxious node of the i-th vertex as the current vertex
                parentVertx[i] = current;
            }
        }
    }

    return constructPath(parentVertx, start, end);
}

// Dijkstra function
string Dijkstra(Graph &graph, int start, int end)
{
    vector<vector<int>> adjMatrix = graph.getAdjacencyMatrix();
    size_t numVertices = graph.getNumVertices();

    // Initialize visited, distanceance, and parent arrays
    vector<bool> visited(numVertices, false);
    vector<int> d(numVertices, INT_MAX);
    vector<int> parentVertx(numVertices, -1);

    // Initialize the priority queue for Dijkstra's algorithm
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Initialize the distanceance of the start vertex as 0
    d[(size_t)start] = 0;
    // Add the start vertex to the priority queue
    pq.push({0, start});

    // While the priority queue is not empty
    while (!pq.empty())
    {
        // Get the vertex with the smallest distanceance
        int u = pq.top().second;
        // Remove the vertex from the priority queue
        pq.pop();

        // If the vertex has been visited, skip it
        if (visited[(size_t)u])
            continue;

        // Mark the vertex as visited
        visited[(size_t)u] = true;

        // For each vertex in the graph
        for (size_t v = 0; v < numVertices; ++v)
        {
            // If the u-th vertex is connected to the v-th vertex and the v-th vertex is not visited
            if (adjMatrix[(size_t)u][v] != 0 && !visited[v])
            {
                // Calculate the new distance to the v-th vertex
                int newdistance = d[(size_t)u] + adjMatrix[(size_t)u][v];
                // If the new distance is smaller than the current distanceance
                if (newdistance < d[v])
                {
                    // Update the distance to the v-th vertex
                    d[v] = newdistance;
                    // Set the parentVertxious node of the v-th vertex as the u-th vertex
                    parentVertx[v] = u;
                    // Add the v-th vertex to the priority queue
                    pq.push({d[v], v});
                }
            }
        }
    }
    // at this stage, parentVertx contains the shortest path from start to end
    return constructPath(parentVertx, start, end);
}

string bellmanfordv2(Graph& graph, int start, int end){
    size_t numVertices = graph.getNumVertices();
    vector<int> d(numVertices, INT_MAX);
    vector<int> parentVertx(numVertices, -1);
    vector<vector<int>> adjMatrix = graph.getAdjacencyMatrix();

    d[(size_t)start] = 0;
    for (size_t i = 0; i < numVertices - 1; ++i)
    {
        for (size_t u = 0; u < numVertices; ++u)
        {
            for (size_t v = 0; v < numVertices; ++v)
            {
                if (adjMatrix[u][v] != 0 && d[u] != INT_MAX && d[u] + adjMatrix[u][v] < d[v])
                {
                    d[v] = d[u] + adjMatrix[u][v];
                    parentVertx[v] = u;
                }
            }
        }
    }
    vector<bool> inNegativeCycle(numVertices, false);
    for (size_t u = 0; u < numVertices; ++u)
    {
        for (size_t v = 0; v < numVertices; ++v)
        {
            if (adjMatrix[u][v] != 0 && d[u] != INT_MAX && d[u] + adjMatrix[u][v] < d[v])
            {
                // graph.setContainsNegativeCycle(true);
                return "Negative cycle detected";
            }
        }
    }

    // if (inNegativeCycle[(size_t)end])
    // {
    //     return "Negative cycle detected";
    // }

    return constructPath(parentVertx, start, end);
}


pair<pair<stack<int>, vector<int>>, pair<int, int>> Algorithms::DFS(Graph &g, stack<int> &orderOfVertices) {
    size_t numVertices = g.getAdjacencyMatrix().size();
    vector<bool> visited(numVertices, false);
    vector<int> parent(numVertices, -1);

    while (!orderOfVertices.empty()) {
        int v = orderOfVertices.top();
        orderOfVertices.pop();
        if (!visited[(size_t)v]) {
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
    visited[(size_t)v] = true;
    vector<int> adjVertices = getAdjVertices(v, g);

    for (int u : adjVertices) {
        if (!visited[(size_t)u]) {
            parent[(size_t)u] = v;
            return DFSUtil(g, u, visited, parent);
        } else if (parent[(size_t)v] != u) {
            // A back edge was found, indicating a cycle
            return make_pair(u, v);
        }
    }

    // No cycle was found from this vertex
    return make_pair(-1, -1);
}


string Algorithms::shortestPath(Graph &graph, int start, int end)
{
  if (start == end) {
    return "The start and end vertices are the same.";
  }
  if (start < 0 || end < 0 || start >= graph.getNumVertices() || end >= graph.getNumVertices()) {
    return "Invalid start or end vertex.";
  }

  if (graph.getWeightsType() == 0) {
    return BFS(graph, start, end);
  } 

  else if (graph.getWeightsType() == 1) {
    return Dijkstra(graph, start, end);
  } 

   return bellmanfordv2(graph, start, end);
  
}




bool DFSVisit(int u, vector<Color>& color, vector<int>& parent, vector<int>& d, vector<int>& f, int& time, Graph& graph) {
    color[(size_t)u] = GRAY;
    time++;
    d[(size_t)u] = time;

    vector<vector<int>> adjMatrix = graph.getAdjacencyMatrix();
    for(size_t v = 0; v < adjMatrix[(size_t)u].size(); v++) {
        if (adjMatrix[(size_t)u][v] != 0) {
            if (color[v] == WHITE) {
                parent[v] = u;
                if (DFSVisit(v, color, parent, d, f, time, graph)) {
                    return true;  // cycle detected
                }
            } else if (color[v] == GRAY) {
                if (!graph.getIsDirected() && parent[(size_t)u] == v) {
                    continue;
                }
                return true;  // cycle detected
            }
        }
    }

    color[(size_t)u] = BLACK;
    time++;
    f[(size_t)u] = time;

    return false;  // no cycle detected
}

bool DFS(Graph& graph) {
    size_t numVertices = graph.getNumVertices();
    vector<Color> color(numVertices, WHITE);
    vector<int> parent(numVertices, -1);
    vector<int> d(numVertices, 0);  // discovery time
    vector<int> f(numVertices, 0);  // finishing time

    int time = 0;

    for(size_t u = 0; u < numVertices; u++) {
        if (color[u] == WHITE) {
            if (DFSVisit(u, color, parent, d, f, time, graph)) {
                return true;  // cycle detected
            }
        }
    }

    return false;  // no cycle detected
}

bool directedIsContainsCycle(Graph& graph) {
    return DFS(graph);
}

bool undirectedIsContainsCycle(Graph& graph) {
    return DFS(graph);
}

bool Algorithms::isContainsCycle(Graph& graph) {
    if(graph.getNumVertices() < 2) return false;
    if(graph.getIsDirected() == true){
        return directedIsContainsCycle(graph);
    } else {
        return undirectedIsContainsCycle(graph);
    }    
}


// this function creates a copy of the original adjMatrix and converts it to an undirected graph
// it helps us in the isBipartite function.
vector<vector<int>> convertToUndirected(Graph &graph) {
    vector<vector<int>> adjMatrix = graph.getAdjacencyMatrix(); // Original adjacency matrix
    vector<vector<int>> newAdjMatrix = adjMatrix; // Copy of the adjacency matrix
    int numVertices = graph.getNumVertices();

    for (size_t i = 0; i < numVertices; i++) {
        for (size_t j = i+1; j < numVertices; j++) {
            if (newAdjMatrix[i][j] != 0 && newAdjMatrix[j][i] != 0) {
                // If there are edges in both directions, take the average of the two weights
                newAdjMatrix[i][j] = newAdjMatrix[j][i] = (newAdjMatrix[i][j] + newAdjMatrix[j][i]) / 2;
            } else if (newAdjMatrix[i][j] != 0) {
                // If there's only an edge from i to j, use its weight for the edge from j to i
                newAdjMatrix[j][i] = newAdjMatrix[i][j];
            } else if (newAdjMatrix[j][i] != 0) {
                // If there's only an edge from j to i, use its weight for the edge from i to j
                newAdjMatrix[i][j] = newAdjMatrix[j][i];
            }
        }
    }

    return newAdjMatrix;
}

string Algorithms::isBipartite(Graph &graph) 
{
    vector<vector<int>> groups(2);
    vector<vector<int>> adjMatrix;

    // Check if the graph is directed
    if (graph.getIsDirected()) {
        // If the graph is directed, get a convert adjMatrix vertion of the graph to undirected.
        adjMatrix = convertToUndirected(graph);
    } else {
        // If the graph is undirected, use its adjacency matrix as is
        adjMatrix = graph.getAdjacencyMatrix();
    }

    size_t numVertices = graph.getNumVertices();
    vector<int> colorArr(numVertices, -1);

    for (size_t i = 0; i < numVertices; i++) {
        if (colorArr[i] == -1) {
            queue<int> q;
            q.push(i);
            colorArr[i] = groups[0].empty() ? 0 : 1; // Color the first vertex with color 0 if group 0 is empty, else color it with 1
            groups[(size_t)colorArr[i]].push_back(i); // Push it to the corresponding group

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (size_t v = 0; v < numVertices; v++) {
                    if (adjMatrix[(size_t)node][v] != 0 && colorArr[v] == -1) {
                        colorArr[v] = 1 - colorArr[(size_t)node]; // Color the vertex with the opposite color of its neighbor
                        groups[(size_t)colorArr[v]].push_back(v); // Push it to the corresponding group
                        q.push(v);
                    } else if (adjMatrix[(size_t)node][v] != 0 && colorArr[v] == colorArr[(size_t)node]) {
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
        result += to_string(groups[0][(size_t)i]);
        if (i != groups[0].size() - 1) {
            result += ",";
        }
    }
    result += "} B={";
    for (int i = 0; i < groups[1].size(); i++) {
        result += to_string(groups[1][(size_t)i]);
        if (i != groups[1].size() - 1) {
            result += ",";
        }
    }
    result += "}";
    return result;
}

string Algorithms::isNegativeCycle(Graph& graph){
    
    if (graph.getWeightsType() != -1)
    {
        return "Graph does not contain a negative cycle";
    }
    if (graph.getContainsNegativeCycle())
    {
        return "Negative cycle detected";
    }
    string helper = Algorithms::shortestPath(graph, 0, 0);
    if(graph.getContainsNegativeCycle()){
        return "Negative cycle detected";
    } else {
        return "Graph does not contain a negative cycle";
    }
}
