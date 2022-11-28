CC = gcc
enable = -DTEST_PLAIN -DTEST_IMPROVED -DTEST_OPENBLAS -DTEST_LARGE

test: matrix.c test.c
	$(CC) -o test matrix.c test.c $(enable) -DUSE_AVX -mavx -lopenblas