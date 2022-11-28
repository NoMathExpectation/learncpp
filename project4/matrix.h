#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stddef.h>
#include <stdbool.h>

#define ALIGN 32
#define COUNT_PER_PACK 8
#define ALL_HIGH 0xFF

typedef struct
{
    size_t row_length;
    size_t column_length;
    bool column_stored;

    float *data;
} matrix;

// initialize a matrix with given row and cloumn size
void createMatrix(matrix *m, const size_t row, const size_t col, bool column_stored);

// generate a random matrix
void randMatrix(matrix *m, const size_t row, const size_t col, bool column_stored);

// get index of matrix
size_t matrixIndex(const matrix *m, const size_t row, const size_t col);

// delete a matrix
void deleteMatrix(matrix *m);

// print a matrix
void printMatrix(const matrix *m);

// internal multiply
void vecdp(float *result, const float *m1, const float *m2, const size_t len);

// multiply matrix m1 with m2 and store the result
int matmul_plain(matrix *result, const matrix *m1, const matrix *m2);

// improved version of multiplication
int matmul_improved(matrix *result, const matrix *m1, const matrix *m2);
#endif