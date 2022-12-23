#include "BFS_and_DFS.hpp"

// void BFS(const IGraph &graph, int vertex) {
//     std::queue<int> q;
//     std::vector<bool> visited(graph.VerticesCount(), false);
//     q.push(vertex);
//     while (!q.empty()) {
//         int current = q.front();
//         visited[current] == true;
//         std::cout << current << ' ';
//         q.pop();
//         std::vector<int> nextVertices = graph.GetNextVertices(current);
//         for (const auto &v : nextVertices) {
//             if (!visited[v]);
//             q.push(v);
//         }
//     }
//     std::cout << '\n';
// }

// void DFS(const IGraph &graph, int vertex) {
//     std::vector<bool> visited(graph.VerticesCount(), false);
//     visited[vertex] = true;
//     std::cout << vertex << ' ';
//     std::vector<int> nextVertices = graph.GetNextVertices(vertex);
//     for (const auto &v : nextVertices) {
//         if (!visited[v]) {
//             DFS(graph, v);
//         }
//     }
// }


void dfs_aux(const IGraph& graph, int vertex, std::vector<bool>& visited, void (*callback)(int v)) {
    visited[vertex] = true;
    callback(vertex);

    for (auto child : graph.GetNextVertices(vertex)) {
        if (!visited[child]) {
            dfs_aux(graph, child, visited, callback);
        }
    }
}

void DFS(const IGraph& graph, void (*callback)(int v)) {
    std::vector<bool> visited;
    visited.resize(graph.VerticesCount(), false);

    for (int i = 0; i < graph.VerticesCount(); ++i) {
        if (!visited[i]) {
            dfs_aux(graph, i, visited, callback);
        }
    }
}

void BFS(const IGraph& graph, void (*callback)(int v)) {
    std::vector<bool> visited;
    std::queue<int> queue;
    visited.resize(graph.VerticesCount(), false);
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        if (!visited[i]) {
            queue.push(i);
            visited[i] = true;
            while (!queue.empty()) {
                int vertex = queue.front();
                queue.pop();
                callback(vertex);
                for (auto child : graph.GetNextVertices(vertex)) {
                    if (!visited[child]) {
                        queue.push(child);
                        visited[child] = true;
                    }
                }
            }
        }
    }

}