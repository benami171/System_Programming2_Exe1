#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
using namespace std;

TEST_CASE("Test isConnected Undirected graph")
{
        ariel::Graph g;
        g.setIsDirected(false);
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == true);

        vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::isConnected(g) == false);
}
TEST_CASE("Test shortestPath")
{
        ariel::Graph g;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};

        g.loadGraph(graph);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

        vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "No path found");
}
TEST_CASE("Test isContainsCycle")
{
        ariel::Graph g;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isContainsCycle(g) == "0");

        vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};

        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::isContainsCycle(g) == "Graph contains a cycle: 0->1->2->0");
}
TEST_CASE("Test isBipartite")
{
        ariel::Graph g;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isBipartite(g) == "Graph is Bipartite and those are the two sets: A={0,2} B={1}");

        vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::isBipartite(g) == "Graph is not Bipartite");

        vector<vector<int>> graph3 = {
            {0, 1, 2, 0, 0},
            {1, 0, 3, 0, 0},
            {2, 3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}};
        g.loadGraph(graph3);
        CHECK(ariel::Algorithms::isBipartite(g) == "Graph is not Bipartite");

        vector<vector<int>> graph4 = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}};
        g.loadGraph(graph4);
        CHECK(ariel::Algorithms::isBipartite(g) == "Graph is Bipartite and those are the two sets: A={0} B={1,2}");
}
TEST_CASE("Test invalid graph")
{
        ariel::Graph g;
        vector<vector<int>> graph = {
            {0, 1, 2, 0},
            {1, 0, 3, 0},
            {2, 3, 0, 4},
            {0, 0, 4, 0},
            {0, 0, 0, 5}};
        CHECK_THROWS(g.loadGraph(graph));
}
TEST_CASE("Test Negative Cycle")
{
        ariel::Graph g;
        g.setIsDirected(true);
        vector<vector<int>> graph = {
            {0, -9, 0, 0},
            {0, 0, -8, 0},
            {0, 0, 0, -10},
            {-7, 0, 0, 0},

        };
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle detected");
}
TEST_CASE("Test Directed and Undirected Graphs")
{
        ariel::Graph g;
        vector<vector<int>> graph = {
            {0, 0, 0, 8},
            {0, 0, 0, 8},
            {0, 0, 0, 8},
            {8, 8, 8, 0}};
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == true);
        CHECK(ariel::Algorithms::isContainsCycle(g) == "0");

        vector<vector<int>> graph2 = {
            {0, 0, 0, 7},
            {0, 0, 0, 8},
            {0, 0, 0, 8},
            {8, 8, 8, 0}};
        g.setIsDirected(true);
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::isConnected(g) == true);
        CHECK(ariel::Algorithms::isContainsCycle(g) != "0");

        vector<vector<int>> graph3 = {
            {0, 2},
            {0, 0}};
        g.loadGraph(graph3);
        CHECK(ariel::Algorithms::isConnected(g) == false);
        CHECK(ariel::Algorithms::isContainsCycle(g) == "0");

        vector<vector<int>> graph4 = {
            {0, 2},
            {2, 0}};
        g.loadGraph(graph4);
        CHECK(ariel::Algorithms::isConnected(g) == true);
        CHECK(ariel::Algorithms::isContainsCycle(g) != "0");

        vector<vector<int>> graph5 = {
            {0, 2},
            {4, 0}};
        g.loadGraph(graph5);
        CHECK(ariel::Algorithms::isConnected(g) == true);
        CHECK(ariel::Algorithms::isContainsCycle(g) != "0");
        CHECK(ariel::Algorithms::isBipartite(g) == "Graph is Bipartite and those are the two sets: A={0} B={1}");
}

