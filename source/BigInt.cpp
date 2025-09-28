#include "/home/andreyk/course_work/include/BigInt.h"
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <fstream>

BigInt::BigInt(const std::string &num) 
{
    digits.resize(num.size());

    for (size_t i = 0; i < num.size(); i++)
        digits[i] = num[num.size() - 1 - i] - '0';
}

BigInt::BigInt(const IntVector &d) : digits(d) {}

void BigInt::fft(ComplexVector &a, bool invert) const 
{
    int n = a.size();
    
    for (int i = 1, j = 0; i < n; i++) 
    {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) 
        {
            j ^= bit;
        }
            
        j ^= bit;
        if (i < j) std::swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) 
    {
        double angle = 2 * PI / len * (invert ? -1 : 1);
        Complex wlen(std::cos(angle), std::sin(angle));

        for (int i = 0; i < n; i += len) 
        {
            Complex w(1, 0);

            for (int j = 0; j < len / 2; j++) 
            {
                Complex u = a[i + j];
                Complex v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert)
        for (Complex &x : a) 
        {
            x /= n;
        }
}

ComplexVector BigInt::prepareArray(const IntVector &arr, int n) const 
{
    ComplexVector res;
    for (int d : arr) 
    {
        res.push_back(Complex(d, 0));
    }

    res.resize(n);
    return res;
}

IntVector BigInt::normalize(const ComplexVector &arr) const 
{
    IntVector result(arr.size());
    long long carry = 0;

    for (size_t i = 0; i < arr.size(); i++) 
    {
        long long val = static_cast<long long>(std::round(arr[i].re)) + carry;
        result[i] = val % 10;
        carry = val / 10;
    }

    while (carry) 
    {
        result.push_back(carry % 10);
        carry /= 10;
    }

    while (result.size() > 1 && result.back() == 0)
    {
        result.pop_back();
    }
    return result;
}

BigInt BigInt::multiply(const BigInt &other) const 
{
    int n = 1;
    while (n < static_cast<int>(digits.size() + other.digits.size())) n <<= 1;

    ComplexVector fa = prepareArray(digits, n);
    ComplexVector fb = prepareArray(other.digits, n);

    fft(fa, false);
    fft(fb, false);

    for (int i = 0; i < n; i++) 
    {
        fa[i] *= fb[i];
    }

    fft(fa, true);

    IntVector result = normalize(fa);
    return BigInt(result);
}

std::string BigInt::toString() const 
{
    std::string s;
    for (int i = digits.size() - 1; i >= 0; i--) 
    {
        s += (digits[i] + '0');
    }

    return s;
}

BigInt BigInt::fromFile(const std::string &filename) 
{
    std::ifstream fin(filename);
    if (!fin) 
    {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    std::string s;
    fin >> s;
    fin.close();
    return BigInt(s);
}

void BigInt::toFile(const std::string &filename) const 
{
    std::ofstream fout(filename);
    if (!fout) 
    {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    
    fout << toString();
    fout.close();
}
