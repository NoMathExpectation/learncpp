#ifndef matrix_cpp
#define matrix_cpp

#include <memory>
#include <functional>
#include <ostream>

template <typename T>
class Matrix
{
protected:
    size_t row;
    size_t col;
    std::shared_ptr<T[]> data;
    size_t start_offset;
    size_t row_interval;

public:
    Matrix(const size_t row, const size_t col) noexcept : row(row), col(col), data(new T[row * col]), start_offset(0), row_interval(col)
    {
    }

    Matrix(const Matrix<T> &another) noexcept : row(another.row), col(another.col), data(another.data), start_offset(0), row_interval(col)
    {
    }

    Matrix(const Matrix<T> &&another) noexcept : Matrix(another)
    {
    }

    Matrix clone() const noexcept
    {
        return combine(*this, [](const T &a, const T &b)
                       { return a; });
    }

    T &operator()(const size_t row, const size_t col) const
    {
        if (row >= this->row || col >= this->col)
        {
            throw std::invalid_argument("Matrix index out of range.");
        }

        return data[start_offset + row_interval * row + col];
    }

    Matrix region_of(size_t start_row, size_t start_col, size_t row, size_t col) const noexcept
    {
        if (start_row + row > this->row || start_col + col > this->col)
        {
            throw std::invalid_argument("Matrix index out of range.");
        }

        Matrix result(*this);
        result.row = row;
        result.col = col;
        result.start_offset = start_offset + start_row * row_interval + start_col;
        result.row_interval = row_interval;
        return result;
    }

    Matrix &operator=(const Matrix<T> &another) noexcept
    {
        this->row = another.row;
        this->col = another.col;
        this->data = another.data;
        this->start_offset = start_offset;
        this->row_interval = row_interval;
        return *this;
    }

    Matrix &operator=(const Matrix<T> &&another) noexcept
    {
        *this = another;
        return *this;
    }

    Matrix operator+(const Matrix<T> &another) const
    {
        return combine(another, std::plus<T>());
    }

    Matrix operator+(const Matrix<T> &&another) const
    {
        return *this + another;
    }

    Matrix operator+(const T &val) const
    {
        return map([&](const T &a)
                   { return a + val; });
    }

    Matrix operator+(const T &&val) const
    {
        return *this + val;
    }

    Matrix operator+=(const Matrix<T> &another)
    {
        return local_combine(another, std::plus<T>());
    }

    Matrix operator+=(const Matrix<T> &&another)
    {
        return *this += another;
    }

    Matrix operator+=(const T &val)
    {
        return local_map([&](const T &a)
                         { return a + val; });
    }

    Matrix operator+=(const T &&val)
    {
        return *this += val;
    }

    Matrix operator-(const Matrix<T> &another) const
    {
        return combine(another, std::minus<T>());
    }

    Matrix operator-(const Matrix<T> &&another) const
    {
        return *this - another;
    }

    Matrix operator-(const T &val) const
    {
        return map([&](const T &a)
                   { return a - val; });
    }

    Matrix operator-(const T &&val) const
    {
        return *this - val;
    }

    Matrix operator-=(const Matrix<T> &another)
    {
        return local_combine(another, std::minus<T>());
    }

    Matrix operator-=(const Matrix<T> &&another)
    {
        return *this -= another;
    }

    Matrix operator-=(const T &val)
    {
        return local_map([&](const T &a)
                         { return a - val; });
    }

    Matrix operator-=(const T &&val)
    {
        return *this -= val;
    }

    Matrix operator*(const Matrix<T> &another) const
    {
        if (col != another.row)
        {
            throw std::invalid_argument("Matrix size not match.");
        }

        Matrix result(row, another.col);

        T *pr = result.data.get();
        for (size_t i = 0; i < result.row; i++)
        {
            for (size_t j = 0; j < result.col; j++)
            {
                T sum = 0;
                for (size_t k = 0; k < col; k++)
                {
                    sum += (*this)(i, k) * another(k, j);
                }
                *(pr++) = sum;
            }
        }

        return result;
    }

