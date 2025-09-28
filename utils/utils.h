#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <utility> 

std::pair<std::string, std::string> readNumbersFromFile(const std::string& inputPath);

void writeResultToFile(const std::string& outputPath, const std::string& resultString);

#endif // UTILS_H