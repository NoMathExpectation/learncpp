#include <iostream>

class OutOfRangeException
{
public:
    const int min, max, actual;

    OutOfRangeException(int min, int max, int actual) : min(min), max(max), actual(actual) {}

    friend std::ostream &operator<<(std::ostream &os, const OutOfRangeException &e)
    {
        os << "Out of range: " << e.min << " <= " << e.actual << " <= " << e.max;
        return os;
    }
};

float calculateAverage(float *p, size_t len)
{
    float sum = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (p[i] < 0 || p[i] > 100)
        {
            throw OutOfRangeException(0, 100, p[i]);
        }

        sum += p[i];
    }
    return sum / len;
}

int main() {
    float scores[4];
    std::cout << "Please input 4 scores: ";
    for (size_t i = 0; i < 4; i++)
    {
        std::cin >> scores[i];
    }

    try {
        std::cout<< "Average: " << calculateAverage(scores, 4) << std::endl;
    } catch (const OutOfRangeException &e) {
        std::cerr << e << std::endl;
    }
    
    return 0;
}