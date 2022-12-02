#include "CStereoShape.cpp"
#ifndef _SPHERE_
#define _SPHERE_
#define PI 3.14159265358979323846
class CSphere : public CStereoShape
{
private:
    double radius;

public:
    CSphere(double radius) : radius(radius) {}

    CSphere(const CSphere &another) : CSphere(another.radius) {}

    CSphere(const CSphere &&another) : CSphere(another) {}

    CSphere() : CSphere(1) {}

    double getArea() const noexcept
    {
        return 4 * PI * radius * radius;
    }

    double getVolume() const noexcept
    {
        return 4 * PI * radius * radius * radius / 3;
    }

    void show() const noexcept
    {
        std::cout << "This is a sphere with radius " << radius << ", area " << getArea() << ", volume " << getVolume() << "." << std::endl;
    }
};
#endif