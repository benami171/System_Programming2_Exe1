#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#define NO_EDGE 0

using namespace std;

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    
    g.setIsDirected(false);
    vector<vector<int>> graph = {
            {NO_EDGE, 1, NO_EDGE},
            {1, NO_EDGE, 1},
            {NO_EDGE, 1, NO_EDGE}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
            {NO_EDGE, 1, 1, NO_EDGE, NO_EDGE},
            {1, NO_EDGE, 1, NO_EDGE, NO_EDGE},
            {1, 1, NO_EDGE, 1, NO_EDGE},
            {NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE},
            {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}
TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
            {NO_EDGE, 1, NO_EDGE},
            {1, NO_EDGE, 1},
            {NO_EDGE, 1, NO_EDGE}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
            {NO_EDGE, 1, 1, NO_EDGE, NO_EDGE},
            {1, NO_EDGE, 1, NO_EDGE, NO_EDGE},
            {1, 1, NO_EDGE, 1, NO_EDGE},
            {NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE},
            {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "NO PATH FROM START TO END");
}
TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
            {NO_EDGE, 1, NO_EDGE},
            {1, NO_EDGE, 1},
            {NO_EDGE, 1, NO_EDGE}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);

    vector<vector<int>> graph2 = {
            {NO_EDGE, 1, 1, NO_EDGE, NO_EDGE},
            {1, NO_EDGE, 1, NO_EDGE, NO_EDGE},
            {1, 1, NO_EDGE, 1, NO_EDGE},
            {NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE},
            {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);
}
// TEST_CASE("Test isBipartite")
// {
//     ariel::Graph g;
//     vector<vector<int>> graph = {
//             {NO_EDGE, 1, NO_EDGE},
//             {1, NO_EDGE, 1},
//             {NO_EDGE, 1, NO_EDGE}};
//     g.loadGraph(graph);
//     CHECK(ariel::Algorithms::isBipartite(g) == "Graph is Bipartite and those are the two sets: A={0,2} B={1}");

//     vector<vector<int>> graph2 = {
//             {NO_EDGE, 1, 1, NO_EDGE, NO_EDGE},
//             {1, NO_EDGE, 1, NO_EDGE, NO_EDGE},
//             {1, 1, NO_EDGE, 1, NO_EDGE},
//             {NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE}};
//     g.loadGraph(graph2);
//     CHECK(ariel::Algorithms::isBipartite(g) == "Graph is not Bipartite");

//     vector<vector<int>> graph3 = {
//             {NO_EDGE, 1, 2, NO_EDGE, NO_EDGE},
//             {1, NO_EDGE, 3, NO_EDGE, NO_EDGE},
//             {2, 3, NO_EDGE, 4, NO_EDGE},
//             {NO_EDGE, NO_EDGE, 4, NO_EDGE, 5},
//             {NO_EDGE, NO_EDGE, NO_EDGE, 5, NO_EDGE}};
//     g.loadGraph(graph3);
//     CHECK(ariel::Algorithms::isBipartite(g) == "Graph is not Bipartite");

//     vector<vector<int>> graph4 = {
//             {NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE}
//     };
//     g.loadGraph(graph4);
//     CHECK(ariel::Algorithms::isBipartite(g) == "Graph is Bipartite and those are the two sets: A={0} B={1,2}");


// }
// TEST_CASE("Test invalid graph")
// {
//     ariel::Graph g;
//     vector<vector<int>> graph = {
//             {NO_EDGE, 1, 2, NO_EDGE},
//             {1, NO_EDGE, 3, NO_EDGE},
//             {2, 3, NO_EDGE, 4},
//             {NO_EDGE, NO_EDGE, 4, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, 5}};
//     CHECK_THROWS(g.loadGraph(graph));
// }
// TEST_CASE("Test Negative Cycle")
// {
//     ariel::Graph g;
//     g.setIsDirected(true);
//     vector<vector<int>> graph = {
//             {NO_EDGE, -9, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, -8, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, -10},
//             {-7, NO_EDGE, NO_EDGE, NO_EDGE},

