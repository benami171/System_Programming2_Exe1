/*
 * Demo program for Exercise 2.
 * Author: Benjamin Saldman.
 */
#define NO_EDGE 0
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
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {NO_EDGE, 1, NO_EDGE},
        {1, NO_EDGE, NO_EDGE},
        {NO_EDGE, NO_EDGE, NO_EDGE}};

    g1.loadGraph(graph1);
    g1.printGraph(); // should return Graph with 3 vertices and 1 edges
    cout << Algorithms::isConnected(g1) << endl; // should return 0
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // should return NO PATH FROM START TO END
    cout << Algorithms::isNegativeCycle(g1) << endl; // should return the graph has no negative cycle
    cout << Algorithms::isBipartite(g1) << endl;    // should return the graph is bipartite
    cout << Algorithms::isContainsCycle(g1) << endl;    // should return 0



    g1.setIsDirected(true);
    vector<vector<int>> graph2 = {
        {NO_EDGE, 1, NO_EDGE},
        {1, NO_EDGE, 1},
        {NO_EDGE, 1, NO_EDGE}};

    g1.loadGraph(graph2);
    g1.printGraph(); // should return Graph with 3 vertices and 4 edges
    cout << Algorithms::isConnected(g1) << endl;        // should return 1
    cout << Algorithms::shortestPath(g1, 0, 2) << endl; // should return 0->1->2
    cout << Algorithms::isNegativeCycle(g1) << endl;    // should return the graph has no negative cycle
    cout << Algorithms::isBipartite(g1) << endl;        // should return the graph is bipartite
    cout << Algorithms::isContainsCycle(g1) << endl;    // should return 1


    // vector<vector<int>> graph3 = {
    //     {NO_EDGE,       2,   NO_EDGE,      9},

    //     {      2, NO_EDGE,         3,      4},

    //     {NO_EDGE,       3,   NO_EDGE,      3},

    //     {      9,       4,         3,NO_EDGE}};

    // g1.setIsDirected(false);
    // g1.loadGraph(graph3);
    // g1.printGraph();                                    // should return Graph with 4 vertices and 5 edges
    // cout << Algorithms::isConnected(g1) << endl;        // should return 1
    // cout << Algorithms::shortestPath(g1, 0, 3) << endl; // should return 0->1->3
    // cout << Algorithms::isNegativeCycle(g1) << endl;    // should return the graph has no negative cycle
    // cout << Algorithms::isBipartite(g1) << endl;        // should return the graph is bipartite
    // cout << Algorithms::isContainsCycle(g1) << endl;    // should return the graph has a cycle


    // g1.setIsDirected(true);
    //     // NEGATIVE WEIGHTS
    //     // NO NEGATIVECYCLE
    //  vector<vector<int>> graph4 = {
    //     {NO_EDGE,      3,      6,NO_EDGE},

    //     {NO_EDGE,NO_EDGE,NO_EDGE,      3},

    //     {NO_EDGE,     -8,NO_EDGE,      3},

    //     {NO_EDGE,NO_EDGE,NO_EDGE,NO_EDGE}};

    // g1.loadGraph(graph4);
    // g1.printGraph();                                    // should return Graph with 4 vertices and 5 edges
    // cout << Algorithms::isConnected(g1) << endl;        // should return 1
    // cout << Algorithms::shortestPath(g1, 0, 3) << endl; // should return 0->2->1->3
    // cout << Algorithms::isNegativeCycle(g1) << endl;    // should return the graph has no negative cycle
    // cout << Algorithms::isBipartite(g1) << endl;        // should return the graph is not bipartite


    //     // NEGATIVE WEIGHT
    //     // NEGATIVE CYCLE
    //     vector<vector<int>> graph5 = {
    //     {NO_EDGE,      3,      6,NO_EDGE,      2,NO_EDGE},

    //     {NO_EDGE,NO_EDGE,NO_EDGE,      3,NO_EDGE,NO_EDGE},

    //     {NO_EDGE,     -8,NO_EDGE,      3,NO_EDGE,      5},

    //     {NO_EDGE,NO_EDGE,      2,NO_EDGE,NO_EDGE,NO_EDGE},

    //     {NO_EDGE,NO_EDGE,NO_EDGE,NO_EDGE,NO_EDGE,      3},

    //     {NO_EDGE,NO_EDGE,NO_EDGE,NO_EDGE,NO_EDGE,NO_EDGE}};

    // g1.loadGraph(graph5);
    // g1.printGraph();
    // cout << Algorithms::isConnected(g1) << endl;        // should return 1
    // cout << Algorithms::shortestPath(g1, 4, 0) << endl; // should return NO PATH FROM START TO END
    // cout << Algorithms::shortestPath(g1,4,5) << endl; // should return 4->5
    // cout << Algorithms::shortestPath(g1, 0, 4) << endl; // should return 0->4
    // cout << Algorithms::shortestPath(g1, 0, 5) << endl; // should return 0->4->5
    //     vector<vector<int>> graph6 = {
    //         {NO_EDGE,5,NO_EDGE},
    //         {NO_EDGE,NO_EDGE,-11},
    //         {5,NO_EDGE,NO_EDGE}};
    // g1.loadGraph(graph6);
    // g1.printGraph();
    // cout << Algorithms::isConnected(g1) << endl;        // should return 1
    // cout << Algorithms::shortestPath(g1, 2, 1) << endl; // should return 0->1->2    

    // vector<vector<int>> graph7 = {
    //     {NO_EDGE,      3,      6,NO_EDGE},

    //     {NO_EDGE,NO_EDGE,NO_EDGE,      3},

    //     {NO_EDGE,     -8,NO_EDGE,      3},

    //     {NO_EDGE,NO_EDGE,      2,NO_EDGE}};
    // g1.loadGraph(graph7);
    // g1.printGraph();
    // cout << Algorithms::isNegativeCycle(g1) << endl; // should return the graph has a negative cycle

    return 0;

}
