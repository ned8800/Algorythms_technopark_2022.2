#include "ListGraph.hpp"
#include <stdexcept>

ListGraph::ListGraph(int size) : adjLists(size) {}

ListGraph::ListGraph(const IGraph &graph) : adjLists(graph.VerticesCount()) {
    for (int i = 0; i < adjLists.size(); ++i) {
        adjLists[i] = graph.GetNextVertices(i);
    }
}

void ListGraph::AddEdge(int from, int to) {
    if (from < 0 || from >= adjLists.size() || to < 0 || to >= adjLists.size()) {
        throw std::out_of_range("At least one of the given vertices is out of range");
    }
    adjLists[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return static_cast<int>(adjLists.size());
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    if (vertex < 0 || vertex >= adjLists.size()) {
        throw std::out_of_range("Given vertex is out of range");
    }
    return adjLists[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    if (vertex < 0 || vertex >= adjLists.size()) {
        throw std::out_of_range("Given vertex is out of range");
    }
    std::vector<int> prevVertices;
    for (int i = 0; i < adjLists.size(); ++i) {
        for (const auto &v: adjLists[i]) {
            if (v == vertex) {
                prevVertices.push_back(i);
            }
        }
    }
    return prevVertices;
}