//     };
//     g.loadGraph(graph);
//     CHECK(ariel::Algorithms::isNegativeCycle(g) == "The graph contains a negative cycle");
// }
// TEST_CASE("Test Directed and Undirected Graphs")
// {
//     ariel::Graph g;
//     vector<vector<int>> graph = {
//         {NO_EDGE, NO_EDGE, NO_EDGE,      8},
//         {NO_EDGE, NO_EDGE, NO_EDGE,      8},
//         {NO_EDGE, NO_EDGE, NO_EDGE,      8},
//         {      8,       8,       8, NO_EDGE}
//     };
//     g.loadGraph(graph);
//     CHECK(ariel::Algorithms::isConnected(g) == true);
//     CHECK(ariel::Algorithms::isContainsCycle(g) == false);
    
//     vector<vector<int>> graph2 = {
//             {NO_EDGE, NO_EDGE, NO_EDGE, 7},
//             {NO_EDGE, NO_EDGE, NO_EDGE, 8},
//             {NO_EDGE, NO_EDGE, NO_EDGE, 8},
//             {8, 8, 8, NO_EDGE}
//     };
//     g.setIsDirected(true);
//     g.loadGraph(graph2);
//     CHECK(ariel::Algorithms::isConnected(g) == true);
//     CHECK(ariel::Algorithms::isContainsCycle(g) != false);

//     vector<vector<int>> graph3 = {
//             {NO_EDGE, 2},
//             {NO_EDGE, NO_EDGE}
//     };
//     g.loadGraph(graph3);
//     CHECK(ariel::Algorithms::isConnected(g) == false);
//     CHECK(ariel::Algorithms::isContainsCycle(g) == false);

//     vector<vector<int>> graph4 = {
//             {NO_EDGE, 2},
//             {2, NO_EDGE}
//     };
//     g.loadGraph(graph4);
//     CHECK(ariel::Algorithms::isConnected(g) == true);
//     CHECK(ariel::Algorithms::isContainsCycle(g) != false);

//     vector<vector<int>> graph5 = {
//             {NO_EDGE, 2},
//             {4, NO_EDGE}
//     };
//     g.loadGraph(graph5);
//     CHECK(ariel::Algorithms::isConnected(g) == true);
//     CHECK(ariel::Algorithms::isContainsCycle(g) != false);
//     CHECK(ariel::Algorithms::isBipartite(g) == "Graph is Bipartite and those are the two sets: A={0} B={1}");
// }

