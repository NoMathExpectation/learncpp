#include <iostream>
using std::cout;
using std::endl;

template <typename T>
T minimum(T a, T b)
{
    return a < b ? a : b;
}

int main() {
    cout << minimum(114, 514) << endl;
    cout << minimum('n', 'm') << endl;
    cout << minimum(19.19, 8.10) << endl;
}