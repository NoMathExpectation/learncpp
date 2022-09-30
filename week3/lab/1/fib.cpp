#include "fib.hpp"
size_t fib(unsigned int n) {
    if (n <= 2) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}