// TEST_CASE("TestAll Directed - No Weights")
// {
//     // 1.
//     ariel::Graph g;
//     vector<vector<int>> graph = {
//             {NO_EDGE, 1, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE, 1, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, 1, 1, NO_EDGE, NO_EDGE, 1},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//     };
//     g.loadGraph(graph);
//     CHECK(ariel::Algorithms::isConnected(g) == false);
//     CHECK(ariel::Algorithms::shortestPath(g,2,6) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g,7,2) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g,4,5) == "-1");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "NO_EDGE");
//     CHECK(ariel::Algorithms::isBipartite(g) == "NO_EDGE");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) == "The graph contains a negative cycle");
//     vector<vector<int>> graph2 = {
//             {NO_EDGE, 1, NO_EDGE, NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, 1},
//             {NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE, 1, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE, NO_EDGE, 1},
//             {1, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//     };
//     g.loadGraph(graph2);
//     CHECK(ariel::Algorithms::isConnected(g) == false);
//     CHECK(ariel::Algorithms::shortestPath(g,2,6) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g,7,2) == "7->NO_EDGE->5->3->2");
//     CHECK(ariel::Algorithms::shortestPath(g,4,5) == "-1");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "NO_EDGE->1->3->7->NO_EDGE");
//     CHECK(ariel::Algorithms::isBipartite(g) == "NO_EDGE");
//     CHECK(ariel::Algorithms::isNegativeCycle(g)=="The graph contains a negative cycle");
//     vector<vector<int>> graph3 = {
//             {NO_EDGE, 1, NO_EDGE, NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, 1},
//             {NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, 1, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, 1},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//     };
//     g.loadGraph(graph3);
//     CHECK(ariel::Algorithms::isConnected(g) == false);
//     CHECK(ariel::Algorithms::shortestPath(g,2,6) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g,7,2) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g,4,5) == "-1");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "NO_EDGE");
//     CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={NO_EDGE, 2, 3, 6}, B={1, 4, 5, 7}");
//     CHECK(ariel::Algorithms::isNegativeCycle(g)=="The graph contains a negative cycle");
//     vector<vector<int>> graph4 = {
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//     };
//     g.loadGraph(graph4);
//     CHECK(ariel::Algorithms::isConnected(g) == false);
//     CHECK(ariel::Algorithms::shortestPath(g,2,6) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g,7,2) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g,4,5) == "-1");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "NO_EDGE");
//     CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={4, 5, 6, 7}, B={NO_EDGE, 1, 2, 3}");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) == "The graph contains a negative cycle"SE("TestAll Directed - Non Negative Weights")
// {
//     ariel::Graph g;
//     vector<vector<int>> graph = {
//             {NO_EDGE, NO_EDGE, 5, NO_EDGE, NO_EDGE},
//             {6, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, 8, NO_EDGE, 4, NO_EDGE},
//             {1, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {2, NO_EDGE, 2, NO_EDGE, NO_EDGE},
//     };
//     g.loadGraph(graph);
//     CHECK(ariel::Algorithms::isConnected(g) == false);
//     CHECK(ariel::Algorithms::shortestPath(g,NO_EDGE,3) == "NO_EDGE->2->3");
//     CHECK(ariel::Algorithms::shortestPath(g,2,3) == "2->3");
//     CHECK(ariel::Algorithms::shortestPath(g,1,4) == "-1");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "NO_EDGE->2->3->NO_EDGE");
//     CHECK(ariel::Algorithms::isBipartite(g) == "NO_EDGE");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) "The graph contains a negative cycle"or<vector<int>> graph2 = {
//             {NO_EDGE, 8, 5, 11, 2},
//             {6, NO_EDGE, 11, 7, 4},
//             {3, 8, NO_EDGE, 4, 7},
//             {1, 4, 1, NO_EDGE, 4},
//             {2, 11, 2, 22, NO_EDGE},
//     };
//     g.loadGraph(graph2);
//     CHECK(ariel::Algorithms::isConnected(g) == true);
//     CHECK(ariel::Algorithms::shortestPath(g,NO_EDGE,3) == "NO_EDGE->4->2->3");
//     CHECK(ariel::Algorithms::shortestPath(g,2,3) == "2->3");
//     CHECK(ariel::Algorithms::shortestPath(g,1,4) == "1->4");
//     CHECK(ariel::Algorithms::isContainsCycle(g) != "NO_EDGE");
//     CHECK(ariel::Algorithms::isBipartite(g) == "NO_EDGE");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) "The graph contains a negative cycle"or<vector<int>> graph3 = {
//             {NO_EDGE, NO_EDGE, 5, NO_EDGE, 2},
//             {6, NO_EDGE, NO_EDGE, NO_EDGE, 4},
//             {3, 8, NO_EDGE, NO_EDGE, NO_EDGE},
//             {1, NO_EDGE, 1, NO_EDGE, NO_EDGE},
//             {2, 11, 2, 22, NO_EDGE},
//     };
//     g.loadGraph(graph3);
//     CHECK(ariel::Algorithms::isConnected(g) == true);
//     CHECK(ariel::Algorithms::shortestPath(g,NO_EDGE,3) == "NO_EDGE->4->3");
//     CHECK(ariel::Algorithms::shortestPath(g,2,3) == "2->NO_EDGE->4->3");
//     CHECK(ariel::Algorithms::shortestPath(g,1,4) == "1->4");
//     CHECK(ariel::Algorithms::isContainsCycle(g) != "NO_EDGE");
//     CHECK(ariel::Algorithms::isBipartite(g) == "NO_EDGE");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) == "The graph contains a negative cycle"SE("TestAll Directed - Negative Weights")
// {
//     ariel::Graph g;
//     vector<vector<int>> graph = {

