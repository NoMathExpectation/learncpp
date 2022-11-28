#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

void createMatrix(matrix *m, const size_t row, const size_t col, bool column_stored)
{
    if (m == NULL)
    {
        return;
    }

    m->row_length = row;
    m->column_length = col;
    m->column_stored = column_stored;

    m->data = aligned_alloc(ALIGN, row * col * sizeof(m->data[0]));
}

void randMatrix(matrix *m, const size_t row, const size_t col, bool column_stored)
{
    createMatrix(m, row, col, column_stored);

#pragma omp parallel for
    float *p = m->data;
    for (int i = 0; i < row * col; i++)
    {
        *(p++) = rand();
    }
}

size_t matrixIndex(const matrix *m, const size_t row, const size_t col)
{
    return m->column_stored ? (col * m->row_length + row) : (row * m->column_length + col);
}

void deleteMatrix(matrix *m)
{
    if (m == NULL || m->data == NULL)
    {
        return;
    }

    free(m->data);
    m->data = NULL;
}

void printMatrix(const matrix *m)
{
    if (m == NULL || m->data == NULL)
    {
        return;
    }

    float *p = m->data;
    for (int i = 0; i < m->row_length; i++)
    {
        for (int j = 0; j < m->column_length; j++)
        {
            printf("%f ", *(p++));
        }
        printf("\n");
    }
}

int matmul_plain(matrix *result, const matrix *m1, const matrix *m2)
{
    if (m1 == NULL || m2 == NULL || result == NULL || m1->data == NULL || m2->data == NULL || m1->column_length != m2->row_length)
    {
        return -1;
    }

    createMatrix(result, m1->row_length, m2->column_length, false);

    for (int i = 0; i < result->column_length; i++)
    {
        for (int j = 0; j < result->row_length; j++)
        {
            float sum = 0;
            for (int k = 0; k < m1->column_length; k++)
            {
                sum += m1->data[matrixIndex(m1, j, k)] * m2->data[matrixIndex(m2, k, i)];
            }
            result->data[matrixIndex(result, j, i)] = sum;
        }
    }
}

int matmul_improved(matrix *result, const matrix *m1, const matrix *m2)
{
    if (m1 == NULL || m2 == NULL || result == NULL || m1->data == NULL || m2->data == NULL || m1->column_length != m2->row_length || m1->column_stored || !m2->column_stored)
    {
        return -1;
    }

    createMatrix(result, m1->row_length, m2->column_length, false);

#pragma omp parallel for
    for (int i = 0; i < result->column_length; i++)
    {
#pragma omp parallel for
        for (int j = 0; j < result->row_length; j++)
        {
            float *pr = result->data + matrixIndex(result, j, i);
            float *pm1 = m1->data + matrixIndex(m1, j, 0);
            float *pm2 = m2->data + matrixIndex(m2, 0, i);
            vecdp(pr, pm1, pm2, m1->column_length);
        }
    }
}


#ifdef USE_AVX
#include <immintrin.h>
void vecdp(float *result, const float *m1, const float *m2, const size_t len)
{
    size_t i = 0;
    __m256 sum8 = _mm256_setzero_ps();

#pragma omp parallel for
    for (; i <= len - 8; i += 8)
    {
        __m256 a = _mm256_load_ps(&m1[i]);
        __m256 b = _mm256_load_ps(&m2[i]);
        __m256 part_sum = _mm256_dp_ps(a, b, ALL_HIGH);
        sum8 = _mm256_add_ps(sum8, part_sum);
    }

    float *sum = aligned_alloc(ALIGN, 8 * sizeof(float));
    _mm256_store_ps(sum, sum8);
    *result = sum[0];
    free(sum);

#pragma omp parallel for
    for (; i < len; i++)
    {
        result[i] = m1[i] * m2[i];
    }
}
#else
#error "Architecture not supported!"
#endif