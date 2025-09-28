#ifndef BIGINT_H
#define BIGINT_H

#include <vector>
#include <string>
#include <cmath>
#include "Complex.h"

typedef std::vector<int> IntVector;
typedef std::vector<Complex> ComplexVector;

class BigInt 
{
private:
    IntVector digits;
    const double PI = acos(-1);

    void fft(ComplexVector &a, bool invert) const;
    ComplexVector prepareArray(const IntVector &arr, int n) const;
    IntVector normalize(const ComplexVector &arr) const;

public:
    BigInt(const std::string &num);
    BigInt(const IntVector &d);

    BigInt multiply(const BigInt &other) const;
    std::string toString() const;

    static BigInt fromFile(const std::string &filename);
    void toFile(const std::string &filename) const;
};

#endif // BIGINT_H
