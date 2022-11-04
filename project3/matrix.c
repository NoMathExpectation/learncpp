#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void createMatrix(matrix *m, int row, int col)
{
    m->row_length = row;
    m->column_length = col;

    m->data = calloc(row, sizeof(m->data[0]));

    for (int i = 0; i < row; i++)
    {
        m->data[i] = calloc(col, sizeof(m->data[0][0]));
    }
}

void deleteMatrix(matrix *m)
{
    if (m->data == NULL)
    {
        return;
    }

    for (int i = 0; i < m->row_length; i++)
    {
        free(m->data[i]);
    }

    free(m->data);
    m->data = NULL;
}

void printMatrix(const matrix *m)
{
    for (int i = 0; i < m->row_length; i++)
    {
        for (int j = 0; j < m->column_length; j++)
        {
            printf("%f ", m->data[i][j]);
        }
        printf("\n");
    }
}

float getMatrixElement(const matrix *m, int row, int col)
{
    return m->data[row][col];
}

void setMatrixElement(matrix *m, int row, int col, float value)
{
    m->data[row][col] = value;
}

void copyMatrix(matrix *dest, const matrix *src)
{
    createMatrix(dest, src->row_length, src->column_length);

    for (int i = 0; i < src->row_length; i++)
    {
        for (int j = 0; j < src->column_length; j++)
        {
            dest->data[i][j] = src->data[i][j];
        }
    }
}

void copyMatrixArray(matrix *dest, const float *src, int row, int col)
{
    createMatrix(dest, row, col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            dest->data[i][j] = src[col * i + j];
        }
    }
}

void identityMatrix(matrix *dest, int size) {
    createMatrix(dest, size, size);

    for (int i = 0; i < size; i++)
    {
        dest->data[i][i] = 1.0;
    }
    
}

int addMatrix(matrix *result, const matrix *m1, const matrix *m2)
{
    if (m1->row_length != m2->row_length || m1->column_length != m2->column_length)
    {
        return -1;
    }

    createMatrix(result, m1->row_length, m1->column_length);

    for (int i = 0; i < m1->row_length; i++)
    {
        for (int j = 0; j < m1->column_length; j++)
        {
            result->data[i][j] = m1->data[i][j] + m2->data[i][j];
        }
    }
}

void addMatrixScalar(matrix *result, const matrix *m, float scalar)
{
    createMatrix(result, m->row_length, m->column_length);

    for (int i = 0; i < m->row_length; i++)
    {
        for (int j = 0; j < m->column_length; j++)
        {
            result->data[i][j] = m->data[i][j] + scalar;
        }
    }
}

int subtractMatrix(matrix *result, const matrix *m1, const matrix *m2)
{
    if (m1->row_length != m2->row_length || m1->column_length != m2->column_length)
    {
        return -1;
    }

    createMatrix(result, m1->row_length, m1->column_length);

    for (int i = 0; i < m1->row_length; i++)
    {
        for (int j = 0; j < m1->column_length; j++)
        {
            result->data[i][j] = m1->data[i][j] - m2->data[i][j];
        }
    }
}

void subtractMatrixScalar(matrix *result, const matrix *m, float scalar)
{
    createMatrix(result, m->row_length, m->column_length);

    for (int i = 0; i < m->row_length; i++)
    {
        for (int j = 0; j < m->column_length; j++)
        {
            result->data[i][j] = m->data[i][j] - scalar;
        }
    }
}

int multiplyMatrix(matrix *result, const matrix *m1, const matrix *m2)
{
    if (m1->column_length != m2->row_length)
    {
        return -1;
    }

    createMatrix(result, m1->row_length, m2->column_length);

    for (int i = 0; i < result->column_length; i++)
    {
        for (int j = 0; j < result->row_length; j++)
        {
            int sum = 0;
            for (int k = 0; k < m1->column_length; k++)
            {
                sum += m1->data[j][k] * m2->data[k][i];
            }
            result->data[j][i] = sum;
        }
    }
}

void multiplyMatrixScalar(matrix *result, const matrix *m, float scalar)
{
    createMatrix(result, m->row_length, m->column_length);

    for (int i = 0; i < result->row_length; i++)
    {
        for (int j = 0; j < result->column_length; j++)
        {
            result->data[i][j] = m->data[i][j] * scalar;
        }
    }
}

void divideMatrixScalar(matrix *result, const matrix *m, float scalar) {
    createMatrix(result, m->row_length, m->column_length);

    for (int i = 0; i < result->row_length; i++)
    {
        for (int j = 0; j < result->column_length; j++)
        {
            result->data[i][j] = m->data[i][j] / scalar;
        }
    }
}

