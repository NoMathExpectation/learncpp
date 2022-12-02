#include "CStereoShape.cpp"
#ifndef _CUBE_
#define _CUBE_
class CCube : public CStereoShape
{
private:
    double length;
    double width;
    double height;

public:
    CCube(double length, double width, double height) : length(length), width(width), height(height)
    {
    }

    CCube(const CCube &another) : CCube(another.length, another.width, another.height)
    {
    }

    CCube(const CCube &&another) : CCube(another)
    {
    }

    CCube() : CCube(1, 1, 1) {}

    double getArea() const noexcept
    {
        return 2 * (length * width + length * height + width * height);
    }

    double getVolume() const noexcept
    {
        return length * width * height;
    }

    void show() const noexcept
    {
        std::cout << "This is a cube with length " << length << ", width " << width << ", height " << height << ", area " << getArea() << ", volume " << getVolume() << "." << std::endl;
    }
};
#endif