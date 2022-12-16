#include <iostream>
#include <cassert>

float calculateAverage(float *p, size_t len)
{
    float sum = 0;
    for (size_t i = 0; i < len; i++)
    {
        assert(p[i] >= 0 && p[i] <= 100);
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

    std::cout<< "Average: " << calculateAverage(scores, 4) << std::endl;
    
    return 0;
}