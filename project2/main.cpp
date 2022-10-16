#include <iostream>
#include "bignum.cpp"
#include "calculator.cpp"

int main()
{
    Calculator calculator;
    std::string expr;

    std::cout << "Welcome to use this calculator!" << std::endl;
    std::cout << "Type \"exit\" or \"exit()\" to exit the program." << std::endl;

    while (true)
    {
        try
        {
            std::getline(std::cin, expr);
            if (expr == "exit" || expr == "exit()")
            {
                break;
            }

            std::cout << calculator.eval(expr) << std::endl;
        }
        catch (std::invalid_argument &error)
        {
            std::cout << error.what() << std::endl;
        }
    }
}