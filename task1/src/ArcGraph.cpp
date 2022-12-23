#include "ArcGraph.hpp"
#include <algorithm>
#include <stdexcept>

ArcGraph::ArcGraph(int size) : verticesCount(size) {}

ArcGraph::ArcGraph(const IGraph &graph) : verticesCount(graph.VerticesCount()) {
    for (int u = 0; u < graph.VerticesCount(); ++u) {
        auto nextVertices = graph.GetNextVertices(u);
        for (const int &v: nextVertices) {
            edges.emplace_back(u, v);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    if (from < 0 || from >= verticesCount || to < 0 || to >= verticesCount) {
        throw std::out_of_range("At least one of the given vertices is out of range");
    }
    edges.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {
    return verticesCount;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    if (vertex < 0 || vertex >= verticesCount) {
        throw std::out_of_range("Given vertex is out of range");
    }
    std::vector<int> nextVertices;
    for (const auto &edge: edges) {
        if (edge.first == vertex) {
            nextVertices.push_back(edge.second);
        }
    }
    return nextVertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    if (vertex < 0 || vertex >= verticesCount) {
        throw std::out_of_range("Given vertex is out of range");
    }
    std::vector<int> prevVertices;
    for (const auto &edge: edges) {
        if (edge.second == vertex) {
            prevVertices.push_back(edge.first);
        }
    }
    return prevVertices;
}
