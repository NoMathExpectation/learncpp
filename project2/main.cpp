#include <iostream>
#include "bignum.cpp"
#include "calculator.cpp"

using namespace std;

int main()
{
    Calculator calculator;
    string expr;

    cout << "Welcome to use this calculator!" << endl;
    cout << "Type \"exit\" or \"exit()\" to exit the program." << endl;

    while (true)
    {
        try
        {
            getline(cin, expr);
            if (expr == "exit" || expr == "exit()")
            {
                break;
            }

            cout << calculator.eval(expr) << endl;
        }
        catch (invalid_argument &error)
        {
            cout << error.what() << endl;
        }
    }
}