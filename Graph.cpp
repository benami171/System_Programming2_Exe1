// NAME: GAL BEN AMI

#include <iostream>
#include <vector>
#include "Algorithms.hpp"
#include <stdexcept>
#include "Graph.hpp"
#include <climits>

using namespace std;
namespace ariel
{

    // Determines the weight type of the graph.
    int whatWeightType(const vector<vector<int>> &matrix)
    {
        int type = 0;
        size_t matSize = matrix.size();
        for (size_t i = 0; i < matSize; i++)
        {
            for (size_t j = 0; j < matSize; j++)
            {
                if (matrix[i][j] < 0)
                {
                    return -1;
                }
                if (matrix[i][j] > 1)
                {
                    type = 1;
                }
            }
        }
        return type;
    }

    /*
     Loads a graph from an adjacency matrix.
     Throws an exception if the matrix is not square or if the diagonal is not zero.
     If the graph is undirected and the matrix is not symmetric, we set the graph to be directed.
    */
    void Graph::loadGraph(const vector<vector<int>> &matrix)
    {
        if (matrix.empty() || matrix[0].size() < 2)
        {
            throw invalid_argument("Input matrix is empty");
        }
        this->numVertices = matrix.size();
        this->adjacencyMatrix = matrix;
        size_t matSize = matrix.size();

        for (size_t i = 0; i < matSize; i++)
        {
            if (matrix[i].size() != matSize)
            {
                throw invalid_argument("Input matrix is not a square matrix");
            }
            for (size_t j = 0; j < matSize; j++)
            {
                if (i == j && matrix[i][j] != 0)
                {
                    throw invalid_argument("In adjacency matrix, the diagonal elements should be zeros");
                }

                if (matrix[i][j] != matrix[j][i] && !this->isDirected)
                {
                    throw invalid_argument("Undirected graph should have symmetric adjacency matrix");
                }
            }
        }
        this->weightType = whatWeightType(matrix); // eventually sets the weight type of the graph
    }

    // Prints the graph, stating whether it's directed or undirected,
    // and the number of vertices and edges.
    void Graph::printGraph()
    {
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
        if (!this->isDirected)
        {
            edges /= 2;
            cout << "Undirected graph with " << numVertices << " vertices and " << edges << " edges." << endl;
        }
        else
        {
            cout << "Directed graph with " << numVertices << " vertices and " << edges << " edges." << endl;
        }
    }

    void Graph::setContainsNegativeCycle(bool flag)
    {
        this->containsNegativeCycle = flag;
    }

    bool Graph::getContainsNegativeCycle() const
    {
        return this->containsNegativeCycle;
    }

    void Graph::setIsDirected(bool type)
    {
        this->isDirected = type;
    }

    void Graph::setWeightsType(int type)
    {
        this->weightType = type;
    }

    size_t Graph::getNumVertices() const
    {
        return numVertices;
    }

    vector<vector<int>> Graph::getAdjacencyMatrix() const
    {
        return adjacencyMatrix;
    }

    bool Graph::getIsDirected() const
    {
        return this->isDirected;
    }

    int Graph::getWeightsType() const
    {
        return this->weightType;
    }
}