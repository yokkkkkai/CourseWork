#ifndef COMPLEX_H
#define COMPLEX_H

class Complex 
{
public:
    double realPart, imaginaryPart;

    Complex(double realPart = 0.0, double imaginaryPart = 0.0);

    Complex operator+(const Complex &summand) const;
    Complex operator-(const Complex &subtrahend) const;
    Complex operator*(const Complex &factor) const;
    Complex& operator*=(const Complex &factor);
    Complex operator/(double divisor) const;
    Complex& operator/=(double divisor);
};

#endif // COMPLEX_H