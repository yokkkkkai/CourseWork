#include "BigInt.h"
#include "utils.h" 
#include <iostream>
#include <string>
#include <stdexcept>
#include <utility> 

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }

    const std::string inputPath = argv[1];
    const std::string outputPath = argv[2];

    try {
        std::pair<std::string, std::string> numbers = readNumbersFromFile(inputPath);
        const std::string& numString1 = numbers.first;
        const std::string& numString2 = numbers.second;

        std::cout << "Starting multiplication...\n";
        
        const BigInt numberA(numString1);
        const BigInt numberB(numString2);

        const BigInt resultC = numberA.multiplyFFT(numberB);
        
        const std::string resultString = resultC.toString();

        writeResultToFile(outputPath, resultString);

        std::cout << "Multiplication successful. Result (length " << resultString.length() 
                  << ") written to " << outputPath << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
        return 1;
    }

    return 0;
}