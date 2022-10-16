#include <iostream>
using namespace std;

int main()
{
    int ints[] = {78, 101, 118, 101, 114, 32, 103, 111, 110, 110, 97, 32, 103, 105, 118, 101, 32, 121, 111, 117, 32, 117, 112, 44, 32, 110, 101, 118, 101, 114, 32, 103, 111, 110, 110, 97, 32, 108, 101, 116, 32, 121, 111, 117, 32, 100, 111, 119, 110, 46, 0};
    char *p = new char[24];
    for (int i = 0; i < 51; i++)
    {
        p[i] = ints[i];
    }

    for (int i = 0; i < 51; i++)
    {
        cout << p[i];
    }
    cout << endl;

    delete p;
    return 0;
}