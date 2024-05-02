#include <iostream>
#include <vector>
#include "Graph.hpp"
#include "Algorithms.hpp"

using namespace ariel;
// int main(){
//     vector<vector<int>> graph = {
//         {0, 1, 0, 0, 0},
//         {1, 0, 3, 0, 0},
//         {0, 3, 0, 4, 0},
//         {0, 0, 4, 0, 5},
//         {0, 0, 0, 5, 0}};
//     Graph g;
//     g.loadGraph(graph);
//     g.printGraph();
//     cout << Algorithms::isConnected(g) << endl; // Should print: "1" (true).
//     cout << Algorithms::shortestPath(g, 0, 3) << endl; // Should print: Graph contains negative weights.
//     cout << Algorithms::isContainsCycle(g) << endl; // Should print: "1" (true).
//     cout << Algorithms::isBipartite(g) << endl; // Should print: "Yes".
// }