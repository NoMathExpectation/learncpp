#include <iostream>
using namespace std;
int main() {
    int a[] = {114, 51, 4, 19, 1, 98, 10};
    for (int i = 0; i < 7; i++) {
        char c = a[i];
        cout << a[i] << ": " << c << endl;
    }
    return 0;
}