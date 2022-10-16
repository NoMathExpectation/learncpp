#include <iostream>
using namespace std;

int main()
{
    int *p = new int[5];
    for (int i = 0; i < 5; i++)
    {
        p[i] = i;
    }

    for (int i = 4; i >= 0; i--)
    {
        cout << p[i] << endl;
    }

    delete p;
    return 0;
}