//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, 6, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, 5, NO_EDGE},
//             {1, NO_EDGE, NO_EDGE, NO_EDGE, 8, -8},
//             {NO_EDGE, 6, NO_EDGE, -8, NO_EDGE, NO_EDGE},
//             {4, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//     };
//     g.loadGraph(graph);
//     CHECK(ariel::Algorithms::isConnected(g) == false);
//     CHECK(ariel::Algorithms::shortestPath(g,NO_EDGE,4) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g,1,5) == "1->4->3->5");
//     CHECK(ariel::Algorithms::shortestPath(g,2,NO_EDGE) == "2->4->3->5->NO_EDGE");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "4->3->4");
//     CHECK(ariel::Algorithms::isBipartite(g) == "NO_EDGE");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) "The graph contains a negative cycle"or<vector<int>> graph2 = {
//             {NO_EDGE, NO_EDGE, -2, NO_EDGE},
//             {1, NO_EDGE, 7, -8},
//             {NO_EDGE, -8, NO_EDGE, NO_EDGE},
//             {4, NO_EDGE, NO_EDGE, NO_EDGE},
//     };
//     g.loadGraph(graph2);
//     CHECK(ariel::Algorithms::isConnected(g) == true);
//     CHECK(ariel::Algorithms::shortestPath(g,NO_EDGE,2) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g,1,3) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g,2,NO_EDGE) == "-1");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "NO_EDGE->2->1->3->NO_EDGE");
//     CHECK(ariel::Algorithms::isBipartite(g) == "NO_EDGE");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) == "The graph contains a negative cycle"
//     vector<vector<int>> graph3 = {
//             {NO_EDGE, NO_EDGE, -2, NO_EDGE},
//             {NO_EDGE, NO_EDGE, 7, -8},
//             {NO_EDGE, -8, NO_EDGE, NO_EDGE},
//             {4, NO_EDGE, NO_EDGE, NO_EDGE},
//     };
//     g.loadGraph(graph3);
//     CHECK(ariel::Algorithms::isConnected(g) == true);
//     CHECK(ariel::Algorithms::shortestPath(g,NO_EDGE,2) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g,1,3) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g,2,NO_EDGE) == "-1");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "NO_EDGE->2->1->3->NO_EDGE");
//     CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={NO_EDGE, 1}, B={2, 3}");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) == "The graph contains a negative cycle");

//     vector<vector<int>> graph4 = {
//             {NO_EDGE, NO_EDGE, -2, NO_EDGE},
//             {NO_EDGE, NO_EDGE, 7, 88},
//             {NO_EDGE, -8, NO_EDGE, NO_EDGE},
//             {4, NO_EDGE, NO_EDGE, NO_EDGE},
//     };
//     g.loadGraph(graph4);
//     CHECK(ariel::Algorithms::isConnected(g) == true);
//     CHECK(ariel::Algorithms::shortestPath(g,NO_EDGE,2) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g,1,3) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g,2,NO_EDGE) == "-1");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "NO_EDGE->2->1->3->NO_EDGE");
//     CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={NO_EDGE, 1}, B={2, 3}");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) =="The graph contains a negative cycle"  vector<vector<int>> graph5 = {
//             {NO_EDGE, NO_EDGE, -2, NO_EDGE},
//             {NO_EDGE, NO_EDGE, 7, NO_EDGE},
//             {NO_EDGE, -8, NO_EDGE, NO_EDGE},
//             {4, 88, NO_EDGE, NO_EDGE},
//     };
//     g.loadGraph(graph5);
//     CHECK(ariel::Algorithms::isConnected(g) == false);
//     CHECK(ariel::Algorithms::shortestPath(g,NO_EDGE,2) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g,1,3) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g,2,NO_EDGE) == "-1");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "2->1->2");
//     CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={NO_EDGE, 1}, B={2, 3}");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) =="The graph contains a negative cycle"  vector<vector<int>> graph6 = {
//             {NO_EDGE, NO_EDGE, -2, NO_EDGE},
//             {NO_EDGE, NO_EDGE, 8, NO_EDGE},
//             {NO_EDGE, -8, NO_EDGE, NO_EDGE},
//             {4, 88, NO_EDGE, NO_EDGE},
//     };
//     g.loadGraph(graph6);
//     CHECK(ariel::Algorithms::isConnected(g) == false);
//     CHECK(ariel::Algorithms::shortestPath(g,NO_EDGE,2) == "NO_EDGE->2");
//     CHECK(ariel::Algorithms::shortestPath(g,1,3) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g,2,NO_EDGE) == "-1");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "2->1->2");
//     CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={NO_EDGE, 1}, B={2, 3}");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) "The graph contains a negative cycle"or<vector<int>> graph7 = {
//             {NO_EDGE, NO_EDGE, 1NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {74, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, 38, NO_EDGE, 1, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, 3, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, 5, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, -1NO_EDGE, NO_EDGE, 22},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE}
//     };
//     g.loadGraph(graph7);
//     CHECK(ariel::Algorithms::shortestPath(g,NO_EDGE,1) == "-1");
//     CHECK(ariel::Algorithms::isConnected(g) == false);



