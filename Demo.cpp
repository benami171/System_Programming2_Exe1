// NAME: GAL BEN AMI

#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <climits>

using ariel::Algorithms;
using namespace std;

int main()
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 0}};

    cout << "GRAPH 1:" << endl;

    g1.loadGraph(graph1);
    g1.printGraph();                                    // should return Undirected graph with 3 vertices and 1 edges.
    cout << Algorithms::isConnected(g1) << endl;        // should return 0
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // should return No path found
    cout << Algorithms::negativeCycle(g1) << endl;      // should return Graph does not contain a negative cycle
    cout << Algorithms::isBipartite(g1) << endl;        // should return Graph is Bipartite and those are the two sets: A={0} B={1,2}
    cout << Algorithms::isContainsCycle(g1) << endl;    // should return 0
    cout << "" << endl;

    g1.setIsDirected(true);
    vector<vector<int>> graph2 = {
        {0, -3, 0},
        {2,  0, 2},
        {0, -2, 0}};

    cout << "GRAPH 2:" << endl;
    g1.loadGraph(graph2);
    g1.printGraph();                                    // should return Directed graph with 3 vertices and 4 edges.
    cout << Algorithms::isConnected(g1) << endl;        // should return 1
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // should return Negative cycle detected
    cout << Algorithms::negativeCycle(g1) << endl;      // should return Negative cycle detected
    cout << Algorithms::isContainsCycle(g1) << endl;    // should return Graph contains a cycle: 0->1->0
    cout << "" << endl;

    vector<vector<int>> graph3 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};

    cout << "GRAPH 3:" << endl;
    g1.loadGraph(graph3);
    g1.printGraph();                                    // should return Directed graph with 3 vertices and 6 edges.
    cout << Algorithms::isConnected(g1) << endl;        // should return 1
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // should return 0->2
    cout << Algorithms::isBipartite(g1) << endl;        // should return Graph is not Bipartite
    cout << Algorithms::isContainsCycle(g1) << endl;    // should return Graph contains a cycle: 0->1->0
    cout << "" << endl;

    g1.setIsDirected(false);
    vector<vector<int>> graph4 = {
        { 0, 1,-1, 5},
        { 1, 0, 3, 5},
        {-1, 3, 0,-5},
        { 5, 5,-5, 0}};
    cout << "GRAPH 4:" << endl;
    g1.loadGraph(graph4);
    g1.printGraph();                                    // should return Undirected graph with 4 vertices and 6 edges.
    cout << Algorithms::isConnected(g1) << endl;        // should return 1
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // should return Negative cycle detected
    cout << Algorithms::negativeCycle(g1) << endl;      // should return Negative cycle detected
    cout << Algorithms::isBipartite(g1) << endl;        // should return Graph is not Bipartite
    cout << Algorithms::isContainsCycle(g1) << endl;    // should return Graph contains a cycle: 0->1->2->0
    cout << "" << endl;

    g1.setIsDirected(true);
    vector<vector<int>> graph5 = {
        { 0, 3, 0, 0, 0, 0, 0},
        { 0, 0, 4, 0, 0, 0, 0},
        { 0, 0, 0, 0, 4, 0, 0},
        { 0,-2, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 5},
        {-2, 0, 0,-6, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0} 
    };

    cout << "GRAPH 5:" << endl;
    g1.loadGraph(graph5);
    g1.printGraph();                                    // should return Directed graph with 7 vertices and 7 edges.
    cout << Algorithms::isConnected(g1) << endl;        // should return 0
    cout << Algorithms::shortestPath(g1, 0, 6) << endl; // should return 0 -> 1 -> 2 -> 4 -> 6
    cout << Algorithms::shortestPath(g1, 3, 5) << endl; // should return No path found
    cout << Algorithms::negativeCycle(g1) << endl;      // should return The graph contains a negative cycle
    cout << Algorithms::isBipartite(g1) << endl;        // should return Graph is Bipartite and those are the two sets: A={0,2,3,6} B={1,5,4}
    cout << "" << endl;

    vector<vector<int>> graph6 = {
        {0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {0, 3, 0, 0, 0},
        {0, 3, 0, 0, 5},
        {0, 0, 0, 0, 0}};

    cout << "GRAPH 6:" << endl;
    g1.loadGraph(graph6);
    g1.printGraph();                                   // should return Directed graph with 5 vertices and 4 edges.
    cout << Algorithms::isConnected(g1) << endl;       // should return 1
    cout << "" << endl;

    return 0;
}
