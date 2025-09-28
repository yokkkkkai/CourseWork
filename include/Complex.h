#ifndef COMPLEX_H
#define COMPLEX_H

class Complex 
{
public:
    double re, im;

    Complex(double real = 0.0, double imag = 0.0);

    Complex operator+(const Complex &other) const;
    Complex operator-(const Complex &other) const;
    Complex operator*(const Complex &other) const;
    Complex& operator*=(const Complex &other);
    Complex operator/(double val) const;
    Complex& operator/=(double val);
};

#endif // COMPLEX_H
