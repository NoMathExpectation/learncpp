#ifndef __MATRIX_H__
#define __MATRIX_H__

typedef struct
{
    int row_length;
    int column_length;

    float **data;
} matrix;

// initialize a matrix with given row and cloumn size
void createMatrix(matrix *m, int row, int col);

// delete a matrix
void deleteMatrix(matrix *m);

// print a matrix
void printMatrix(const matrix *m);

// get the corresponding element of the matrix
float getMatrixElement(const matrix *m, int row, int col);

// set the corresponding element of the matrix to value
void setMatrixElement(matrix *m, int row, int col, float value);

// copy a matrix from source to destination
void copyMatrix(matrix *dest, const matrix *src);

// copy a matrix from a 2d array
void copyMatrixArray(matrix *dest, const float *src, int row, int col);

// create a identity matrix
void identityMatrix(matrix *dest, int size);

// add two matrix and store the result
int addMatrix(matrix *result, const matrix *m1, const matrix *m2);

// add matrix with a scalar and store the result
void addMatrixScalar(matrix *result, const matrix *m, float scalar);

// subtract matrix m2 from m1 and store the result
int subtractMatrix(matrix *result, const matrix *m1, const matrix *m2);

// subtract matrix with a scalar and store the result
void subtractMatrixScalar(matrix *result, const matrix *m, float scalar);

// multiply matrix m1 with m2 and store the result
int multiplyMatrix(matrix *result, const matrix *m1, const matrix *m2);

// multiply matrix with a scalar and store the result
void multiplyMatrixScalar(matrix *result, const matrix *m, float scalar);

// divide matrix with a scalar and store the result
void divideMatrixScalar(matrix *result, const matrix *m, float scalar);

// find the minimum value of the matrix
float minMatrix(const matrix *m);

// find the maximum value of the matrix
float maxMatrix(const matrix *m);

// put the specified row in matrix m to dest
int rowMatrix(matrix *dest, const matrix *m, int row);

// put the specified column in matrix m to dest
int columnMatrix(matrix *dest, const matrix *m, int col);

// delete the specified row in matrix m and store to dest
int deleteRowMatrix(matrix *dest, const matrix *m, int row);

// delete the specified column in matrix m and store to dest
int deleteColumnMatrix(matrix *dest, const matrix *m, int col);

// delete the specified row and column in matrix m and store to dest
int deleteRowColumnMatrix(matrix *dest, const matrix *m, int row, int col);

// find the determinant of the matrix
float determinantMatrix(const matrix *m);

// transpose given matrix and store the result
void transposeMatrix(matrix *result, const matrix *m);

// invert given matrix and store the result
int invertMatrix(matrix *result, const matrix *m);
#endif