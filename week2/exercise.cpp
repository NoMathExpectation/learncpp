#include <iostream>

using std::cout;
using std::endl;

int main() {
    int num1 = 1234567890;
    int num2 = 1234567890;
    int sum = num1 + num2;
    cout << "sum = " << sum << endl;

    float f1 = 1234567890.0f;
    float f2 = 1.0f;
    float fsum = f1 + f2;
    cout << "fsum = " << fsum << endl;
    cout << "(fsum == f1) is " << (fsum == f1) << endl;

    float f = 0.1f;
    float sum10x = f + f + f + f + f + f + f + f + f + f;

    cout<<"sum10x = "<< sum10x << endl;
    cout<<"(sum10x == 1) is "<< (sum10x == 1.0) << endl;
    return 0;
}