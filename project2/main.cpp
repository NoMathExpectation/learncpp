#include <iostream>
#include "bignum.cpp"

using namespace std;

int main()
{
    Bignum a, b, c;
    cin >> a >> b;
    c = a + b;
    cout << a << " + " << b << " = " << c << endl;

    return 0;
}