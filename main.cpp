/**
 * @file main.cpp
 * @brief Главный файл программы для вычисления кратчайшего пути в графе
 * @author ГУАП, Калашников Андрей, группа 2455
 * @date 2025
 */

#include "Graph.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <stdexcept>

/**
 * @brief Главная функция программы
 * @details
 * Программа принимает два аргумента командной строки:
 * 1. Имя входного файла (.txt), содержащего ребра графа.
 * 2. Имя выходного файла (.dot), куда будет сохранено дерево кратчайших путей.
 *
 * Программа автоматически определяет количество вершин в графе
 * на основе максимального индекса, встреченного во входном файле.
 * В качестве стартовой вершины для алгоритма Дейкстры
 * используется вершина с минимальным индексом.
 *
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return 0 при успешном выполнении, 1 при ошибке
 */
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <input_file.txt> <output_file.dot>" << std::endl;
        return 1;
    }

    std::string inputFilename = argv[1];
    std::string outputFilename = argv[2];

    try
    {
        std::ifstream fin(inputFilename.c_str());
        if (!fin.is_open())
            throw std::runtime_error("Cannot open input file: " + inputFilename);

        int maxVertex = -1;
        int minVertex = std::numeric_limits<int>::max();
        int u, v, w;

        while (fin >> u >> v >> w)
        {
            if (fin.fail())
                throw std::runtime_error("Invalid data in input file: " + inputFilename);

            if (u > maxVertex) maxVertex = u;
            if (v > maxVertex) maxVertex = v;
            if (u < minVertex) minVertex = u;
            if (v < minVertex) minVertex = v;
        }
        fin.close();

        if (maxVertex == -1)
            throw std::runtime_error("No edges found in file or file is empty!");

        Graph graph(maxVertex + 1);
        graph.readFromFile(inputFilename);

        std::vector<int> distances = graph.dijkstra(minVertex);
        graph.writeResultToDot(outputFilename, minVertex);

        std::cout << "Results written to: " << outputFilename << std::endl;

        graph.printResult(distances, 0);
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Input Error (out of range): " << e.what() << std::endl;
        return 1;
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}