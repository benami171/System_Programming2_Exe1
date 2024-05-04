#include <iostream>
#include <vector>
#include "Algorithms.hpp"
#include <stdexcept>
#include "Graph.hpp"
#include <climits>

using namespace std;
using namespace ariel;

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

        // If the graph is undirected, check if the matrix is symmetric
        if (!getIsDirected())
        {
            for (size_t i = 0; i < matrix.size(); ++i)
            {
                for (size_t j = 0; j < i; ++j)
                {
                    if (matrix[i][j] != matrix[j][i])
                    {
                        throw invalid_argument("Undirected graph can only load a symmetric matrix.");
                    }
                }
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
                if (matrix[i][j] != INT_MAX)
                {
                    adjacencyMatrix[i][j] = matrix[i][j];
                    if (matrix[i][j] < 0)
                    {
                        hasNegativeWeights = true;
                    }
                    else if (matrix[i][j] > 0)
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
        else
        {
            // Check if the graph is unweighted
            bool isUnweighted = true;
            for (size_t i = 0; i < matrix.size(); ++i)
            {
                for (size_t j = 0; j < matrix[i].size(); ++j)
                {
                    if (matrix[i][j] != INT_MAX && matrix[i][j] != 0 && matrix[i][j] != 1)
                    {
                        isUnweighted = false;
                        break;
                    }
                }
                if (!isUnweighted)
                {
                    break;
                }
            }
            if (isUnweighted)
            {
                setWeightsType(0);
            }
            else
            {
                setWeightsType(1);
            }
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

void Graph::setContainsNegativeCycle(bool flag)
{
    this->containsNegativeCycle = flag;
}

bool Graph::getContainsNegativeCycle()
{
    return this->containsNegativeCycle;
}
// check if the graph is directed or undirected
// by comparing the adjacency matrix with its transpose
void Graph::setIsDirected(bool type)
{
    this->isDirected = type;
}

void Graph::setWeightsType(int type)
{
    this->isWeighted = type;
}

size_t Graph::getNumVertices()
{
    return numVertices;
}

vector<vector<int>> Graph::getAdjacencyMatrix()
{
    return adjacencyMatrix;
}

bool Graph::getIsDirected()
{
    return this->isDirected;
}

int Graph::getWeightsType()
{
    return this->isWeighted;
}
