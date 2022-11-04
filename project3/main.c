#include <stdio.h>
#include "matrix.h"

void main()
{
    matrix m1, m2, m3;
    float a[6] = {1, 2, 3, 4, 5, 6};

    copyMatrixArray(&m1, a, 2, 3);
    copyMatrixArray(&m2, a, 3, 2);

    multiplyMatrix(&m3, &m1, &m2);

    printMatrix(&m3);

    deleteMatrix(&m1);
    deleteMatrix(&m2);
    deleteMatrix(&m3);

    matrix m4;
    float b[] = {1, 2, 0, 0, 3, 4, 5, 0, 0, 6, 7, 8, 0, 0, 9, 10};
    copyMatrixArray(&m4, b, 4, 4);

    printf("%f\n", determinantMatrix(&m4));

    matrix m4inv;
    invertMatrix(&m4inv, &m4);
    printMatrix(&m4inv);

    deleteMatrix(&m4);
    deleteMatrix(&m4inv);

    matrix m5;
    identityMatrix(&m5, 4);
    printMatrix(&m5);

    deleteMatrix(&m5);
}