    Matrix operator*(const Matrix<T> &&another) const
    {
        return *this * another;
    }

    Matrix operator*(const T &val) const
    {
        return map([&](const T &a)
                   { return a * val; });
    }

    Matrix operator*(const T &&val) const
    {
        return *this * val;
    }

    Matrix operator*=(const T &val)
    {
        return local_map([&](const T &a)
                         { return a * val; });
    }

    Matrix operator*=(const T &&val)
    {
        return *this *= val;
    }

    Matrix operator/(const T &val) const
    {
        return map([&](const T &a)
                   { return a / val; });
    }

    Matrix operator/(const T &&val) const
    {
        return *this / val;
    }

    Matrix operator/=(const T &val)
    {
        return local_map([&](const T &a)
                         { return a / val; });
    }

    Matrix operator/=(const T &&val)
    {
        return *this /= val;
    }

    bool operator==(const Matrix<T> &another)
    {
        if (row != another.row || col != another.col)
        {
            return false;
        }

        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                if ((*this)(i, j) != another(i, j))
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator==(const Matrix<T> &&another)
    {
        return *this == another;
    }

    bool operator!=(const Matrix<T> &another)
    {
        return !(*this == another);
    }

    bool operator!=(const Matrix<T> &&another)
    {
        return *this != another;
    }

    Matrix transpose() const
    {
        Matrix result(col, row);

        T *pr = result.data.get();
        for (size_t i = 0; i < col; i++)
        {
            for (size_t j = 0; j < row; j++)
            {
                *(pr++) = (*this)[j, i];
            }
        }

        return result;
    }

    Matrix combine(const Matrix<T> &another, std::function<T(const T &, const T &)> combine) const
    {
        if (row != another.row || col != another.col)
        {
            throw std::invalid_argument("Matrix size not match.");
        }

        Matrix result(row, col);

        T *pr = result.data.get();
        T *pa = data.get() + start_offset;
        T *pb = another.data.get() + another.start_offset;

        for (size_t i = 0; i < row; i++)
        {
            for (size_t i = 0; i < col; i++)
            {
                *(pr++) = combine(*(pa++), *(pb++));
            }
            pa += row_interval - col;
            pb += another.row_interval - col;
        }

        return result;
    }

    Matrix &local_combine(const Matrix<T> &another, std::function<T(const T &, const T &)> combine)
    {
        if (row != another.row || col != another.col)
        {
            throw std::invalid_argument("Matrix size not match.");
        }

        T *pa = data.get() + start_offset;
        T *pb = another.data.get() + another.start_offset;

        for (size_t i = 0; i < row; i++)
        {
            for (size_t i = 0; i < col; i++)
            {
                *pa = combine(*pa, *(pb++));
                pa++;
            }
            pa += row_interval - col;
            pb += another.row_interval - col;
        }

        return *this;
    }

    Matrix map(std::function<T(const T &)> mapping) const
    {
        Matrix result(row, col);

        T *pr = result.data.get();
        T *p = data.get() + start_offset;

        for (size_t i = 0; i < row; i++)
        {
            for (size_t i = 0; i < col; i++)
            {
                *(pr++) = mapping(*(p++));
            }
            p += row_interval - col;
        }

        return result;
    }

    Matrix &local_map(std::function<T(const T &)> mapping)
    {
        T *p = data.get() + start_offset;

        for (size_t i = 0; i < row; i++)
        {
            for (size_t i = 0; i < col; i++)
            {
                *p = mapping(*p);
                p++;
            }
            p += row_interval - col;
        }

        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix)
    {
        T *p = matrix.data.get() + matrix.start_offset;

        for (size_t i = 0; i < matrix.row; i++)
        {
            for (size_t i = 0; i < matrix.col; i++)
            {
                os << *(p++) << " ";
            }
            p += matrix.row_interval - matrix.col;
            os << std::endl;
        }

        return os;
    }
};

#endif