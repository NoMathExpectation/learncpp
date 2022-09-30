#include "fac.hpp"
size_t fac(unsigned int n) {
    if (n <= 1) {
        return 1;
    }
    return n * fac(n - 1);
}