// }
// TEST_CASE("TestAll Undirected - No Weights")
// {
//     ariel::Graph g;
//     vector <vector<int>> graph = {
//             {NO_EDGE, 1, NO_EDGE, 1, 1, NO_EDGE},
//             {1, NO_EDGE, NO_EDGE, NO_EDGE, 1, 1},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, 1, 1},
//             {1, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {1, 1, 1, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, 1, 1, NO_EDGE, NO_EDGE, NO_EDGE},
//     };
//     g.loadGraph(graph);
//     CHECK(ariel::Algorithms::isConnected(g) == true);
//     CHECK(ariel::Algorithms::shortestPath(g,NO_EDGE,4) == "NO_EDGE->4");
//     CHECK(ariel::Algorithms::shortestPath(g,1,5) == "1->5");
//     CHECK(ariel::Algorithms::shortestPath(g,2,NO_EDGE) == "2->4->NO_EDGE");
//     CHECK(ariel::Algorithms::isContainsCycle(g) != "NO_EDGE");
//     CHECK(ariel::Algorithms::isBipartite(g) == "NO_EDGE");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) "The graph contains a negative cycle"or <vector<int>> graph2 = {
//             {NO_EDGE, NO_EDGE, NO_EDGE, 1, 1},
//             {NO_EDGE, NO_EDGE, NO_EDGE, 1, 1},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {1, 1, NO_EDGE, NO_EDGE, NO_EDGE},
//             {1, 1, NO_EDGE, NO_EDGE, NO_EDGE},
//     };
//     g.loadGraph(graph2);
//     CHECK(ariel::Algorithms::isConnected(g) == false);
//     CHECK(ariel::Algorithms::shortestPath(g,NO_EDGE,2) == "-1");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "NO_EDGE->3->1->4->NO_EDGE");
//     CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={NO_EDGE, 1, 2}, B={3, 4}");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) "The graph contains a negative cycle"or <vector<int>> graph3 = {
//             {NO_EDGE, NO_EDGE, NO_EDGE, 1, 1},
//             {NO_EDGE, NO_EDGE, NO_EDGE, 1, 1},
//             {NO_EDGE, NO_EDGE, NO_EDGE, 1, NO_EDGE},
//             {1, 1, 1, NO_EDGE, NO_EDGE},
//             {1, 1, NO_EDGE, NO_EDGE, NO_EDGE},
//     };
//     g.loadGraph(graph3);
//     CHECK(ariel::Algorithms::isConnected(g) == true);
//     CHECK(ariel::Algorithms::shortestPath(g,NO_EDGE,2) == "NO_EDGE->3->2");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "NO_EDGE->3->1->4->NO_EDGE");
//     CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={NO_EDGE, 1, 2}, B={3, 4}");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) "The graph contains a negative cycle"or <vector<int>> graph4 = {
//             {NO_EDGE, 1, 1, 1},
//             {1, NO_EDGE, 1, 1},
//             {1, 1, NO_EDGE, 1},
//             {1, 1, 1, NO_EDGE}
//     };
//     g.loadGraph(graph4);
//     CHECK(ariel::Algorithms::isConnected(g) == true);
//     CHECK(ariel::Algorithms::shortestPath(g,NO_EDGE,2) == "NO_EDGE->2");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "1->2->3->1");
//     CHECK(ariel::Algorithms::isBipartite(g) == "NO_EDGE");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) == "The graph contains a negative cycle"ASE("TestAll Undirected - Non Negative Weights")
// {
//     ariel::Graph g;
//     vector <vector<int>> graph = {
//             {NO_EDGE,  12, NO_EDGE, 1, 1NO_EDGE, NO_EDGE},
//             {12, NO_EDGE,  NO_EDGE, NO_EDGE, 1,  1},
//             {NO_EDGE,  NO_EDGE,  NO_EDGE, NO_EDGE, 1,  2},
//             {1,  NO_EDGE,  NO_EDGE, NO_EDGE, NO_EDGE,  NO_EDGE},
//             {1NO_EDGE, 1,  1, NO_EDGE, NO_EDGE,  NO_EDGE},
//             {NO_EDGE,  1,  2, NO_EDGE, NO_EDGE,  NO_EDGE},
//     };
//     g.loadGraph(graph);
//     CHECK(ariel::Algorithms::isConnected(g) == true);
//     CHECK(ariel::Algorithms::shortestPath(g, NO_EDGE, 4) == "NO_EDGE->4");
//     CHECK(ariel::Algorithms::shortestPath(g, 1, 5) == "1->5");
//     CHECK(ariel::Algorithms::shortestPath(g, 2, NO_EDGE) == "2->4->NO_EDGE");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "1->4->2->5->1");
//     CHECK(ariel::Algorithms::isBipartite(g) == "NO_EDGE");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) "The graph contains a negative cycle"or <vector<int>> graph2 = {
//             {NO_EDGE,  12, NO_EDGE, 1, NO_EDGE, NO_EDGE},
//             {12, NO_EDGE,  NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE,  NO_EDGE,  NO_EDGE, NO_EDGE, 1, 2},
//             {1,  NO_EDGE,  NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE,  NO_EDGE,  1, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE,  NO_EDGE,  2, NO_EDGE, NO_EDGE, NO_EDGE}
//     };
//     g.loadGraph(graph2);
//     CHECK(ariel::Algorithms::isConnected(g) == false);
//     CHECK(ariel::Algorithms::shortestPath(g, NO_EDGE, 4) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g, 1, 5) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g, 2, 5) == "2->5");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "NO_EDGE");
//     CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={NO_EDGE, 2}, B={1, 3, 4, 5}");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) "The graph contains a negative cycle"or <vector<int>> graph3 = {
//             {NO_EDGE, NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, 1, 2},
//             {1, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, 1, NO_EDGE, NO_EDGE, NO_EDGE},
//             {NO_EDGE, NO_EDGE, 2, NO_EDGE, NO_EDGE, NO_EDGE}
//     };
//     g.loadGraph(graph3);
//     CHECK(ariel::Algorithms::isConnected(g) == false);
//     CHECK(ariel::Algorithms::shortestPath(g, NO_EDGE, 4) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g, 1, 5) == "-1");
//     CHECK(ariel::Algorithms::shortestPath(g, NO_EDGE, 1) == "-1");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "NO_EDGE");
//     CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={NO_EDGE, 1, 2}, B={3, 4, 5}");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) == "The graph contains a negative cycle"SE("TestAll Undirected - Negative Weights")
// {
//     ariel::Graph g;
//     vector<vector<int>> graph = {
//             {NO_EDGE, NO_EDGE, NO_EDGE,   1, NO_EDGE,  NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE,   NO_EDGE, NO_EDGE,  NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE,   NO_EDGE, -1, -22},
//             {1, NO_EDGE, NO_EDGE,   NO_EDGE, NO_EDGE,  NO_EDGE},
//             {NO_EDGE, NO_EDGE, -1,  NO_EDGE, NO_EDGE,  8},
//             {NO_EDGE, NO_EDGE, -22, NO_EDGE, 8,  NO_EDGE}
//     };
//     g.loadGraph(graph);
//     CHECK(ariel::Algorithms::isConnected(g) == false);
//     CHECK(ariel::Algorithms::shortestPath(g, NO_EDGE, 3) == "NO_EDGE->3");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "2->4->5->2");
//     CHECK(ariel::Algorithms::isBipartite(g) == "NO_EDGE");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) == "The graph contains a negative cycle"
//     vector<vector<int>> graph2 = {
//             {NO_EDGE, NO_EDGE, NO_EDGE,  1, NO_EDGE,  NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE,  NO_EDGE, NO_EDGE,  NO_EDGE},
//             {NO_EDGE, NO_EDGE, NO_EDGE,  NO_EDGE, -1, 22},
//             {1, NO_EDGE, NO_EDGE,  NO_EDGE, NO_EDGE,  NO_EDGE},
//             {NO_EDGE, NO_EDGE, -1, NO_EDGE, NO_EDGE,  8},
//             {NO_EDGE, NO_EDGE, 22, NO_EDGE, 8,  NO_EDGE}
//     };
//     g.loadGraph(graph2);
//     CHECK(ariel::Algorithms::isConnected(g) == false);
//     CHECK(ariel::Algorithms::shortestPath(g, 2, 4) == "2->4");
//     CHECK(ariel::Algorithms::isContainsCycle(g) == "2->4->5->2");
//     CHECK(ariel::Algorithms::isBipartite(g) == "NO_EDGE");
//     CHECK(ariel::Algorithms::isNegativeCycle(g) "The graph contains a negative cycle"or<vector<int>> graph3 = {
//             {NO_EDGE, 7,  NO_EDGE,  NO_EDGE,  NO_EDGE},
//             {7, NO_EDGE,  -1, 1NO_EDGE, NO_EDGE},
//             {NO_EDGE, -1, NO_EDGE,  1NO_EDGE, 7},
//             {NO_EDGE, 1NO_EDGE, 1NO_EDGE, NO_EDGE,  NO_EDGE},
//             {NO_EDGE, NO_EDGE,  7,  NO_EDGE,  NO_EDGE}

