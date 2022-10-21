#include "libswap.hpp"

void swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap(long &a, long &b) {
    int temp = a;
    a = b;
    b = temp;
}