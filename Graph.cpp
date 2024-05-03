#include <iostream>
#include <vector>
#include "Algorithms.hpp"
#include <stdexcept>
#include "Graph.hpp"
#include <climits>

using namespace std;
using namespace ariel;

// check if the graph is directed or undirected
// by comparing the adjacency matrix with its transpose
void Graph::setIsDirected(bool value)
{
    this->isDirected = value;
}

void Graph::setWeightsType(int type)
{
    if (type != 1 && type != 0 && type != -1)
    {
        throw invalid_argument("Invalid input");
    }
    this->isWeighted = type;
}

void Graph::loadGraph(vector<vector<int>> &matrix)
{
    if (!matrix.empty())
    {
        // Check if the matrix is square
        for (const auto &row : matrix)
        {
            if (row.size() != matrix.size())
            {
                throw invalid_argument("The graph is not a square matrix.");
            }
        }

        // Load the adjacency matrix
        adjacencyMatrix.clear();
        adjacencyMatrix.resize(matrix.size(), vector<int>(matrix.size(), INT_MAX));
        bool hasNegativeWeights = false;
        bool hasPositiveWeights = false;
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            for (size_t j = 0; j < matrix[i].size(); ++j)
            {
                if (i == j)
                {
                    adjacencyMatrix[i][j] = 0;
                }
                else if (matrix[i][j] != 0)
                {
                    adjacencyMatrix[i][j] = matrix[i][j];
                    if (matrix[i][j] < 0)
                    {
                        hasNegativeWeights = true;
                    }
                    else if (matrix[i][j] > 1)
                    {
                        hasPositiveWeights = true;
                    }
                }
            }
        }
        numVertices = matrix.size();

        // Determine the type of weights and call setWeightsType accordingly
        if (hasNegativeWeights)
        {
            setWeightsType(-1);
        }
        else if (hasPositiveWeights)
        {
            setWeightsType(1);
        }
        else
        {
            setWeightsType(0);
        }
    }
}

void Graph::printGraph()
{
    int edges = 0;
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i)
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j)
        {
            if (i != j && adjacencyMatrix[i][j] != INT_MAX)
            {
                ++edges;
            }
        }
    }
    if (isDirected == false)
    { // if the graph is undirected
        edges /= 2;
    }
    cout << "Graph with " << numVertices << " vertices and " << edges << " edges." << endl;
}

size_t Graph::getNumVertices()
{
    return numVertices;
}

vector<vector<int>> Graph::getAdjacencyMatrix()
{
    return adjacencyMatrix;
}

bool Graph::getIsDirected(Graph graph)
{
    return graph.isDirected;
}

int Graph::getWeightsType(Graph graph)
{
    return graph.isWeighted;
}

