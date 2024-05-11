#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <sstream> // for std::stringstream, stringstream used to redirect cout to a string



using namespace std;




TEST_CASE("Test loading valid undirected graph")
{
    ariel::Graph g;
    g.setIsDirected(false);
    vector<vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    CHECK_NOTHROW(g.loadGraph(graph));
    CHECK(g.getNumVertices() == 3);
    CHECK(g.getWeightsType() == 0);
}

TEST_CASE("Test loading valid directed graph")
{
    ariel::Graph g;
    g.setIsDirected(true);
    vector<vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}};
    CHECK_NOTHROW(g.loadGraph(graph));
    CHECK(g.getNumVertices() == 3);
    CHECK(g.getWeightsType() == 0);
}

TEST_CASE("Test loading graph with negative weights")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, -1, 2},
        {-1, 0, 3},
        {2, 3, 0}};
    CHECK_NOTHROW(g.loadGraph(graph));
    CHECK(g.getNumVertices() == 3);
    CHECK(g.getWeightsType() == -1);
}

TEST_CASE("Test loading graph with non-square matrix")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2},
        {1, 0, 3}};
    CHECK_THROWS(g.loadGraph(graph));
}

TEST_CASE("Test loading undirected graph with non-symmetric matrix")
{
    ariel::Graph g;
    g.setIsDirected(false);
    vector<vector<int>> graph = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    CHECK_THROWS(g.loadGraph(graph));
}

TEST_CASE("Test printGraph method")

{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}};
    g.loadGraph(graph);
    // Redirect cout to a stringstream
    std::stringstream buffer; // will be used to store the output
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf()); // save old buffer and redirect cout to buffer
    g.printGraph();
    // Reset cout to its old self
    std::cout.rdbuf(prevcoutbuf); // reset to standard output again
    CHECK(buffer.str() == "Graph with 3 vertices and 6 edges.\n");
}
