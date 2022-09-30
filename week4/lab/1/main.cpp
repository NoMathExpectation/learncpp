#include "stuinfo.hpp"
#include <iostream>
using namespace std;

int main()
{
    const int n = 3;
    stuinfo students[n];

    inputstu(students, n);

    sortstu(students, n);

    showstu(students, n);

    char name[20];
    cout << "Input a name to find the student: ";
    cin >> name;

    if (findstu(students, n, name))
    {
        cout << "Student found." << endl;
    }
    else
    {
        cout << "No studnet found." << endl;
    }

    return 0;
}