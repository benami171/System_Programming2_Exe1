/*
 * Demo program for Exercise 2.
 * Author: Benjamin Saldman.
 */

#include "Graph.hpp"
#include "Algorithms.hpp"
using ariel::Algorithms;

#include <iostream>
#include <stdexcept>
#include <vector>
#include <climits>

using namespace std;

int main()
{
    ariel::Graph g;
    vector<vector<int>> graph11 = {
        {INT_MAX, 1, INT_MAX},
        {1, INT_MAX, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX}};
    g.loadGraph(graph11);
    g.printGraph();
    cout << Algorithms::isConnected(g) << endl; // should return 0

    ariel::Graph g1(true);
    vector<vector<int>> graph12 = {
        {INT_MAX, 1, INT_MAX},
        {1, INT_MAX, 1},
        {INT_MAX, 1, INT_MAX}};

    g1.loadGraph(graph12);
    g1.printGraph();
    cout << Algorithms::isConnected(g1) << endl;        // should return 1
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // should return

    return 0;

    // // 3x3 matrix that represents a connected graph.
    // vector<vector<int>> graph = {
    //     {INT_MAX, 1, INT_MAX},
    //     {1, INT_MAX, 1},
    //     {INT_MAX, 1, INT_MAX}};
    // g.loadGraph(graph); // Load the graph to the object.

    // g.printGraph();                                    // Should print: "Graph with 3 vertices and 4 edges."
    // cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    // cout << Algorithms::shortestPath(g, INT_MAX, 2) << endl; // Should print: INT_MAX->1->2.
    // cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "INT_MAX" (false).
    // cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={INT_MAX, 2}, B={1}."

    // // 5x5 matrix that represents a non-connected graph with a cycle.
    // vector<vector<int>> graph2 = {
    //     {INT_MAX, 1, 1, INT_MAX, INT_MAX},
    //     {1, INT_MAX, 1, INT_MAX, INT_MAX},
    //     {1, 1, INT_MAX, 1, INT_MAX},
    //     {INT_MAX, INT_MAX, 1, INT_MAX, INT_MAX},
    //     {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX}};

    // g.loadGraph(graph2); // Load the graph to the object.

    // g.printGraph();                                    // Should print: "Graph with 5 vertices and 8 edges."
    // cout << Algorithms::isConnected(g) << endl;        // Should print: "INT_MAX" (false).
    // cout << Algorithms::shortestPath(g, INT_MAX, 4) << endl; // Should print: "-1" (there is no path between INT_MAX and 4).
    // cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "The cycle is: INT_MAX->1->2->INT_MAX".
    // cout << Algorithms::isBipartite(g) << endl;        // Should print: "INT_MAX" (false).

    // // 5x5 matrix that reprsents a connected weighted graph.
    // vector<vector<int>> graph3 = {
    //     {INT_MAX, 1, 2, INT_MAX, INT_MAX},
    //     {1, INT_MAX, 3, INT_MAX, INT_MAX},
    //     {2, 3, INT_MAX, 4, INT_MAX},
    //     {INT_MAX, INT_MAX, 4, INT_MAX, 5},
    //     {INT_MAX, INT_MAX, INT_MAX, 5, INT_MAX}};
    // g.loadGraph(graph3); // Load the graph to the object.

    // g.printGraph();                                    // Should print: "Graph with 5 vertices and 1INT_MAX edges."
    // cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    // cout << Algorithms::shortestPath(g, INT_MAX, 4) << endl; // Should print: INT_MAX->2->3->4.
    // cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "INT_MAX" (false).
    // cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={INT_MAX, 2, 4}, B={1, 3}."

    // // 5x4 matrix that reprsents invalid graph.
    // vector<vector<int>> graph4 = {
    //     {INT_MAX, 1, 2, INT_MAX},
    //     {1, INT_MAX, 3, INT_MAX},
    //     {2, 3, INT_MAX, 4},
    //     {INT_MAX, INT_MAX, 4, INT_MAX},
    //     {INT_MAX, INT_MAX, INT_MAX, 5}};
    // try
    // {
    //     g.loadGraph(graph4); // Load the graph to the object.
    // }
    // catch (const std::invalid_argument &e)
    // {
    //     cout << e.what() << endl; // Should print: "Invalid graph: The graph is not a square matrix."
    // }
}
