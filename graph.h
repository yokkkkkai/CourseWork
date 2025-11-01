#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <queue>
#include <limits>
#include <utility>

/**
 * @brief Класс, представляющий граф в виде списка смежности.
 */
class Graph {
private:
    int V; // Количество вершин

    // Псевдоним для ребра (соседняя_вершина, вес_ребра)
    typedef std::pair<int, int> Edge;

    // Список смежности
    std::vector<std::vector<Edge>> adj;

    // Псевдоним для элемента в приоритетной очереди (расстояние, вершина)
    typedef std::pair<int, int> PII;

public:
    /**
     * @brief Конструктор графа.
     * @param V Количество вершин в графе.
     */
    Graph(int V);

    /**
     * @brief Добавляет ориентированное ребро в граф.
     * @param u Исходная вершина.
     * @param v Конечная вершина.
     * @param weight Вес ребра.
     */
    void addEdge(int u, int v, int weight);

    /**
     * @brief Реализует алгоритм Дейкстры.
     * @param startNode Стартовая вершина.
     * @return Вектор кратчайших расстояний от startNode до всех
     * остальных вершин.
     */
    std::vector<int> dijkstra(int startNode);
};

#endif // GRAPH_H