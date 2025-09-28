#include "/home/andreyk/course_work/include/Complex.h"
#include <cmath>

Complex::Complex(double realPart, double imaginaryPart) : realPart(realPart), imaginaryPart(imaginaryPart) {}

Complex Complex::operator+(const Complex &summand) const 
{
    return Complex(realPart + summand.realPart, imaginaryPart + summand.imaginaryPart);
}

Complex Complex::operator-(const Complex &subtrahend) const 
{
    return Complex(realPart - subtrahend.realPart, imaginaryPart - subtrahend.imaginaryPart);
}

Complex Complex::operator*(const Complex &factor) const 
{
    return Complex(realPart * factor.realPart - imaginaryPart * factor.imaginaryPart, 
                   realPart * factor.imaginaryPart + imaginaryPart * factor.realPart);
}

Complex& Complex::operator*=(const Complex &factor) 
{
    double newRealPart = realPart * factor.realPart - imaginaryPart * factor.imaginaryPart;
    double newImaginaryPart = realPart * factor.imaginaryPart + imaginaryPart * factor.realPart;
    
    realPart = newRealPart;
    imaginaryPart = newImaginaryPart;
    return *this;
}

Complex Complex::operator/(double divisor) const 
{
    return Complex(realPart / divisor, imaginaryPart / divisor);
}

Complex& Complex::operator/=(double divisor) 
{
    realPart /= divisor;
    imaginaryPart /= divisor;
    return *this;
}