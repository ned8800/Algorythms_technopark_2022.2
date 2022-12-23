#ifndef GRAPH_INCLUDE_MATRIXGRAPH_H_
#define GRAPH_INCLUDE_MATRIXGRAPH_H_

#include "IGraph.hpp"
#include <vector>

struct MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(int size);

    explicit MatrixGraph(const IGraph &graph);

    ~MatrixGraph() override = default;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<bool>> adjMatrix;
};

#endif  // GRAPH_INCLUDE_MATRIXGRAPH_H_
