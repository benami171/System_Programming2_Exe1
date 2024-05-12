# Graph Algorithms Project

- This project implements various graph algorithms in C++. The algorithms are implemented in the `Algorithms` class and are used to perform operations on instances of the `Graph` class.
- The graph is undirected by default in the constructor, if we want to state that the graph is directed we will type 'Graph g(true);' or use the 'setIsDirected' method in Graph.cpp

## Algorithms Implemented

- `isConnected(Graph graph)`: Checks if theres a vertex that can reach all other vertices.
- `shortestPath(Graph& graph, int start, int end)`: Finds the shortest path between two vertices in the graph using BFS, Dijkstra or Bellman-Ford algorithm.
- `isContainsCycle(Graph& graph)`: Checks if the graph contains a cycle using DFS.
- `findCycle(Graph& graph)`: A helper function to find a cycle in the graph.
- `isBipartite(Graph& graph)`: Checks if the graph is bipartite.
- `negativeCycle(Graph& graph)`: Checks if the graph contains a negative cycle using Bellman-Ford algorithm.

## How to Run

The project includes a Makefile for easy compilation and running of the code. Here are some commands you can use:

- `make run`: Compiles the code and runs the demo.
- `make demo`: Compiles the code for the demo.
- `make test`: Compiles the code for the tests.
- `make tidy`: Runs clang-tidy on the source files to check for code quality issues.
- `make valgrind`: Runs valgrind on the demo and test executables to check for memory leaks.
- `make clean`: Removes all compiled files.

## Testing

The project includes a test file that contains a lot of tests to check the algorithms on directed/undirected graphs
with negative weights/no weights/positive weights.
