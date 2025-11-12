/**
 * @file Graph.h
 * @brief Заголовочный файл класса Graph для работы с взвешенным ориентированным графом
 * @author ГУАП, Калашников Андрей, группа 2455
 * @date 2025
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <string>
#include <stdexcept>

/**
 * @typedef PII
 * @brief Псевдоним для пары <int, int>, используется для хранения (расстояние, вершина)
 * в очереди с приоритетом в алгоритме Дейкстры.
 */
typedef std::pair<int, int> PII;

/**
 * @class Graph
 * @brief Класс для представления взвешенного ориентированного графа
 *
 * Этот класс использует список смежности для хранения графа и
 * предоставляет методы для добавления ребер, чтения графа из файла,
 * вычисления кратчайших путей с помощью алгоритма Дейкстры и
 * записи результата в файл формата Graphviz (.dot).
 */
class Graph {
public:
    /**
     * @brief Конструктор класса Graph
     * @param V Количество вершин в графе. Вершины будут проиндексированы от 0 до V-1.
     * @throws std::invalid_argument если V <= 0.
     */
    Graph(int V);

    /**
     * @brief Добавляет ориентированное ребро в граф
     * @param u Начальная вершина (индекс от 0 до V-1)
     * @param v Конечная вершина (индекс от 0 до V-1)
     * @param weight Вес ребра
     * @throws std::out_of_range если u или v находятся вне допустимого диапазона [0, V-1].
     */
    void addEdge(int u, int v, int weight);

    /**
     * @brief Выполняет алгоритм Дейкстры для поиска кратчайших путей
     * @param startNode Стартовая вершина (индекс от 0 до V-1)
     * @return Вектор `dist` размером V, где `dist[i]` - кратчайшее расстояние
     * от `startNode` до вершины `i`.
     * Если вершина `i` недостижима, `dist[i]` будет равен `std::numeric_limits<int>::max()`.
     * @throws std::out_of_range если `startNode` находится вне допустимого диапазона [0, V-1].
     */
    std::vector<int> dijkstra(int startNode);

    /**
     * @brief Читает граф из текстового файла
     * @details Файл должен содержать тройки чисел (u, v, weight) в каждой строке,
     * представляющие ребра графа.
     * @param filename Имя файла
     * @throws std::runtime_error если файл не удается открыть или
     * если данные в файле имеют неверный формат.
     * @throws std::out_of_range (через addEdge) если вершины в файле
     * выходят за пределы [0, V-1].
     */
    void readFromFile(std::string filename);

    /**
     * @brief Записывает дерево кратчайших путей в файл формата Graphviz (.dot)
     * @details Использует внутренний вектор `last_prev`, который должен быть
     * заполнен предыдущим вызовом `dijkstra()`.
     * @param filename Имя файла (например, "output.dot")
     * @param startVertex Стартовая вершина, использованная в `dijkstra()`
     * @throws std::out_of_range если `startVertex` находится вне допустимого диапазона.
     * @throws std::runtime_error если файл не удается открыть для записи или
     * если внутренние данные (last_prev) повреждены.
     */
    void writeResultToDot(const std::string& filename,
        int startVertex);

    /**
     * @brief Выводит расстояния до всех вершин в стандартный поток вывода (консоль)
     * @param distances Вектор расстояний, полученный от `dijkstra()`
     * @param startVertex Стартовая вершина, от которой производился расчет
     * @throws std::out_of_range если `startVertex` находится вне допустимого диапазона.
     */
    void printResult(const std::vector<int>& distances, int startVertex);

private:
    /**
     * @typedef Edge
     * @brief Псевдоним для пары <int, int>, используется для хранения
     * (конечная вершина, вес) в списке смежности.
     */
    typedef std::pair<int, int> Edge;

    int vertex_count; /**< @brief Общее количество вершин в графе (V) */
    
    /**< @brief Список смежности. 
     * `adjacency_list[u]` содержит вектор пар (v, weight),
     * представляющих ребра из `u` в `v` с весом `weight`.
     */
    std::vector<std::vector<Edge> > adjacency_list;

    /**< @brief Вектор "предков". 
     * `last_prev[i]` хранит вершину, из которой был сделан
     * последний шаг в вершину `i` в кратчайшем пути.
     * Заполняется методом `dijkstra()`.
     */
    std::vector<int> last_prev;
};

#endif