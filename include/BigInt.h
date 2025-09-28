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
    IntVector digits_; 
    const double PI_ = acos(-1); 

    void fft(ComplexVector &complexArray, bool invert) const;
    ComplexVector prepareArray(const IntVector &digitArray, int requiredSize) const;
    IntVector normalize(const ComplexVector &complexResult) const;

public:
    BigInt(const std::string &numString); 
    BigInt(const IntVector &digitArray); 

    BigInt multiplyFFT(const BigInt &other) const;
    std::string toString() const;
};

#endif // BIGINT_H