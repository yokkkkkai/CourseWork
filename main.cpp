#include "include/BigInt.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return -1;
    }

    try {
        std::ifstream fin(argv[1]);
        if (!fin) {
            std::cerr << "Error: Cannot open file " << argv[1] << std::endl;
            return -1;
        }

        std::string num1, num2;
        fin >> num1 >> num2;
        fin.close();

        if (num1.empty() || num2.empty()) {
            std::cerr << "Error: Input file must contain two numbers" << std::endl;
            return -1;
        }

        BigInt a(num1);
        BigInt b(num2);

        BigInt c = a.multiply(b);

        c.toFile(argv[2]);

        std::cout << "Multiplication successful. Result written to " << argv[2] << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
