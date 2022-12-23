#include "MatrixGraph.hpp"
#include <algorithm>
#include <stdexcept>

MatrixGraph::MatrixGraph(int size) : adjMatrix(size, std::vector<bool>(size, false)) {}

MatrixGraph::MatrixGraph(const IGraph &graph) : adjMatrix(graph.VerticesCount(),
                                                          std::vector<bool>(graph.VerticesCount(), false)) {
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        std::vector<int> nextVertices = graph.GetNextVertices(i);
        for (const auto &vertex: nextVertices) {
            adjMatrix[i][vertex] = true;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    if (from < 0 || from >= adjMatrix.size() || to < 0 || to >= adjMatrix.size()) {
        throw std::out_of_range("At least one of the given vertices is out of range");
    }
    adjMatrix[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
    return static_cast<int>(adjMatrix.size());
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    if (vertex < 0 || vertex >= adjMatrix.size()) {
        throw std::out_of_range("Given vertex is out of range");
    }
    std::vector<int> nextVertices;
    for (int j = 0; j < adjMatrix.size(); ++j) {
        if (adjMatrix[vertex][j]) {
            nextVertices.push_back(j);
        }
    }
    return nextVertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    if (vertex < 0 || vertex >= adjMatrix.size()) {
        throw std::out_of_range("Given vertex is out of range");
    }
    std::vector<int> prevVertices;
    for (int i = 0; i < adjMatrix.size(); ++i) {
        if (adjMatrix[i][vertex]) {
            prevVertices.push_back(i);
        }
    }
    return prevVertices;
}