float minMatrix(const matrix *m)
{
    if (m->row_length <= 0 || m->column_length <= 0)
    {
        return 0.0;
    }

    float min = m->data[0][0];

    for (int i = 0; i < m->row_length; i++)
    {
        for (int j = 0; j < m->column_length; j++)
        {
            if (min > m->data[i][j])
            {
                min = m->data[i][j];
            }
        }
    }

    return min;
}

float maxMatrix(const matrix *m)
{
    if (m->row_length <= 0 || m->column_length <= 0)
    {
        return 0.0;
    }

    float max = m->data[0][0];

    for (int i = 0; i < m->row_length; i++)
    {
        for (int j = 0; j < m->column_length; j++)
        {
            if (max < m->data[i][j])
            {
                max = m->data[i][j];
            }
        }
    }

    return max;
}

int rowMatrix(matrix *dest, const matrix *m, int row) {
    if (row < 0 || row >= m->row_length) {
        return -1;
    }

    createMatrix(dest, 1, m->column_length);

    for (int i = 0; i < m->column_length; i++) {
        dest->data[0][i] = m->data[row][i];
    }

    return 0;
}

int columnMatrix(matrix *dest, const matrix *m, int col) {
    if (col < 0 || col >= m->column_length) {
        return -1;
    }

    createMatrix(dest, m->row_length, 1);

    for (int i = 0; i < m->row_length; i++) {
        dest->data[i][0] = m->data[i][col];
    }

    return 0;
}

int deleteRowMatrix(matrix *dest, const matrix *m, int row) {
    if (row < 0 || row >= m->row_length) {
        return -1;
    }

    createMatrix(dest, m->row_length - 1, m->column_length);

    int si = 0;
    for (int i = 0; i < m->row_length; i++)
    {
        if (i == row) {
            continue;
        }

        for (int j = 0; j < m->column_length; j++)
        {
            dest->data[si][j] = m->data[i][j];
        }

        si++;
    }

    return 0;
}

int deleteColumnMatrix(matrix *dest, const matrix *m, int col) {
    if (col < 0 || col >= m->column_length) {
        return -1;
    }

    createMatrix(dest, m->row_length, m->column_length - 1);

    int si = 0;
    for (int i = 0; i < m->column_length; i++)
    {
        if (i == col) {
            continue;
        }

        for (int j = 0; j < m->row_length; j++)
        {
            dest->data[j][si] = m->data[j][i];
        }

        si++;
    }

    return 0;
}

int deleteRowColumnMatrix(matrix *dest, const matrix *m, int row, int col) {
    if (row < 0 || row >= m->row_length || col < 0 || col >= m->column_length) {
        return -1;
    }

    matrix mid;
    deleteRowMatrix(&mid, m, row);
    deleteColumnMatrix(dest, &mid, col);
    deleteMatrix(&mid);

    return 0;
}

float determinantMatrix(const matrix *m)
{
    if (m->row_length != m->column_length || m->row_length == 0)
    {
        return 0.0;
    }

    if (m->row_length == 1)
    {
        return m->data[0][0];
    }

    if (m->row_length == 2)
    {
        return m->data[0][0] * m->data[1][1] - m->data[0][1] * m->data[1][0];
    }

    int minus = -1;
    int sign = minus;
    float sum = 0;
    for (int k = 0; k < m->column_length; k++)
    {
        matrix sub;
        deleteRowColumnMatrix(&sub, m, 0, k);
        
        sign *= minus;
        sum += sign * m->data[0][k] * determinantMatrix(&sub);

        deleteMatrix(&sub);
    }
    
    return sum;
}

void transposeMatrix(matrix *result, const matrix *m)
{
    createMatrix(result, m->column_length, m->row_length);

    for (int i = 0; i < m->row_length; i++)
    {
        for (int j = 0; j < m->column_length; j++)
        {
            result->data[j][i] = m->data[i][j];
        }
    }
}

int invertMatrix(matrix *result, const matrix *m)
{
    if (m->row_length != m->column_length || m->row_length <= 0) {
        return -1;
    }

    float det = determinantMatrix(m);
    if (det == 0.0) {
        return -1;
    }

    matrix adj;
    createMatrix(&adj, m->row_length, m->column_length);
    for (int i = 0; i < m->row_length; i++)
    {
        for (int j = 0; j < m->column_length; j++)
        {
            matrix sub;
            deleteRowColumnMatrix(&sub, m, i, j);

            adj.data[j][i] = pow(-1, i + j) * determinantMatrix(&sub);
            deleteMatrix(&sub);
        }
    }
    
    multiplyMatrixScalar(result, &adj, 1.0 / det);
    deleteMatrix(&adj);
    
    return 0;
}