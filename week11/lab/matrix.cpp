#include <memory>
#include <iostream>

class Matrix
{
protected:
    size_t row;
    size_t col;
    std::shared_ptr<float[]> data;

public:
    Matrix(size_t row, size_t col) noexcept : row(row), col(col), data(new float[row * col])
    {
        std::cout << "Matrix created." << std::endl;
    }

    Matrix(const Matrix &another) noexcept : row(another.row), col(another.col), data(another.data)
    {
        std::cout << "Matrix created and copied." << std::endl;
    }

    Matrix(Matrix &&another) noexcept : Matrix(another)
    {
    }

    ~Matrix()
    {
        std::cout << "Matrix destroyed." << std::endl;
    }

    Matrix &operator=(const Matrix &another) noexcept
    {
        this->row = another.row;
        this->col = another.col;
        this->data = another.data;
        std::cout << "Matrix copied." << std::endl;
        return *this;
    }

    Matrix &operator=(const Matrix &&another) noexcept
    {
        *this = another;
        return *this;
    }

    Matrix operator+(const Matrix &another) const noexcept
    {
        Matrix result(row, col);

        for (size_t i = 0; i < row * col; i++)
        {
            result.data[i] = data[i] + another.data[i];
        }

        return result;
    }

    Matrix operator+(const Matrix &&another) const noexcept
    {
        return *this + another;
    }

    Matrix operator*(const float val) const noexcept
    {
        Matrix result(row, col);

        for (size_t i = 0; i < row * col; i++)
        {
            result.data[i] = data[i] * val;
        }

        return result;
    }
};

int main()
{
    Matrix a(3, 4), b(3, 4);
    Matrix c = a + b;
    Matrix d = a * 2.0f;
    Matrix e = c;
    e = d;
}