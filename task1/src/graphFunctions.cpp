#include "graphFunctions.hpp"
#include <iostream>
#include <queue>

void BFS(const IGraph &graph, int vertex) {
    std::queue<int> q;
    std::vector<bool> visited(graph.VerticesCount());
    q.push(vertex);
    while (!q.empty()) {
        int current = q.front();
        visited[current] == true;
        std::cout << current << ' ';
        q.pop();
        std::vector<int> nextVertices = graph.GetNextVertices(current);
        for (const auto &v : nextVertices) {
            if (!visited[v]);
            q.push(v);
        }
    }
    std::cout << '\n';
}

void DFS(const IGraph &graph, int vertex) {
    std::vector<bool> visited(graph.VerticesCount());
    visited[vertex] = true;
    std::cout << vertex << ' ';
    std::vector<int> nextVertices = graph.GetNextVertices(vertex);
    for (const auto &v : nextVertices) {
        if (!visited[v]) {
            DFS(graph, v);
        }
    }
}
