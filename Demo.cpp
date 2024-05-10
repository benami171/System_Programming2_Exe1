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
#define NO_EDGE 0

using namespace std;

int main()
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {NO_EDGE, 1, NO_EDGE},
        {1, NO_EDGE, NO_EDGE},
        {NO_EDGE, NO_EDGE, NO_EDGE}};
    

    cout << "GRAPH 1:" << endl;

    g1.loadGraph(graph1);
    g1.printGraph(); // should return Graph with 3 vertices and 1 edges
    cout << Algorithms::isConnected(g1) << endl; // should return 0
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // should return NO PATH FROM START TO END
    cout << Algorithms::isNegativeCycle(g1) << endl; // should return the graph has no negative cycle
    cout << Algorithms::isBipartite(g1) << endl;    // should return the graph is bipartite
    cout << Algorithms::isContainsCycle(g1) << endl;    // should return 0
    cout << "" << endl;

    g1.setIsDirected(true);
    vector<vector<int>> graph2 = {
        {NO_EDGE,       1, NO_EDGE},
        {      1, NO_EDGE,       1},
        {NO_EDGE,       1, NO_EDGE}};

    cout << "GRAPH 2:" << endl;
    g1.loadGraph(graph2);
    g1.printGraph(); // should return Graph with 3 vertices and 4 edges
    cout << Algorithms::isConnected(g1) << endl;        // should return 1
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // should return 0->1->2
    cout << Algorithms::isNegativeCycle(g1) << endl;    // should return the graph has no negative cycle
    cout << Algorithms::isBipartite(g1) << endl;        // should return the graph is bipartite
    cout << Algorithms::isContainsCycle(g1) << endl;    // should return 1

    vector<vector<int>> graph3 = {
        {NO_EDGE, 1, 1},
        {1, NO_EDGE, 1},
        {1, 1, NO_EDGE}};

    cout << "GRAPH 3:" << endl;
    g1.loadGraph(graph3);
    g1.printGraph(); // should return Graph with 3 vertices and 6 edges
    cout << Algorithms::isConnected(g1) << endl;        // should return 1
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // should return 0->2
    cout << Algorithms::isNegativeCycle(g1) << endl;    // should return the graph has no negative cycle
    cout << Algorithms::isBipartite(g1) << endl;        // should return the graph is  not bipartite
    cout << Algorithms::isContainsCycle(g1) << endl;    // should return 1

    g1.setIsDirected(false);
    vector<vector<int>> graph4 = {
        {NO_EDGE,      1,     -1,      5},
        {      1,NO_EDGE,      3,      5},
        {     -1,      3,NO_EDGE,     -5},
        {      5,      5,     -5,NO_EDGE}};
    cout << "GRAPH 4:" << endl;
    g1.loadGraph(graph4);
    g1.printGraph();                                    // Undirected graph with 4 vert and 6 edg 
    cout << Algorithms::isConnected(g1) << endl;        // should return 1
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // should return  
    cout << Algorithms::isNegativeCycle(g1) << endl;    
    cout << Algorithms::isBipartite(g1) << endl;
    cout << Algorithms::isContainsCycle(g1) << endl;

//     g1.setIsDirected(true);
//     // a graph that has a negative cycle and is bipartit (e.g. A={0,3,2,6} B={1,4,5,})
//     vector<vector<int>> graph5 = {
//     //  0  1  2  3  4  5  6
//     {  0, 3, 0, 0, 0, 0, 0}, // 0
//     {  0, 0, 4, 0, 0, 0, 0}, // 1
//     {  0, 0, 0, 0, 4, 0, 0}, // 2
//     {  0,-2, 0, 0, 0, 0, 0}, // 3
//     {  0, 0, 0, 0, 0, 0, 5}, // 4
//     { -2, 0, 0,-6, 0, 0, 0}, // 5
//     {  0, 0, 0, 0, 0, 0, 0}  // 6
// };

//     g1.loadGraph(graph5);
//     g1.printGraph();
//     cout << Algorithms::isConnected(g1) << endl; // should return yes
//     cout << Algorithms::shortestPath(g1, 0, 6) << endl; // should return 0->1->2->4->6
//     cout << Algorithms::shortestPath(g1, 3, 5) << endl; // should return no path from 3 to 5
//     cout << Algorithms::isNegativeCycle(g1) << endl;
//     cout << Algorithms::isBipartite(g1) << endl;
//     cout << Algorithms::isContainsCycle(g1) << endl;


    return 0;

}
