# Graph Algorithms Project

This project implements various graph algorithms in C++. The algorithms are implemented in the `Algorithms` class and are used to perform operations on instances of the `Graph` class.

## Algorithms Implemented

- `isConnected(Graph graph)`: Checks if all vertices in the graph are connected.
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

The project includes a test file that contains a lot of tests to check the project's functionality.

## Note

This project uses the clang++ compiler with the C++11 standard. It also uses the clang-tidy tool for code quality checks and valgrind for memory leak detection.
