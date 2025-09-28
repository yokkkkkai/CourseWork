#include "utils.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

std::pair<std::string, std::string> readNumbersFromFile(const std::string& inputPath) 
{
    std::ifstream inputFile(inputPath);
    if (!inputFile) {
        throw std::runtime_error("Cannot open input file: " + inputPath);
    }

    std::string numString1, numString2;
    
    if (!(inputFile >> numString1 >> numString2) || numString1.empty() || numString2.empty()) {
        throw std::runtime_error("Input file is corrupted or does not contain two valid numbers.");
    }

    inputFile.close();
    return {numString1, numString2};
}

void writeResultToFile(const std::string& outputPath, const std::string& resultString) 
{
    std::ofstream outputFile(outputPath);
    if (!outputFile) {
        throw std::runtime_error("Cannot open output file for writing: " + outputPath);
    }

    outputFile << resultString << "\n";
    outputFile.close();
}