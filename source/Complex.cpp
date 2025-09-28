#include "/home/andreyk/course_work/include/Complex.h"
#include <cmath>

Complex::Complex(double real, double imag) : re(real), im(imag) {}

Complex Complex::operator+(const Complex &other) const 
{
    return Complex(re + other.re, im + other.im);
}

Complex Complex::operator-(const Complex &other) const 
{
    return Complex(re - other.re, im - other.im);
}

Complex Complex::operator*(const Complex &other) const 
{
    return Complex(re * other.re - im * other.im, re * other.im + im * other.re);
}

Complex& Complex::operator*=(const Complex &other) 
{
    double r = re * other.re - im * other.im;
    double i = re * other.im + im * other.re;
    re = r;
    im = i;
    return *this;
}

Complex Complex::operator/(double val) const 
{
    return Complex(re / val, im / val);
}

Complex& Complex::operator/=(double val) 
{
    re /= val;
    im /= val;
    return *this;
}
