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
    this->numVertices = matrix.size();
    size_t matSize = matrix.size();
    this->adjacencyMatrix = matrix;

    for(size_t i = 0; i < matSize; i++)
    {
        if (matrix[i].size() != matSize)
        {
            throw invalid_argument("Input matrix is not a square matrix");
        }
        for (int j = 0; j < matSize; j++)
        {
            if (i == j && matrix[i][j] != 0)
            {
                throw invalid_argument("In adjacency matrix, the diagonal elements should be zeros");
            }

            if( matrix[i][j] != matrix[j][i] && !this->isDirected)
            {
                throw invalid_argument("Undirected graph should have symmetric adjacency matrix");
            }
        }
    }
    this->isWeighted = whatWeightType(matrix);
}

void Graph::printGraph()
{
    bool type = getIsDirected();
    int edges = 0;
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i)
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j)
        {
            if (i != j && adjacencyMatrix[i][j] != 0)
            {
                ++edges;
            }
        }
    }
    if (isDirected == false)
    { // if the graph is undirected
        edges /= 2;
        cout << "Undirected graph with " << numVertices << " vertices and " << edges << " edges." << endl;
    }
    else
    {
        cout << "Directed graph with " << numVertices << " vertices and " << edges << " edges." << endl;
    }
}

int whatWeightType(vector<vector<int>> &matrix)
{
    int type = 0;
    int matSize = matrix.size();
    for (int i = 0; i < matSize; i++)
    {
        for (int j = 0; j < matSize; j++)
        {
            if (matrix[i][j] < 0)
            {
                return -1;
            }
            else if (matrix[i][j] > 0)
            {
                type = 1;
            }
        }
    }
    return type;
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
