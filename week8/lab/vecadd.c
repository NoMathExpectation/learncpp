#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#ifdef WITH_AVX2
#include <immintrin.h>
void add(float *a, float *b, size_t n, float *result)
{
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (size_t i = 0; i < n; i += 16)
    {
        __m512 a512 = _mm512_load_ps(&a[i]);
        __m512 b512 = _mm512_load_ps(&b[i]);
        __m512 result512 = _mm512_add_ps(a512, b512);
        _mm512_store_ps(&result[i], result512);
    }
}
#endif

#ifdef WITH_NEON
#include <arm_neon.h>
void add(float *a, float *b, size_t n, float *result)
{
#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (size_t i = 0; i < n; i += 8)
    {
        float32x4_t a128 = vld1q_f32(&a[i]);
        float32x4_t b128 = vld1q_f32(&b[i]);
        float32x4_t result128 = vaddq_f32(a128, b128);
        _mm512_store_epi64(&result[i], result128);
    }
}
#endif

void main()
{
    const size_t length = 1024 * 1024 * 8;
    const size_t align = 64;
    float *vec1 = (float *)aligned_alloc(align, length * sizeof(float));
    float *vec2 = (float *)aligned_alloc(align, length * sizeof(float));
    for (size_t i = 0; i < length; i++)
    {
        vec1[i] = (float)i;
        vec2[i] = (float)i;
    }

    float *vec_result = (float *)aligned_alloc(align, length * sizeof(float));

    clock_t start = clock();
    add(vec1, vec2, length, vec_result);
    clock_t end = clock();

    for (size_t i = 0; i < 8; i++)
    {
        printf("%f ", vec_result[i]);
    }
    printf("...\nTime: %dms", (end - start) * 1000 / CLOCKS_PER_SEC);

    free(vec1);
    free(vec2);
    free(vec_result);
}