//     };
//     g.loadGraph(graph3);
//     CHECK(ariel::Algorithms::isNegativeCycle(g) "The graph contains a negative cycle"or<vector<int>> graph6={{NO_EDGE, 1NO_EDGE, -1, 1, NO_EDGE},
//                                 {1NO_EDGE, NO_EDGE, 1NO_EDGE, NO_EDGE, NO_EDGE},
//                                 {-1, 1NO_EDGE, NO_EDGE, NO_EDGE, 2},
//                                 {1, NO_EDGE, NO_EDGE, NO_EDGE, NO_EDGE},
//                                 {NO_EDGE, NO_EDGE, 2, NO_EDGE, NO_EDGE}};
//     g.loadGraph(graph6);
//     CHECK(ariel::Algorithms::shortestPath(g,1,NO_EDGE)=="1->2->NO_EDGE");
//     CHECK(ariel::Algorithms::shortestPath(g,1,2)=="1->NO_EDGE->2");

// }
// TEST_CASE("TestAll invalid graphs")
// {
//     ariel::Graph g;
//     vector<vector<int>> graph = {
//             {NO_EDGE, 1, 2, NO_EDGE},
//             {1, NO_EDGE, 3, NO_EDGE},
//             {2, 3, NO_EDGE, 4},
//             {NO_EDGE, NO_EDGE, 4, 1}
//     };
//     CHECK_THROWS(g.loadGraph(graph));

//     vector<vector<int>> graph2 = {
//             {NO_EDGE,1,1,1,1}
//     };
//     CHECK_THROWS(g.loadGraph(graph2));

//     vector<vector<int>> graph3 = {
//             {NO_EDGE,1},
//             {1,NO_EDGE}
//     };
//     CHECK_NOTHROW(g.loadGraph(graph3));

//     vector <vector<int>> graph4 = {
//             {NO_EDGE}
//     };
//     CHECK_THROWS(g.loadGraph(graph4));
//}