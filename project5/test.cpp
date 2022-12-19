#include <iostream>
#include "matrix.cpp"

int main()
{
    Matrix<float> a(4, 4);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            a(i, j) = i * 4 + j + 1;
        }
    }
    std::cout << "a = " << std::endl
              << a << std::endl;

    Matrix<float> b(4, 4);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            b(i, j) = 15 - i * 4 - j;
        }
    }
    std::cout << "b = " << std::endl
              << b << std::endl;

    Matrix<float> c = a + b;
    std::cout << "c = a + b = " << std::endl
              << c << std::endl;

    Matrix<float> d = c.region_of(1, 1, 2, 2);
    std::cout << "d = c.region_of(1, 1, 2, 2) = " << std::endl
              << d << std::endl;

    d *= 4;
    std::cout << "d *= 4 = " << std::endl
              << d << std::endl;
    std::cout << "c = " << std::endl
              << c << std::endl;

    Matrix<float> e = d.clone();
    e /= 4;
    std::cout << "e = d.clone()" << std::endl;
    std::cout << "e /= 4 =" << std::endl
              << e << std::endl;
    std::cout << "d = " << std::endl
              << d << std::endl;

    c.local_map([](float x)
                {
        if (x - 64.0 < 1e-6 && x - 64.0 > -1e-6)
            return x / 2;
        else
            return x * 2; });
    std::cout << "c.local_map(...)" << std::endl;
    std::cout << "c = " << std::endl
              << c << std::endl;
}