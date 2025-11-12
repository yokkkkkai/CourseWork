/**
 * @file Graph.cpp
 * @brief Реализация методов класса Graph
 * @author ГУАП, Калашников Андрей, группа 2455
 * @date 2025
 */

#include "Graph.h"
#include <queue>
#include <limits>
#include <fstream>
#include <iostream>
#include <stdexcept>

Graph::Graph(int V) : vertex_count(V), adjacency_list(V)
{
    if (V <= 0)
        throw std::invalid_argument("Graph must have at least one vertex.");
}

void Graph::addEdge(int u, int v, int weight)
{
    if (u < 0 || u >= vertex_count || v < 0 || v >= vertex_count)
        throw std::out_of_range("Error: Vertex index out of graph bounds.");
    adjacency_list[u].push_back(std::make_pair(v, weight));
}

std::vector<int> Graph::dijkstra(int startNode)
{
    if (startNode < 0 || startNode >= vertex_count)
        throw std::out_of_range("Start vertex out of bounds.");

    std::vector<int> dist(vertex_count, std::numeric_limits<int>::max());
    std::vector<int> prev(vertex_count, -1);

    std::priority_queue<PII, std::vector<PII>, std::greater<PII> > pq;

    dist[startNode] = 0;
    pq.push(std::make_pair(0, startNode));

    size_t i;
    int u, v, w;

    while (!pq.empty())
    {
        int d = pq.top().first;
        u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;

        for (i = 0; i < adjacency_list[u].size(); ++i)
        {
            v = adjacency_list[u][i].first;
            w = adjacency_list[u][i].second;

            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push(std::make_pair(dist[v], v));
            }
        }
    }

    last_prev = prev;
    return dist;
}

void Graph::readFromFile(std::string filename)
{
    std::ifstream fin(filename.c_str());
    if (!fin.is_open())
        throw std::runtime_error("File is not open: " + filename);

    int u, v, w;
    while (fin >> u >> v >> w)
    {
        if (fin.fail())
            throw std::runtime_error("Invalid data in file: " + filename);
        addEdge(u, v, w);
    }

    fin.close();
}

void Graph::writeResultToDot(const std::string& filename, int startVertex)
{
    if (startVertex < 0 || startVertex >= vertex_count)
        throw std::out_of_range("Start vertex out of bounds for DOT output.");

    std::ofstream fout(filename.c_str());
    if (!fout.is_open())
        throw std::runtime_error("Cannot open output file: " + filename);

    fout << "digraph G {\n";

    for (int u = 0; u < vertex_count; ++u)
    {
        fout << "    " << u;
        if (u == startVertex)
            fout << " [shape=doublecircle, style=filled, fillcolor=blue]";
        else
            fout << " [shape=circle]";
        fout << ";\n";
    }

    for (int u = 0; u < vertex_count; ++u)
    {
        for (size_t i = 0; i < adjacency_list[u].size(); ++i)
        {
            int v = adjacency_list[u][i].first;
            int w = adjacency_list[u][i].second;

            bool isInShortestPath = (last_prev[v] == u);

            fout << "    " << u << " -> " << v
                 << " [label=" << w;
            if (isInShortestPath)
                fout << ", color=red";
            fout << "];\n";
        }
    }

    fout << "}\n";
    fout.close();
}


void Graph::printResult(const std::vector<int>& distances, int startVertex)
{
    if (startVertex < 0 || startVertex >= vertex_count)
        throw std::out_of_range("Start vertex out of bounds for printing.");

    std::cout << "Shortest distances from vertex " << startVertex << ":\n";
    for (size_t i = 0; i < distances.size(); ++i)
    {
        std::cout << "Vertex " << i << ": ";
        if (distances[i] == std::numeric_limits<int>::max())
            std::cout << "unreachable";
        else
            std::cout << distances[i];
        std::cout << '\n';
    }
}