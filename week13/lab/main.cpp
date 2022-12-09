#include "matrix.cpp"
#include <cstring>

using namespace std;

template <typename T>
void useMatrixTemplate(Matrix<T> &m, T array[][MAXCOL], T array2[][MAXCOL])
{
    cout << "Setting matrix:" << endl;
    m.set(array);
    m.print();

    cout << "Adding matrix:" << endl;
    m.add(array2);
    m.print();
}

int main()
{
    string str1[MAXROW][MAXCOL] = {{"Congra", "y", "ar"}, {"alm", "don", "La"}};
    string str2[MAXROW][MAXCOL] = {{"tulations", "ou", "e"}, {"ost", "e the", "b!"}};

    int num1[MAXROW][MAXCOL] = {{1, 2, 3}, {4, 5, 6}};
    int num2[MAXROW][MAXCOL] = {{6, 5, 4}, {3, 2, 1}};

    Matrix<string> stringMartix(2, 3);
    Matrix<int> intMatrix(2, 3);

    cout << "Demonstrating with string matrix:" << endl;
    useMatrixTemplate(stringMartix, str1, str2);

    cout << "\nDemonstrating with int matrix:" << endl;
    useMatrixTemplate(intMatrix, num1, num2);

    return 0;
}