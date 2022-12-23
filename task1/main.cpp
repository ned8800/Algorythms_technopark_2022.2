#include <iostream>

#include "ArcGraph.hpp"
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "SetGraph.hpp"
#include "graphFunctions.hpp"

int main() {
    ArcGraph arcGraph(7);
    arcGraph.AddEdge(0, 1);
    arcGraph.AddEdge(0, 2);
    arcGraph.AddEdge(1, 3);
    arcGraph.AddEdge(1, 4);
    arcGraph.AddEdge(2, 5);
    arcGraph.AddEdge(2, 6);

    std::cout << "===ArcGraph===\n"
                 "Вершин: " << arcGraph.VerticesCount() << "\n"
                 "Обход в глубину: ";
    DFS(arcGraph, 0);
    std::cout << "Обход в ширину: ";
    BFS(arcGraph, 0);
    



    ListGraph listGraph(arcGraph);

    std::cout << "\n===ListGraph===\n"
                 "Вершин: " << listGraph.VerticesCount() << "\n"
                 "Обход в глубину: ";
    DFS(listGraph, 0);
    std::cout << "Обход в ширину: ";
    BFS(listGraph, 0);




    MatrixGraph matrixGraph(listGraph);

    std::cout << "\n===MatrixGraph===\n"
                 "Вершин: " << matrixGraph.VerticesCount() << "\n"
                 "Обход в глубину: ";
    DFS(matrixGraph, 0);
    std::cout << "Обход в ширину: ";
    BFS(matrixGraph, 0);




    SetGraph setGraph(matrixGraph);

    std::cout << "\n===SetGraph===\n"
                 "Вершин: " << setGraph.VerticesCount() << "\n"
                 "Обход в глубину: ";
    DFS(setGraph, 0);
    std::cout << "Обход в ширину: ";
    BFS(setGraph, 0);




    SetGraph arcGraphAgain(setGraph);

    std::cout << "\n===ArcGraph Again===\n"
                 "Вершин: " << arcGraphAgain.VerticesCount() << "\n"
                 "Обход в глубину: ";
    DFS(arcGraphAgain, 0);
    std::cout << "Обход в ширину: ";
    BFS(arcGraphAgain, 0);
}