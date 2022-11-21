#include <iostream>

class Complex
{
private:
    double real;
    double imaginary;

public:
    Complex(double real, double imaginary) noexcept
    {
        this->real = real;
        this->imaginary = imaginary;
    }

    Complex() noexcept : Complex(0, 0)
    {
    }

    Complex(const Complex &) noexcept = default;

    Complex(Complex &&) noexcept = default;

    double getReal() const noexcept
    {
        return real;
    }

    double getImaginary() const noexcept
    {
        return imaginary;
    }

    Complex &operator=(const Complex &) noexcept = default;

    Complex &operator=(Complex &&) noexcept = default;

    Complex &operator=(const double &val) noexcept
    {
        real = val;
        imaginary = 0;
        return *this;
    }

    Complex &operator=(double &&val) noexcept
    {
        *this = val;
        return *this;
    }

    Complex operator+(const Complex &another) const noexcept
    {
        return Complex(real + another.real, imaginary + another.imaginary);
    }

    Complex operator+(const Complex &&another) const noexcept
    {
        return *this + another;
    }

    Complex operator+(const double &val) const noexcept
    {
        return Complex(real + val, imaginary);
    }

    friend Complex operator+(const double &val, const Complex &complex) noexcept
    {
        return complex + val;
    }

    friend Complex operator+(const double &val, const Complex &&complex) noexcept
    {
        return complex + val;
    }

    Complex operator-(const Complex &another) const noexcept
    {
        return Complex(real - another.real, imaginary - another.imaginary);
    }

    Complex operator-(const Complex &&another) const noexcept
    {
        return *this - another;
    }

    Complex operator-(const double &val) const noexcept
    {
        return Complex(real - val, imaginary);
    }

    friend Complex operator-(const double &val, const Complex &complex) noexcept
    {
        return complex - val;
    }

    friend Complex operator-(const double &val, const Complex &&complex) noexcept
    {
        return complex - val;
    }

    Complex operator*(const Complex &another) const noexcept
    {
        return Complex(real * another.real - imaginary * another.imaginary, real * another.imaginary + imaginary * another.real);
    }

    Complex operator*(const Complex &&another) const noexcept
    {
        return *this * another;
    }

    Complex operator*(const double &val) const noexcept
    {
        return Complex(real * val, imaginary * val);
    }

    friend Complex operator*(const double &val, const Complex &complex) noexcept
    {
        return complex * val;
    }

    friend Complex operator*(const double &val, const Complex &&complex) noexcept
    {
        return complex * val;
    }

    Complex conjugate() const noexcept {
        return Complex(real, -imaginary);
    }

    Complex operator!() const noexcept {
        return conjugate();
    }

    Complex operator/(const Complex &another) const noexcept
    {
        return *this * !another / (another.real * another.real + another.imaginary * another.imaginary);
    }

    Complex operator/(const Complex &&another) const noexcept
    {
        return *this / another;
    }

    Complex operator/(const double &val) const noexcept
    {
        return Complex(real / val, imaginary / val);
    }

    friend Complex operator/(const double &val, const Complex &complex) noexcept
    {
        return Complex(val, 0) / complex;
    }

    friend Complex operator/(const double &val, const Complex &&complex) noexcept
    {
        return val / complex;
    }

    bool operator==(const Complex &another) const noexcept
    {
        return real == another.real && imaginary == another.imaginary;
    }

    bool operator==(const Complex &&another) const noexcept
    {
        return *this == another;
    }

    bool operator==(const double &val) const noexcept
    {
        return real == val && imaginary == 0;
    }

    friend bool operator==(const double &val, const Complex &complex) noexcept
    {
        return complex == val;
    }

    friend bool operator==(const double &val, const Complex &&complex) noexcept
    {
        return complex == val;
    }

    bool operator!=(const Complex &another) const noexcept
    {
        return !(*this == another);
    }

    bool operator!=(const Complex &&another) const noexcept
    {
        return *this != another;
    }

    bool operator!=(const double &val) const noexcept
    {
        return !(*this == val);
    }

    friend bool operator!=(const double &val, const Complex &complex) noexcept
    {
        return complex != val;
    }

    friend bool operator!=(const double &val, const Complex &&complex) noexcept
    {
        return complex != val;
    }

    friend std::istream &operator>>(std::istream &in, Complex &complex) {
        in >> complex.real >> complex.imaginary;
        return in;
    }

    friend std::ostream &operator<<(std::ostream &out, const Complex &complex) {
        out << complex.real << ((complex.imaginary >= 0) ? "+" : "") << complex.imaginary << 'i';
        return out;
    }
};

int main() {
    Complex a, b;
    std::cin >> a >> b;

    std::cout << a << '+' << b << '=' << a + b << std::endl;
    std::cout << a << '-' << b << '=' << a - b << std::endl;
    std::cout << a << '*' << b << '=' << a * b << std::endl;
    std::cout << a << '/' << b << '=' << a / b << std::endl;
    std::cout << a << ((a == b) ? "==" : "!=") << b << std::endl;
}