#include <iostream>
#include "libswap.hpp"
using namespace std;

int main() {
    int a = 1, b = 2;
    swap(1, 2);
    cout << a << " " << b << endl;

    int c = 3, d = 4;
    swap(&c, &d);
    cout << c << " " << d << endl;

    long e = 5, f = 6;
    swap(e, f);
    cout << e << " " << f << endl;
}