TEST_CASE("Test Directed - No Weights")
{
        // 1.
        ariel::Graph g(true);
        vector<vector<int>> graph = {
            {0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 1, 0},
            {0, 0, 0, 1, 1, 0, 0, 1},
            {0, 0, 0, 0, 0, 0, 0, 0},
        };
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == false);
        CHECK(ariel::Algorithms::shortestPath(g, 2, 6) == "No path found");
        CHECK(ariel::Algorithms::shortestPath(g, 7, 2) == "No path found");
        CHECK(ariel::Algorithms::shortestPath(g, 4, 5) == "No path found");
        CHECK(ariel::Algorithms::isContainsCycle(g) == "0");
        CHECK(ariel::Algorithms::isBipartite(g) == "Graph is not Bipartite");
        CHECK(ariel::Algorithms::negativeCycle(g) == "Graph does not contain a negative cycle");
        vector<vector<int>> graph2 = {
            {0, 1, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 1},
            {0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 1, 0},
            {0, 0, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0},
        };
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::isConnected(g) == false);
        CHECK(ariel::Algorithms::shortestPath(g, 2, 6) == "No path found");
        CHECK(ariel::Algorithms::shortestPath(g, 4, 5) == "No path found");
        CHECK(ariel::Algorithms::shortestPath(g, 7, 2) == "7->0->1->3->2");
        CHECK(ariel::Algorithms::isContainsCycle(g) == "Graph contains a cycle: 0->1->3->7->0");
        CHECK(ariel::Algorithms::isBipartite(g) == "Graph is not Bipartite");
        CHECK(ariel::Algorithms::negativeCycle(g) == "Graph does not contain a negative cycle");
        vector<vector<int>> graph3 = {
            {0, 1, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1},
            {0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 1},
            {0, 0, 0, 0, 0, 0, 0, 0},
        };
        g.loadGraph(graph3);
        CHECK(ariel::Algorithms::isConnected(g) == false);
        CHECK(ariel::Algorithms::shortestPath(g, 2, 6) == "No path found");
        CHECK(ariel::Algorithms::shortestPath(g, 7, 2) == "No path found");
        CHECK(ariel::Algorithms::shortestPath(g, 4, 5) == "No path found");
        CHECK(ariel::Algorithms::isContainsCycle(g) == "0");
        CHECK(ariel::Algorithms::isBipartite(g) == "Graph is Bipartite and those are the two sets: A={0,6,3,4} B={1,5,7,2}");
        CHECK(ariel::Algorithms::negativeCycle(g) == "Graph does not contain a negative cycle");

        vector<vector<int>> graph4 = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
        };
        g.loadGraph(graph4);
        CHECK(ariel::Algorithms::isConnected(g) == false);
        CHECK(ariel::Algorithms::shortestPath(g, 2, 6) == "No path found");
        CHECK(ariel::Algorithms::shortestPath(g, 7, 2) == "No path found");
        CHECK(ariel::Algorithms::shortestPath(g, 4, 5) == "No path found");
        CHECK(ariel::Algorithms::isContainsCycle(g) == "0");
        CHECK(ariel::Algorithms::isBipartite(g) == "Graph is Bipartite and those are the two sets: A={0} B={1,2,3,4,5,6,7}");
        CHECK(ariel::Algorithms::negativeCycle(g) == "Graph does not contain a negative cycle");
}
TEST_CASE("Test Directed - Non Negative Weights")
{
        ariel::Graph g(true);
        vector<vector<int>> graph = {
            {0, 0, 5, 0, 0},
            {6, 0, 0, 0, 0},
            {0, 8, 0, 4, 0},
            {1, 0, 0, 0, 0},
            {2, 0, 2, 0, 0},
        };
        g.loadGraph(graph);
        CHECK(ariel::Algorithms::isConnected(g) == false);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->2->3");
        CHECK(ariel::Algorithms::shortestPath(g, 2, 3) == "2->3");
        CHECK(ariel::Algorithms::shortestPath(g, 1, 4) == "No path found");
        CHECK(ariel::Algorithms::isContainsCycle(g) == "Graph contains a cycle: 0->2->1->0");
        CHECK(ariel::Algorithms::isBipartite(g) == "Graph is not Bipartite");
        CHECK(ariel::Algorithms::negativeCycle(g) == "Graph does not contain a negative cycle");

        vector<vector<int>> graph2 = {
            {0, 8, 5, 11, 2},
            {6, 0, 11, 7, 4},
            {3, 8, 0, 4, 7},
            {1, 4, 1, 0, 4},
            {2, 11, 2, 22, 0},
        };
        g.loadGraph(graph2);
        CHECK(ariel::Algorithms::isConnected(g) == true);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->4->2->3");
        CHECK(ariel::Algorithms::shortestPath(g, 2, 3) == "2->3");
        CHECK(ariel::Algorithms::shortestPath(g, 1, 4) == "1->4");
        CHECK(ariel::Algorithms::isContainsCycle(g) != "0");
        CHECK(ariel::Algorithms::isBipartite(g) == "Graph is not Bipartite");
        CHECK(ariel::Algorithms::negativeCycle(g) == "Graph does not contain a negative cycle");
        vector<vector<int>> graph3 = {
            {0, 0, 5, 0, 2},
            {6, 0, 0, 0, 4},
            {3, 8, 0, 0, 0},
            {1, 0, 1, 0, 0},
            {2, 11, 2, 22, 0},
        };

        g.loadGraph(graph3);
        CHECK(ariel::Algorithms::isConnected(g) == true);
        CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->4->3");
        CHECK(ariel::Algorithms::shortestPath(g, 2, 3) == "2->0->4->3");
        CHECK(ariel::Algorithms::shortestPath(g, 1, 4) == "1->4");
        CHECK(ariel::Algorithms::isContainsCycle(g) != "0");
        CHECK(ariel::Algorithms::isBipartite(g) == "Graph is not Bipartite");
        CHECK(ariel::Algorithms::negativeCycle(g) == "Graph does not contain a negative cycle");
}
    TEST_CASE("Test Directed - Negative Weights")
{
    ariel::Graph g(true);
    vector<vector<int>> graph = {

            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 6, 0},
            {0, 0, 0, 0, 5, 0},
            {1, 0, 0, 0, 8,-9},
            {0, 6, 0, -8,0, 0},
            {4, 0, 0, 0, 0, 0},
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::shortestPath(g,0,4) == "No path found");
    CHECK(ariel::Algorithms::shortestPath(g,1,5) == "1->4->3->5");
    CHECK(ariel::Algorithms::shortestPath(g,2,0) == "2->4->3->5->0");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "Graph contains a cycle: 1->4->1");
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is not Bipartite");
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle detected");
       vector<vector<int>> graph2 = {
            {0, 0,-2, 0},
            {1, 0, 7,-8},
            {0,-8, 0, 0},
            {4, 0, 0, 0},
    };
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g,0,2) == "Negative cycle detected");
    CHECK(ariel::Algorithms::shortestPath(g,1,3) == "Negative cycle detected");
    CHECK(ariel::Algorithms::shortestPath(g,2,0) == "Negative cycle detected");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "Graph contains a cycle: 0->2->1->0");
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is not Bipartite");
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle detected");
    vector<vector<int>> graph3 = {
            {0, 0, -2, 0},
            {0, 0,  7,-8},
            {0, -8, 0, 0},
            {4,  0, 0, 0},
    };
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g,0,2) == "Negative cycle detected");
    CHECK(ariel::Algorithms::shortestPath(g,1,3) == "Negative cycle detected");
    CHECK(ariel::Algorithms::shortestPath(g,2,0) == "Negative cycle detected");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "Graph contains a cycle: 2->1->2");
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is Bipartite and those are the two sets: A={0,1} B={2,3}");
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle detected");

    vector<vector<int>> graph4 = {
            {0, 0, -2, 0},
            {0, 0, 7, 88},
            {0, -8, 0, 0},
            {4, 0, 0,  0},
    };
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g,0,2) == "Negative cycle detected");
    CHECK(ariel::Algorithms::shortestPath(g,1,3) == "Negative cycle detected");
    CHECK(ariel::Algorithms::shortestPath(g,2,0) == "Negative cycle detected");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "Graph contains a cycle: 2->1->2");
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is Bipartite and those are the two sets: A={0,1} B={2,3}");
    CHECK(ariel::Algorithms::negativeCycle(g) =="Negative cycle detected");
       vector<vector<int>> graph5 = {
            {0, 0, -2, 0},
            {0, 0, 7, 0},
            {0, -8, 0, 0},
            {4, 88, 0, 0},
    };
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::shortestPath(g,0,2) == "Negative cycle detected");
    CHECK(ariel::Algorithms::shortestPath(g,1,3) == "Negative cycle detected");
    CHECK(ariel::Algorithms::shortestPath(g,2,0) == "Negative cycle detected");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "Graph contains a cycle: 2->1->2");
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is Bipartite and those are the two sets: A={0,1} B={2,3}");
    CHECK(ariel::Algorithms::negativeCycle(g) =="Negative cycle detected");
 vector<vector<int>> graph6 = {
            {0, 0, -2, 0},
            {0, 0, 8, 0},
            {0, -8, 0, 0},
            {4, 88, 0, 0},
    };
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::shortestPath(g,0,2) == "0->2");
    CHECK(ariel::Algorithms::shortestPath(g,1,3) == "No path found");
    CHECK(ariel::Algorithms::shortestPath(g,2,0) == "No path found");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "Graph contains a cycle: 2->1->2");
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is Bipartite and those are the two sets: A={0,1} B={2,3}");
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle detected");
     vector<vector<int>> graph7 = {
            { 0, 0,10, 0,  0, 0, 0},
            {74, 0, 0, 0,  0, 0, 0},
            { 0,38, 0, 1,  0, 0, 0},
            { 0, 0, 0, 0,  0, 3, 0},
            { 0, 0, 0, 5,  0, 0, 0},
            { 0, 0, 0, 0,-10, 0,22},
            { 0, 0, 0, 0,  0, 0, 0}
    };
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::shortestPath(g,0,1) == "Negative cycle detected");
    CHECK(ariel::Algorithms::isConnected(g) == false);

}
TEST_CASE("Test Undirected - No Weights")
{
    ariel::Graph g;
    vector <vector<int>> graph = {
            {0, 1, 0, 1, 1, 0},
            {1, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 1, 1},
            {1, 0, 0, 0, 0, 0},
            {1, 1, 1, 0, 0, 0},
            {0, 1, 1, 0, 0, 0},
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g,0,4) == "0->4");
    CHECK(ariel::Algorithms::shortestPath(g,1,5) == "1->5");
    CHECK(ariel::Algorithms::shortestPath(g,2,0) == "2->4->0");
    CHECK(ariel::Algorithms::isContainsCycle(g) != "0");
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is not Bipartite");
    CHECK(ariel::Algorithms::negativeCycle(g) == "Graph does not contain a negative cycle");
     vector<vector<int>> graph2 = {
            {0, 0, 0, 1, 1},
            {0, 0, 0, 1, 1},
            {0, 0, 0, 0, 0},
            {1, 1, 0, 0, 0},
            {1, 1, 0, 0, 0},
    };
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::shortestPath(g,0,2) == "No path found");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "Graph contains a cycle: 0->3->1->4->0");
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is Bipartite and those are the two sets: A={0,1} B={3,4,2}");
    CHECK(ariel::Algorithms::negativeCycle(g) == "Graph does not contain a negative cycle");
     vector<vector<int>> graph3 = {
            {0, 0, 0, 1, 1},
            {0, 0, 0, 1, 1},
            {0, 0, 0, 1, 0},
            {1, 1, 1, 0, 0},
            {1, 1, 0, 0, 0},
    };
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g,0,2) == "0->3->2");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "Graph contains a cycle: 0->3->1->4->0");
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is Bipartite and those are the two sets: A={0,1,2} B={3,4}");
    CHECK(ariel::Algorithms::negativeCycle(g) == "Graph does not contain a negative cycle");
}
     TEST_CASE("Test Undirected - Non Negative Weights")
{
    ariel::Graph g;
    vector <vector<int>> graph = {
            {0,  12, 0, 1, 10, 0},
            {12, 0,  0, 0, 1,  1},
            {0,  0,  0, 0, 1,  2},
            {1,  0,  0, 0, 0,  0},
            {10, 1,  1, 0, 0,  0},
            {0,  1,  2, 0, 0,  0},
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0->4");
    CHECK(ariel::Algorithms::shortestPath(g, 1, 5) == "1->5");
    CHECK(ariel::Algorithms::shortestPath(g, 2, 0) == "2->4->0");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "Graph contains a cycle: 0->1->4->0");
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is not Bipartite");
    CHECK(ariel::Algorithms::negativeCycle(g) == "Graph does not contain a negative cycle");
     vector<vector<int>> graph2 = {
            {0,  12, 0, 1, 0, 0},
            {12, 0,  0, 0, 0, 0},
            {0,  0,  0, 0, 1, 2},
            {1,  0,  0, 0, 0, 0},
            {0,  0,  1, 0, 0, 0},
            {0,  0,  2, 0, 0, 0}
    };
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "No path found");
    CHECK(ariel::Algorithms::shortestPath(g, 1, 5) == "No path found");
    CHECK(ariel::Algorithms::shortestPath(g, 2, 5) == "2->5");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0");
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is Bipartite and those are the two sets: A={0,4,5} B={1,3,2}");
    CHECK(ariel::Algorithms::negativeCycle(g) == "Graph does not contain a negative cycle");
     vector<vector<int>> graph3 = {
            {0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 2},
            {1, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0},
            {0, 0, 2, 0, 0, 0}
    };
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "No path found");
    CHECK(ariel::Algorithms::shortestPath(g, 1, 5) == "No path found");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "No path found");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0");
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is Bipartite and those are the two sets: A={0,4,5} B={3,1,2}");
    CHECK(ariel::Algorithms::negativeCycle(g) == "Graph does not contain a negative cycle");
}
    TEST_CASE("Test Undirected - Negative Weights")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
            {0, 0, 0,   1, 0,  0},
            {0, 0, 0,   0, 0,  0},
            {0, 0, 0,   0,-1,-22},
            {1, 0, 0,   0, 0,  0},
            {0, 0, -1,  0, 0,  8},
            {0, 0, -22, 0, 8,  0}
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->3");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "Graph contains a cycle: 2->4->5->2");
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is not Bipartite");
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle detected");
    vector<vector<int>> graph2 = {
            {0, 0, 0,  1, 0,  0},
            {0, 0, 0,  0, 0,  0},
            {0, 0, 0,  0, -1,22},
            {1, 0, 0,  0, 0,  0},
            {0, 0, -1, 0, 0,  8},
            {0, 0, 22, 0, 8,  0}
    };
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);
    CHECK(ariel::Algorithms::shortestPath(g, 2, 4) == "Negative cycle detected");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "Graph contains a cycle: 2->4->5->2");
    CHECK(ariel::Algorithms::isBipartite(g) == "Graph is not Bipartite");
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle detected");
    
}
TEST_CASE("Testing invalid graphs loading")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
            {0, 1, 2, 0},
            {1, 0, 3, 0},
            {2, 3, 0, 4},
            {0, 0, 4, 1}
    };
    CHECK_THROWS(g.loadGraph(graph));

    vector<vector<int>> graph2 = {
            {0,1,2}
    };
    CHECK_THROWS(g.loadGraph(graph2));


    vector <vector<int>> graph4 = {
            {0}
    };
    CHECK_THROWS(g.loadGraph(graph4));
}
