#include <iostream>
using std::cout;
using std::endl;

void displaySquare(int side = 4, char filledCharacter = '*')
{
    for (size_t i = 0; i < side; i++)
    {
        for (size_t j = 0; j < side; j++)
        {
            cout << filledCharacter;
        }
        cout << endl;
    }
}

int main()
{
    displaySquare();
    cout << endl;

    displaySquare(3);
    cout << endl;

    displaySquare(5, '#');
}