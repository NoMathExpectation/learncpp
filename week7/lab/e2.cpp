#include <iostream>
using std::cout;
using std::endl;

int vabs(int *p, size_t n) {
    int sum = 0;
    for (size_t i = 0; i < n; i++)
    {
        sum += p[i] > 0 ? p[i] : -p[i];
    }
    return sum;
}

float vabs(float *p, size_t n) {
    float sum = 0;
    for (size_t i = 0; i < n; i++)
    {
        sum += p[i] > 0 ? p[i] : -p[i];
    }
    return sum;
}

double vabs(double *p, size_t n) {
    double sum = 0;
    for (size_t i = 0; i < n; i++)
    {
        sum += p[i] > 0 ? p[i] : -p[i];
    }
    return sum;
}

int main()
{
    int a[] = { 1, 1, -4, 5, -1, 4 };
    float b[] = { 1.14, -5.14, 19.19, 8.1, 0 };
    double c[] = { 1.9, -1.9, 8.1, 0 };

    cout << vabs(a, 6) << endl;
    cout << vabs(b, 5) << endl;
    cout << vabs(c, 4) << endl;
}