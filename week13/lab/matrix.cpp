#include <iostream>

#define MAXROW 5
#define MAXCOL 5

template <typename T>
class Matrix
{
private:
    T data[MAXROW][MAXCOL];
    size_t row, col;

public:
    Matrix(const size_t row = MAXROW, const size_t col = MAXCOL) noexcept : row(row), col(col)
    {
    }

    void print() const noexcept
    {
        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void set(T array[][MAXCOL]) noexcept
    {
        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                data[i][j] = array[i][j];
            }
        }
    }

    void add(T array[][MAXCOL]) noexcept
    {
        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                data[i][j] += array[i][j];
            }
        }
    }
};