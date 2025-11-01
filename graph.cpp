#include "graph.h"

// Конструктор: инициализирует V и список смежности adj.
Graph::Graph(int V) : V(V), adj(V) {}

/**
 * @brief Добавляет ориентированное ребро в граф.
 */
void Graph::addEdge(int u, int v, int weight) {
    // Добавляем ребро u -> v с весом weight
    adj[u].push_back(std::make_pair(v, weight));
    
    // Если граф неориентированный, раскомментируйте строку ниже:
    // adj[v].push_back(std::make_pair(u, weight));
}

/**
 * @brief Реализует алгоритм Дейкстры (O(ElogV)).
 */
std::vector<int> Graph::dijkstra(int startNode) {
    // 1. Инициализация
    std::vector<int> dist(V, std::numeric_limits<int>::max());
    
    // min-heap (расстояние, вершина)
    std::priority_queue<PII, std::vector<PII>, std::greater<PII>> pq;

    // 2. Стартовая вершина
    dist[startNode] = 0;
    pq.push(std::make_pair(0, startNode));

    // 3. Основной цикл
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        // Оптимизация: пропускаем устаревшие записи в очереди
        if (d > dist[u]) {
            continue;
        }

        // 4. Релаксация ребер
        // (Используем синтаксис C++11 - range-based for loop)
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            // Если нашли путь короче
            if (dist[u] != std::numeric_limits<int>::max() && 
                dist[u] + weight < dist[v]) {
                
                dist[v] = dist[u] + weight;
                pq.push(std::make_pair(dist[v], v));
            }
        }
    }

    // 5. Возвращаем результат
    return dist;
}