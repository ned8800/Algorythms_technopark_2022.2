#include <stdexcept>
#include "SetGraph.hpp"

SetGraph::SetGraph(int size) : adjSets(size) {}

SetGraph::SetGraph(const IGraph &graph) : adjSets(graph.VerticesCount()){
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        auto nextVertices = graph.GetNextVertices(i);
        for (const auto &vertex: nextVertices) {
            adjSets[i].insert(vertex);
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    if (from < 0 || from >= adjSets.size() || to < 0 || to >= adjSets.size()) {
        throw std::out_of_range("At least one of the given vertices is out of range");
    }
    adjSets[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return static_cast<int>(adjSets.size());
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    if (vertex < 0 || vertex >= adjSets.size()) {
        throw std::out_of_range("Given vertex is out of range");
    }
    std::vector<int> nextVertices;
    for (const auto &v: adjSets[vertex]) {
        nextVertices.push_back(v);
    }
    return nextVertices;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    if (vertex < 0 || vertex >= adjSets.size()) {
        throw std::out_of_range("Given vertex is out of range");
    }
    std::vector<int> prevVertices;
    for (int u = 0; u < adjSets.size(); ++u) {
        for (const auto &v: adjSets[u]) {
            if (v == vertex) {
                prevVertices.push_back(u);
            }
        }
    }
    return prevVertices;
}
