#include <iostream>
#include <charconv>
using namespace std;

int length(char *charStart)
{
    int length = 0;
    while (*(charStart++) != '\0')
    {
        length++;
    }
    return length;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Not enough numbers. Please make sure you have inputed two numbers." << endl;
        return 1;
    }

    char *n1 = argv[1];
    char *n2 = argv[2];
    char *n1End = n1 + length(n1);
    char *n2End = n2 + length(n2);
    long double d1, d2;

    from_chars_result result1 = from_chars(n1, n1End, d1);
    from_chars_result result2 = from_chars(n2, n2End, d2);

    if (result1.ptr != n1End || result2.ptr != n2End)
    {
        cout << "The input cannot be converted to numbers. Please check your input." << endl;
        return 1;
    }

    cout << d1 << " * " << d2 << " = " << d1 * d2 << endl;

    return 0;
}