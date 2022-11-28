#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef TEST_OPENBLAS
#include <cblas.h>
#endif

void testMulTime(int size)
{
    matrix m1, m2;
    createMatrix(&m1, size, size, false);
    createMatrix(&m2, size, size, true);

    printf("Testing matrix size %d x %d multiplication.\n", size);

    matrix m3, m4, m5;
#ifdef TEST_OPENBLAS
    createMatrix(&m5, size, size, false);
#endif
    clock_t startp, endp, starti, endi, startblas, endblas;

#ifdef TEST_PLAIN
    startp = clock();
    matmul_plain(&m3, &m1, &m2);
    endp = clock();
#endif
#ifdef TEST_IMPROVED
    starti = clock();
    matmul_improved(&m4, &m1, &m2);
    endi = clock();
#endif
#ifdef TEST_OPENBLAS
    startblas = clock();
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, size, size, size, 1, m1.data, size, m2.data, size, 0, m5.data, size);
    endblas = clock();
#endif

    deleteMatrix(&m1);
    deleteMatrix(&m2);
#ifdef TEST_PLAIN
    deleteMatrix(&m3);
#endif
#ifdef TEST_IMPROVED
    deleteMatrix(&m4);
#endif
#ifdef TEST_OPENBLAS
    deleteMatrix(&m5);
#endif

#ifdef TEST_PLAIN
    printf("Plain: %f millsecs.\n", (double)(endp - startp) * 1000 / CLOCKS_PER_SEC);
#endif
#ifdef TEST_IMPROVED
    printf("Improved: %f millsecs.\n", (double)(endi - starti) * 1000 / CLOCKS_PER_SEC);
#endif
#ifdef TEST_OPENBLAS
    printf("OpenBLAS: %f millsecs.\n", (double)(endblas - startblas) * 1000 / CLOCKS_PER_SEC);
#endif
    printf("\n");
}

void main()
{
    srand(time(NULL));
    testMulTime(16);
    testMulTime(128);
    testMulTime(1000);
    testMulTime(8000);
#ifdef TEST_LARGE
    testMulTime(64000);
#endif
}