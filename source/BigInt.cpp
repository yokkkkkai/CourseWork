#include "/home/andreyk/course_work/include/BigInt.h"
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <fstream>

BigInt::BigInt(const std::string &numString) 
{
    digits_.resize(numString.size());

    for (size_t i = 0; i < numString.size(); i++)
        digits_[i] = numString[numString.size() - 1 - i] - '0';
}

BigInt::BigInt(const IntVector &digitArray) : digits_(digitArray) {}

void BigInt::fft(ComplexVector &complexArray, bool invert) const 
{
    int size = complexArray.size();
    
    for (int i = 1, j = 0; i < size; i++) 
    {
        int bit = size >> 1;
        for (; j & bit; bit >>= 1) 
        {
            j ^= bit;
        }
            
        j ^= bit;
        if (i < j) std::swap(complexArray[i], complexArray[j]);
    }

    for (int currentLength = 2; currentLength <= size; currentLength <<= 1) 
    {
        double baseAngle = 2 * PI_ / currentLength * (invert ? -1 : 1);
        Complex rotationFactorBase(std::cos(baseAngle), std::sin(baseAngle));

        for (int i = 0; i < size; i += currentLength) 
        {
            Complex currentRotationFactor(1, 0);

            for (int j = 0; j < currentLength / 2; j++) 
            {
                Complex upperValue = complexArray[i + j];
                Complex lowerValue = complexArray[i + j + currentLength / 2] * currentRotationFactor;
                
                complexArray[i + j] = upperValue + lowerValue;
                complexArray[i + j + currentLength / 2] = upperValue - lowerValue;
                
                currentRotationFactor *= rotationFactorBase;
            }
        }
    }

    if (invert)
        for (Complex &x : complexArray) 
        {
            x /= size;
        }
}

ComplexVector BigInt::prepareArray(const IntVector &digitArray, int requiredSize) const 
{
    ComplexVector complexDigits;
    for (int digit : digitArray) 
    {
        complexDigits.push_back(Complex(digit, 0));
    }

    complexDigits.resize(requiredSize);
    return complexDigits;
}

IntVector BigInt::normalize(const ComplexVector &complexResult) const 
{
    IntVector resultDigits(complexResult.size());
    long long carry = 0;

    for (size_t i = 0; i < complexResult.size(); i++) 
    {
        long long digitValue = static_cast<long long>(std::round(complexResult[i].realPart)) + carry;
        resultDigits[i] = digitValue % 10; 
        carry = digitValue / 10;          
    }

    while (carry) 
    {
        resultDigits.push_back(carry % 10);
        carry /= 10;
    }

    while (resultDigits.size() > 1 && resultDigits.back() == 0)
    {
        resultDigits.pop_back();
    }
    return resultDigits;
}

BigInt BigInt::multiplyFFT(const BigInt &other) const 
{
    int requiredSize = 1;
    int minimumSize = digits_.size() + other.digits_.size();
    while (requiredSize < minimumSize) 
    {
        requiredSize <<= 1;
    }

    ComplexVector firstComplexArray = prepareArray(digits_, requiredSize);
    ComplexVector secondComplexArray = prepareArray(other.digits_, requiredSize);

    fft(firstComplexArray, false);
    fft(secondComplexArray, false);

    for (int i = 0; i < requiredSize; i++) 
    {
        firstComplexArray[i] *= secondComplexArray[i];
    }

    fft(firstComplexArray, true);

    IntVector resultDigits = normalize(firstComplexArray);
    return BigInt(resultDigits);
}

std::string BigInt::toString() const 
{
    std::string resultString;
    for (int i = digits_.size() - 1; i >= 0; i--) 
    {
        resultString += (digits_[i] + '0');
    }

    return resultString;
}