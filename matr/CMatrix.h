#pragma once

#include <algorithm>


template<typename T, size_t rows, size_t cols>
class CMatrix
{
public:
    typedef enum Type
    {
        Normal,
        Identity
    };

    CMatrix(Type type = Normal)
    {
        switch (type)
        {
        case Identity:
        {
            size_t ones_count = std::min(rows, cols);
            for (size_t row = 0; row < ones_count; ++row)
            {
                _matrix[row][row] = 1;
            }
        }
            break;
        }
    }
    CMatrix(const T* array_)
    {
        for (size_t row = 0; row < rows; ++row)
        {
            _matrix[row] = array_ + row * cols;
        }
    }
    CMatrix(const CMatrix& matrix_)
    {
        for (size_t row = 0; row < rows; ++row)
        {
            _matrix[row] = matrix_[row];
        }
    }
    ~CMatrix()
    {

    }

    CMatrix& operator=(const CMatrix& matrix_)
    {
        for (size_t row = 0; row < rows; ++row)
        {
            _matrix[row] = matrix_[row];
        }

        return *this;
    }
    CMatrix& operator+=(const CMatrix& matrix_)
    {
        for (size_t row = 0; row < rows; ++row)
        {
            _matrix[row] += matrix_[row];
        }

        return *this;
    }
    CMatrix operator+(const CMatrix& matrix_)
    {
        CMatrix result(*this);
        result += matrix_;
        return result;
    }
    CMatrix& operator-=(const CMatrix& matrix_)
    {
        for (size_t row = 0; row < rows; ++row)
        {
            _matrix[row] -= matrix_[row];
        }

        return *this;
    }
    CMatrix operator-(const CMatrix& matrix_)
    {
        CMatrix result(*this);
        result -= matrix_;
        return result;
    }

    CMatrix& operator+=(const T& value_)
    {

    }
    CMatrix& operator*=(const T& value_)
    {
        for (size_t row = 0; row < rows; ++row)
        {
            _matrix[row] *= value_;
        }

        return *this;
    }

    CVector<T, cols>& operator[](size_t index_)
    {
        return _matrix[index_];
    }
    const CVector<T, cols>& operator[](size_t index_) const
    {
        return _matrix[index_];
    }

    CMatrix& RowReduce()
    {
        for (size_t k = 0; k < rows; ++k)
        {
            if (_matrix[k][k] != 0 && _matrix[k][k] != 1.) _matrix[k] *= 1. / _matrix[k][k];

            if (k > 0)
            {
                for (size_t i = 0; i < k; ++i)
                {
                    if (_matrix[i][k] != 0.)
                    {
                        _matrix[i] -= _matrix[k] * _matrix[i][k];
                    }
                }
            }

            for (size_t i = k + 1; i < rows; ++i)
            {
                _matrix[i] -= _matrix[k] * _matrix[i][k];
            }
        }

        return *this;
    }

private:
    CVector<T, cols> _matrix[rows];

};

template<typename T, size_t rows, size_t dim, size_t cols>
CMatrix<T, rows, cols> operator*(const CMatrix<T, rows, dim>& matrix1_, const CMatrix<T, dim, cols>& matrix2_)
{
    CMatrix<T, rows, cols> result;

    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols; ++col)
        {
            for (size_t d = 0; d < dim; ++d)
            {
                result[row][col] += matrix1_[row][d] * matrix2_[d][col];
            }
        }
    }

    return result;
}

template<typename T, size_t rows, size_t cols>
std::ostream& operator<<(std::ostream& os_, const CMatrix<T, rows, cols>& matrix_)
{
    for (size_t row = 0; row < rows; ++row)
    {
        os_ << matrix_[row] << std::endl;
    }

    return os_;
}

template<typename T, size_t rows, size_t cols1, size_t cols2>
CMatrix<T, rows, cols1 + cols2> AppendHorz(const CMatrix<T, rows, cols1>& matrix1_, const CMatrix<T, rows, cols2>& matrix2_)
{
    CMatrix<T, rows, cols1 + cols2> result;

    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols1; ++col)
        {
            result[row][col] = matrix1_[row][col];
        }
        for (size_t col = 0; col < cols2; ++col)
        {
            result[row][cols1 + col] = matrix2_[row][col];
        }
    }

    return result;
}

template<typename T, size_t rows1, size_t rows2, size_t cols>
CMatrix<T, rows1 + rows2, cols> AppendVert(const CMatrix<T, rows1, cols>& matrix1_, const CMatrix<T, rows2, cols>& matrix2_)
{
    CMatrix<T, rows1 + rows2, cols> result;

    for (size_t row = 0; row < rows1; ++row)
    {
        result[row] = matrix1_[row];
    }
    for (size_t row = 0; row < rows2; ++row)
    {
        result[rows1 + row] = matrix2_[row];
    }

    return result;
}
